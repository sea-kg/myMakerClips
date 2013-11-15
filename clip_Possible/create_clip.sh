#!/bin/bash

# ffmpeg -r 1/5 -i SL37053%d.JPG -c:v libx264 -r 30 -pix_fmt yuv420p out.mp4

# ffmpeg -f image2 -i SL37053%d.JPG -r 30 -vcodec mjpeg -pix_fmt yuv420p output/foo.avi

# mencoder -speed 0.1 "mf://SL%06d.JPG" -o output/movie_drilldata.avi -ovc lavc -lavcopts vcodec=mjpeg

# ffmpeg -r 30 -i sl%06d.jpg -codec copy output/output.mkv


# ffmpeg -f image2 -i SL37053%d.JPG -r 30 -vcodec mjpeg -pix_fmt yuv420p output/foo.avi

# avconv -f image2 -r 30 -i sl%04d.jpg video.avi
