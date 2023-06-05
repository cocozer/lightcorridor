#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


Texture Texture::loadTexture(const char* fileName) {
    Texture texture;
    texture.textureData= stbi_load(fileName, &texture.textureWidth, &texture.textureHeight, &texture.textureChannels, 0);
    if (texture.textureData == NULL) {
        printf("La texture n'a pas pu être chargée.\n");
    }

    glGenTextures(1, &texture.textureID);
    glBindTexture(GL_TEXTURE_2D, texture.textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture.textureWidth, texture.textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE,
    texture.textureData);
    glBindTexture(GL_TEXTURE_2D, 0);

    stbi_image_free(texture.textureData);
    return texture;
}