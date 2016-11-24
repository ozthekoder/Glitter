#pragma once

#include <cstdio>
#include <cstdlib>
#include "keyboard-handler.hpp"
#include "mouse-handler.hpp"
#include "event-emitter.hpp"
#include <iostream>

namespace OZ {
  class InputManager {
    public:
      InputManager(GLFWwindow* window) {
        MouseHandler::init(window);
        KeyboardHandler::init(window);
      };
      ~InputManager() {};
  };
};
