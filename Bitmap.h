#ifndef _BITMAP_
#define _BITMAP_

#include <stdio.h>
#include <iostream>
#include <string.h>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

struct Color
{
	unsigned char R, G, B;
};

struct ColorHSV
{
	double H, S, V;			// 0 <= H < 360, 0 <= S <= 1, 0 <= V <= 1
};

struct Bitmap
{
	int width;
	int height;
	int rowSize;
	//unsigned char *pixels;
	vector<unsigned char> pixels;
	vector<vector<Color>> Pixels2D;
	vector<vector<ColorHSV>> Pixels2D_HSV;
};

// Functions in Bitmap.cpp

//int LoadBitmap(const char *fname, Bitmap &bmp);
Bitmap LoadBitmap(string fname);
//int SaveBitmap(const char *fname, const Bitmap &bmp);
int SaveBitmap(string fname, Bitmap &bmp);
//void DisposeBitmap(Bitmap &bmp);

bool SetPixel(Bitmap &bmp, int row, int col, Color color);
bool GetPixel(const Bitmap &bmp, int row, int col, Color &color);

void pixels_to_Pixels2D(Bitmap &bmp);
void Pixels2D_to_pixels(Bitmap &bmp);

void BGR2HSV(Bitmap &bmp);
void HSV2BGR(Bitmap &bmp);

void copyPixels2D(Bitmap &bmp, Bitmap &new_bmp);
void copyPixels2D_HSV(Bitmap &bmp, Bitmap &new_bmp);
// Functions in Effect.cpp

void AdjustBrightness(Bitmap &bmp, double factor, double bright);
Bitmap AdjustSaturation(Bitmap &bmp, double S_val);
void Enlarge(const Bitmap &inbmp, Bitmap &outbmp);
void BGR2Gray(Bitmap &bitmap);
void BGR2Binary(Bitmap &bitmap);

#endif
