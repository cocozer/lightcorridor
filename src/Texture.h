#pragma once
#define GLFW_INCLUDE_NONE
// #include "GLFW/glfw3.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <string>

// #define STB_IMAGE_IMPLEMENTATION
// #include "stb_image.h"

struct Texture {
    unsigned int textureID;
    int textureWidth;
    int textureHeight;
    int textureChannels;
    unsigned char* textureData;

    // Texture(std::string fileName);
    void loadTexture();

};