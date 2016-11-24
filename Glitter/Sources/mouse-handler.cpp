// Local Headers
#include "mouse-handler.hpp"

namespace OZ {
  double MouseHandler::mouseX = 720.0f;
  double MouseHandler::mouseY = 450.0f;
  double MouseHandler::lastMouseX = 720.0f;
  double MouseHandler::lastMouseY = 450.0f;

  void MouseHandler::init(GLFWwindow* window) {
    glfwSetCursorPosCallback(window, MouseHandler::handle);
  }

  void MouseHandler::handle(GLFWwindow* window, double xpos, double ypos) {
      MouseHandler::lastMouseX = MouseHandler::mouseX;
      MouseHandler::lastMouseY = MouseHandler::mouseY;
      MouseHandler::mouseX = xpos;
      MouseHandler::mouseY = ypos;
      double xdiff = MouseHandler::mouseX - MouseHandler::lastMouseX;
      double ydiff = MouseHandler::mouseY - MouseHandler::lastMouseY;

      std::cout << "MOUSEX: "<< xpos << " MOUSEY: " << ypos << std::endl;
      eventEmitter.emit(0, xdiff, ydiff);
  }
};
