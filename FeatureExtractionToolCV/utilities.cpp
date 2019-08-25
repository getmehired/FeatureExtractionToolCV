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
	bool statusCreated = false;
	string fullPath = directory + "\\*" + extension;
	WIN32_FIND_DATAA data;
	HANDLE hFind;
	if ((hFind = FindFirstFileA(fullPath.c_str(), &data)) != INVALID_HANDLE_VALUE) {
		do {
			nameVector.push_back(directory + "\\" + data.cFileName);
		} while (FindNextFileA(hFind, &data) != 0);
		FindClose(hFind);
		statusCreated = true;
	}
	return statusCreated;
}


/*
	CreateFolderInsideDir-> create a folder inside the given directory and update the outputPath
	dir -> given dir
	folderName -> new folder name
	outputDir -> updated directory
*/
bool utilities::CreateFolderInsideDir(std::string dir, std::string folderName, std::string & outputDir)
{
	outputDir = dir + "\\" + folderName;
	_mkdir(outputDir.c_str());
	return true;
}

bool utilities::seperateImageNameFromDir(std::string dir, std::string & name)
{
	name = "";
	size_t i = dir.length() - 1;
	while (i >= 0 && dir[i] != '\\') {
		name = dir[i] + name;
		i--;
	}
	int locDot = name.find_last_of(".");
	cout << name << endl;
	if (locDot == -1) {
		return false;
	}
	int fileNameLength = name.length() - 1;
	name.replace(locDot, fileNameLength, "");
	cout << name << endl;
	return true;
}
