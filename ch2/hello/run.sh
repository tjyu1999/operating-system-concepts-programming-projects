#!/bin/bash

sudo insmod hello.ko
sleep 1
cat /proc/hello
sleep 1
sudo rmmod hello
sudo dmesg -c
