#!/bin/sh
ffmpeg -i "$1" -ac 1 -ar 48000 -f s16le "$2"