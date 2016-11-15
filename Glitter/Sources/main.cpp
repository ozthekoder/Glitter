// Local Headers
#include "glitter.hpp"
#include "shader.hpp"

// System Headers
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <fstream>

// Standard Headers
#include <cstdio>
#include <cstdlib>
#include <iostream>

using namespace OZ;
int main(int argc, char * argv[]) {

  // Load GLFW and Create a Window
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
  auto mWindow = glfwCreateWindow(mWidth, mHeight, "OpenGL", nullptr, nullptr);

  // Check for Valid Context
  if (mWindow == nullptr) {
    fprintf(stderr, "Failed to Create OpenGL Context");
    return EXIT_FAILURE;
  }
  // Create Context and Load OpenGL Functions
  glfwMakeContextCurrent(mWindow);
  gladLoadGL();
  fprintf(stderr, "OpenGL %s\n", glGetString(GL_VERSION));

  //Creates a triangle in the center of the viewport
  GLfloat vertices[] = {
    // Positions         // Colors
    0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // Bottom Right
    -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // Bottom Left
    0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,    // Top
  };

  GLuint indices[] = {  // Note that we start from 0!
    0, 1, 2    // Second Triangle
  };

  //First create a VAO so that all created VBO and EBO stuff is tracked.
  GLuint VAO;
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  //Creating a VBO
  GLuint VBO;
  glGenBuffers(1, &VBO);

  //Creating a EBO.
  GLuint EBO;
  glGenBuffers(1, &EBO);

  //Binds the vertex buffer to GL_ARRAY_BUFFER and indices to GL_ELEMENT_BUFFER to be sent to the shaders
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

  //Send the vertex data to VBO and index data to EBO.
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  Shader shader;
  shader
  .attach("vertex.vert")
  .attach("fragment.frag")
  .link();
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
  glEnableVertexAttribArray(1);

  //Clear the current VAO context.
  glBindVertexArray(0);

  //Create the viewport
  int width, height;
  glfwGetFramebufferSize(mWindow, &width, &height);
  glViewport(0, 0, width, height);
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  // Rendering Loop
  while (glfwWindowShouldClose(mWindow) == false) {
    if (glfwGetKey(mWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
      glfwSetWindowShouldClose(mWindow, true);

    // Background Fill Color
    glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Update the uniform color
    GLfloat timeValue = glfwGetTime();
    GLfloat greenValue = (sin(timeValue) / 2) + 0.5;
    glm::vec4 color(0.0f, greenValue, 0.0f, 1.0f);

    shader
    .activate();

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    // Flip Buffers and Draw
    glfwSwapBuffers(mWindow);
    glfwPollEvents();
  }

  glfwTerminate();
  return EXIT_SUCCESS;
}
