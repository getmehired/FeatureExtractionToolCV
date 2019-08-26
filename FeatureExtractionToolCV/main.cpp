#include <iostream>
#include <string>
#include <Windows.h>
#include <opencv2/opencv.hpp>
#include "utilities.h"

using namespace std;
using namespace cv;


/*
Write this following function for a given image and ranges of min and max -> L , A, B value
it can segment particular color object from the image
*/
Mat runColorSegmentationUsingLAB(Mat * img, int LMin, int LMax, int aMin, int aMax, int bMin, int bMax) {
	Mat imageLab, maskLab, resultLab;
	Scalar minLab, maxLab;
	minLab = Scalar(LMin, aMin, bMin);
	maxLab = Scalar(LMax, aMax, bMax);
	cvtColor(*img, imageLab, COLOR_BGR2HSV);
	inRange(imageLab, minLab, maxLab, maskLab);
	bitwise_and(*img, *img, resultLab, maskLab);
	return resultLab;
}

/*
Write this following function for a given image and ranges of min and max -> H, S, V value
it can segment particular color object from the image
*/
Mat runColorSegmentationUsingHSV(Mat * img, int HMin, int HMax, int SMin, int SMax, int VMin, int VMax) {
	Mat imageHSV, maskHSV, resultHSV;
	Scalar minHSV, maxHSV;
	minHSV = Scalar(HMin, SMin, VMin);
	maxHSV = Scalar(HMax, SMax, VMax);
	cvtColor(*img, imageHSV, COLOR_BGR2HSV);
	inRange(imageHSV, minHSV, maxHSV, maskHSV);
	bitwise_and(*img, *img, resultHSV, maskHSV);
	return resultHSV;
}


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
		//imshow("HSV", runColorSegmentationUsingHSV(srcImg, 46, 95, 156, 255, 99, 181)); //range given in the HW pdf
		/*
			- analysis using HSV value range (in GIMP pointer information)
			- HSV values conversion from GIMP to openCV:
				- opencvH = gimpH / 2
				- opencvS = (gimpS / 100) * 255
				- opencvV = (gimpV / 100) * 255
		*/
		imshow("HSV", runColorSegmentationUsingHSV(&srcImg, 54, 67, 168, 231, 63, 158));
		imshow("LAB", runColorSegmentationUsingLAB(&srcImg, 82, 115, 52, 118, 137, 203)); //range given in the HW pdf
		key = waitKey();

		if (key == 's') {
			imwrite(updatedFolderDir + "\\" + name + ".png", srcImg);
		}
	}

	return 0;
}