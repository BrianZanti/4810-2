#include <stdlib.h>
#include <GL/glut.h>
#include "rayGroup.h"
#include <iostream>
using namespace std;
////////////////////////
//  Ray-tracing stuff //
////////////////////////
double RayGroup::intersect(Ray3D ray,RayIntersectionInfo& iInfo,double mx){
  ray = this->getInverseMatrix() * ray;
  ray.direction /= ray.direction.length();
  double tempMx = -1;
  RayIntersectionInfo tempInfo;
  if(this->bBox.intersect(ray))
    {
      for(int i = 0; i < this->sNum; i++)
	{            
	  if(shapes[i]->bBox.intersect(ray))
	    {
	      tempMx = this->shapes[i]->intersect(ray, tempInfo, tempMx);
	    }
	}
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
}

BoundingBox3D RayGroup::setBoundingBox(void){
  Point3D bBoxVertices[sNum*2];
  for(int i = 0; i < sNum; i++)
    {
      this->shapes[i]->bBox = this->shapes[i]->setBoundingBox();
      bBoxVertices[2*i] = this->shapes[i]->bBox.p[0];
      bBoxVertices[2*i+1] = this->shapes[i]->bBox.p[1];
    }
  this->bBox = BoundingBox3D(bBoxVertices,sNum*2);
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
