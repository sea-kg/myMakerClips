#!/bin/bash

kill $(ps aux | grep 'ffmpeg .*channel.*' | awk '{print $2}')

function startChannel {
	ffmpeg -re -f lavfi -i "movie=filename=$1.flv:loop=0, setpts=N/(FRAME_RATE*TB)" -vcodec libx264 -preset veryfast -pix_fmt yuv420p -f flv rtmp://10.20.16.87:1935/live/$1 &
}

startChannel "channel_01"
startChannel "channel_02"
startChannel "channel_03"
startChannel "channel_04"
startChannel "channel_05"
startChannel "channel_06"
startChannel "channel_07"
startChannel "channel_08"
startChannel "channel_09"
startChannel "channel_10"
startChannel "channel_11"
startChannel "channel_12"
startChannel "channel_13"
startChannel "channel_14"
startChannel "channel_15"
startChannel "channel_16"
