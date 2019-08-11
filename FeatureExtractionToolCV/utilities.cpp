#include "utilities.h"



utilities::utilities()
{



}

utilities::~utilities()
{


}

/*
CreateAListOfPathFromGivenExt - > create path of all the imges from a given directory, image extension and save the path in a vector
directory -> the directory where the images are located
extension -> image extension example:: ".png"
nameVector -> it will hold all the images full reading path
*/
bool utilities::CreateAListOfPathFromGivenExt(std::string directory, std::string extension, std::vector<std::string>& nameVector)
{
	try {
		glob(directory + "\\*" + extension, nameVector, false); // no clear documentation of this func for c++ win...
	}
	catch (...) { // catch all - if error it means failure
		return false;
	}
	return true;
}


/*
	CreateFolderInsideDir-> create a folder inside the given directory and update the outputPath
	dir -> given dir
	folderName -> new folder name
	outputDir -> updated directory
*/
bool utilities::CreateFolderInsideDir(std::string dir, std::string folderName, std::string & outputDir)
{
	try {
		outputDir = dir + "\\" + folderName;
		_mkdir(outputDir.c_str());
		return true;
	}
	catch (...) { // catch all - if error it means failure
		return false;
	}
}

bool utilities::seperateImageNameFromDir(std::string dir, std::string & name)
{
	// go backwards until a '/' is reached
	try {
		size_t idx = dir.length() - 1;
		name = "";
		while (idx >= 0 && dir[idx] != '\\') {
			name = dir[idx] + name;
			idx--;
		}
		return true;
	}
	catch (...) { // catch all - if error it means failure
		return false;
	}
}
