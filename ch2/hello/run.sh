#!/bin/bash

sudo insmod hello.ko
sleep 5
cat /proc/hello
sleep 5
cat /proc/hello
sudo rmmod hello
sudo dmesg -c
