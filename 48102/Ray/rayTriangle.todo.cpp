#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "rayTriangle.h"

////////////////////////
//  Ray-tracing stuff //
////////////////////////
void RayTriangle::initialize(void){
    Plane3D* tempPlane = new Plane3D(this->v[0]->position, this->v[1]->position, this->v[2]->position);
  this->plane = *tempPlane;
  this->v1 = this->v[1]->position - this->v[0]->position;
  this->v2 = this->v[2]->position - this->v[0]->position;
 
}
double RayTriangle::intersect(Ray3D ray,RayIntersectionInfo& iInfo,double mx){
   double t =  -(ray.position.dot(this->plane.normal) + this->plane.distance) / (ray.direction.dot(this->plane.normal));
 if(t < 0 || (t > mx && mx > 0))
    {
      return mx;
    }
  Matrix3D* A = new Matrix3D();
  for(int i = 0; i < 3; i++)
    {
      A->m[i][0] = v1[i];      
      A->m[i][1] = v2[i];
      A->m[i][2] = 1; 
    }
  Point3D p = ray.position + ray.direction * t - this->v[0]->position;
  Point3D combo = A->invert() * p;
  if(combo[0] <= 1 && combo[0] >= 0 && combo[1] <= 1 && combo[1] >= 0 )
    {
      if(combo[0] + combo[1] <= 1)
	{
	  if(t < mx || mx < 0)
	    {
	      iInfo.material = this->material;
	      iInfo.normal = this->plane.normal;
	      iInfo.iCoordinate = p + this->v[0]->position;
	      return t;
	    }
	}
	
    }
  return mx;
}

BoundingBox3D RayTriangle::setBoundingBox(void){
  Point3D vertices[] = {this->v[0]->position, this->v[1]->position, this->v[2]->position};
  return BoundingBox3D(vertices,3);
  
}

//////////////////
// OpenGL stuff //
//////////////////
int RayTriangle::drawOpenGL(int materialIndex){
	return -1;
}
