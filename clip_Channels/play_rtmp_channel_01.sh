#!/bin/bash

ffmpeg -re -f lavfi -i "movie=filename=channel_01.flv:loop=0, setpts=N/(FRAME_RATE*TB)" -vcodec libx264 \
  -preset veryfast -pix_fmt yuv420p -f flv rtmp://10.20.16.87:1935/live/channel_01
