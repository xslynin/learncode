#!/bin/bash

echo 'ready to make and export to share'
rm /home/vx/share/led.bin
make
[ -f "./led.bin" ] || { echo 'damn, something goes wrong!'; exit 1;}
cp led.bin /home/vx/share
make clean
echo '\n Finish!'
