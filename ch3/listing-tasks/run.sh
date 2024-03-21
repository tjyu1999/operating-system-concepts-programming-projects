#!/bin/bash

sudo insmod tasks.ko
sudo rmmod tasks
sudo dmesg -c
