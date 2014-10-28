#include "image.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// allows the use of min() and max() functions
#include <algorithm>
#include <iostream>
using namespace std;


Pixel::Pixel(const Pixel32& p)
{
}

Pixel32::Pixel32(const Pixel& p)
{
}


int Image32::AddRandomNoise(const float& noise,Image32& outputImage) const
{ 
  int seed = time(NULL);
  srand(seed);
  for(int i = 0; i < outputImage.width(); i++)
    {
      for(int j =0; j < outputImage.height(); j++)
	{	 
	  

	  double randDec = (double)rand()/RAND_MAX;	  
          int rNoise = noise*(randDec*(511)-255);	 	  	     	  
	  int r = (int)(outputImage(i,j).r) + rNoise;

	  randDec = (double)rand()/RAND_MAX;
	  int gNoise = noise*(randDec*(511)-255);	
	  int g =(int)(outputImage(i,j).g) + gNoise;
	  
	  randDec = (double)rand()/RAND_MAX;
	  int bNoise = noise*(randDec*(511)-255);	 
	  int b =(int)(outputImage(i,j).b) + bNoise;

	  
	  
	  if(r > 255)
	    {
	      outputImage(i,j).r = 255;
	    }
	  else if(r < 0)
	    {
	      outputImage(i,j).r = 0;
	    }
	  else 
	    {
	      outputImage(i,j).r = (unsigned char)r;
	    }
	  
	 
	  if(g > 255)
	    {
	      outputImage(i,j).g = 255;
	    }
	  else if(g < 0)
	    {
	      outputImage(i,j).g = 0;
	    }
	  else
	    {
	      outputImage(i,j).g = (unsigned char)g;
	    }	  

	  if(b > 255)
	    {
	      outputImage(i,j).b = 255;
	    }
	  else if(b < 0)
	    {
	      outputImage(i,j).b = 0;
	    }
	  else
	    {
	      outputImage(i,j).b = (unsigned char)b;
	    }
	  	  
	}      
	}
  return 1;
}

int Image32::Brighten(const float& brightness,Image32& outputImage) const
{
  for(int i = 0; i < outputImage.width(); i++)
    {
      for(int j = 0; j < outputImage.height(); j++)
	{
	  if(outputImage(i,j).r * brightness > 255)
	    {
	      outputImage(i,j).r = 255;
	    }
	  else
	    {
	      outputImage(i,j).r *= brightness;
	    } 

	  if(outputImage(i,j).g * brightness > 255)
	    {
	      outputImage(i,j).g = 255;
	    }
	  else
	    {
	      outputImage(i,j).g *= brightness;
	    }

	  if(outputImage(i,j).b * brightness > 255)
	    {
	      outputImage(i,j).b = 255;
	    }
	  else
	    {
	      outputImage(i,j).b *= brightness;
	    }
	}
    }
  return 1;
}

int Image32::Luminance(Image32& outputImage) const
{
  for(int i = 0; i < outputImage.width(); i++)
    {
      for(int j = 0; j < outputImage.height(); j++)
	{
	  float l = 0.3 * (float)outputImage(i,j).r + 0.59 * (float)outputImage(i,j).g + 0.11 * (float)outputImage(i,j).b;
	  outputImage(i,j).r = (unsigned char)l;
	  outputImage(i,j).g = (unsigned char)l;
	  outputImage(i,j).b = (unsigned char)l;
	}
    }
	return 1;
}
int Image32::Contrast(const float& contrast,Image32& outputImage) const
{
  float totalL = 0.0;
  for(int i = 0; i < outputImage.width(); i++)
    {
      for(int j = 0; j < outputImage.height(); j++)
	{
	  float l = 0.3 * (float)outputImage(i,j).r + 0.59 * (float)outputImage(i,j).g + 0.11 * (float)outputImage(i,j).b;
	  
	  totalL += l;
      	}
    }
  float avgL = totalL / (float)(outputImage.height() * outputImage.width());
 
  for(int i = 0; i < outputImage.width(); i++)
    {
      for(int j = 0; j < outputImage.height(); j ++)
	{
	  float r = avgL + contrast*((float)outputImage(i,j).r-avgL);	  
	  if(r > 255)
	    {
	      r = 255;
	    }
	  if(r < 0)
	    {
	      r = 0;	     
	    }	 
	  outputImage(i,j).r = (unsigned char)r;

	  float g = avgL + contrast*((float)outputImage(i,j).g-avgL);
	  if(g > 255)
	    {
	      g = 255;
	    }
	  if(g < 0)
	    {
	      g = 0;	     
	    }
	  outputImage(i,j).g = (unsigned char)g;

  	  float b = avgL + contrast*((float)outputImage(i,j).b-avgL);
	  if(b > 255)
	    {
	      b = 255;
	    }
	  if(b < 0)
	    {
	      b = 0;	     
	    }
	  outputImage(i,j).b = (unsigned char)b;
	}
    }

	return 1;
}

int Image32::Saturate(const float& saturation,Image32& outputImage) const
{
  for(int i = 0; i < outputImage.width(); i++)
    {
      for(int j = 0; j < outputImage.height(); j++)
	{
	  float l = 0.3 * (float)outputImage(i,j).r + 0.59 * (float)outputImage(i,j).g + 0.11 * (float)outputImage(i,j).b;


	  float r = l + saturation*((float)outputImage(i,j).r-l);	  
	  if(r > 255)
	    {
	      r = 255;
	    }
	  if(r < 0)
	    {
	      r = 0;	     
	    }	 
	  outputImage(i,j).r = (unsigned char)r;

	  float g = l + saturation*((float)outputImage(i,j).g-l);
	  if(g > 255)
	    {
	      g = 255;
	    }
	  if(g < 0)
	    {
	      g = 0;	     
	    }
	  outputImage(i,j).g = (unsigned char)g;

  	  float b = l + saturation*((float)outputImage(i,j).b-l);
	  if(b > 255)
	    {
	      b = 255;
	    }
	  if(b < 0)
	    {
	      b = 0;	     
	    }
	  outputImage(i,j).b = (unsigned char)b;

	 
	}
    }
	return 1;
}

int Image32::Quantize(const int& bits,Image32& outputImage) const
{
  for(int i = 0; i < outputImage.width(); i++)
    {
      for(int j = 0; j < outputImage.height(); j++)
	{	  	  
	  outputImage(i,j).r = (unsigned char)(255 / (pow(2,bits)-1)*floor((float)outputImage(i,j).r * pow(2, bits) / (float)256));
	  outputImage(i,j).g = (unsigned char)(255 / (pow(2,bits)-1)*floor((float)outputImage(i,j).g * pow(2, bits) / (float)256));
	  outputImage(i,j).b = (unsigned char)(255 / (pow(2,bits)-1)*floor((float)outputImage(i,j).b * pow(2, bits) / (float)256));	  
	}
    }
	return 1;
}

int Image32::RandomDither(const int& bits,Image32& outputImage) const
{
  const float x = 0.5;
  outputImage.AddRandomNoise(x , outputImage);
  outputImage.Quantize(bits, outputImage);
    return 1;	
}
int Image32::OrderedDither2X2(const int& bits,Image32& outputImage) const
{
  int D[2][2];
  D[0][0] = 1;
  D[1][0] = 4;
  D[0][1] = 3;
  D[1][1] = 2;
  for(int  x= 0; x < outputImage.width(); x++)
    {
      for(int y = 0; y < outputImage.height(); y++)
      {
	int i = x % 2;
	int j = y % 2;
	float cr = (float)outputImage(x,y).r / 255 * (pow(2,bits)-1);
	float er = cr - floor(cr);
	
	if(er > (float)D[i][j] / 5)
	  {
	    outputImage(x,y).r = (unsigned char)(ceil(cr) * 255 / (pow(2,bits)-1));
	  }
	else
	  {
	    outputImage(x,y).r = (unsigned char)(floor(cr) * 255 / (pow(2,bits)-1));
	  }

	float cg = (float)outputImage(x,y).g / 255 * (pow(2,bits)-1);
	float eg = cg - floor(cg);
	
	if(eg > (float)D[i][j] / 5)
	  {
	    outputImage(x,y).g = (unsigned char)(ceil(cg) * 255 / (pow(2,bits)-1));
	  }
	else
	  {
	    outputImage(x,y).g = (unsigned char)(floor(cg) * 255 / (pow(2,bits)-1));
	  }

	float cb = (float)outputImage(x,y).b / 255 * (pow(2,bits)-1);
	float eb = cb - floor(cb);	
	if(eb > (float)D[i][j] / 5)
	  {
	    outputImage(x,y).b = (unsigned char)(ceil(cb) * 255 / (pow(2,bits)-1));
	  }
	else
	  {
	    outputImage(x,y).b = (unsigned char)(floor(cb) * 255 / (pow(2,bits)-1));
	  }
      }
    }
	return 1;
}

int Image32::FloydSteinbergDither(const int& bits,Image32& outputImage) const
{
  Image32* tempImage = new Image32();
  tempImage->setSize(outputImage.width(),outputImage.height());
  float alpha = 7.0/16.0;
  float beta = 3.0/16.0;
  float gamma = 5.0/16.0;
  float delta = 1.0/16.0;
  for(int i = 0; i < outputImage.width(); i++)
    {
      for(int j = 0; j < outputImage.height(); j++)
	{
	  tempImage->pixel(i,j).r = (unsigned char)(255 / (pow(2,bits)-1)*floor((float)outputImage(i,j).r * pow(2, bits) / (float)256));
	  float error = (float)outputImage(i,j).r - (float)tempImage->pixel(i,j).r;
	  float r;
	  if(i != outputImage.width()-1)
	    {
	      r = (float)outputImage(i+1,j).r + alpha * error;
	      if(r > 255)
		{
		  r = 255;
		}
	      if(r < 0)
		{
		  r = 0;
		}
	      outputImage(i+1,j).r = (unsigned char)r;
	    }
	  
	  if( j != outputImage.height()-1 && i != 0)
	    {
	      r = (float)outputImage(i-1,j+1).r + beta * error;
	      if(r > 255)
		{
		  r = 255;
		}
	      if(r < 0)
		{
		  r = 0;
		}
	      outputImage(i-1,j+1).r = (unsigned char)r;
	    }
	  
	  if( j != outputImage.height()-1 )
	    {
	      r = (float)outputImage(i,j+1).r + gamma * error;
	      if(r > 255)
		{
		  r = 255;
		}
	      if(r < 0)
		{
		  r = 0;
		}
	      outputImage(i,j+1).r = (unsigned char)r;
	    }
	  
	  if( i != outputImage.width()-1 && j != outputImage.height()-1)
	    {
	      r = (float)outputImage(i+1,j+1).r + delta * error;
	      if(r > 255)
		{
		  r = 255;
		}
	      if(r < 0)
		{
		  r = 0;
		}
	      outputImage(i+1,j+1).r = (unsigned char)r;
	    }
	  
  	  tempImage->pixel(i,j).g = (unsigned char)(255 / (pow(2,bits)-1)*floor((float)outputImage(i,j).g * pow(2, bits) / (float)256));
	  error = (float)outputImage(i,j).g - (float)tempImage->pixel(i,j).g;
	  float g;
	  if(i != outputImage.width()-1)
	    {
	      g = (float)outputImage(i+1,j).g + alpha * error;
	      if(g > 255)
		{
		  g = 255;
		}
	      if(g < 0)
		{
		  g = 0;
		}
	      outputImage(i+1,j).g = (unsigned char)g;
	    }
	  
	  if( j != outputImage.height()-1 && i != 0)
	    {
	      g = (float)outputImage(i-1,j+1).g + beta * error;
	      if(g > 255)
		{
		  g = 255;
		}
	      if(g < 0)
		{
		  g = 0;
		}
	      outputImage(i-1,j+1).g = (unsigned char)g;
	    }
	  
	  if( j != outputImage.height()-1 )
	    {
	      g = (float)outputImage(i,j+1).g + gamma * error;
	      if(g > 255)
		{
		  g = 255;
		}
	      if(g < 0)
		{
		  g = 0;
		}
	      outputImage(i,j+1).g = (unsigned char)g;
	    }
	  
	  if( i != outputImage.width()-1 && j != outputImage.height()-1)
	    {
	      g = (float)outputImage(i+1,j+1).g + delta * error;
	      if(g > 255)
		{
		  g = 255;
		}
	      if(g < 0)
		{
		  g = 0;
		}
	      outputImage(i+1,j+1).g = (unsigned char)g;
	    }
	
	  tempImage->pixel(i,j).b = (unsigned char)(255 / (pow(2,bits)-1)*floor((float)outputImage(i,j).b * pow(2, bits) / (float)256));
	  error = (float)outputImage(i,j).b - (float)tempImage->pixel(i,j).b;
	  float b;
	  if(i != outputImage.width()-1)
	    {
	      b = (float)outputImage(i+1,j).b + alpha * error;
	      if(b > 255)
		{
		  b = 255;
		}
	      if(b < 0)
		{
		  b = 0;
		}
	      outputImage(i+1,j).b = (unsigned char)b;
	    }
	  
	  if( j != outputImage.height()-1 && i != 0)
	    {
	      b = (float)outputImage(i-1,j+1).b + beta * error;
	      if(b > 255)
		{
		  b = 255;
		}
	      if(b < 0)
		{
		  b = 0;
		}
	      outputImage(i-1,j+1).b = (unsigned char)b;
	    }
	  
	  if( j != outputImage.height()-1 )
	    {
	      b = (float)outputImage(i,j+1).b + gamma * error;
	      if(b > 255)
		{
		  b = 255;
		}
	      if(b < 0)
		{
		  b = 0;
		}
	      outputImage(i,j+1).b = (unsigned char)b;
	    }
	  
	  if( i != outputImage.width()-1 && j != outputImage.height()-1)
	    {
	      b = (float)outputImage(i+1,j+1).b + delta * error;
	      if(b > 255)
		{
		  b = 255;
		}
	      if(b < 0)
		{
		  b = 0;
		}
	      outputImage(i+1,j+1).b = (unsigned char)b;
	    }

	}
    }
  outputImage = *tempImage;
  return 1;
}

int Image32::Blur3X3(Image32& outputImage) const
{
   float mask[3][3] = {{1.0/16.0,2.0/16.0,1.0/16.0},{2.0/16.0,4.0/16.0,2.0/16.0},{1.0/16.0,2.0/16.0,1.0/16.0}};
  Image32* tempImage = new Image32();
  tempImage->setSize(outputImage.width(), outputImage.height());
  for( int i = 0; i < outputImage.width(); i++)
    {
      for(int j = 0; j < outputImage.height(); j++)
	{
	  float tempMask[3][3];
	  for(int x = 0; x < 3; x++)
	    {
	      for(int y = 0; y < 3; y++)
		{
		  tempMask[y][x] = mask[y][x];
		}
	    }	    	
	      if(i == 0)
		{
		  tempMask[0][0] = 0.0;
		  tempMask[1][0] = 0.0;
		  tempMask[2][0] = 0.0;
		}
	      if(i == outputImage.width() - 1)
		{
		  tempMask[0][2] = 0.0;
		  tempMask[1][2] = 0.0;
		  tempMask[2][2] = 0.0;
		}
	      if(j == 0)
		{
		  tempMask[0][0] = 0.0;
		  tempMask[0][1] = 0.0;
		  tempMask[0][2] = 0.0;
		}
	      if(j == outputImage.height()-1)
		{
		  tempMask[2][0] = 0.0;
		  tempMask[2][1] = 0.0;
		  tempMask[2][2] = 0.0;
		}
	    
	  float weight = 0.0;
	  for(int x = 0; x < 3; x++)
	    {
	      for(int y = 0; y < 3; y++)
		{
		  weight += tempMask[y][x];
		}
	    }
	  for(int x = 0; x < 3; x++)
	    {
	      for(int y = 0; y < 3; y++)
		{
		  tempMask[y][x] = tempMask[y][x]/weight;
		}
	    }
	  
	  float r = 0.0;
	  float g = 0.0;
	  float b = 0.0;
	  for(int x = -1; x < 2; x++)
	    {
	      for(int y = -1; y < 2; y++)
		{
		  if(tempMask[y+1][x+1] != 0)
		    {
		      r += (float)(outputImage(i+x,j+y).r)*tempMask[y+1][x+1];
		      g += (float)(outputImage(i+x,j+y).g)*tempMask[y+1][x+1];
		      b += (float)(outputImage(i+x,j+y).b)*tempMask[y+1][x+1];  
		    }
		}
	    }
	
	  //	  cout << (int)outputImage(i,j).r<<","<<(int)outputImage(i+1,
	  if(r>255)
	    {
	      r = 255;
	    }
	  if(r<0)
	    {
	      r = 0;
	    }
	  tempImage->pixel(i,j).r = (unsigned char)r;

	  if(g > 255)
	    {
	      g = 255;
	    }
	  if(g < 0)
	    {
	      g = 0;
	    }
	  tempImage->pixel(i,j).g = (unsigned char)g;

	  if(b>255)
	    {
	      b = 255;
	    }
	  if(b<0)
	    {
	      b = 0;
	    }
	    tempImage->pixel(i,j).b = (unsigned char)b;
	    }
    }
  outputImage = *tempImage;
  return 1;
}

int Image32::EdgeDetect3X3(Image32& outputImage) const
{
  float mask[3][3] = {{-1.0,-1.0,-1.0},{-1.0,0.0,-1.0},{-1.0,-1.0,-1.0}};
  Image32* tempImage = new Image32();
  tempImage->setSize(outputImage.width(), outputImage.height());
  for( int i = 0; i < outputImage.width(); i++)
    {
      for(int j = 0; j < outputImage.height(); j++)
	{
	  float tempMask[3][3];
	  for(int x = 0; x < 3; x++)
	    {
	      for(int y = 0; y < 3; y++)
		{
		  tempMask[y][x] = mask[y][x];
		}
	    }	    	
	      if(i == 0)
		{
		  tempMask[0][0] = 0.0;
		  tempMask[1][0] = 0.0;
		  tempMask[2][0] = 0.0;
		}
	      if(i == outputImage.width() - 1)
		{
		  tempMask[0][2] = 0.0;
		  tempMask[1][2] = 0.0;
		  tempMask[2][2] = 0.0;
		}
	      if(j == 0)
		{
		  tempMask[0][0] = 0.0;
		  tempMask[0][1] = 0.0;
		  tempMask[0][2] = 0.0;
		}
	      if(j == outputImage.height()-1)
		{
		  tempMask[2][0] = 0.0;
		  tempMask[2][1] = 0.0;
		  tempMask[2][2] = 0.0;
		}
	    
	  float total = 0.0;
	  for(int x = 0; x < 3; x++)
	    {
	      for(int y = 0; y < 3; y++)
		{
		  total += tempMask[y][x];
		}
	    }
	  tempMask[1][1] = -1*total;
	  
	  float r = 0.0;
	  float g = 0.0;
	  float b = 0.0;
	  for(int x = -1; x < 2; x++)
	    {
	      for(int y = -1; y < 2; y++)
		{
		  if(tempMask[y+1][x+1] != 0)
		    {
		      r += (float)(outputImage(i+x,j+y).r)*tempMask[y+1][x+1];
		      g += (float)(outputImage(i+x,j+y).g)*tempMask[y+1][x+1];
		      b += (float)(outputImage(i+x,j+y).b)*tempMask[y+1][x+1];  
		    }
		}
	    }
	
   
	  if(r>255)
	    {
	      r = 255;
	    }
	  if(r<0)
	    {
	      r = 0;
	    }
	  tempImage->pixel(i,j).r = (unsigned char)r;

	  if(g > 255)
	    {
	      g = 255;
	    }
	  if(g < 0)
	    {
	      g = 0;
	    }
	  tempImage->pixel(i,j).g = (unsigned char)g;

	  if(b>255)
	    {
	      b = 255;
	    }
	  if(b<0)
	    {
	      b = 0;
	    }
	    tempImage->pixel(i,j).b = (unsigned char)b;
	    }
    }
  outputImage = *tempImage;
  return 1;
}
int Image32::ScaleNearest(const float& scaleFactor,Image32& outputImage) const
{
  Image32* tempImage = new Image32();
  tempImage->setSize((int)(outputImage.width()*scaleFactor), (int)(outputImage.height()*scaleFactor));
  for(int i = 0; i < tempImage->width(); i++)
    {
      for(int j = 0; j < tempImage->height(); j++)
	{
	  tempImage->pixel(i,j) = outputImage.NearestSample(i/scaleFactor, j/scaleFactor);
	 
	}
    }
  outputImage = *tempImage;
  return 1;
}

int Image32::ScaleBilinear(const float& scaleFactor,Image32& outputImage) const
{
  Image32* tempImage = new Image32();
  tempImage->setSize((int)(outputImage.width()*scaleFactor), (int)(outputImage.height()*scaleFactor));
  for(int i = 0; i < tempImage->width(); i++)
    {
      for(int j = 0; j < tempImage->height(); j++)
	{
	  tempImage->pixel(i,j) = outputImage.BilinearSample(i/scaleFactor, j/scaleFactor);	 
			
	}
    }
    outputImage = *tempImage;
  return 1;
}
			
int Image32::ScaleGaussian(const float& scaleFactor,Image32& outputImage) const
{
  Image32* tempImage = new Image32();
  tempImage->setSize((int)(outputImage.width()*scaleFactor), (int)(outputImage.height()*scaleFactor));
  for(int i = 0; i < tempImage->width(); i++)
    {
      for(int j = 0; j < tempImage->height(); j++)
	{
	  float variance;
	  if(scaleFactor > 1)
	    {
	      variance = 1.0;
	    }
	  else
	    {
	      variance = 1.0/scaleFactor;
	    }
	  float radius = ceil(2.0 * sqrt(variance));
	  tempImage->pixel(i,j) = outputImage.GaussianSample(i/scaleFactor, j/scaleFactor, variance, radius);	 
			
	}
    }
    outputImage = *tempImage;
  return 1;
}

int Image32::RotateNearest(const float& angle,Image32& outputImage) const
{
  Image32* tempImage = new Image32();
  float radian = fmod(angle,360)*PI/180;
  float a = 1;
  float b = 1;
  if(radian > PI/2 && radian < 3*PI/2)
    {
      a = -1;
    }
  if(radian > PI && radian < 2*PI)
    {
      b = -1;
    }
  int width = a * outputImage.width() * cos(radian) + b * outputImage.height() * sin(radian);
  int height = a * outputImage.height() * cos(radian) + b * outputImage.width() * sin(radian);
    
  tempImage->setSize((int)width, (int)height);
  for(int i = 0; i < tempImage->width(); i++)
    {
      for(int j = 0; j < tempImage->height(); j++)
	{
	  float x;
	  float y;
	  if(radian >= 0 && radian < PI/2)
	    {
	      x = i;
	      y = j - outputImage.width() * sin(radian);
	    }
	  if(radian >= PI/2 && radian < PI)
	    {
	      x = i + outputImage.width() * cos(radian);
	      y = j - height;
	    }
	  if(radian >= PI && radian < 3*PI/2)
	    {	     
	      x = i - width;
	      y = j - outputImage.width() * sin(radian) - height;
	    }
	  if(radian >= 3*PI/2 && radian < 2*PI)
	    {
	      x = i + outputImage.width() * cos(radian) - width;
	      y = j;
	    }
	  
	  Pixel32* tempPixel = new Pixel32();
      	  *tempPixel = outputImage.NearestSample((x-y*tan(radian))*cos(radian) , y/cos(radian) + (x-y*tan(radian))*sin(radian));
	  tempImage->pixel(i,j) = *tempPixel;
	}
    }
  outputImage.setSize(width,height);
  outputImage = *tempImage;
  return 1;
}

int Image32::RotateBilinear(const float& angle,Image32& outputImage) const
{
  Image32* tempImage = new Image32();
  float radian = fmod(angle,360)*PI/180;
  float a = 1;
  float b = 1;
  if(radian > PI/2 && radian < 3*PI/2)
    {
      a = -1;
    }
  if(radian > PI && radian < 2*PI)
    {
      b = -1;
    }
  int width = a * outputImage.width() * cos(radian) + b * outputImage.height() * sin(radian);
  int height = a * outputImage.height() * cos(radian) + b * outputImage.width() * sin(radian);
    
  tempImage->setSize((int)width, (int)height);
  for(int i = 0; i < tempImage->width(); i++)
    {
      for(int j = 0; j < tempImage->height(); j++)
	{
	  float x;
	  float y;
	  if(radian >= 0 && radian < PI/2)
	    {
	      x = i;
	      y = j - outputImage.width() * sin(radian);
	    }
	  if(radian >= PI/2 && radian < PI)
	    {
	      x = i + outputImage.width() * cos(radian);
	      y = j - height;
	    }
	  if(radian >= PI && radian < 3*PI/2)
	    {	     
	      x = i - width;
	      y = j - outputImage.width() * sin(radian) - height;
	    }
	  if(radian >= 3*PI/2 && radian < 2*PI)
	    {
	      x = i + outputImage.width() * cos(radian) - width;
	      y = j;
	    }
	  
	  Pixel32* tempPixel = new Pixel32();
      	  *tempPixel = outputImage.BilinearSample((x-y*tan(radian))*cos(radian) , y/cos(radian) + (x-y*tan(radian))*sin(radian));
	  tempImage->pixel(i,j) = *tempPixel;
	}
    }
  outputImage.setSize(width,height);
  outputImage = *tempImage;
  return 1;
}
	
int Image32::RotateGaussian(const float& angle,Image32& outputImage) const
{
  Image32* tempImage = new Image32();
  float radian = fmod(angle,360)*PI/180;
  float a = 1;
  float b = 1;
  if(radian > PI/2 && radian < 3*PI/2)
    {
      a = -1;
    }
  if(radian > PI && radian < 2*PI)
    {
      b = -1;
    }
  int width = a * outputImage.width() * cos(radian) + b * outputImage.height() * sin(radian);
  int height = a * outputImage.height() * cos(radian) + b * outputImage.width() * sin(radian);
    
  tempImage->setSize((int)width, (int)height);
  for(int i = 0; i < tempImage->width(); i++)
    {
      for(int j = 0; j < tempImage->height(); j++)
	{
	  float x;
	  float y;
	  if(radian >= 0 && radian < PI/2)
	    {
	      x = i;
	      y = j - outputImage.width() * sin(radian);
	    }
	  if(radian >= PI/2 && radian < PI)
	    {
	      x = i + outputImage.width() * cos(radian);
	      y = j - height;
	    }
	  if(radian >= PI && radian < 3*PI/2)
	    {	     
	      x = i - width;
	      y = j - outputImage.width() * sin(radian) - height;
	    }
	  if(radian >= 3*PI/2 && radian < 2*PI)
	    {
	      x = i + outputImage.width() * cos(radian) - width;
	      y = j;
	    }
	  
	  Pixel32* tempPixel = new Pixel32();
      	  *tempPixel = outputImage.GaussianSample((x-y*tan(radian))*cos(radian) , y/cos(radian) + (x-y*tan(radian))*sin(radian),1,2);
	  tempImage->pixel(i,j) = *tempPixel;
	}
    }
  outputImage.setSize(width,height);
  outputImage = *tempImage;
  return 1;
}


int Image32::SetAlpha(const Image32& matte)
{
	return 0;
}

int Image32::Composite(const Image32& overlay,Image32& outputImage) const
{
	return 0;
}

int Image32::CrossDissolve(const Image32& source,const Image32& destination,const float& blendWeight,Image32& ouputImage)
{
	return 0;
}
int Image32::Warp(const OrientedLineSegmentPairs& olsp,Image32& outputImage) const
{
	return 0;
}

int Image32::FunFilter(Image32& outputImage) const
{
  int seed = time(NULL);
  srand(seed);
  //  AddRandomNoise(.5,outputImage);
  for(int i = 0; i < outputImage.width()/16; i++)
    {
      for(int j = 0; j < outputImage.height()/16; j++)
	{	  
	  Image32* tempImage = new Image32();
	  tempImage->setSize(16,16);
	  for(int x = 0; x < 16; x++)
	    {
	      for(int y = 0; y < 16; y++)
		{
		  tempImage->pixel(x,y).r = outputImage(i*16+x,j*16+y).r;
		  tempImage->pixel(x,y).g = outputImage(i*16+x,j*16+y).g;
		  tempImage->pixel(x,y).b = outputImage(i*16+x,j*16+y).b;
		}
	    }
	  float random = rand();
	  float angle = 0;
	  if(random > 0.25)
	    {
	      angle = 90.0;
	    }
	  if(random > 0.5)
	    {
	      angle = 180.0;
	    }
	  if(random > 0.75)
	    {
	      angle = 270.0;
	    }
	  RotateNearest(angle,*tempImage);
	  for(int x = 0; x < 16; x++)
	    {
	      for(int y = 0; y < 16; y++)
		{
		  outputImage(i*16+x,j*16+y).r = tempImage->pixel(x,y).g;
		  outputImage(i*16+x,j*16+y).g = tempImage->pixel(x,y).b;
		  outputImage(i*16+x,j*16+y).b = tempImage->pixel(x,y).r;

		}
	    }
	}       
    }
  return 1;
}

int Image32::Crop(const int& x1,const int& y1,const int& x2,const int& y2,Image32& outputImage) const
{
  Image32* tempImage = new Image32();
  tempImage->setSize(abs(x1-x2)+1, abs(y1-y2)+1);
  int widthStart = x1;
  if(x2 < x1)
    {
      widthStart = x2;
    }
  int heightStart = y1;
  if(y2 < y1)
    {
      heightStart = y2;
    }
  for(int i = widthStart; i < widthStart+tempImage->width(); i++)
    {
      for(int j = heightStart; j < heightStart + tempImage->height(); j++)
	{
	  tempImage->pixel(i-widthStart,j-heightStart) = outputImage(i,j);	  
	}
    }
  outputImage = *tempImage;
		
       return 1;
}

Pixel32 Image32::NearestSample(const float& x,const float& y) const
{
  int xcoor = round(x);
  int ycoor = round(y);
  Pixel32* newPixel = new Pixel32();
  newPixel->r = 0;
  newPixel->g = 0;
  newPixel->b = 0;

  if(xcoor >= this->width())
    {
      xcoor = this->width()-1;
    }
  if(xcoor <= 0)
    {
      xcoor = 0;
    }
  if(x > this->width() || x < 0)
    {
      return *newPixel;
    }

  if(ycoor >= this->height())
    {
      ycoor = this->height()-1;
    }
  if(ycoor <= 0)
    {
      ycoor = 0;
    }
  if(y > this->height() || y < 0)
    {
      return *newPixel;
    }
  return this->pixel(xcoor, ycoor);

}

Pixel32 Image32::BilinearSample(const float& x,const float& y) const
{
  Pixel32 *newPixel = new Pixel32();
  newPixel->r = 0;
  newPixel->g = 0;
  newPixel->b = 0;
  if(x > this->width() || x < 0 || y > this->height() || y < 0)
    {
      return *newPixel;
    }

  int x1 = floor(x);
  if(x1 >= this->width())
    {
      x1 = this->width() - 1;
    }
  int x2 = x1 + 1;
  if(x1 == this->width() - 1)
    {
      x2 = x1;
    }
  int y1 = floor(y);
  if(y1 >= this->height())
    {
      y1 = this->height() - 1;
    }
  int y2 = y1 + 1;
  if(y1 == this->height() -1)
    {
      y2 = y1;
    }
  float dx = x - x1;
  float dy = y - y1;
  float ar = this->pixel(x1,y2).r*(1 - dx) + this->pixel(x2,y2).r*(dx);
  float br = this->pixel(x1,y1).r*(1 - dx) + this->pixel(x2,y1).r*(dx);  
  float bilinR = ar * dy + br * (1-dy);
  unsigned char r = (unsigned char)bilinR;
  if(bilinR > 255)
    {
      r = 255;
    }
  else if(bilinR < 0)
    {
      r = 0;
    }

  float ag = this->pixel(x1,y2).g*(1 - dx) + this->pixel(x2,y2).g*(dx);
  float bg = this->pixel(x1,y1).g*(1 - dx) + this->pixel(x2,y1).g*(dx);
  float bilinG = ag * dy + bg * (1-dy);
  unsigned char g = bilinG;
  if(bilinG > 255)
    {
      g = 255;
    }
  else if(bilinG < 0)
    {
      g = 0;
    }
  // cout << (float)(this->pixel(x1,y2).b) << endl;
  float ab = (float)(this->pixel(x1,y2).b)*(1 - dx) + (float)(this->pixel(x2,y2).b)*(dx);
  float bb = this->pixel(x1,y1).b*(1 - dx) + this->pixel(x2,y1).b*(dx);
  float bilinB= ab * dy + bb * (1-dy);
  unsigned char b = (unsigned char)bilinB;
  if(bilinB > 255)
    {
      b = 255;
    }
  else if(bilinB < 0)
    {
      b = 0;
    }

  newPixel->r = r;
  newPixel->g = g;
  newPixel->b = b;
  return *newPixel;
  
}

Pixel32 Image32::GaussianSample(const float& x,const float& y,const float& variance,const float& radius) const
{
  Pixel32* newPixel = new Pixel32();
  float r = 0.0;
  float g = 0.0;
  float b = 0.0;
  int x0 = round(x-radius/2.0);
  int y0 = round(y-radius/2.0);
  float mask[(int)radius][(int)radius];
  float totalWeight = 0.0;
  int count = 0;
  for(int i = x0+1; i < x0 + (int)radius+1; i++)
    {
      for(int j = y0; j < y0 + (int)radius; j++)
	{
	  
	  if(j >= 0 && j < this->height() && i >= 0 && i < this->width())
	    {	    	  	    	      	    
	      float gauss = exp((pow((float)(x-i),2)+pow((float)(y-j),2))/(-2.0*variance));	      		      
	      count++;
	      mask[j-y0][i-x0] = gauss;
	      totalWeight += gauss;	     
	    }
	    else
	      {		
		mask[j-y0][i-x0] = 0.0;		
	      }
	    }
	}    
        
   for(int i = x0+1; i < x0 + (int)radius+1; i++)
    {
      for(int j = y0; j < y0 + (int)radius; j++)
	{
	  if(mask[j-y0][i-x0] != 0.0)	  
	    {
	      r += mask[j-y0][i-x0] * (float)this->pixel(i,j).r / totalWeight;
	      g += mask[j-y0][i-x0] * (float)this->pixel(i,j).g / totalWeight;
	      b += mask[j-y0][i-x0] * (float)this->pixel(i,j).b / totalWeight;
	    }
	}
    }

  if(r > 255)
    {
      r = 255;
    }
  if(r < 0)
    {
      r = 0;
    }
  if(g > 255)
    {
      g = 255;
    }
  if(g < 0)
    {
      g = 0;
    }
  if(b > 255)
    {
      b = 255;
    }
  if(b < 0)
    {
      b = 0;
    }
  
  newPixel->r = (unsigned char)r;
  newPixel->g = (unsigned char)g;
  newPixel->b = (unsigned char)b;
  return *newPixel;
}
