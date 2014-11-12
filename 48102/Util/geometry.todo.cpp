#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <SVD/SVDFit.h>
#include <SVD/MatrixMNTC.h>
#include "geometry.h"
using namespace std;

///////////////////////
// Ray-tracing stuff //
///////////////////////

double intersectPlane(Ray3D ray, Point3D p1, Point3D p2, Plane3D plane, double mx)
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
	     return t;
	   }
       }
   }
 return mx;
}

double BoundingBox3D::intersect(const Ray3D& ray) const {
  double mx = -1;
  double x = this->p[1].p[0] - this->p[0].p[0];
  double y = this->p[1].p[1] - this->p[0].p[1];
  double z = this->p[1].p[2] - this->p[0].p[2];
  Point3D p1 = this->p[0];
  Point3D p2 = p1;
  p2[1] += y;
  Point3D p3 = p2;
  p3[0] += x;
  Point3D p4 = p1;
  p4[0] += x;
  Point3D p5 = p1;
  p5[2] += z;
  Point3D p6 = p5;
  p6[1] += y;
  Point3D p7 = p6;
  p7[0] += x;
  Point3D p8 = p5;
  p8[0] += x;
  
  mx = intersectPlane(ray, p1, p8, Plane3D(p1,p8,p4), mx);
  mx = intersectPlane(ray, p1, p6, Plane3D(p1,p6,p2), mx);
  mx = intersectPlane(ray, p5, p7, Plane3D(p5,p7,p6), mx);
  mx = intersectPlane(ray, p2, p7, Plane3D(p2,p7,p3), mx);
  mx = intersectPlane(ray, p4, p7, Plane3D(p4,p7,p8), mx);
  mx = intersectPlane(ray, p1, p3, Plane3D(p1,p3,p4), mx);
  
  return mx;
}

/////////////////////
// Animation stuff //
/////////////////////
Matrix3D::Matrix3D(const Point3D& e){
	(*this)=Matrix3D();
}

Matrix3D::Matrix3D(const Quaternion& q){
	(*this)=Matrix3D();
}
Matrix3D Matrix3D::closestRotation(void) const {
	return (*this);
}
/* While these Exp and Log implementations are the direct implementations of the Taylor series, the Log
 * function tends to run into convergence issues so we use the other ones:*/
Matrix3D Matrix3D::Exp(const Matrix3D& m,int iter){
	return m;
}
