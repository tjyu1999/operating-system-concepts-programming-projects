#!/bin/bash

sudo insmod hello.ko
sleep 3
cat /proc/hello
sleep 3
cat /proc/hello
sudo rmmod hello
sudo dmesg -c
