#!/bin/bash

sudo insmod color.ko
sudo rmmod pid
sudo dmesg -c
