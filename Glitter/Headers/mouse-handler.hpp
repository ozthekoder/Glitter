#pragma once

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <functional>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "globals.h"

namespace OZ {
  class MouseHandler {
    public:
      static double mouseX, mouseY, lastMouseX, lastMouseY;
      static void init(GLFWwindow* window);
      static void handle(GLFWwindow* window, double xpos, double ypos);
  };
};
