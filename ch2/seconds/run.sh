#!/bin/bash

sudo insmod seconds.ko
sleep 1
cat /proc/seconds
sleep 1
sudo rmmod seconds
sudo dmesg -c
