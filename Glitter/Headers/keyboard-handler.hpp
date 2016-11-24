#pragma once

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <functional>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "globals.h"


namespace OZ {
  class KeyboardHandler {
    public:
      static bool keys[1024];
      static void init(GLFWwindow* window);
      static void handle(GLFWwindow* window, int key, int scancode, int action, int mode);
  };
};
