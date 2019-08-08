#include <iostream>
#include <string>
#include <Windows.h>
#include <vector>
#include<direct.h>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;


/*
	CreateFolderInsideDir-> create a folder inside the given directory and update the outputPath
	dir -> given dir
	folderName -> new folder name
	outputDir -> updated directory
	*/
bool CreateFolderInsideDir(string dir, string folderName,string  & outputDir) {

	string path = dir+folderName+"//";
	_mkdir(path.c_str());
	outputDir = path;
	return true;
}

/*
CreateAListOfPathFromGivenExt - > create path of all the imges from a given directory, image extension and save the path in a vector
directory -> the directory where the images are located
extension -> image extension example:: ".png"
nameVector -> it will hold all the images full reading path
*/
bool CreateAListOfPathFromGivenExt(string directory,string extension,vector<string>&nameVector) {
	vector<cv::String> fn;
	glob(directory+"*.png", fn, false);
	size_t count = fn.size(); //number of png files in images folder
	cout << count << endl;
	for (size_t i = 0; i < count; i++) {
		nameVector.push_back(fn[i]);
	}
	return true;
}

bool seperateImageNameFromDir(string dir,string &name) {
	char sep = '/';
	size_t i = dir.rfind(sep, dir.length());
	cout << i << endl;
	if (i != string::npos) {
		name=dir.substr(i + 1, dir.length() - i);
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