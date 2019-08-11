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
	try {
		outputDir = dir + "\\" + folderName;
		_mkdir(outputDir.c_str());
		return true;
	}
	catch (...) { // catch all - if error it means failure
		return false;
	}
}

/*
CreateAListOfPathFromGivenExt - > create path of all the imges from a given directory, image extension and save the path in a vector
directory -> the directory where the images are located
extension -> image extension example:: ".png"
nameVector -> it will hold all the images full reading path
*/
bool CreateAListOfPathFromGivenExt(string& directory, string& extension, vector<string>& nameVector) {
	try {
		glob(directory + "\\*" + extension, nameVector, false); // no clear documentation of this func for c++ win...
	}
	catch (...) { // catch all - if error it means failure
		return false;
	}
	return true;
}

/*
seperateImageNameFromDir - > get the filename from a complete file path
file_path -> the full path where the image is located
file_name -> image name
*/
bool seperateImageNameFromDir(string& file_path, string& file_name) {
	// go backwards until a '/' is reached
	try {
		size_t idx = file_path.length() - 1;
		file_name = "";
		while (idx >= 0 && file_path[idx] != '\\') {
			file_name = file_path[idx] + file_name;
			idx--;
		}
		return true;
	}
	catch (...) { // catch all - if error it means failure
		return false;
	}
}

int main(int argc, char** argv) {

	cout << "You have entered " << argc << " arguments:" << "\n";

	for (int i = 0; i < argc; ++i)
		cout << argv[i] << "\n";

	if (argc == 1) {
		printf("Error: found in input arguments! \n");
		printf("Expected: 1st input argument the directory of images \n");
		printf("Expected: 2nd input argument the extension of the images that need to be processed \n");
		printf("Example c:\\imageDatabase .jpg\n");
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

		string windowName = name;
		namedWindow(windowName, WINDOW_AUTOSIZE);
		imshow(windowName, srcImg);
		key = waitKey();

		if (key == 's') {
			imwrite(updatedFolderDir + "\\" + name + ".png", srcImg);
		}
	}

	return 0;
}