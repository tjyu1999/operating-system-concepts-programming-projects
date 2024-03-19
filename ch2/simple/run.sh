#!/bin/bash

sudo insmod simple.ko
sleep 5
cat /proc/simple
sleep 5
cat /proc/simple
sudo rmmod simple
sudo dmesg -c
