#include "rayScene.h"
#include <GL/glut.h>
#include <math.h>
#include <algorithm>
#include <iostream>
using namespace std;

///////////////////////
// Ray-tracing stuff //
///////////////////////

Point3D RayScene::Reflect(Point3D v,Point3D n){
  if( v.dot(n) <= 0 )
    {
      return Point3D(0,0,0);
    }
  return (n * (v.dot(n)) * 2 - v) / (n * (v.dot(n)) * 2 - v).length();
}

int RayScene::Refract(Point3D v,Point3D n,double ir,Point3D& refract){
  if(v.dot(n) < 0)
    {
      n *= -1;
    }
  double thetai = acos(v.dot(n));
  double thetar = asin(sin(thetai)/ir);
  if(thetar > thetai)
    {
      return 0;
    }
  refract = n * (cos(thetai)/ir - cos(thetar)) - v/ir;
  refract /= refract.length();
  return 1;
}

Ray3D RayScene::GetRay(RayCamera* camera,int i,int j,int width,int height){
  Ray3D* ray = new Ray3D();
  ray->position = camera->position;
  float imageDist = height / (2 * tan(camera->heightAngle/2.0));
  float verticalDist = (float)(j+0.5) - (float)(height/2.0);
  float horizontalDist = (float)(i+0.5) - (float)(width/2.0);
  Point3D p = camera->direction * imageDist;
  p += (camera->up) * verticalDist;
  p += (camera->right) * horizontalDist;
  ray->direction = p / p.length();
  return *ray;
}

Point3D RayScene::GetColor(Ray3D ray,int rDepth,Point3D cLimit){
  double mx = -1;
  RayIntersectionInfo iInfo;
  for(int i = 0; i < this->group->sNum; i++)
    {
      mx = this->group->shapes[i]->intersect(ray, iInfo, mx );
    }
  Point3D* color = new Point3D(0,0,0);
  if(mx > 0)
    {      
      RayIntersectionInfo permanentInfo = iInfo;
      *color += this->ambient * iInfo.material->ambient + iInfo.material->emissive;
      for(int i = 0; i < this->lightNum; i++)
	{	
	  Point3D lightContributions = (this->lights[i]->getDiffuse(this->camera->position,iInfo) + this->lights[i]->getSpecular(this->camera->position,iInfo));	  
	  Point3D t = this->lights[i]->transparency(iInfo,this->group,cLimit);  
	  *color += lightContributions*t ;
	}
      /*************Reflection*****************/     
      if(cLimit.p[0] < 1 && cLimit.p[1] < 1 && cLimit.p[2] < 1 && rDepth > 0)
	{	  
	  Ray3D reflect;	  
	  reflect.direction = Reflect(-ray.direction, permanentInfo.normal);
	  if(reflect.direction.length()  != 0)
	    {	     	    
	      reflect.position = permanentInfo.iCoordinate + reflect.direction * 0.00001;
	      rDepth--;

	      Point3D tempColor = GetColor(reflect, rDepth, cLimit/permanentInfo.material->specular) * permanentInfo.material->specular;

	      if(tempColor.p[0] != this->background.p[0] && tempColor.p[1] != this->background.p[1] && tempColor.p[2] != this->background.p[2])
		{
		  *color += tempColor;
		}
	    }		    
	}	
      /*************Refraction****************/
      if(cLimit.p[0] < 1 && cLimit.p[1] && cLimit.p[2] < 1 && rDepth > 0)
	{
	  Ray3D refract;	  
	  refract.position = permanentInfo.iCoordinate;	  	  
	  Point3D* direction = new Point3D();
	  if(Refract(-ray.direction, permanentInfo.normal,permanentInfo.material->refind, *direction) && permanentInfo.material->transparent.length() > 0)
	    {
	      refract.direction = *direction;
	      refract.position += refract.direction * 0.00001;
	      rDepth--;
	      Point3D tempColor = GetColor(refract, rDepth, cLimit/permanentInfo.material->transparent) * permanentInfo.material->transparent;

	      if(tempColor.p[0] != this->background.p[0] && tempColor.p[1] != this->background.p[1] && tempColor.p[2] != this->background.p[2])
		{
		  *color += tempColor;
		}
	    }
	}
      /***************************************/
      for(int i = 0; i < 3; i++)
	{
	  color->p[i] = min(1.0, color->p[i]);
	  color->p[i] = max(0.0, color->p[i]);
	}
    }
  else
    {
      return this->background;
    }
  return *color;
    
}

//////////////////
// OpenGL stuff //
//////////////////
void RayMaterial::drawOpenGL(void){
}
void RayTexture::setUpOpenGL(void){
}
