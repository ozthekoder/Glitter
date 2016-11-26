#include "engine.hpp"

namespace OZ {
  EventEmitter eventEmitter;

  Engine& Engine::loadConfig(std::string configFile) {
    std::ifstream fileStream(configFile);
    auto src = std::string(std::istreambuf_iterator<char>(fileStream), (std::istreambuf_iterator<char>()));
    this->config = nlohmann::json::parse(src);
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
    this->lastFrameTime = 0.0;
    return *this;
  }

  Engine& Engine::createWindow() {
    GLfloat width, height;
    GLFWmonitor* monitor;
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

    std::string title = this->config["window"]["title"].get<std::string>();
    auto w = glfwCreateWindow(width, height, title.c_str(), monitor, nullptr);
    if (w == nullptr) {
      fprintf(stderr, "Failed to Create OpenGL Context");
      throw "Failed to Create OpenGL Context";
    }

    this->window = w;
    glfwMakeContextCurrent(this->window);
    gladLoadGL();

    fprintf(stderr, "OpenGL %s\n", glGetString(GL_VERSION));

    return *this;
  }

  Engine& Engine::loadAssets() {
    int i = 0;
    for (std::string modelPath : this->config["assets"]["models"]) {
      this->models.push_back(new Mesh(PROJECT_SOURCE_DIR + modelPath));
      i++;
    }
    return *this;
  }

  Engine& Engine::attachAndLinkShaders() {
    this->shader = new Shader();
    int i = 0;
    for (std::string shaderPath : this->config["shaders"]) {
      shaderPath = PROJECT_SOURCE_DIR + shaderPath;
      this->shader->attach(shaderPath);
      i++;
    }
    shader->link();
    return *this;
  }

  Engine& Engine::registerInputListeners() {
    return *this;
  }

  Engine& Engine::setupViewport() {
    this->viewport = new Viewport(
        GLfloat(this->config["viewport"]["near"]),
        GLfloat(this->config["viewport"]["far"]),
        GLfloat(this->config["viewport"]["fov"])
        );
    this->viewport->init(this->window);
    return *this;
  }

  Engine& Engine::setupCamera() {
    this->camera.init(CAMERA_TYPE_FPS);
    glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    return *this;
  }

  GLfloat Engine::getDt() {
    GLfloat currentFrame, dt;
    currentFrame = glfwGetTime();
    dt = currentFrame - this->lastFrameTime;
    this->lastFrameTime = currentFrame;
    return dt;
  }

  Engine& Engine::runWorld() {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_DEPTH_TEST);

    while (glfwWindowShouldClose(this->window) == false) {
      this->runFrame();
    }

    //glDeleteVertexArrays(1, &VAO);
    glfwTerminate();

    return *this;
  }

  Engine& Engine::runFrame() {
    glfwPollEvents();
    GLfloat dt = this->getDt();
    glm::mat4 model, view, projection;
    glm::vec3 cubePositions[] = {
      glm::vec3( 0.0f,  0.0f,  0.0f),
      glm::vec3( 2.0f,  5.0f, -15.0f),
      glm::vec3(-1.5f, -2.2f, -2.5f),
      glm::vec3(-3.8f, -2.0f, -12.3f),
      glm::vec3( 2.4f, -0.4f, -3.5f),
      glm::vec3(-1.7f,  3.0f, -7.5f),
      glm::vec3( 1.3f, -2.0f, -2.5f),
      glm::vec3( 1.5f,  2.0f, -2.5f),
      glm::vec3( 1.5f,  0.2f, -1.5f),
      glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    // Positions of the point lights
    glm::vec3 pointLightPositions[] = {
      glm::vec3(0.7f,  0.2f,  2.0f),
      glm::vec3(2.3f, -3.3f, -4.0f),
      glm::vec3(-4.0f,  2.0f, -12.0f),
      glm::vec3(0.0f,  0.0f, -3.0f)
    };

    glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    projection = this->viewport->getProjectionMatrix();
    for(GLuint i = 0; i < 10; i++)
    {
      glm::mat4 model;
      model = glm::translate(model, cubePositions[i]);
      GLfloat angle = 20.0f * i;

      model = glm::rotate(model, angle, glm::vec3(1.0f, 0.3f, 0.5f));
      view = this->camera
        .calculateLinearDisplacement(dt)
        .calculateAngularDisplacement(this->window , dt)
        .getViewMatrix();

      this->shader->activate();
      for(Mesh* m : this->models) {
        m->draw(this->shader->get());
      }

      shader
        ->bind("model", model)
        .bind("view", view)
        .bind("projection", projection);
    }

    glfwSwapBuffers(this->window);
    return *this;
  }

  Engine& Engine::updateGameLogic() {
    return *this;
  }

  Engine& Engine::finish() {
    return *this;
  }

  Engine& Engine::pause() {
    return *this;
  }

}
