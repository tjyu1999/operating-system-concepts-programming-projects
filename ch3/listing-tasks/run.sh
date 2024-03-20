#!/bin/bash

sudo insmod listing_tasks.ko
sudo insmod listing_tasks_dfs.ko
sudo rmmod listing_tasks
sudo rmmod listing_tasks_dfs
sudo dmesg -c
