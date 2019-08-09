#include <iostream>
#include <string>
#include <Windows.h>
#include <opencv2/opencv.hpp>
#include "utilities.h"

using namespace std;
using namespace cv;



int main(int argc, char** argv) {

	//Checking number of different argumnets
	cout << "You have entered " << argc << " arguments:" << "\n";

	for (int i = 0; i < argc; ++i)
		cout << argv[i] << "\n";

	//Throwing out the argumnet expectations
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

	//Initializing the utilities object
	utilities utl;


	//creating list of images with given ext
	error1 = utl.CreateAListOfPathFromGivenExt(inputDir, ext, imageList);

	if (!error1) {
		printf("Failed during the task of retriving list of images from a folder\n");
		return 0;
	}

	//Creating a folder for saving processed output
	error2 = utl.CreateFolderInsideDir(inputDir, "savedImages", updatedFolderDir);


	if (!error2) {
		printf("Failed during the task of creating output processed folders\n");
		return 0;
	}

	cv::Mat srcImg;
	char key;

	//looping through the imageList vector
	for (int i = 0; i < imageList.size(); i++) {
		srcImg = imread(imageList[i], IMREAD_COLOR);

		if (srcImg.empty()) {
			printf("Error while reading images\n");
			printf("Invalid image directory\n");
			return 0;
		}


		utl.seperateImageNameFromDir(imageList[i], name);
		//seperateImageNameFromDir(imageList[i], name);

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