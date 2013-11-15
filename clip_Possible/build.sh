#!/bin/bash
qmake create_clip.pro

make

./create_clip
if [ -f video.avi ]; then
	rm video.avi
fi
	
	
# avconv -f image2 -r 30 -i images/clip-%06d.png video.avi

avconv -f image2 -r 30 -i images/clip-%06d.png -i source.mp3 -acodec copy -b 1200k video.avi
