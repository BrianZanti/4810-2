#include <math.h>
#include <GL/glut.h>
#include "rayDirectionalLight.h"
#include "rayScene.h"

////////////////////////
//  Ray-tracing stuff //
////////////////////////
Point3D RayDirectionalLight::getDiffuse(Point3D cameraPosition,RayIntersectionInfo& iInfo){
   return iInfo.material->diffuse * ((iInfo.normal).dot(-this->direction)) * this->color;
}
Point3D RayDirectionalLight::getSpecular(Point3D cameraPosition,RayIntersectionInfo& iInfo){
    Point3D r = RayScene::Reflect(-this->direction, iInfo.normal);
  Point3D v = (cameraPosition - iInfo.iCoordinate) / (cameraPosition - iInfo.iCoordinate).length();
  if(v.dot(r) > 0)
    {
      return iInfo.material->specular * pow(v.dot(r), iInfo.material->specularFallOff) * this->color;
    }
  else
    {
      return this->color - this->color;
    }
}
int RayDirectionalLight::isInShadow(RayIntersectionInfo& iInfo,RayShape* shape,int& isectCount){
    Ray3D* shadowRay = new Ray3D();
  shadowRay->direction = this->direction * -1;
  shadowRay->position = iInfo.iCoordinate;
  shadowRay->position += (shadowRay->direction * 0.00001);
   
  double lightDist = -1;
  double mx = shape->intersect(*shadowRay, iInfo, lightDist);
  if(mx > 0)
    {
      return 0;
    }
  return 1;
}
Point3D RayDirectionalLight::transparency(RayIntersectionInfo& iInfo,RayShape* shape,Point3D cLimit){
  int y = 0;
  int& isectCount = y;
  int x = isInShadow(iInfo, shape, isectCount);
  if(x == 0)
    {
      return iInfo.material->transparent;
    }
  return Point3D(1,1,1);
}

//////////////////
// OpenGL stuff //
//////////////////
void RayDirectionalLight::drawOpenGL(int index){
}
