//
//  CascFiles.hpp
//  FaceRecon
//

#ifndef CascFiles_hpp
#define CascFiles_hpp

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

class CascFiles {
private:
    // cascades paths
    string pathToCascadesDir;
    
    string path_face_cascade;
    string path_eyes_cascade;
    string path_profile_cascade;
    
    CascadeClassifier face_cascade;
    CascadeClassifier eyes_cascade;
    CascadeClassifier profile_cascade;
    
    RNG rng;        // random number generator
    
public:
    // constructor(s)
    CascFiles();
    CascFiles(string _pathToCascadesDir);
    
    // methods
    void setAllCascades ();
    CascadeClassifier getCascade (int _cascadeType);
};

#endif /* CascFiles_hpp */
