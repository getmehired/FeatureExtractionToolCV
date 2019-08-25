#pragma once
#include <string>
#include <vector>
#include <Windows.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <direct.h>

using namespace std;
using namespace cv;





class utilities {
private:


public:


	utilities();
	virtual ~utilities();
	bool CreateAListOfPathFromGivenExt(std::string directory, std::string extension, std::vector<std::string>& nameVector);
	bool CreateFolderInsideDir(std::string dir, std::string folderName, std::string &outputDir);
	bool seperateImageNameFromDir(std::string dir, std::string &name);




};