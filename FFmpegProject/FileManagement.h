#ifndef _FILEMANAGEMENT_H_
#define _FILEMANAGEMENT_H_


#include <iostream>
#include <fstream>



class FileManagement
{
public:
	FileManagement() {
		std::ofstream fout;
		fout.open("TestingFile.txt");
	}
	FileManagement(const char * fileName) {
		std::ofstream fout;
		fout.open(fileName);
	}
private:

};


#endif