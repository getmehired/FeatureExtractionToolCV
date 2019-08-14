#include <iostream>
#include <string>
#include <Windows.h>
#include <vector>
#include <opencv2/opencv.hpp>
#include <direct.h>

using namespace std;
using namespace cv;




/*
	CreateFolderInsideDir-> create a folder inside the given directory and update the outputPath
	dir -> given dir
	folderName -> new folder name
	outputDir -> updated directory
*/

bool CreateFolderInsideDir(string& dir, string folderName, string& outputDir) {
	outputDir = dir + "\\" + folderName;
	_mkdir(outputDir.c_str());
	return true;
}

/*
CreateAListOfPathFromGivenExt - > create path of all the imges from a given directory, image extension and save the path in a vector
directory -> the directory where the images are located
extension -> image extension example:: ".png"
nameVector -> it will hold all the images full reading path
*/
bool CreateAListOfPathFromGivenExt(string directory, string extension, vector<string>& nameVector) {
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

bool seperateImageNameFromDir(string dir, string& fileName) {
	fileName = "";
	size_t i = dir.length() - 1;
	while (i >= 0 && dir[i] != '\\') {
		fileName = dir[i] + fileName;
		i--;
	}
	int locDot = fileName.find_last_of(".");
	cout << fileName << endl;
	if (locDot == -1) {
		return false;
	}
	int fileNameLength = fileName.length() - 1;
	fileName.replace(locDot, fileNameLength, "");
	cout << fileName << endl;
	return true;
}

int main(int argc, char** argv) {

	cout << "You have entered " << argc << " arguments:" << "\n";

	for (int i = 0; i < argc; ++i)
		cout << argv[i] << "\n";

	if (argc == 1) {
		printf("Error: found in input arguments! \n");
		printf("Expected: 1st input argument the directory of images \n");
		printf("Expected: 2nd input argument the extension of the images that need to be processed \n");
		printf("Example c:\imageDatabase .jpg\n");
		return 0;
	}

	string inputDir = argv[1];
	string ext = argv[2];
	string updatedFolderDir, name;
	vector<string> imageList;
	bool error1 = false, error2 = false;

	
	//it will find all the images with the given extension and list them in the vector imageList
	error1 = CreateAListOfPathFromGivenExt(inputDir, ext, imageList);
	if (!error1) {
		printf("Failed during the task of retriving list of images from a folder\n");
		return 0;
	}

	//it will use the given directory and create another folder named savedImages
	error2 = CreateFolderInsideDir(inputDir, "savedImages", updatedFolderDir);

	if (!error2) {
		printf("Failed during the task of creating output processed folders\n");
		return 0;
	}

	cv::Mat srcImg;
	char key;

	for (int i = 0; i < imageList.size(); i++) {
		srcImg = imread(imageList[i], IMREAD_COLOR);

		if (srcImg.empty()) {
			printf("Error while reading images\n");
			printf("Invalid image directory\n");
			return 0;
		}

		//it will take each directory from the vector and seperate the name of the imge from the direcory
		// example :
		// a directory : C:\Users\mimtiaz\visualStudio17Projects\getMeHired\computerVision\standredImages\baboon.bmp
		//the seperateImageNameFromDir() function will seperate the baboon.bmp name from the main direcorty and put them in name variable
		seperateImageNameFromDir(imageList[i], name);

		string windowName = "Original Image";
		namedWindow(windowName, WINDOW_AUTOSIZE);
		imshow(windowName, srcImg);
		key = waitKey();

		if (key == 's') {
			imwrite(updatedFolderDir + "\\" + name + ".png", srcImg);
		}
	}
	


	return 0;
}