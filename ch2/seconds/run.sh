#!/bin/bash

sudo insmod seconds.ko
sleep 5
cat /proc/seconds
sleep 5
cat /proc/seconds
sudo rmmod seconds
sudo dmesg -c
