#include "viewport.hpp"

namespace OZ {
  void Viewport::init(GLFWwindow* window) {
    glfwGetFramebufferSize(window, &this->width, &this->height);
    glViewport(0, 0, this->width, this->height);
  }

  glm::mat4 Viewport::getProjectionMatrix() {
    glm::mat4 projection = glm::perspective(fov, (float)(this->width / this->height), this->near, this->far);
    return projection;
  }
}
