#!/bin/bash

echo 'ready to make and export to share'
rm /home/vx/share/target.bin
make
[ -f "./target.bin" ] || { echo 'damn, something goes wrong!'; exit 1;}
cp target.bin /home/vx/share
make clean
echo '\n Finish!'
