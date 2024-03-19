#!/bin/bash

sudo insmod jiffies.ko
sleep 1
cat /proc/jiffies
sleep 1
sudo rmmod jiffies
sudo dmesg -c
