#!/bin/bash

sudo insmod jiffies.ko
sleep 5
cat /proc/jiffies
sleep 5
cat /proc/jiffies
sudo rmmod jiffies
sudo dmesg -c
