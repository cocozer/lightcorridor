#pragma once
#define GLFW_INCLUDE_NONE
// #include "GLFW/glfw3.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <string>


struct Texture {
    unsigned int textureID;
    int textureWidth;
    int textureHeight;
    int textureChannels;
    unsigned char* textureData;

    static Texture loadTexture(const char* fileName);

};