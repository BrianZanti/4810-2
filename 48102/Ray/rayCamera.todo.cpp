#include <GL/glut.h>
#include <math.h>
#include "rayCamera.h"



//////////////////
// OpenGL stuff //
//////////////////
void RayCamera::drawOpenGL(void){
  Point3D d = this->position+this->direction;
  gluLookAt(this->position.p[0],this->position.p[1],this->position.p[2], d.p[0],d.p[1],d.p[2],this->up[0],this->up[1],this->up[2]);
}
void RayCamera::rotateUp(Point3D center,float angle){
}
void RayCamera::rotateRight(Point3D center,float angle){
}
void RayCamera::moveForward(float dist){
}
void RayCamera::moveRight(float dist){
}
void RayCamera::moveUp(float dist){
}
