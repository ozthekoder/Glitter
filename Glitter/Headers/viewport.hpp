#pragma once

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <functional>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "globals.h"

namespace OZ {
  class Viewport {
    public:
      GLfloat fov, nearZ, farZ;
      int width, height;
      Viewport() {}
      Viewport(GLfloat initNear, GLfloat initFar, GLfloat initFov) {
        nearZ = initNear;
        farZ = initFar;
        fov = initFov;
      }
      ~Viewport() {}
      void init(GLFWwindow* window);
      glm::mat4 getProjectionMatrix();
  };
};
