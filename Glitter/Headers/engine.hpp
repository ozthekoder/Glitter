// Preprocessor Directives
#ifndef OZ_ENGINE
#define OZ_ENGINE
#pragma once

// System Headers
#include <btBulletDynamicsCommon.h>
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
#include "viewport.hpp"
#include "shader.hpp"
#include "camera.hpp"
#include "mesh.hpp"
using Json = nlohmann::json;

namespace OZ {
  class Engine {
    public:
      Json config;
      Json state;
      std::vector<Mesh*> models;
      GLfloat lastFrameTime;
      GLFWwindow* window;
      Camera camera;
      Shader shader;
      Viewport* viewport;
      Engine() {};
      ~Engine() {};
      Engine& loadConfig(std::string configFile);
      Engine& init();
      Engine& loadAssets();
      Engine& createWindow();
      Engine& registerInputListeners();
      Engine& setupViewport();
      Engine& setupCamera();
      Engine& attachAndLinkShaders();
      GLfloat getDt();
      Engine& runWorld();
      Engine& runFrame();
      Engine& updateGameLogic();
      Engine& finish();
      Engine& pause();
  };
};
#endif //~ Engine Header

