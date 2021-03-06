#include <math.h>
#include <GL/glut.h>
#include "rayScene.h"
#include "raySphere.h"

////////////////////////
//  Ray-tracing stuff //
////////////////////////
double RaySphere::intersect(Ray3D ray,RayIntersectionInfo& iInfo,double mx){
  Point3D l = this->center - ray.position;
  double tca = l.dot(ray.direction);
  double dsquared = l.dot(l) - pow(tca,2);
  if( dsquared > pow(this->radius,2))
    {
      return mx;
    }
  double thc = sqrt(pow(this->radius,2) - dsquared);
  double t = tca - thc;
  if(t > 0 )
    {
      if(t < mx || mx < 0)
	{
	  iInfo.material = this->material;
	  Point3D p = ray.position + ray.direction * t;
	  iInfo.iCoordinate = p;
	  iInfo.normal = (p - this->center) / (p - this->center).length();
	  return t;       
	}
    }
  return mx;
}
BoundingBox3D RaySphere::setBoundingBox(void){
  Point3D p=Point3D(radius,radius,radius);
  bBox=BoundingBox3D(center+p,center-p);
  return bBox;
}

//////////////////
// OpenGL stuff //
//////////////////
int RaySphere::drawOpenGL(int materialIndex){
  glColor3f(1.0,1.0,1.0);
  glTranslatef(this->center.p[0],this->center.p[1],this->center.p[2]);
  gluSphere(gluNewQuadric(),this->radius,this->openGLComplexity,openGLComplexity);
  return -1;
}
