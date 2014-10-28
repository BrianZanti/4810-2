#include <math.h>
#include <GL/glut.h>
#include "rayScene.h"
#include "raySpotLight.h"


////////////////////////
//  Ray-tracing stuff //
////////////////////////
Point3D getColor(Point3D color, double kc, double kl, double kq, double dDotl,double distance, double dropOffRate, double cutOffAngle)
{
  color = (color * pow(dDotl,dropOffRate)) / (kc + kl * distance + pow(kq,2) * distance);
  if(dDotl < cos(cutOffAngle))
    {
      for(int i = 0; i < 3; i++)
	{
	  color.p[i] = 0;
	}
    }
    return color;
}

Point3D RaySpotLight::getDiffuse(Point3D cameraPosition,RayIntersectionInfo& iInfo){
  
  double distance = (this->location - iInfo.iCoordinate).length();
  Point3D l = (this->location - iInfo.iCoordinate) / (this->location - iInfo.iCoordinate).length();
  double dDotl = this->direction.dot(-l);
  Point3D color = getColor(this->color, this->constAtten, this->linearAtten, this->quadAtten, dDotl, distance, this->dropOffRate, this->cutOffAngle);
  return iInfo.material->diffuse * (iInfo.normal.dot(l)) * color;
}
Point3D RaySpotLight::getSpecular(Point3D cameraPosition,RayIntersectionInfo& iInfo){
    Point3D l = (this->location - iInfo.iCoordinate) / (this->location - iInfo.iCoordinate).length();
  double distance = (this->location - iInfo.iCoordinate).length();
  double dDotl = this->direction.dot(-l);
  Point3D color = getColor(this->color, this->constAtten, this->linearAtten, this->quadAtten, dDotl, distance, this->dropOffRate, this->cutOffAngle);
  Point3D v = (cameraPosition - iInfo.iCoordinate) / (cameraPosition - iInfo.iCoordinate).length();
  Point3D r = RayScene::Reflect(l, iInfo.normal);
  if(v.dot(r) < 0)
    {
      for(int i = 0; i < 3; i++)
	{
	  color.p[i] = 0;
	}
    }
  return iInfo.material->specular * pow(v.dot(r), iInfo.material->specularFallOff) * color;
  
}
int RaySpotLight::isInShadow(RayIntersectionInfo& iInfo,RayShape* shape,int& isectCount){
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
Point3D RaySpotLight::transparency(RayIntersectionInfo& iInfo,RayShape* shape,Point3D cLimit){
	return Point3D(1,1,1);
}

//////////////////
// OpenGL stuff //
//////////////////
void RaySpotLight::drawOpenGL(int index){
}
