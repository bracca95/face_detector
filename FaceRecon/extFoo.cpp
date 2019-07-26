//
//  extFoo.cpp
//  FaceRecon
//

#include "extFoo.hpp"

/* global variables */

// cascades paths
string pathToCascadesDir = "/Users/bracca/Programmi/opencv-3.4.3/data/haarcascades/";
string face_cascade_name = "haarcascade_frontalface_alt.xml";
string eyes_cascade_name = "haarcascade_eye_tree_eyeglasses.xml";
string profile_cascade_name = "haarcascade_profileface.xml";

string path_face_cascade = pathToCascadesDir + face_cascade_name;
string path_eyes_cascade = pathToCascadesDir + eyes_cascade_name;
string path_cascade_profile = pathToCascadesDir + profile_cascade_name;

CascadeClassifier face_cascade;
CascadeClassifier eyes_cascade;
CascadeClassifier profile_cascade;

RNG rng(12345);                         // random number generator

// name used for the window
string window = "Video";


/* functions definition */
void detectAndDisplay (VideoCapture stapleVideo, string fullPath) {
    
    // variable init
    Mat frame;
    Mat frame_gray;
    vector<Rect> faces;
    vector<Rect> profiles;
    vector<Rect> eyes;
    
    // open cascades with exception manager
    try {
        face_cascade = openCascade(path_face_cascade);
        eyes_cascade = openCascade(path_eyes_cascade);
        profile_cascade = openCascade(path_cascade_profile);
    } catch (const char* err_msg) {
        cerr << err_msg;
        return;
    }
    
    // open video with exception manager
    try {
        stapleVideo = openVideo(fullPath);
    } catch (const char* err_msg_vid) {
        cerr << err_msg_vid;
        return;
    }
    
    // main cycle (operate frame by frame)
    while (true) {
        // put video in a Mat
        stapleVideo >> frame;
        
        // conversion to make the cascade detection work
        cvtColor (frame, frame_gray, CV_BGR2GRAY);
        equalizeHist (frame_gray, frame_gray);
        
        // plot faces, profiles and eyes
        plotHaar(frame, frame_gray, faces, eyes, profiles, fullPath);
        
        imshow(window, frame);
        
        // the waitKey's number specifies the time interval between two frames
        // the "waited key" input is 27 (in ASCII) which corresponds to ESC
        char c = (char)waitKey(1);
        if(c==27) break;
    }
    
    // When everything done, release the video capture object
    stapleVideo.release();
    
    // Closes all the frames
    destroyAllWindows();
    return;
    
}

void plotHaar (Mat frame, Mat frame_gray, vector<Rect> faces, vector<Rect> eyes, vector<Rect> profiles, string fullPath) {
    
    // conversion to make the cascade detection work
    cvtColor (frame, frame_gray, CV_BGR2GRAY);
    equalizeHist (frame_gray, frame_gray);
    
    // Detect faces (vector with n possible faces in the video)
    face_cascade.detectMultiScale(frame_gray, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30));
    profile_cascade.detectMultiScale(frame_gray, profiles, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30));
    
    // draw circle that identifies the face for every one seen
    for(size_t i = 0; i < faces.size(); i++) {
        Point center(faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5);
        ellipse(frame, center, Size(faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar(0, 0, 255), 4, 8, 0);
        
        // put the i-th face in a matrix, so that you can identify eyes on it
        Mat faceROI = frame_gray(faces[i]);
        eyes_cascade.detectMultiScale(faceROI, eyes, 1.1, 2, 0 |CV_HAAR_SCALE_IMAGE, Size(30, 30));
        
        // draw eyes circle
        for(size_t j = 0; j < eyes.size(); j++) {
            Point center(faces[i].x + eyes[j].x + eyes[j].width*0.5, faces[i].y + eyes[j].y + eyes[j].height*0.5);
            int radius = cvRound( (eyes[j].width + eyes[j].height)*0.25 );
            circle(frame, center, radius, Scalar(255, 0, 0), 4, 8, 0);
        }
    }
    
    // draw for profile faces
    for(size_t i = 0; i < profiles.size(); i++) {
        Point center(profiles[i].x + profiles[i].width*0.5, profiles[i].y + profiles[i].height*0.5);
        ellipse(frame, center, Size(profiles[i].width*0.5, profiles[i].height*0.5), 0, 0, 360, Scalar(0, 0, 255), 4, 8, 0);
    }
    
}


CascadeClassifier openCascade (string path_cascade) {
    CascadeClassifier name_cascade;
    if (!name_cascade.load(path_cascade)) {
        cout << "cascade: " << path_cascade;
        throw " unable to open";
    }
    return name_cascade;
}


VideoCapture openVideo (string fullPath) {
    VideoCapture stapleVideo;
    
    // try to open video reference, specify "Camera" in the path if you want that
    if (fullPath != "Camera") {
        stapleVideo.open(fullPath);
    } else {
        stapleVideo.open(0);
    }
    
    // check if video was opened
    if (!stapleVideo.isOpened()) {
        // throw an exception if there is no video
        throw "no video to display";
    }
    
    // give a name to a window and open it to display the video
    namedWindow(window, WINDOW_AUTOSIZE);
    return stapleVideo;
}
