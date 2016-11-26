// Local Headers
#include "keyboard-handler.hpp"

namespace OZ {
  bool KeyboardHandler::keys[1024] = { 0 };

  void KeyboardHandler::init(GLFWwindow* window) {
    glfwSetKeyCallback(window, KeyboardHandler::handle);
  }

  void KeyboardHandler::handle(GLFWwindow* window, int key, int scancode, int action, int mode) {
      if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
      if(action == GLFW_PRESS)
        KeyboardHandler::keys[key] = true;
      else if(action == GLFW_RELEASE)
        KeyboardHandler::keys[key] = false;

      eventEmitter.emit(1, key, action);
  }
};

