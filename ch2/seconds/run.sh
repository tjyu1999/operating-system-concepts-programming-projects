#!/bin/bash

sudo insmod seconds.ko
cat /proc/seconds
sudo rmmod seconds
sudo dmesg -c
