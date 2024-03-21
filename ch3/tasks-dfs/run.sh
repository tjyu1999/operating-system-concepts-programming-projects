#!/bin/bash

sudo insmod tasks_dfs.ko
sudo rmmod tasks_dfs
sudo dmesg -c
