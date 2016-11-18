#pragma once

#include <cstdio>
#include <cstdlib>
#include "shader.hpp"
#include <iostream>

namespace OZ {
  class Texture {
    public:
      GLuint textureId;
      GLuint textureSlot;
      GLuint textureIndex;
      int width, height, channels;

      Texture() {};
      Texture(
          GLuint initTextureId,
          GLuint initTextureSlot,
          GLuint initTextureIndex,
          int initWidth,
          int initHeight,
          int initChannels
          ) {
        textureId = initTextureId;
        textureSlot = initTextureSlot;
        textureIndex = initTextureIndex;
        width = initWidth;
        height = initHeight;
        channels = initChannels;
      };
      ~Texture() {};

      void use(Shader* shader, std::string shaderUniformName);
  };
};
