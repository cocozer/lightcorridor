#ifndef __GL_DRAWING_H
#define __GL_DRAWING_H

// Fonction utilitaire (Ne pas regarder)
void computePerspectiveMatrix(float* matrix,float fovyInDegrees, float aspectRatio,float znear, float zfar);
void computeLookAtMatrix(float *matrix, float *eyePosition3D, float *center3D, float *upVector3D);

// Fonction de dessin d'un repere. L'axe x est rouge, l'axe y vert et l'axe z bleu.
void glDrawRepere(float length);

#endif
