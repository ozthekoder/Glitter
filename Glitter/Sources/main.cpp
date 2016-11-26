// Local Headers
#include "engine.hpp"

using namespace OZ;

int main(int argc, char * argv[]) {

  std::string configPath = PROJECT_SOURCE_DIR "/Glitter/Config/config.json";
  Engine engine;

  try {
    engine
      .loadConfig(configPath)
      .init()
      .createWindow()
      .loadAssets()
      .attachAndLinkShaders()
      .registerInputListeners()
      .setupViewport()
      .setupCamera()
      .runWorld();

  } catch (const char* msg) {
    std::cerr << msg << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
