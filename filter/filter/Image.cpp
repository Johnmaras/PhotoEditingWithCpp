//------------------------------------------------------------
//
// C++ course assignment code 
//
// G. Papaioannou, 2015
//
//
#include <iostream>
#include "Array.h"
#include "Serializable.h"
#include "Vec3.h"
#include "Image.h"
#include "ppm_format.h"

using namespace std;
using namespace math;
using namespace imaging;

// We put every class or function associated with the image storage, compression and manipulation 
// in the "imaging" namespace
namespace imaging{

	//------------------------------------ class Image ------------------------------------------------
	// 
	// It is the class that represents a generic data container for an image. It holds the actual buffer
	// of the pixel values and provides methods for accessing them either as individual pixels or as
	// a memory block. The Image class alone does not provide any functionality for loading and storing an image, as
	// it is the result or input to such a procedure. 
	//
	// The internal buffer of an image object stores the actual bytes (data) of the color image as
	// a contiguous sequence of RGB triplets. Hence, the size of the buffer variable holding these data is
	// 3 X width X height bytes.
	Vec3<component_t> Image::getPixel(unsigned int x, unsigned int y) const{
		Vec3<component_t> vec = Vec3<component_t>();
			if((x < width) && (y < height) && (x*y >= 0)){
				return buffer[y * width + x];
			}else{
				return vec;
			}
		}															// get the color of the image at location (x,y)
																	// Do any necessary bound checking. Also take into account
																	// the "interleaved" flag to fetch the appropriate data
																	// Return a black (0,0,0) color in case of an out-of-bounds
																	// x,y pair

		// data mutators
		void Image::setPixel(unsigned int x, unsigned int y, Vec3<component_t> & value){
			if ((x < width) && (y < height) && (x * y >= 0)){
				buffer[y * width + x][RED] = value[RED];
				buffer[y * width + x][GREEN] = value[GREEN];
				buffer[y * width + x][BLUE] = value[BLUE];
			}
			else{
				cout << "Width or heigth out of bounds!" << endl;
			}
		}

		int Image::getSize() const{
			return width * height;
		}

		// Set the RGB values for an (x,y) pixel. Do all 
		// necessary bound checks and respect the "interleaved"
		// flag when updating our data.
		void Image::setData(const component_t * & data_ptr){
			int size = getSize();
			buffer = new Vec3<component_t>[size];
			Vec3<component_t> newvec;
			unsigned int k = 0;
			for (unsigned int i = 0; i < size; i++){
				newvec = Vec3<component_t>();
				newvec[RED] = data_ptr[k + RED];
				newvec[GREEN] = data_ptr[k + GREEN];
				newvec[BLUE] = data_ptr[k + BLUE];
				buffer[i] = newvec;
				k += 3;
			}
		}
		// Copy the data from data_ptr to the internal buffer.
		// The function ASSUMES a proper size for the incomming data array.
		void Image::resize(unsigned int new_width, unsigned int new_height){
			/*to be filled!!!*/
		}
		// Change the internal data storage size to the new ones.
		// If the one or both of the dimensions are smaller, clip the 
		// by discarding the remaining pixels in the rows / columns outside
		// the margins. If the new dimensions are larger, pad the old pixels
		// with zero values (black color).

		bool Image::operator << (string filename){
			Image * test = ReadPPM(filename.c_str());
			if(test == nullptr){
				return false;
			}else{
				*this = *test;
				return true;
			}
		}

		bool Image::operator >> (string filename){
			return WritePPM(*this, filename.c_str());
		}

		// constructors and destructor
		Image::Image() : Array(0, 0){
			buffer = nullptr; 
		}	// default: zero dimensions, nullptr for the buffer.	
		
		Image::Image(unsigned int _width, unsigned int _height) : Array(0, 0){
			width = _width;
			height = _height;
			buffer = nullptr;
		}

		Image::Image(unsigned int _width, unsigned int _height, const component_t * data_ptr = nullptr) : Array(0, 0){
			width = _width;
			height = _height;
			setData(data_ptr);
		}

		Image::Image(const Image &src) : Array(src.width, src.height){
			buffer = new Vec3<component_t>[getSize()];
			memcpy(buffer, src.buffer, getSize() * sizeof(Vec3<component_t>));
		}
		
		Image::~Image(){}

		Image & Image::operator = (const Image & right){
			if (buffer) {
				delete[] buffer;
			}

			width = right.width;
			height = right.height;
			buffer = new Vec3<component_t>[getSize()];

			memcpy(buffer, right.buffer, getSize() * sizeof(Vec3<component_t>));

			return *this;
		}

} //namespace imaging