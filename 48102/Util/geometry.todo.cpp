#include <stdlib.h>
#include <math.h>

#include <SVD/SVDFit.h>
#include <SVD/MatrixMNTC.h>
#include "geometry.h"


///////////////////////
// Ray-tracing stuff //
///////////////////////
double getMx(Ray3D ray, double mx, Plane3D plane, Point3D* vertices){
  double t =  -(ray.position.dot(plane.normal) + plane.distance) / (ray.direction.dot(plane.normal));
  if(t < 0 || (t > mx && mx > 0))
    {
      return mx;
    }
  Point3D v1 = vertices[1] - vertices[0];
  Point3D v2 = vertices[2] - vertices[0];
  Matrix3D* A = new Matrix3D();
  for(int i = 0; i < 3; i++)
    {
      A->m[i][0] = v1[i];      
      A->m[i][1] = v2[i];
      A->m[i][2] = 1; 
    }
  Point3D p = ray.position + ray.direction * t - vertices[0];
  Point3D combo = A->invert() * p;
  if(combo[0] <= 1 && combo[0] >= 0 && combo[1] <= 1 && combo[1] >= 0 )
    {
      if(combo[0] + combo[1] <= 1)
	{
	  if(t < mx || mx < 0)
	    {
	      return t;
	    }
	}
	
    }
  return mx;
}


double BoundingBox3D::intersect(const Ray3D& ray) const {
  double mx = -1;
  Point3D p1;
  Point3D p2;
  Point3D p3;
  double x = this->p[1].p[0] - this->p[0].p[0];
  double y = this->p[1].p[1] - this->p[0].p[1];
  double z = this->p[1].p[2] - this->p[0].p[2];
  Point3D vertices[3];

  /*********** x , x z **********************************/
  p1 = this->p[0];
  p2 = this->p[0];
  p3 = this->p[0];
  p2.p[0] += x;
  p3.p[0] += x;
  p3.p[2] += z;
  vertices[0] = p1;
  vertices[1] = p2;
  vertices[3] = p3;
  mx = getMx(ray, mx, Plane3D(p1,p2,p3), vertices);
  /************** x , x y ******************************/
    p1 = this->p[0];
  p2 = this->p[0];
  p3 = this->p[0];
  p2.p[0] += x;
  p3.p[0] += x;
  p3.p[1] += y;
  vertices[0] = p1;
  vertices[1] = p2;
  vertices[3] = p3;
  mx = getMx(ray, mx, Plane3D(p1,p2,p3), vertices);
  
  p1 = this->p[0];
  p2 = this->p[0];
  p3 = this->p[0];
  p2.p[1] += y;
  p3.p[0] += x;
  p3.p[1] += y;
  vertices[0] = p1;
  vertices[1] = p2;
  vertices[3] = p3;
  mx = getMx(ray, mx, Plane3D(p1,p2,p3), vertices);
  /*
  p1 = this->p[0];
  p2 = this->p[0];
  p3 = this->p[0];
  p2.p[1] += y;
  p3.p[1] += y;
  p3.p[2] += z;
  vertices[0] = p1;
  vertices[1] = p2;
  vertices[3] = p3;
  mx = getMx(ray, mx, Plane3D(p1,p2,p3), vertices);

  
  p1 = this->p[0];
  p2 = this->p[0];
  p3 = this->p[0];
  p2.p[2] += z;
  p3.p[2] += z;
  p3.p[0] += x;
  vertices[0] = p1;
  vertices[1] = p2;
  vertices[3] = p3;
  mx = getMx(ray, mx, Plane3D(p1,p2,p3), vertices);

  
  p1 = this->p[0];
  p2 = this->p[0];
  p3 = this->p[0];
  p2.p[2] += z;
  p3.p[2] += z;
  p3.p[1] += y;
  vertices[0] = p1;
  vertices[1] = p2;
  vertices[3] = p3;
  mx = getMx(ray, mx, Plane3D(p1,p2,p3), vertices);




  
  p1 = this->p[1];
  p2 = this->p[1];
  p3 = this->p[1];
  p2.p[0] -= x;
  p3.p[0] -= x;
  p3.p[2] -= z;
  vertices[0] = p1;
  vertices[1] = p2;
  vertices[3] = p3;
  mx = getMx(ray, mx, Plane3D(p1,p2,p3), vertices);
  
  p1 = this->p[0];
  p2 = this->p[0];
  p3 = this->p[0];
  p2.p[0] -= x;
  p3.p[0] -= x;
  p3.p[1] -= y;
  vertices[0] = p1;
  vertices[1] = p2;
  vertices[3] = p3;
  mx = getMx(ray, mx, Plane3D(p1,p2,p3), vertices);
  
  p1 = this->p[0];
  p2 = this->p[0];
  p3 = this->p[0];
  p2.p[1] -= y;
  p3.p[0] -= x;
  p3.p[1] -= y;
  vertices[0] = p1;
  vertices[1] = p2;
  vertices[3] = p3;
  mx = getMx(ray, mx, Plane3D(p1,p2,p3), vertices);
  
  p1 = this->p[0];
  p2 = this->p[0];
  p3 = this->p[0];
  p2.p[1] -= y;
  p3.p[1] -= y;
  p3.p[2] -= z;
  vertices[0] = p1;
  vertices[1] = p2;
  vertices[3] = p3;
  mx = getMx(ray, mx, Plane3D(p1,p2,p3), vertices);

  
  p1 = this->p[0];
  p2 = this->p[0];
  p3 = this->p[0];
  p2.p[2] -= z;
  p3.p[2] -= z;
  p3.p[0] -= x;
  vertices[0] = p1;
  vertices[1] = p2;
  vertices[3] = p3;
  mx = getMx(ray, mx, Plane3D(p1,p2,p3), vertices);

  
  p1 = this->p[0];
  p2 = this->p[0];
  p3 = this->p[0];
  p2.p[2] -= z;
  p3.p[2] -= z;
  p3.p[1] -= y;
  vertices[0] = p1;
  vertices[1] = p2;
  vertices[3] = p3;
  mx = getMx(ray, mx, Plane3D(p1,p2,p3), vertices);
*/  
  if(mx!=0)
    {
      cout << "true" << endl;
    }
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
