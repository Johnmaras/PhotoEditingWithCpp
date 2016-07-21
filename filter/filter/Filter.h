//------------------------------------------------------------
//
// C++ course assignment code 
//
// G. Papaioannou, 2014
//
//
//-------------------------------------------------------------

#ifndef _FILTER
#define _FILTER

#include "Image.h"
#include <algorithm>

namespace imaging{
	class Filter{
	public:

		void gray(Image * image);
		void color(Image * image, component_t r, component_t g, component_t b);
		void blur(Image * image);
		void median(Image * image);
		void diff(Image * image);

		Filter(){};
		virtual ~Filter(){};
	};

	void gray(Image * image){

		Vec3<component_t> graypixel = Vec3<component_t>();
		unsigned int x = 0, y = 0;
		for (unsigned int i = 0; i < image->getSize(); i++){
			
			graypixel = Vec3<component_t>((image->getPixel(x, y)[0] + image->getPixel(x, y)[1] + image->getPixel(x, y)[2]) / 3);

			image->setPixel(x, y, graypixel);

			if (x == image->getWidth() - 1){
				x = 0;
				y++;
			}else{
				x++;
			}

		}
	}

	void color(Image * image, component_t r, component_t g, component_t b){

		Vec3<component_t> colorpixel = Vec3<component_t>();
		unsigned int x = 0, y = 0;
		for (unsigned int i = 0; i < image->getSize(); i++){

			colorpixel = Vec3<component_t>(image->getPixel(x, y)[0] * r, image->getPixel(x, y)[1] * g, image->getPixel(x, y)[2] * b);

			image->setPixel(x, y, colorpixel);

			if (x == image->getWidth() - 1){
				x = 0;
				y++;
			}
			else{
				x++;
			}

		}
	}

	void blur(Image * image){

		Vec3<component_t> blurpixel = Vec3<component_t>();
		Vec3<component_t> *tempbuffer = new Vec3<component_t>[image->getSize()];
		memcpy(tempbuffer, image->getRawDataPtr(), image->getSize() * sizeof(Vec3<component_t>));

		component_t r, g, b;

		unsigned int x = 0, y = 0, width = image->getWidth(), height = image->getHeight(), k;
		int m, n;
		for(unsigned int i = 0; i < image->getSize(); i++){

			m = -1,	n = -1, k = 0, r = 0, g = 0, b = 0;
			for(unsigned int j = 0; j < 9; j++){
				
				if ((x - m >= 0) && (x - m < width) && (y - n >= 0) && (y - n < height)){
					
					k++;

					r += tempbuffer[(y - n) * width + (x - m)][0];
					g += tempbuffer[(y - n) * width + (x - m)][1];
					b += tempbuffer[(y - n) * width + (x - m)][2];
				}

				if (m < 1){
					m++;
				}else{
					m = -1;
					n++;
				}

			}//for inside

			blurpixel = Vec3<component_t>(r / k, g / k, b / k);
			image->setPixel(x, y, blurpixel);

			if (x == width - 1){
				x = 0;
				y++;
			}
			else{
				x++;
			}
		}//for outside

		delete[] tempbuffer;
	}

	void median(Image * image){

		component_t * red = new component_t[9];
		component_t * green = new component_t[9];
		component_t * blue = new component_t[9];

		Vec3<component_t> medianpixel = Vec3<component_t>();
		Vec3<component_t> *tempbuffer = new Vec3<component_t>[image->getSize()];
		memcpy(tempbuffer, image->getRawDataPtr(), image->getSize() * sizeof(Vec3<component_t>));

		component_t r, g, b;

		unsigned int x = 0, y = 0, width = image->getWidth(), height = image->getHeight(), k;
		int m, n;
		for (unsigned int i = 0; i < image->getSize(); i++){

			m = -1, n = -1, k = 0, r = 0, g = 0, b = 0;
			for (unsigned int j = 0; j < 9; j++){

				if ((x - m >= 0) && (x - m < width) && (y - n >= 0) && (y - n < height)){

					k++;
					red[k] = tempbuffer[(y - n) * width + (x - m)][0];
					green[k] = tempbuffer[(y - n) * width + (x - m)][1];
					blue[k] = tempbuffer[(y - n) * width + (x - m)][2];
				}

				if (m < 1){
					m++;
				}
				else{
					m = -1;
					n++;
				}

			}//for inside
			sort(red, red + k);
			sort(green, green + k);
			sort(blue, blue + k);
			medianpixel = Vec3<component_t>(red[k / 2], green[k / 2], blue[k / 2]);
			image->setPixel(x, y, medianpixel);

			if (x == width - 1){
				x = 0;
				y++;
			}
			else{
				x++;
			}
		}//for outside

		delete[] red;
		delete[] green;
		delete[] blue;

		delete[] tempbuffer;
	}

	void diff(Image * image){

		component_t minr, ming, minb, maxr, maxg, maxb;
		component_t r, g, b;
		unsigned int x = 0, y = 0, width = image->getWidth(), height = image->getHeight();
		int m, n;

		Vec3<component_t> diffpixel = Vec3<component_t>();

		Vec3<component_t> *tempbuffer = new Vec3<component_t>[image->getSize()];

		memcpy(tempbuffer, image->getRawDataPtr(), image->getSize() * sizeof(Vec3<component_t>));

		for (unsigned int i = 0; i < image->getSize(); i++){

			minr = 1, ming = 1, minb = 1, maxr = 0, maxg = 0, maxb = 0;
			m = -1, n = -1;
			for (unsigned int j = 0; j < 9; j++){

				if ((x - m >= 0) && (x - m < width) && (y - n >= 0) && (y - n < height)){

					r = tempbuffer[(y - n) * width + (x - m)][0];
					g = tempbuffer[(y - n) * width + (x - m)][1];
					b = tempbuffer[(y - n) * width + (x - m)][2];

					if (r < minr){
						minr = r;
					}else if (r > maxr){
						maxr = r;
					}

					if (g < ming){
						ming = g;
					}else if (g > maxg){
						maxg = g;
					}

					if (b < minb){
						minb = b;
					}else if (b > maxb){
						maxb = b;
					}
				}

				if (m < 1){
					m++;
				}else{
					m = -1;
					n++;
				}

			}//for inside
			
			diffpixel = Vec3<component_t>(maxr - minr, maxg - ming, maxb - minb);

			image->setPixel(x, y, diffpixel);

			if (x == width - 1){
				x = 0;
				y++;
			}
			else{
				x++;
			}
		}//for outside

		delete[] tempbuffer;
	}


}
#endif