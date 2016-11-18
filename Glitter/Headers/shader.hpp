#pragma once

// System Headers
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

// Standard Headers
#include <string>

// Define Namespace
namespace OZ {
  class Shader {
    public:

      GLuint foo;
      // Implement Custom Constructor and Destructor
      Shader() { mProgram = glCreateProgram(); }
      ~Shader() { glDeleteProgram(mProgram); }

      // Public Member Functions
      Shader& activate();
      Shader& attach(std::string const& filename);
      GLuint   create(std::string const& filename);
      GLuint   get() { return mProgram; }
      Shader& link();

      // Wrap Calls to glUniform
      void bind(GLuint location, GLuint value);
      void bind(GLuint location, GLfloat value);
      void bind(GLuint location, glm::mat4 const& matrix);
      void bind(GLuint location, glm::vec4 const& vector);

      template<typename T> Shader& bind(std::string const& name, T&& value) {
        int location = glGetUniformLocation(mProgram, name.c_str());
        if (location == -1) fprintf(stderr, "Missing Uniform: %s\n", name.c_str());
        else bind(location, std::forward<T>(value));
        return *this;
      }

    private:

      // Disable Copying and Assignment
      //Shader(Shader const&) = delete;
      //Shader& operator=(Shader const&) = delete;

      // Private Member Variables
      GLuint mProgram;
      GLint  mStatus;
      GLint  mLength;

  };
};
