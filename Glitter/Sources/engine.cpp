#include "engine.hpp"

namespace OZ {
  EventEmitter eventEmitter;
  Engine& Engine::loadConfig(std::string configFile) {
    std::ifstream fileStream(configFile);
    auto src = std::string(std::istreambuf_iterator<char>(fileStream), (std::istreambuf_iterator<char>()));
    this->config = Json::parse(src);
    std::cout << "LOADED CONFIG ==>> " << this->config.dump(2) << std::endl;

    return *this;
  }

  Engine& Engine::init() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
  }

  Engine& Engine::createWindow() {
    GLfloat width, height;
    auto monitor;
    if(this->config["window"]["fullscreen"]) {
      const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
      width = mode->width;
      height = mode->height;
      monitor = glfwGetPrimaryMonitor();
    } else {
      width = config["window"]["width"];
      height = config["window"]["height"];
      monitor = nullptr;
    }

    auto w = glfwCreateWindow(width, height, this->config["window"]["title"], monitor, nullptr);
    if (window == nullptr) {
      fprintf(stderr, "Failed to Create OpenGL Context");
      return EXIT_FAILURE;
    }

    this->window = w;
    glfwMakeContextCurrent(this->window);
    gladLoadGL();

    fprintf(stderr, "OpenGL %s\n", glGetString(GL_VERSION));

  }

  Engine& Engine::loadAssets() {

  }

  Engine& Engine::registerInputListeners() {

  }

  Engine& Engine::start() {

  }

  Engine& runFrame() {

  }

  Engine& updateGameLogic() {

  }

  Engine& Engine::finish() {

  }

  Engine& Engine::pause() {

  }

}
