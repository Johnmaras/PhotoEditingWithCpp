//------------------------------------------------------------
//
// C++ course assignment code 
//
// G. Papaioannou, 2015
//
//

#ifndef _ARRAY_
#define _ARRAY_

namespace math
{

	//---------------------------------------------------------------------------------------------
	// Do NOT modify this section. For the implementation, see comment below the class declaration

	template <typename T>
	class Array
	{
	protected:
		T * buffer;
		unsigned int width, height;

	public:

		unsigned int getWidth() const { return width; }      // returns the width of the image
		unsigned int getHeight() const { return height; }    // returns the height of the image

		void * getRawDataPtr();                              // Obtain a pointer to the internal data
		// This is NOT a copy of the internal image data, but rather 
		// a pointer to the internally allocated space, so DO NOT
		// attempt to delete the pointer. 

		T & operator () (int x, int y);                      // return a reference to the element at position (column x, row y) 
		// of the array (zero-based)

		const T & operator() (int x, int y) const;          // return a reference to the element at position (column x, row y) 
		// of the array (zeor-based)

		Array(unsigned int w, unsigned int h);               // Constructors. No default constructor allowed, as it makes no sense.
		Array(const Array<T> & source);                      //

		Array & operator = (const Array<T> & source);        // Copy assignment operator.

		bool operator == (const Array<T> & source) const;    // returns true if the current array and the source have the same dimensions AND 
															 // one by one their elements of type T are the same. 

		void resize(unsigned int new_width, unsigned int new_height);	// Change the internal data storage size to the new ones.
		// If the one or both of the dimensions are smaller, clip the 
		// by discarding the remaining elements in the rows / columns outside
		// the margins. If the new dimensions are larger, pad the old elements
		// with elements initialized ot their default value (i.e. with their default initializer/constructor).

		virtual ~Array();									 // The destructor

	};

	// This is a templated class so include its implementation in the header file below this line:
	//--------------------------------------------------------------------------------------------
	
	template <typename T> void * Array<T>::getRawDataPtr(){
		return buffer;
	}

	template <typename T> T & Array<T>::operator () (int x, int y){
		return buffer[x * y];
	}

	template <typename T> const T & Array<T>::operator () (int x, int y) const{
		return buffer[x * y];
	}

	template <typename T> Array<T>::Array(unsigned int w, unsigned int h): width(w), height(h), buffer(nullptr){}

	template <typename T> Array<T>::Array(const Array<T> & source) : width(source.width), height(source.height), buffer(source.buffer){	}

	template <typename T> Array<T> & Array<T>::operator = (const Array<T> & source){
		Array<T> left = Array<T>(source);
		return left;
	}

	template <typename T> bool Array<T>::operator == (const Array<T> & source) const{
		if (getWidth() * getHeight() != source->getWidth() * source->getHeight()){
			return false;
		}else{
			for (int i = 0; i < getWidth() * getHeight(); i++){
				if (buffer[i] != source->getRawDataPtr()[i]){
					return false;
				}
			}
		}
		return true;
	}

	template <typename T> void Array<T>::resize(unsigned int new_width, unsigned int new_height){
		//TO BE FILLED!!!
	}

	template <typename T> Array<T>::~Array(){
		delete[] buffer;
	}

} // namespace math

#endif