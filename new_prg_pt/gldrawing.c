#include <OpenGL/gl.h>

#include <stdio.h>
#include <string.h>
#include <math.h>

#include "gldrawing.h"
#include "visu.h"


void fillMatrixFrustum(float *matrix, float left, float right, float bottom, float top,
						float znear, float zfar)
{
	float temp=0;
	float temp2, temp3, temp4;
	temp = 2.0 * znear;
	temp2 = right - left;
	temp3 = top - bottom;
	temp4 = zfar - znear;
	matrix[0] = temp / temp2;
	matrix[1] = 0.0;
	matrix[2] = 0.0;
	matrix[3] = 0.0;
	matrix[4] = 0.0;
	matrix[5] = temp / temp3;
	matrix[6] = 0.0;
	matrix[7] = 0.0;
	matrix[8] = (right + left) / temp2;
	matrix[9] = (top + bottom) / temp3;
	matrix[10] = (-zfar - znear) / temp4;
	matrix[11] = -1.0;
	matrix[12] = 0.0;
	matrix[13] = 0.0;
	matrix[14] = (-temp * zfar) / temp4;
	matrix[15] = 0.0;
}

float normalize(float* a_vec) {
	float nrm = sqrt(a_vec[0]*a_vec[0]+a_vec[1]*a_vec[1]+a_vec[2]*a_vec[2]);
	if (nrm<0.0001) return 0.0;
	a_vec[0]/=nrm;a_vec[1]/=nrm;a_vec[2]/=nrm;
	return nrm;
}

void vectProduct(float* a,float* b,float* result) {
	result[0] = a[1]*b[2]-a[2]*b[1];
	result[1] = a[2]*b[0]-a[0]*b[2];
	result[2] = a[0]*b[1]-a[1]*b[0];
}
float dotProduct(float*a,float*b) {return (a[0]*b[0]+a[1]*b[1]+a[2]*b[2]);}

void computeLookAtMatrix( float *matrix, float *eyePosition3D,
							float *center3D, float *upVector3D )
{
	float forward[3], side[3], up[3];
	float matrix2[16];
	// --------------------
	forward[0] = center3D[0] - eyePosition3D[0];
	forward[1] = center3D[1] - eyePosition3D[1];
	forward[2] = center3D[2] - eyePosition3D[2];
	normalize(forward);
	// --------------------
	// Side = forward x up
	vectProduct(forward, upVector3D, side);
	normalize(side);
	// --------------------
	// Recompute up as: up = side x forward
	vectProduct(side, forward, up);
	// --------------------
	matrix2[0] = side[0];
	matrix2[4] = side[1];
	matrix2[8] = side[2];
	//matrix2[12] = 0.0;
	matrix2[12] = -dotProduct(side,eyePosition3D);
	// --------------------
	matrix2[1] = up[0];
	matrix2[5] = up[1];
	matrix2[9] = up[2];
	//matrix2[13] = 0.0;
	matrix2[13] = -dotProduct(up,eyePosition3D);
	// --------------------
	matrix2[2] = -forward[0];
	matrix2[6] = -forward[1];
	matrix2[10] = -forward[2];
	//matrix2[14] = 0.0;
	matrix2[14] = dotProduct(forward,eyePosition3D);
	// --------------------
	matrix2[3] = matrix2[7] = matrix2[11] = 0.0;
	matrix2[15] = 1.0;
	// --------------------
	//MultiplyMatrices4by4OpenGL_FLOAT(resultMatrix, matrix, matrix2);
	//glhTranslatef2(resultMatrix,
	//				-eyePosition3D[0], -eyePosition3D[1], -eyePosition3D[2]);
	// --------------------
	memcpy(matrix, matrix2, 16*sizeof(float));
}

void computePerspectiveMatrix(float *matrix, float fovyInDegrees, float aspectRatio,
            		          float znear, float zfar)
{
	float ymax, xmax;
	ymax = znear * tanf(fovyInDegrees * M_PI / 360.0);
	xmax = ymax * aspectRatio;
	// ymin = -ymax;
	// xmin = -ymax * aspectRatio; = -xmax;
	fillMatrixFrustum(matrix, -xmax, xmax, -ymax, ymax, znear, zfar);
}

void glDrawRepere(float length) {
	// dessin du repère
	glBegin(GL_LINES);
		glColor3f(1.,0.,0.);
		glVertex3f(0.,0.,0.);
		glVertex3f(length,0.,0.);
		glColor3f(0.,1.,0.);
		glVertex3i(0.,0.,0.);
		glVertex3i(0.,length,0.);
		glColor3f(0.,0.,1.);
		glVertex3i(0.,0.,0.);
		glVertex3i(0.,0.,length);
	glEnd();
}

void glDrawObject() {
	float white[3] = {1.0,1.0,1.0};
	glPointSize(size_pt);
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,white);
	glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,1.0);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glVertexPointer(3,GL_FLOAT,0,vertex_coord);
	glNormalPointer(GL_FLOAT,0,normal_coord);
	glDrawArrays(GL_POINTS,0,vertex_number);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}
