#include <iostream>
#include <string>
#include <Windows.h>
#include <vector>
#include<direct.h>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;






bool CreateFolderInsideDir(string dir, string folderName,string  & outputDir) {
	
	string path = dir+folderName+"//";
	_mkdir(path.c_str());
	outputDir = path;
	return true;
}


bool CreateAListOfPathFromGivenExt(string directory,string extension,vector<string>&nameVector) {
	vector<cv::String> fn;
	glob(directory+"*.jpg", fn, false);
	size_t count = fn.size(); //number of png files in images folder
	cout << count << endl;
	for (size_t i = 0; i < count; i++) {
		nameVector.push_back(fn[i]);
		//nameVector.push_back(imread(fn[i]));
	}
	return true;
}

bool seperateImageNameFromDir(string dir) {
	char sep = '/';
	size_t i = dir.rfind(sep, dir.length());
	if (i != string::npos) {
		return(dir.substr(i + 1, dir.length() - i));
	}

	return true;
}
int main(int argc, char* argv[]) {

	cout << "You have entered " << argc << " arguments:" << "\n";
	//string outputDir = "C:/F/Fahim/";
	string outputDir = " ";
	CreateFolderInsideDir("C:/F/","Fahim", outputDir);
	cout << "new directory:"<<outputDir << endl;
	vector<string> imageList;
	Mat srcImg;
	CreateAListOfPathFromGivenExt(outputDir, ".jpg", imageList);
	for (size_t i = 0; i < imageList.size(); i++) {
		srcImg = imread(imageList[i]);
		string windowName = "Original Image";
		namedWindow(windowName, WINDOW_AUTOSIZE);
		imshow(windowName, srcImg);
		waitKey();
	}

	return 0;
}