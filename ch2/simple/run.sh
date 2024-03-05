sudo insmod simple.ko
sleep 3
cat /proc/simple
sleep 3
cat /proc/simple
sudo rmmod simple
sudo dmesg -c
