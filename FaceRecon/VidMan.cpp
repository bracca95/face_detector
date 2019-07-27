//
//  VidMan.cpp
//  FaceRecon
//

#include "VidMan.hpp"

VidMan::VidMan() {
    
}

VidMan::VidMan(string _fullPath, CascFiles _casc) {
    fullPath = _fullPath;
    casc = _casc;
}

void VidMan::playVideo() {
    
    // variable init
    VideoCapture baseVideo;
    
    // open cascades with exception manager
    try {
        casc.setAllCascades();
    } catch (const char* err_msg) {
        cerr << err_msg << endl;
        return;
    }
    
    // return cascade classifiers
    CascadeClassifier faceCasc = casc.getCascade(0);
    CascadeClassifier eyesCasc = casc.getCascade(1);
    CascadeClassifier profileCasc = casc.getCascade(2);
    
    // try to open video reference
    if (fullPath == "Camera")
        baseVideo.open(0);
    else
        baseVideo.open(fullPath);
    
    if (!baseVideo.isOpened()) {
        // throw an exception if there is no video
        throw "no video to display";
        return;
    }
    
    // name used for the window
    string window = "Video";
    namedWindow(window, WINDOW_AUTOSIZE);
    
    // main cycle (operate frame by frame)
    while (true) {
        // put video in a Mat
        baseVideo >> frame;
        
        // conversion to make the cascade detection work
        cvtColor (frame, frame_gray, CV_BGR2GRAY);
        equalizeHist (frame_gray, frame_gray);
        
        // plot faces, profiles and eyes
        plotHaar(faceCasc, eyesCasc, profileCasc);
        
        imshow(window, frame);
        
        // the waitKey's number specifies the time interval between two frames
        // the "waited key" input is 27 (in ASCII) which corresponds to ESC
        char c = (char)waitKey(1);
        if(c==27) break;
    }
    
    // When everything done, release the video capture object
    baseVideo.release();
    
    // Closes all the frames
    destroyAllWindows();
    return;
}

void VidMan::plotHaar(CascadeClassifier faceCasc, CascadeClassifier eyesCasc, CascadeClassifier profileCasc) {
    
    // conversion to make the cascade detection work
    cvtColor (frame, frame_gray, CV_BGR2GRAY);
    equalizeHist (frame_gray, frame_gray);
    
    // Detect faces (vector with n possible faces in the video)
    faceCasc.detectMultiScale(frame_gray, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30));
    profileCasc.detectMultiScale(frame_gray, profiles, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30));
    
    // draw circle that identifies the face for every one seen
    for(size_t i = 0; i < faces.size(); i++) {
        Point center(faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5);
        ellipse(frame, center, Size(faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar(0, 0, 255), 4, 8, 0);
        
        // put the i-th face in a matrix, so that you can identify eyes on it
        Mat faceROI = frame_gray(faces[i]);
        eyesCasc.detectMultiScale(faceROI, eyes, 1.1, 2, 0 |CV_HAAR_SCALE_IMAGE, Size(30, 30));
        
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
