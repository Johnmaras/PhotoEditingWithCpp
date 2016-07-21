#include <iostream>
#include <string>
#include <vector>
#include "ppm_format.h"
#include "Image.h"
#include "Filter.h"

using namespace std;
using namespace imaging;
int main(int argc, char* argv[]){

	component_t r = 0, g = 0, b = 0;
	string file, comparestr = "-f", comparestr2 = "color";
	vector<string> filters;
	float *imagedata;
	bool flag = true;

	//προσθέτει σε ένα vector όλα τα ορίσματα(εκτός από την εφαρμογή)
	for (unsigned int i = 1; i < argc; i++){
		filters.push_back(argv[i]);
	}

	//ελέγχει αν έχει δοθεί αρχείο εισόδου εικόνας. Αν βρει αρχείο, αφαιρεί από το vector το τελευταίο όρισμα(το οποίο είναι το path του αρχείου)
	if (flag){
		file = argv[argc - 1];
		int dotfound = file.find_first_of('.');
		if (dotfound <= -1 || file.substr(file.find_first_of('.')).compare(".ppm") != 0){
			std::cout << "No input file has been given!" << endl;
			flag = false;
		}
		else{
			filters.pop_back();
		}
	}

	//αν έχει δοθεί αρχείο εικόνας, δημιουργεί Image αντικείμενο και βρίσκει το average των χρωμάτων των pixel
	if (flag){
		Image * image = new Image();

		if (*image << file){
			std::cout << "Image dimensions are : " << image->getWidth() << "x" << image->getHeight() << endl;
			imagedata = new float[image->getSize() * 3];

			unsigned int x = 0, y = 0;
			for (unsigned int i = 0; i < image->getSize(); i++){
				imagedata[3 * i] = image->getPixel(x, y)[0];

				imagedata[3 * i + 1] = image->getPixel(x, y)[1];

				imagedata[3 * i + 2] = image->getPixel(x, y)[2];


				if (x == image->getWidth() - 1){
					x = 0;
					y++;
				}
				else{
					x++;
				}
			}

			for (int i = 0; i < image->getSize() * 3; i += 3){
				r += imagedata[i];
				g += imagedata[i + 1];
				b += imagedata[i + 2];
			}

			r /= image->getSize();
			g /= image->getSize();
			b /= image->getSize();

			std::cout << "The average color of the image is(" << r << ", " << g << ", " << b << ")" << endl;


			//ελέγχει το vector για τυχόν λάθη στα φιλτρα και ξαναφτιάχνει μέρος του vector(ξεκινώντας από το "κελί" 0) βάζοντας τα ονόματα των φιλτρων που διαβάζει
			string filter;
			flag = false;	//χρησιμεύει στο να ελέγχει πότε ανοίγει ένα φίλτρο(δηλαδή βρίσκει -f στα ορίσματα της εφαρμογής) και πότε 
			//ή αν κλείνει(δηλαδή βρίσκει έγκυρο όνομα φίλτρου)
			int k = -1;
			for (unsigned int i = 0; i < filters.size(); i++){
				if (filters[i].compare(comparestr) == 0){	//αν filters[i] == "-f", υποθέτει πως μετά θα υπάρχει έγκυρο όνομα φίλτρου
					flag = false;
					if ((i + 1) < filters.size()){	//αυτός ο έλεγχος για λάθος στο όνομα φίλτρου πετυχαίνει αν το λάθος είναι στο τελευταίο φίλτρο
						filter = filters[++i];
					}
					else{
						filter = "";
					}
				}
				if (filter.compare(comparestr) == 0 || filter.compare("") == 0){	//αν filter == "-f" ή filter == "", τότε υπάρχει λάθος με το όνομα κάποιου φίλτρου
					std::cout << "Filter name is missing!" << endl;
					flag = false;
					break;
				}else if (filter.compare("gray") == 0){
					filters[++k] = "gray";
					flag = true;
				}else if (filter.compare("color") == 0){
					filters[++k] = "color";
					filters[++k] = filters[++i];
					filters[++k] = filters[++i];
					filters[++k] = filters[++i];
					flag = true;
				}else if (filter.compare("blur") == 0){
					filters[++k] = "blur";
					flag = true;
				}else if (filter.compare("median") == 0){
					filters[++k] = "median";
					flag = true;
				}else if (filter.compare("diff") == 0){
					filters[++k] = "diff";
					flag = true;
				}else{
					std::cout << "Filter name is missing!" << endl;
					flag = false;
					break;
				}
			}


			if (flag){

				//εφαρμόζει τα φίλτρα στην εικόνα
				for (unsigned int i = 0; i <= k; i++){
					if (filters[i].compare("gray") == 0){
						gray(image);
						std::cout << "Gray filter applied" << endl;
					}else if (filters[i].compare("color") == 0){
						r = stof(filters[++i]);

						g = stof(filters[++i]);

						b = stof(filters[++i]);

						imaging::color(image, r, g, b);
						std::cout << "Color filter applied" << endl;
					}else if (filters[i].compare("blur") == 0){
						blur(image);
						std::cout << "Blur filter applied" << endl;
					}else if (filters[i].compare("median") == 0){
						median(image);
						std::cout << "Median filter applied" << endl;
					}else if (filters[i].compare("diff") == 0){
						diff(image);
						std::cout << "Diff filter applied" << endl;
					}
				}

				//γράφει την καινούρια εικόνα
				string copypath = file.substr(0, file.find_first_of('.')) + ".filtered.ppm";
				if (*image >> copypath){
					std::cout << "Image successfully wrote to " << copypath << " file!" << endl;
				}
				else{
					std::cout << "Write failed!" << endl;
				}
			}
		}		
	}

	system("pause");
	return 0;
}