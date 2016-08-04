#!/bin/bash
qmake create_clip.pro

make

function makeChannel {
	echo $1
	./create_clip "$1" "$2"
	if [ -f "$1.flv" ]; then
	        rm "$1"
	fi
	ffmpeg -f image2 -r 25 -i images/clip-%06d.png -b 100k -vcodec libx264 -pix_fmt yuv420p -f flv "$1.flv"
}

makeChannel "channel_01" "3c3c3c"
makeChannel "channel_02" "ff0202"
makeChannel "channel_03" "ffd602"
makeChannel "channel_04" "7569ec"
makeChannel "channel_05" "1db336"
makeChannel "channel_06" "ff18f1"
makeChannel "channel_07" "ffffff"
makeChannel "channel_08" "000000"
makeChannel "channel_09" "3c3c3c"
makeChannel "channel_10" "ff0202"
makeChannel "channel_11" "ffd602"
makeChannel "channel_12" "7569ec"
makeChannel "channel_13" "1db336"
makeChannel "channel_14" "ff18f1"
makeChannel "channel_15" "ffffff"
makeChannel "channel_16" "000000"
