//
//  extFoo.hpp
//  FaceRecon
//

#ifndef extFoo_hpp
#define extFoo_hpp

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

// plot profile, faces and eyes
void plotHaar (Mat frame, Mat frame_gray, vector<Rect> faces, vector<Rect> eyes, vector<Rect> profiles, string fullPath);

// function used to open the video and detect the people
void detectAndDisplay (VideoCapture stapleVideo, string fullPath);

// function use to open cascades
CascadeClassifier openCascade (string path_cascade);

// open video
VideoCapture openVideo (string videoPath);

void userSetsMode ();

#endif /* extFoo_hpp */
