#include "Bitmap.h"

int main()
{
	string inFileName("MARBLES.BMP");
	string outFileName("out.bmp");
	Bitmap bmp = LoadBitmap(inFileName);

	
	printf("%dx%d\n", bmp.width, bmp.height);

	Bitmap new_bmp = AdjustSaturation(bmp, 0.3);

	SaveBitmap(outFileName, new_bmp);
		
	printf("Bye!\n");

	return 0;
}
