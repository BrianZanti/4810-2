#include "rayScene.h"
#include <GL/glut.h>
#include <math.h>
#include <algorithm>
using namespace std;

///////////////////////
// Ray-tracing stuff //
///////////////////////

Point3D RayScene::Reflect(Point3D v,Point3D n){
  return (n * (v.dot(n)) * 2 - v) / (n * (v.dot(n)) * 2 - v).length();
}

int RayScene::Refract(Point3D v,Point3D n,double ir,Point3D& refract){
  return 0;
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
  Point3D* color = new Point3D();
  if(mx > 0)
    {
      for(int i = 0; i < 3; i++)
	{
	  color->p[i] = 0;
	}
      *color += this->ambient * iInfo.material->ambient + iInfo.material->emissive;
      for(int i = 0; i < this->lightNum; i++)
	{
	  int x = 0;
	  int& isectCount = x;
	  Point3D lightContributions = (this->lights[i]->getDiffuse(this->camera->position,iInfo) + this->lights[i]->getSpecular(this->camera->position,iInfo))*1;
	  int s = this->lights[i]->isInShadow(iInfo,this->group,isectCount);
	  *color += lightContributions * s;
	}
      
      for(int i = 0; i < 3; i++)
	{
	  color->p[i] = min(1.0, color->p[i]);
	  color->p[i] = max(0.0, color->p[i]);
	}
    }
  else
    {
      *color = this->background;
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
