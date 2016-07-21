//------------------------------------------------------------
//
// C++ course assignment code 
//
// G. Papaioannou, 2015
//
//
//-------------------------------------------------------------

#ifndef _PPM
#define _PPM

#include "Image.h"


namespace imaging
{

	Image * ReadPPM(const char * filename);
	bool WritePPM(Image & image, const char * filename);
	void clearImage(Image * image);

} //namespace imaging

#endif