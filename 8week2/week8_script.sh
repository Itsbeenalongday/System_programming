sudo rmmod sound_dev
make clean
make
sudo insmod sound_dev.ko
rm -f sound_app
gcc -o sound_app sound_app.c
