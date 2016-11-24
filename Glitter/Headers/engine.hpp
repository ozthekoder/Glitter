// System Headers
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include <iostream>
#include <memory>
#include <functional>

// Standard Headers
#include <cstdio>
#include <cstdlib>
#include "globals.h"

// Local Headers
#include "keyboard-handler.hpp"
#include "mouse-handler.hpp"
#include "event-emitter.hpp"
#include "json.hpp"
#include "shader.hpp"
#include "camera.hpp"

using Json = nlohmann::json;

namespace OZ {
  class Engine {
    public:
      Json config;
      Json state;
      GLfloat lastFrameTime;
      GLFWwindow* window;
      Camera camera;
      Engine() {};
      ~Engine() {};
      Engine& loadConfig(std::string configFile);
      Engine& init();
      Engine& loadAssets();
      Engine& createWindow();
      Engine& registerInputListeners();
      Engine& setupCamera();
      Engine& start();
      Engine& runFrame();
      Engine& updateGameLogic();
      Engine& finish();
      Engine& pause();
  };
};
