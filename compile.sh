#!/bin/bash

# init directory to host binary files
subDirMain="build"

# init subfolders for different architectures
subDirMac="macos"
subDirLnx="linux"

# fullpaths to binary dirs
macosBuild="$subDirMain/$subDirMac"
linuxBuild="$subDirMain/$subDirLnx"

# if the build dir and subdirs haven't been created yet:
if [[ ! -e $macosBuild ]]; then
	mkdir -p $macosBuild
fi

# ls the directories
for dirs in */ ; do
	# by exclusion: if not "*xcodeproj"
	if [[ ${dirs} != *"xcodeproj"* ]]; then
		# if not "build"
		if [[ ${dirs} != *"build"* ]]; then
			# the remaining is the one that has all the .cpp files
			mainDir=$dirs
			#echo "$mainDir" # DEBUG
		fi
	fi
done

# compile command
g++ -I /usr/local/include \
	-L /usr/local/lib -lopencv_core -lopencv_imgproc \
						-lopencv_highgui -lopencv_ml \
						-lopencv_video -lopencv_videoio \
						-lopencv_features2d -lopencv_calib3d \
						-lopencv_objdetect -lopencv_imgcodecs \
						$mainDir/*.cpp -o $macosBuild/target