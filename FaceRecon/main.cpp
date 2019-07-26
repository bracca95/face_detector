//
//  main.cpp
//  FaceRecon
//

#include "extFoo.hpp"

// if the user wants to operate over camera flux
string camera = "Camera";

// header
void printUsage ();

int main(int argc, const char * argv[]) {
    
    // main operation: use either camera or videoFullPath, depending on the application
    VideoCapture cap;
    detectAndDisplay(cap, camera);

    return 0;
}

// print usage function
void printUsage () {
    cout << "Sample usage: " << endl
    << "(1) ./target -vf='/path/to/video/file.mp4' " << "-gt='/path/to/groundtruth.txt' " << endl
    << "(2) ./target -vf='/path/to/video/file.mp4'" << endl;
}
