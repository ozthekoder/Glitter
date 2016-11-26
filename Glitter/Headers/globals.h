#pragma once
#ifndef HEADER_GLOBALS
#define HEADER_GLOBALS

#define PATH_TO(x) PROJECT_SOURCE_DIR x
#include "event-emitter.hpp"

// any source file that includes this will be able to use "eventEmitter"

namespace OZ {
  extern EventEmitter eventEmitter;
}
#endif
