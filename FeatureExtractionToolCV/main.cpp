#include <iostream>
#include <string>
#include <Windows.h>
#include <vector>
#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <opencv2/core/utils/filesystem.hpp>

using namespace std;
using namespace cv;


/*
	CreateFolderInsideDir-> create a folder inside the given directory and update the outputPath
	dir -> given dir
	folderName -> new folder name
	outputDir -> updated directory
*/

bool CreateFolderInsideDir(String inputDir, String folderName, string& outDir) {

	String newOutDir = inputDir + folderName;
	cv::utils::fs::createDirectory(newOutDir);
	outDir = newOutDir;
	cout << "Updated output folder name: " << outDir << endl;
	return true;
}

/*
CreateAListOfPathFromGivenExt - > create path of all the images from a given directory, image extension and save the path in a vector
directory -> the directory where the images are located
extension -> image extension example:: ".png"
nameVector -> it will hold all the images full reading path
*/
bool CreateAListOfPathFromGivenExt(String imgDir, String imgExt, vector<string>& nameVector) {
	vector<cv::String> imagesList;
	//Search for all the image pathnames matching this pattern: imgDir + .png
	//to be included in the vector imagesList, otherwise false 
	glob(imgDir + "\\*" + imgExt, imagesList, false);
	cout << imgDir + "\\*" + imgExt << endl;
	//Check count of the files within imagesList
	size_t cnt = imagesList.size();
	cout << "Number of images: " << cnt << endl;
	//Loop through the imagesList and add each of them to the nameVector
	for (size_t i = 0; i < cnt; i++) {
		nameVector.push_back(imagesList[i]);
		cout << "Image filepath name: " << nameVector[i] << endl;
	}

	return true;
}

bool seperateImageNameFromDir(String imgDir, String& imgName) {
	char sep = '/';
#ifdef _WIN32
	sep = '\\';
#endif

	size_t s = imgDir.rfind(sep, imgDir.length());
	if (s != string::npos) {
		String rawName = imgDir.substr(s + 1, imgDir.length() - s);

		size_t lastindex = rawName.find_last_of(".");
		imgName = rawName.substr(0, lastindex);

		cout << "Image name: " << imgName << endl;
	}

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
	error2 = CreateFolderInsideDir(inputDir, "_saved", updatedFolderDir);
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
		//it will take each directory from the vector and seperate the name of the image from the direcory
		// example :
		// a directory : C:\Users\mimtiaz\visualStudio17Projects\getMeHired\computerVision\standredImages\baboon.bmp
		//the seperateImageNameFromDir() function will seperate the baboon.bmp name from the main direcorty and put them in name variable
		seperateImageNameFromDir(imageList[i], name);
		string windowName = "Original Image";
		namedWindow(windowName, WINDOW_AUTOSIZE);
		imshow(windowName, srcImg);
		key = waitKey();
		if (key == 's') {
			String saveDir = updatedFolderDir + "\\" + name + ".bmp";
			cout << "Image saved here: " << saveDir << endl;
			imwrite(saveDir, srcImg);
		}
	}




	return 0;
}