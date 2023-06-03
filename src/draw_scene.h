#pragma once

#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "Texture.h"


void drawDecorX();
void drawDecorZ();
void drawDecor();
void drawMenuStart(Texture& texturefond, Texture& textureplay, Texture& texturequit);
void drawMenuPause(Texture& texturefond, Texture& texturecontinue, Texture& texturequit);
void drawMenuLose(Texture& texturefond, Texture& texturestart, Texture& texturequit);
void drawMenuWin(Texture& texturefond, Texture& texturestart, Texture& texturequit);