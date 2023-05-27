#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
// const std::string fileName
void Texture::loadTexture() {
    textureData= stbi_load("../doc/059C.jpg", &textureWidth, &textureHeight, &textureChannels, 0);
    if (textureData == NULL) {
        printf("La texture n'a pas pu être chargée.\n");
    }

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);
    glBindTexture(GL_TEXTURE_2D, 0);

    stbi_image_free(textureData);
}