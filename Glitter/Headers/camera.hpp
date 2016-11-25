#pragma once

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "globals.h"
#define CAMERA_TYPE_FPS 0
#define CAMERA_TYPE_TPS 1
#define CAMERA_TYPE_STRATEGY 2
#define CAMERA_TYPE_SIDE_SCROLLER 3
#define MOVE_FORWARD 0
#define MOVE_LEFT 1
#define MOVE_BACK 2
#define MOVE_RIGHT 3



namespace OZ {
  class Camera {
    public:
      GLuint type;
      bool moveDirections[4];
      GLfloat pitch, yaw, velocity, sensitivity;
      glm::vec3 position, direction, up;
      Camera() {};
      ~Camera() {};
      Camera& init(GLuint type);
      Camera& initFPS();
      Camera& setType(GLuint t);
      Camera& setVelocity(GLfloat v);
      Camera& setSensitivity(GLfloat s);
      Camera& setPosition(GLfloat x, GLfloat y, GLfloat z);
      Camera& setPosition(glm::vec3 posVec);
      Camera& setDirection(GLfloat x, GLfloat y, GLfloat z);
      Camera& setDirection(glm::vec3 directionVec);
      Camera& setUp(GLfloat x, GLfloat y, GLfloat z);
      Camera& setUp(glm::vec3 upVec);
      Camera& calculateLinearDisplacement(GLfloat dt);
      Camera& calculateAngularDisplacement(GLFWwindow* window, GLfloat dt);
      glm::mat4 getViewMatrix();
  };
};
