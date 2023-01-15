#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <time.h>
using namespace std;

void wipe_cr_in_file(const string&);

main(int argc, char** argv) {
	vector<string> filenames;
	// bool flagQuiet = false;

	srand(time(NULL));

	// Process the args, the 0 is the executable's absolulte path
	for (int i = 1; i < argc; i++) {
		if(argv[i][0] == '-') {
			// Process the flag settings
			const char* str_ptr = argv[i] + 1;
			while (*str_ptr) {
				switch (*str_ptr) {
					// case 'q': case 'Q': flagQuiet = true; break; // This is how to do it
					default:
						// Unknown flag
						;
				}
				str_ptr++;
			}
			continue;
		}
		else {
			filenames.push_back(argv[i]);
		}
	}

	if (filenames.size() > 0) {
		for (unsigned int i = 0; i < filenames.size(); i++) {
			const string& filename = filenames[i];
			wipe_cr_in_file(filename);
		}
	}

	return 0;
}

void wipe_cr_in_file(const string& filename) {
	char itoabuffer[50];
	string filename2 = filename + "_______" + itoa(rand(), itoabuffer, 10);

	const char* filename_cstr = filename.c_str();
	const char* filename2_cstr = filename2.c_str();

	ifstream in(filename_cstr, std::ios::binary);

	if (in) {
		ofstream out(filename2_cstr, std::ios::binary);
		char charv;
		char charv2;
		while (in.read(&charv, 1)) {
			if (charv == 13) {
				if (in.read(&charv2, 1)) {
					if (charv2 != 10) { out.write(&charv, 1); }
					out.write(&charv2, 1);
				}
				else {
					out.write(&charv, 1);
				}
			}
			else {
				out.write(&charv, 1);
			}
		}
		out.close();
		in.close();

		// TODO: add sanity check!

		std::remove(filename_cstr);
		std::rename(filename2_cstr, filename_cstr);
	}
}