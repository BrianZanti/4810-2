#include <math.h>
#include <GL/glut.h>
#include "rayScene.h"
#include "rayBox.h"
#include "rayTriangle.h"

////////////////////////
//  Ray-tracing stuff //
////////////////////////

double intersectPlane(Ray3D ray, Point3D p1, Point3D p2, Plane3D plane, double mx, RayIntersectionInfo& tempInfo)
{
  double t =  -(ray.position.dot(plane.normal) + plane.distance) / (ray.direction.dot(plane.normal));
 if(t < 0 || (t > mx && mx > 0))
    {
      return mx;
    }
 Point3D p = ray.position + ray.direction * t;
 if(p[0] >= p1[0] && p[0] <= p2[0])
   {
     if(p[1] >= p1[1] && p[1] <= p2[1])
       {
	 if(p[2] >= p1[2] && p[2] <= p2[2])
	   {	     
	     tempInfo.normal = plane.normal;
	     tempInfo.iCoordinate = ray.position + ray.direction * t;
	     return t;
	   }
       }
   }
 return mx;
}
double RayBox::intersect(Ray3D ray,RayIntersectionInfo& iInfo,double mx)
{			
  double ogMx = mx;
  RayIntersectionInfo tempInfo;

  Point3D p1 = this->center;
  p1 -= this->length/2.0;
  Point3D p2 = p1;
  p2[1] += this->length[1];
  Point3D p3 = p2;
  p3[0] += this->length[0];
  Point3D p4 = p1;
  p4[0] += this->length[0];
  Point3D p5 = p1;
  p5[2] += this->length[2];
  Point3D p6 = p5;
  p6[1] += this->length[1];
  Point3D p7 = p6;
  p7[0] += this->length[0];
  Point3D p8 = p5;
  p8[0] += this->length[0];
  
  mx = intersectPlane(ray, p1, p8, Plane3D(p1,p8,p4), mx, tempInfo);
  mx = intersectPlane(ray, p1, p6, Plane3D(p1,p6,p2), mx, tempInfo);
  mx = intersectPlane(ray, p5, p7, Plane3D(p5,p7,p6), mx, tempInfo);
  mx = intersectPlane(ray, p2, p7, Plane3D(p2,p7,p3), mx, tempInfo);
  mx = intersectPlane(ray, p4, p7, Plane3D(p4,p7,p8), mx, tempInfo);
  mx = intersectPlane(ray, p1, p3, Plane3D(p1,p3,p4), mx, tempInfo);
  
  if(mx < ogMx || (ogMx < 0 && mx > 0))
    {
      iInfo = tempInfo;
      iInfo.material = this->material;
      return mx;
    }
  return ogMx;
}
BoundingBox3D RayBox::setBoundingBox(void){
	return bBox;
}

//////////////////
// OpenGL stuff //
//////////////////
int RayBox::drawOpenGL(int materialIndex){
	return -1;
}
