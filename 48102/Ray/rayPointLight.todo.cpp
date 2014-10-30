#include <math.h>
#include <GL/glut.h>
#include "rayPointLight.h"
#include "rayScene.h"

////////////////////////
//  Ray-tracing stuff //
////////////////////////
Point3D getColor(Point3D color, double distance, double kc, double kl, double kq)
{
  return color / (kc + kl * distance + pow(kq,2)*distance);	
}

Point3D RayPointLight::getDiffuse(Point3D cameraPosition,RayIntersectionInfo& iInfo){  	
  Point3D color = getColor(this->color, (this->location - iInfo.iCoordinate).length(), this->constAtten, this->linearAtten, this->quadAtten);

  Point3D l = (this->location - iInfo.iCoordinate) / (this->location - iInfo.iCoordinate).length();

  return iInfo.material->diffuse * (iInfo.normal.dot(l)) * color;
}

Point3D RayPointLight::getSpecular(Point3D cameraPosition,RayIntersectionInfo& iInfo){
    double distance = (this->location - iInfo.iCoordinate).length();
  Point3D color = getColor(this->color, distance, this->constAtten, this->linearAtten, this->quadAtten);
  Point3D l = (this->location - iInfo.iCoordinate) / (this->location - iInfo.iCoordinate).length();
  Point3D r = RayScene::Reflect(l, iInfo.normal);
  Point3D v = (cameraPosition - iInfo.iCoordinate) / (cameraPosition - iInfo.iCoordinate).length();
  if(v.dot(r) < 0)
    {
      for(int i = 0; i < 3; i++)
	{
	  color[i] = 0;
	}
    }
  return iInfo.material->specular * pow(v.dot(r), iInfo.material->specularFallOff) * color;
  
}
int RayPointLight::isInShadow(RayIntersectionInfo& iInfo,RayShape* shape,int& isectCount){
    Ray3D* shadowRay = new Ray3D();
  shadowRay->direction = (this->location - iInfo.iCoordinate) / (this->location - iInfo.iCoordinate).length();
  shadowRay->position = iInfo.iCoordinate;
  for(int i = 0; i < 3; i++)
    {
      shadowRay->position += (shadowRay->direction * 0.00001);
    }
  double lightDist = (this->location - iInfo.iCoordinate).length();
  double mx = shape->intersect(*shadowRay, iInfo, lightDist);
  if(mx < lightDist)
    {
      return 0;
    }
  return 1;
}
Point3D RayPointLight::transparency(RayIntersectionInfo& iInfo,RayShape* shape,Point3D cLimit){
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
void RayPointLight::drawOpenGL(int index){
}
