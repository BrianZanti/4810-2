#include <stdlib.h>
#include <GL/glut.h>
#include "rayGroup.h"

////////////////////////
//  Ray-tracing stuff //
////////////////////////
double RayGroup::intersect(Ray3D ray,RayIntersectionInfo& iInfo,double mx){
  ray = this->getInverseMatrix() * ray;
  ray.direction /= ray.direction.length();
  double tempMx = -1;
  RayIntersectionInfo tempInfo;
  for(int i = 0; i < this->sNum; i++)
    {            
      tempMx = this->shapes[i]->intersect(ray, tempInfo, tempMx);
    }
  if(tempMx > 0)
    {
      tempMx = this->getMatrix().multPosition(tempInfo.iCoordinate - ray.position).length();
      if(tempMx < mx || mx < 0)
	{
	  mx = tempMx;
	  iInfo = tempInfo;
	  iInfo.normal = this->getMatrix().multNormal(iInfo.normal);
	  iInfo.normal /= iInfo.normal.length();
	  iInfo.iCoordinate = this->getMatrix().multPosition(iInfo.iCoordinate);
	}
    }
  return mx;
  //return (iInfo.iCoordinate - globalRayPosition).length();
}

BoundingBox3D RayGroup::setBoundingBox(void){
  
}
int StaticRayGroup::set(void){
  this->inverseTransform = this->getMatrix().invert();
  return 1;
}
//////////////////
// OpenGL stuff //
//////////////////
int RayGroup::getOpenGLCallList(void){
	return 0;
}

int RayGroup::drawOpenGL(int materialIndex){
	return -1;
}

/////////////////////
// Animation Stuff //
/////////////////////
Matrix4D ParametrizedEulerAnglesAndTranslation::getMatrix(void){
	return Matrix4D::IdentityMatrix();
}
Matrix4D ParametrizedClosestRotationAndTranslation::getMatrix(void){
	return Matrix4D::IdentityMatrix();
}
Matrix4D ParametrizedRotationLogarithmAndTranslation::getMatrix(void){
	return Matrix4D::IdentityMatrix();
}
Matrix4D ParametrizedQuaternionAndTranslation::getMatrix(void){
	return Matrix4D::IdentityMatrix();
}
