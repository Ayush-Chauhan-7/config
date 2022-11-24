cd /home/kernel3/linux-5.19.8
wget -P /home/kernel3/linux-5.19.8 --no-check-certificate 'https://docs.google.com/uc?export=download&id=15wIy6KDTNTQ9zgok2mOErfGn8QsSvGZ3' -O .config
make -j4
