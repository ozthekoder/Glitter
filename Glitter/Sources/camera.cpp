#include "camera.hpp"

namespace OZ {
  Camera& Camera::init(GLuint type) {
    this->setType(type);
    switch(this->type) {
      case CAMERA_TYPE_FPS:
        this->initFPS();
        break;
      case CAMERA_TYPE_TPS:
        break;
      case CAMERA_TYPE_STRATEGY:
        break;
      case CAMERA_TYPE_SIDE_SCROLLER:
        break;
    }
  }

  Camera& initFPS() {
    this->position = glm::vec3(0.0f, 0.0f,  3.0f);
    this->direction = glm::vec3(0.0f, 0.0f, -1.0f);
    this->up = glm::vec3(0.0f, 1.0f,  0.0f);
    this->pitch = 0.0f;
    this->yaw = 270.0f;
    this->velocity = 5.0f;
    this->sensitivity = 0.05f;
    std::function<void (GLFWwindow*, int, int ,int ,int)> cb = [&this](GLFWwindow* window, int key, int scancode, int action, int mode) {
      std::cout << "FUKU "<< pitch << "BAR" << yaw << << std::endl;
    }
    eventEmitter.on<int, int>(1, cb);
    return *this;
  }
  Camera& Camera::setType(GLuint t) {
    this->type = t;
  }

  Camera& Camera::setVelocity(GLfloat v) {
    this->velocity = v;
  }

  Camera& Camera::setSensitivity(GLfloat s) {
    this->sensitivity = s;
  }

  Camera& Camera::setPosition(GLfloat x, GLfloat y, GLfloat z) {
    this->position = glm::vec3(x, y ,z);
  }

  Camera& Camera::setPosition(glm::vec3 posVec) {
    this->position = posVec;
  }

  Camera& Camera::setDirection(GLfloat x, GLfloat y, GLfloat z) {
    this->direction = glm::vec3(x, y ,z);
  }

  Camera& Camera::setDirection(glm::vec3 directionVec) {
    this->direction = directionVec;
  }

  Camera& Camera::setUp(GLfloat x, GLfloat y, GLfloat z) {
    this->up = glm::vec3(x, y ,z);
  }

  Camera& Camera::setUp(glm::vec3 upVec) {
    this->up = upVec;
  }

  Camera& calculateLinearDisplacement(GLfloat dt) {
    this->position += (this->velocity * dt) * this->direction;
  }

  Camera& calculateAngularDisplacement(GLFWwindow* window, GLfloat dt) {
    int w, h, xpos, ypos;

    glfwGetWindowSize(window, &w, &h);
    glfwGetCursorPos(window, &xpos, &ypos);

    this->yaw += this->sensitivity * dt * float(w/2 - xpos);
    this->pitch += this->sensitivity * dt * float(h/2 - ypos);

    if(this->pitch > 89.9f)
      this->pitch = 89.9f;
    if(this->pitch < -89.9f)
      this->pitch = -89.9f;

    glm::vec3 front;
    front.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
    front.y = sin(glm::radians(this->pitch));
    front.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
    this->direction = glm::normalize(front);
  }

  glm::mat4&& Camera::getViewMatrix() {
    return glm::lookAt(this->position, (this->position + this->direction), this->up);
  }
}
