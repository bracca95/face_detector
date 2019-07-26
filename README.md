
# Face recognition using Haar Cascade

The program is based on the Haar Cascade algorithm[1] and it can detect faces either directly on a live video, streamed by the PC camera, or retrieve the information from a stored file.

Some existing code has been used to write this program[2][3]

# 1) Compile OpenCV
The first thing you need is a compiled version of OpenCV (I am using 3.4.3). Refer to an OpenCV installation guide for your architecture.

# 2) IDE
Any IDEs can be used to read/write the program. Some OpenCV libraries may be required to correctly interpret commands.
Header libraries are found in /usr/local/include.
Library files are found in /usr/local/lib.

# 3) Build the program
To build the program, move into the main (highest) project *HOGdetector* directory and run the `compile.sh` script. 
Customizations might be required to compile properly.

# 4) Usage
A directory called `build` will appear after building. Open a terminal in the location of the executable and run:

    ./target

The program will open your PC camera and detect you face.

License
----
Refer to LICENSE


# References
[1] https://ieeexplore.ieee.org/document/8265863
[2] https://docs.opencv.org/trunk/db/d28/tutorial_cascade_classifier.html
[3] https://docs.opencv.org/2.4/doc/tutorials/objdetect/cascade_classifier/cascade_classifier.html
