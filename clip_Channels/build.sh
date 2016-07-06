#!/bin/bash
qmake create_clip.pro

make

./create_clip "Channel 1" "3c3c3c"
if [ -f channel01.avi ]; then
	rm channel01.avi
fi
ffmpeg -f image2 -r 2 -i images/clip-%06d.png -b 100k -vcodec libx264 channel01.mp4

./create_clip "Channel 2" "ff0202"
if [ -f channel02.avi ]; then
	rm channel02.avi
fi
ffmpeg -f image2 -r 2 -i images/clip-%06d.png -b 100k -vcodec libx264 channel02.mp4

./create_clip "Channel 3" "ffd602"
if [ -f channel03.avi ]; then
	rm channel03.avi
fi
ffmpeg -f image2 -r 2 -i images/clip-%06d.png -b 100k -vcodec libx264 channel03.mp4

./create_clip "Channel 4" "7569ec"
if [ -f channel04.avi ]; then
	rm channel04.avi
fi
ffmpeg -f image2 -r 2 -i images/clip-%06d.png -b 100k -vcodec libx264 channel04.mp4

./create_clip "Channel 5" "1db336"
if [ -f channel05.avi ]; then
	rm channel05.avi
fi
ffmpeg -f image2 -r 2 -i images/clip-%06d.png -b 100k -vcodec libx264 channel05.mp4

./create_clip "Channel 6" "ff18f1"
if [ -f channel06.avi ]; then
	rm channel06.avi
fi
ffmpeg -f image2 -r 2 -i images/clip-%06d.png -b 100k -vcodec libx264 channel06.mp4

./create_clip "Channel 7" "ffffff"
if [ -f channel07.avi ]; then
	rm channel07.avi
fi
ffmpeg -f image2 -r 2 -i images/clip-%06d.png -b 100k -vcodec libx264 channel07.mp4

./create_clip "Channel 8" "000000"
if [ -f channel08.avi ]; then
	rm channel08.avi
fi
ffmpeg -f image2 -r 2 -i images/clip-%06d.png -b 100k -vcodec libx264 channel08.mp4

# avconv -f image2 -r 30 -i images/clip-%06d.png video.avi



# ffmpeg -f image2 -r 30 -i images/clip-%06d.png -i source.mp3 -acodec copy -b 1200k video.avi
