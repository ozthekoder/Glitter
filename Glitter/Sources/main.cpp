// Local Headers
#include "engine.hpp"

using namespace OZ;

int main(int argc, char * argv[]) {

  std::string configPath = PROJECT_SOURCE_DIR "/Glitter/Config/config.json";
  Engine engine;
  std::cout << "BBBBBB" << std::endl;

  try {
    engine
      .loadConfig(configPath)
      .init()
      .createWindow()
      .loadAssets()
      .attachAndLinkShaders()
      .setupViewport()
      .setupCamera()
      .runWorld();
      std::cout << "AAAAAAA" << std::endl;

  } catch (const char* msg) {
    std::cerr << msg << std::endl;
    return EXIT_FAILURE;
  }
  std::cout << "DDDDDDDD" << std::endl;

  // Check for Valid Context
  std::cout << "xxxxxxxxxxx" << std::endl;

  return EXIT_SUCCESS;
}
