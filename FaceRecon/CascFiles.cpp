//
//  CascFiles.cpp
//  FaceRecon
//

#include "CascFiles.hpp"

// basic constructor (avoid bugs)
CascFiles::CascFiles() {
    
}

// constructor 1 parameter: NEED THIS
CascFiles::CascFiles(string _pathToCascadesDir) {
    pathToCascadesDir = _pathToCascadesDir;
    path_face_cascade = _pathToCascadesDir + "haarcascade_frontalface_alt.xml";
    path_eyes_cascade = _pathToCascadesDir + "haarcascade_eye_tree_eyeglasses.xml";
    path_profile_cascade = _pathToCascadesDir + "haarcascade_profileface.xml";
    rng(12345);
}

// set all the cascades
void CascFiles::setAllCascades () {
    
    if (!face_cascade.load(path_face_cascade))
        throw "unable to open face cascades";
    
    if (!eyes_cascade.load(path_eyes_cascade))
        throw "unable to open eyes cascades";
    
    if (!profile_cascade.load(path_profile_cascade))
        throw "unable to open profile cascades";
    
}

// return cascade
CascadeClassifier CascFiles::getCascade (int _cascadeType) {
    CascadeClassifier chosen;
    
    switch (_cascadeType) {
        case 0:
            chosen = face_cascade;
            break;
        case 1:
            chosen = eyes_cascade;
            break;
        case 2:
            chosen = profile_cascade;
            break;
    }
    
    return chosen;
}
