#!/bin/bash

sudo insmod pid.ko
echo "1179" > /proc/pid
cat /proc/pid
sudo rmmod pid
