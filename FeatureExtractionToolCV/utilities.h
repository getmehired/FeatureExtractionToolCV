#pragma once
#include <string>
#include <vector>
#include <Windows.h>
#include <direct.h>
#include <iostream>
#include <opencv2/opencv.hpp>

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