// Local Headers
#include "texture.hpp"

namespace OZ {
  void Texture::use(Shader* shader, std::string shaderUniformName) {
    glActiveTexture(this->textureSlot);
    glBindTexture(GL_TEXTURE_2D, this->textureId);
    shader->bind(shaderUniformName, this->textureIndex);
  }
};
