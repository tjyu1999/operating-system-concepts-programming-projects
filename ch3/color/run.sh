#!/bin/bash

sudo insmod color.ko
sudo rmmod color
sudo dmesg -c
