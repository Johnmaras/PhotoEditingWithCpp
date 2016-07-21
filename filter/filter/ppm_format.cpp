#include <iostream>
#include <fstream>
#include <string>
#include "ppm_format.h"

using namespace std;
using namespace imaging;

namespace imaging{

	Image * ReadPPM(const char* filename){

		Image * newimage = nullptr;

		int div, space, size, size2, size3 = 0;
		int x = 1;
		unsigned int width, height;

		component_t *datafloat = nullptr;
		unsigned char *datachar = nullptr;

		string st, st2, head;

		bool flag = true;

		ifstream file(filename, ios::in | ios::binary | ios::ate);

		if (file.is_open()) {

			size = file.tellg();
			datachar = new unsigned char[size];
			file.seekg(0, ios::beg);

			file.read((char*)datachar, size);
			file.seekg(0, ios::beg);

			getline(file, st);
			while ((!st.empty()) && (x <= 4) && flag){

				space = st.find_first_of(' ');
				if (space != -1){
					st2 = st.substr(0, space);
					st = st.substr(space + 1);
				}else{
					st2 = st;
					
					getline(file, st);
				}
				switch (x){
				case 1:
					if (st2 != "P6"){
						cout << "File is not in P6 format!" << endl;
						flag = false;
					}else{
						head = "P6\n";
					}
					break;
				case 2:
					width = stoi(st2);
					head += to_string(width) + "\n";
					break;
				case 3:
					height = stoi(st2);
					head += to_string(height) + "\n";
					break;
				case 4:
					if (st2 != "255"){
						cout << "Error on pixel max value" << endl;
						flag = false;
					}else{
						div = stoi(st2);
						head += to_string(div) + "\n";
					}
					break;
				}
				x++;
			}
			size3 = head.size();
			if (flag){
				size2 = size - size3;
				datafloat = new component_t[size2];
				for (int i = 0; i < size2; i++){
					datafloat[i] = datachar[i + size3] / (float)div;
				}
				newimage = new Image(width, height, datafloat);
			}
		}else{
			cout << "File not found!" << endl;
		}
		
		file.close();

		return newimage;
	}

	bool WritePPM(Image & image, const char * filename){

		//διαγράφει το filename, αν υπάρχει ήδη, και δημιουργεί ένα καινούριο
		if(remove(filename) == 0){
			cout << endl << filename << " already exists, but I will overwrite it!" << endl;
		}
		ofstream filecopy(filename, ios::out | ios::app | ios::binary);

		if (filecopy.is_open()){
			string head = "P6\n";
			unsigned char *datachar = new unsigned char[image.getWidth() * image.getHeight() * 3];
			unsigned int x = 0, y = 0;
			for (unsigned int i = 0; i < image.getSize(); i++){
				datachar[3 * i] = image.getPixel(x, y)[0] * 255;
				
				datachar[3 * i + 1] = image.getPixel(x, y)[1] * 255;
				
				datachar[3 * i + 2] = image.getPixel(x, y)[2] * 255;

				if (x == image.getWidth() - 1){
					x = 0;
					y++;
				}else{
					x++;
				}
			}

			head += to_string(image.getWidth()) + "\n" + to_string(image.getHeight());
			head += "\n255\n";

			filecopy.write(head.c_str(), head.size());
			filecopy.write((char*)datachar, image.getSize() * 3);

			return true;
		}else{
			return false;
		}
	}
}