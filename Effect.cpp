﻿#include "Bitmap.h"

void Enlarge(const Bitmap &inbmp, Bitmap &outbmp)
{
	outbmp.width = 2 * inbmp.width;
	outbmp.height = 2 * inbmp.height;
	outbmp.rowSize = ((3 * outbmp.width + 3) / 4) * 4;
	outbmp.pixels.resize(outbmp.rowSize * outbmp.height);
	for (int row = 0; row < inbmp.height; row++)
		for (int col = 0; col < inbmp.width; col++)
		{
			Color color;
			GetPixel(inbmp, row, col, color);
			SetPixel(outbmp, 2 * row, 2 * col, color);
			SetPixel(outbmp, 2 * row, 2 * col + 1, color);
			SetPixel(outbmp, 2 * row + 1, 2 * col, color);
			SetPixel(outbmp, 2 * row + 1, 2 * col + 1, color);
		}
}

void AdjustBrightness(Bitmap &bmp, double factor, double bright)
{
	//bright: độ sáng
	for (int row = 0; row < bmp.height; row++)
		for (int col = 0; col < bmp.width; col++)
		{
			Color color;
			GetPixel(bmp, row, col, color);

			if (color.R*factor + bright> 255)
				color.R = 255;
			else
				color.R = color.R*factor + bright;

			if (color.G*factor + bright > 255)
				color.G = 255;
			else
				color.G = color.G*factor + bright;

			if (color.B*factor + bright > 255)
				color.B = 255;
			else
				color.B = color.B*factor + bright;

			SetPixel(bmp, row, col, color);
		}
}

//void AdjustSaturation(const Bitmap &bmp, double factor)
Bitmap AdjustSaturation(Bitmap &bmp, double S_val)
{
	Bitmap new_bmp;
	new_bmp.height = bmp.height;
	new_bmp.width = bmp.width;
	new_bmp.rowSize = bmp.rowSize;

	if (bmp.Pixels2D_HSV.empty())
		BGR2HSV(bmp);
	copyPixels2D_HSV(bmp, new_bmp);

	for (int row = 0; row < new_bmp.height; row++)
		for (int col = 0; col < new_bmp.width; col++)
			new_bmp.Pixels2D_HSV[row][col].S = S_val;

	HSV2BGR(new_bmp);
	Pixels2D_to_pixels(new_bmp);

	return new_bmp;
}

void BGR2Gray(Bitmap &bitmap)
{
	for (int row = 0; row < bitmap.height; row++)
	{
		for (int col = 0; col < bitmap.width; col++)
		{
			Color color;
			GetPixel(bitmap, row, col, color);
			//cường độ sáng tại điểm ảnh (row, col)
			int I = 0.114 * color.B + 0.587 * color.G + 0.299 * color.R;
			color.B = color.G = color.R = I;
			SetPixel(bitmap, row, col, color);
		}
	}
}

//tính giá trị ngưỡng nhị phân
double adaptiveThreshold(Bitmap bitmap)
{
	int sum = 0;
	for (int row = 0; row < bitmap.height; row++)
		for (int col = 0; col < bitmap.width; col++)
		{
			int offset = (bitmap.height - 1 - row)*bitmap.rowSize + col * 3;
			sum += bitmap.pixels[offset];
		}
	return sum * 1.0 / (bitmap.height*bitmap.width);
}

void BGR2Binary(Bitmap &bitmap)
{
	BGR2Gray(bitmap);
	double T = adaptiveThreshold(bitmap);			//T là ngưỡng nhị phân
	for (int row = 0; row < bitmap.height; row++)
		for (int col = 0; col < bitmap.width; col++)
		{
			Color color;
			GetPixel(bitmap, row, col, color);

			int bin = 0;
			if (color.R > T)
				bin = 255;

			color.B = color.G = color.R = bin;
			SetPixel(bitmap, row, col, color);
		}
}