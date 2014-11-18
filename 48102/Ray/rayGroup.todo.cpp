#include <stdlib.h>
#include <GL/glut.h>
#include "rayGroup.h"
#include <iostream>
using namespace std;
////////////////////////
//  Ray-tracing stuff //
/////////////////////////
double RayGroup::intersect(Ray3D ray,RayIntersectionInfo& iInfo,double mx){
  double originalMx = mx;
  ray = this->getInverseMatrix() * ray;
  ray.direction /= ray.direction.length();
  if(mx > 0)
    {
      mx = this->getInverseMatrix().multPosition(iInfo.iCoordinate - ray.position).length();
    }
  RayIntersectionInfo tempInfo;
  double groupMx = this->bBox.intersect(ray);
  if(groupMx < mx || (mx < 0 && groupMx > 0))
     {      
      int shapeHits = 0;
      for(int i = 0; i < this->sNum; i++)
	{            	  	  
	  double shapeMx = shapes[i]->bBox.intersect(ray);
	  if(shapeMx > 0)
	    {
	      this->hits[shapeHits].shape = this->shapes[i];
	      this->hits[shapeHits].t = shapeMx;	 
	      shapeHits++;
	    }
	}
      qsort(hits, shapeHits, sizeof(RayShapeHit),RayShapeHit::Compare);
      double localMx = -1;
      for(int i = 0; i < shapeHits; i++)
	{
	  localMx = this->hits[i].shape->intersect(ray, tempInfo, localMx);
	  
	  if(localMx < mx || (localMx > 0 && mx < 0))
	    {	  
	      mx = this->getMatrix().multPosition(tempInfo.iCoordinate - ray.position).length();		  
	      iInfo = tempInfo;
	      iInfo.normal = this->getMatrix().multNormal(iInfo.normal);
	      iInfo.normal /= iInfo.normal.length();
	      iInfo.iCoordinate = this->getMatrix().multPosition(iInfo.iCoordinate);	    
	      return mx;
	    }
	}      
    }
  return originalMx;
}

BoundingBox3D RayGroup::setBoundingBox(void){
  Point3D* pList;
  BoundingBox3D tBBox;
  pList=new Point3D[sNum*2];
  for(int i=0;i<sNum;i++){
    tBBox=shapes[i]->setBoundingBox();
    pList[2*i  ]=tBBox.p[0];
    pList[2*i+1]=tBBox.p[1];
  }
  tBBox=BoundingBox3D(pList,sNum*2);

  delete[] pList;
  bBox=tBBox.transform(getMatrix());
  return bBox;
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
  for(int i = 0; i < this->sNum; i++)
    {
      this->shapes[i]->drawOpenGL(0);
    }
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
