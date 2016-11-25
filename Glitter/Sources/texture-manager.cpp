/*#include "texture-manager.hpp"*/

//namespace OZ {
  //Texture* TextureManager::generateTexture(std::string imagePath) {
    //auto index = imagePath.rfind(".");
    //auto ext = imagePath.substr(index + 1);
    //int desiredNumOfTextureComponents = STBI_rgb;

    //if(ext == "jpg" || ext == "jpeg") {
      //desiredNumOfTextureComponents = STBI_rgb;
    //} else if (ext == "png") {
      //desiredNumOfTextureComponents = STBI_rgb_alpha;
    //}

    //GLuint textureId, textureSlot, textureIndex;
    //int width, height, channels, format;
    //unsigned char* image = stbi_load(imagePath.c_str(), &width, &height, &channels, 0);

    //if (!image) {
      //fprintf(stderr, "%s %s\n", "Failed to Load Texture", imagePath.c_str());
    //}

    //switch (channels) {
      //case 1 : format = GL_ALPHA;     break;
      //case 2 : format = GL_LUMINANCE; break;
      //case 3 : format = GL_RGB;       break;
      //case 4 : format = GL_RGBA;      break;
    //}

    //textureIndex = this->useAvailableMemoryLocation();
    //textureSlot = this->slots[textureIndex];
    //glGenTextures(1, &textureId);
    //glActiveTexture(textureSlot);
    //glBindTexture(GL_TEXTURE_2D, textureId);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, image);
    //glGenerateMipmap(GL_TEXTURE_2D);
    //stbi_image_free(image);
    //glBindTexture(GL_TEXTURE_2D, 0);
    //Texture* texture = new Texture(textureId, textureSlot, textureIndex, width, height, format);
    //return texture;
  //}

  //void TextureManager::releaseMemoryLocation(int location) {
    //this->available[location] = true;
  //}

  //GLuint TextureManager::useAvailableMemoryLocation() {
    //for (int i=0; i<32; i++) {
      //if (this->available[i]) {
        //this->available[i] = false;
        //return i;
      //}
    //}

    //return 0;
  //}
/*}*/
