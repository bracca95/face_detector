//
//  main.cpp
//  FaceRecon
//

#include "VidMan.hpp"

// header
void printUsage ();

int main(int argc, const char * argv[]) {
    
    /* PARSER */
    const char* keys = {
        "{help h|     | show help message}"
        "{c     |     | path of cascades}"
        "{v     |     | path of ground truth. Omit if not exists}"
    };
    
    CommandLineParser parser(argc, argv, keys);
    
    if (parser.has("help")) {
        parser.printMessage();
        printUsage();
        exit(0);
    }
    
    string casca = parser.get<string>("c");
    string video = parser.get<string> ("v");
    
    // main operation: use either camera or videoFullPath, depending on the application
    if (casca == "") {
        printUsage();
        exit(0);
    }
    
    CascFiles casc = CascFiles(casca);
    VidMan vidman = VidMan("", casc);
    vidman.playVideo();
    
    return 0;
}

// print usage function
void printUsage () {
    cout << "Sample usage: " << endl
    << "(1) ./target -c='/path/to/video/cascades-dir' -v='/path/to/video.mp4' " << endl
    << "(2) ./target -c='/path/to/video/cascades-dir'" << endl;
}
