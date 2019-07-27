//
//  VidMan.hpp
//  FaceRecon
//

#ifndef VidMan_hpp
#define VidMan_hpp

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "CascFiles.hpp"

using namespace std;
using namespace cv;

class VidMan {
private:
    Mat frame;
    Mat frame_gray;
    vector<Rect> faces;
    vector<Rect> profiles;
    vector<Rect> eyes;
    string fullPath;
    
    CascFiles casc;
    
public:
    // constructor(s)
    VidMan();
    VidMan(string _fullPath, CascFiles _casc);
    
    // methods
    void playVideo();
    void plotHaar(CascadeClassifier faceCasc, CascadeClassifier eyesCasc, CascadeClassifier profileCasc);
    
};

#endif /* VidMan_hpp */
