# Mqtt

## Installing Mqtt development libraries

Install dependencies to allow for compilation of mqtt

```shell
sudo apt-get update
sudo apt-get install build-essential gcc make cmake cmake-gui cmake-curses-gui libssl-dev
```

Next clone, compile and install paho C client library of MQTT

```shell
cd
git clone https://github.com/eclipse/paho.mqtt.c.git
cd paho.mqtt.c
make
sudo make install
```

The Paho C client comprises four shared libraries:

 * libmqttv3a.so - asynchronous
 * libmqttv3as.so - asynchronous with SSL
 * libmqttv3c.so - "classic" / synchronous
 * libmqttv3cs.so - "classic" / synchronous with SSL

This project currently makes use of the classic synchronous client.

Next we need to compile and install the C++ wrapper library for the MQTT libraries

```shell
cd
git clone https://github.com/eclipse/paho.mqtt.cpp.git
cd paho.mqtt.cpp
make
```

Unfortunately this repo's Makefile does not contain an install target. So we will have to this
manually. The libraries need to be installed to `/usr/local/lib` and the header files should be placed in `/usr/local/include`

```shell
cd ~/paho.mqtt.cpp
sudo install -m 644  lib/libmqttpp.so.0.1 /usr/local/lib
sudo /sbin/ldconfig /usr/local/lib
sudo ln -s libmqttpp.so.0 /usr/local/lib/libmqttpp.so
sudo cp -r src/mqtt /usr/local/include/mqtt
sudo chmod 644 /usr/local/include/mqtt/*
echo '/usr/local/lib' | sudo tee /etc/ld.so.conf.d/mqttpp.conf
sudo /sbin/ldconfig
```
