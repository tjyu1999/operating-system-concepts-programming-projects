#!/bin/bash

sudo insmod jiffies.ko
sleep 3
cat /proc/jiffies
sleep 3
cat /proc/jiffies
sudo rmmod jiffies
sudo dmesg -c
