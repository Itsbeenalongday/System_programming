sudo rmmod led_dev
sudo rmmod button_dev
cd led_dev/
pwd
make clean
make
sudo insmod led_dev.ko
cd ..
cd button_dev/
pwd
make clean
make
sudo insmod button_dev.ko
cd ..
pwd
cd control_app/
make clean
make
make test
