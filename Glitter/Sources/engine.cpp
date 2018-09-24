#include "engine.hpp"

namespace OZ
{
EventEmitter eventEmitter;

Engine &Engine::loadConfig(std::string configFile)
{
  std::ifstream fileStream(configFile);
  auto src = std::string(std::istreambuf_iterator<char>(fileStream), (std::istreambuf_iterator<char>()));
  this->config = Json::parse(src);
  std::cout << "LOADED CONFIG ==>> " << this->config.dump(2) << std::endl;

  return *this;
}

Engine &Engine::init()
{
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
  this->lastFrameTime = 0.0f;
  this->FPS = 0;
  return *this;
}

Engine &Engine::createWindow()
{
  GLfloat width, height;
  GLFWmonitor *monitor;
  if (this->config["window"]["fullscreen"])
  {
    const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    width = mode->width;
    height = mode->height;
    monitor = glfwGetPrimaryMonitor();
  }
  else
  {
    width = config["window"]["width"];
    height = config["window"]["height"];
    monitor = nullptr;
  }

  std::string title = this->config["window"]["title"].get<std::string>();
  auto w = glfwCreateWindow(width, height, title.c_str(), monitor, nullptr);
  if (w == nullptr)
  {
    fprintf(stderr, "Failed to Create OpenGL Context");
    throw "Failed to Create OpenGL Context";
  }

  this->window = w;
  glfwMakeContextCurrent(this->window);
  gladLoadGL();

  fprintf(stderr, "OpenGL %s\n", glGetString(GL_VERSION));

  return *this;
}

Engine &Engine::loadAssets()
{
  int i = 0;
  for (std::string modelPath : this->config["assets"]["models"])
  {
    modelPath = PROJECT_SOURCE_DIR + modelPath;
    this->models.push_back(new Mesh(modelPath));
    i++;
  }
  return *this;
}

Engine &Engine::attachAndLinkShaders()
{
  int i = 0;
  this->shader.init();
  for (std::string shaderPath : this->config["shaders"])
  {
    shaderPath = PROJECT_SOURCE_DIR + shaderPath;
    this->shader.attach(shaderPath);
    i++;
  }
  shader.link();
  return *this;
}

Engine &Engine::registerInputListeners()
{
  MouseHandler::init(this->window);
  KeyboardHandler::init(this->window);

  return *this;
}

Engine &Engine::setupViewport()
{
  this->viewport = new Viewport(
      GLfloat(this->config["viewport"]["near"]),
      GLfloat(this->config["viewport"]["far"]),
      GLfloat(this->config["viewport"]["fov"]));
  this->viewport->init(this->window);
  return *this;
}

Engine &Engine::setupCamera()
{
  this->camera.init(CAMERA_TYPE_FPS);
  glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  return *this;
}

GLfloat Engine::getDt()
{
  GLfloat currentFrame, dt;
  currentFrame = glfwGetTime();
  dt = currentFrame - this->lastFrameTime;
  this->lastFrameTime = currentFrame;
  return dt;
}

Engine &Engine::runWorld()
{
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glEnable(GL_DEPTH_TEST);
  while (glfwWindowShouldClose(this->window) == false)
  {
    this->runFrame();
  }
  glfwTerminate();

  return *this;
}

Engine &Engine::runFrame()
{
  glfwPollEvents();
  GLfloat dt = this->getDt();
  this->FPS = int(1.0f / dt);
  glm::mat4 view, projection;

  glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  shader.activate();

  projection = this->viewport->getProjectionMatrix();
  view = this->camera
             .calculateLinearDisplacement(dt)
             .calculateAngularDisplacement()
             .getViewMatrix();

  unsigned int i = 0;
  for (Mesh *m : this->models)
  {
    glm::mat4 model;
    model = glm::translate(model, glm::vec3((10.0f * i), -1.75f, 0.0f)); // Translate it down a bit so it's at the center of the scene
    model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));              // It's a bit too big for our scene, so scale it down
    shader
        .bind("model", model)
        .bind("view", view)
        .bind("projection", projection);

    m->draw(shader.get());
    i++;
  }

  glfwSwapBuffers(this->window);
  return *this;
}

Engine &Engine::updateGameLogic()
{
  return *this;
}

Engine &Engine::finish()
{
  return *this;
}

Engine &Engine::pause()
{
  return *this;
}

} // namespace OZ
