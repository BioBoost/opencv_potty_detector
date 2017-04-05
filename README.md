# OpenCV Potty Detector

This OpenCV application is meant to run on a Raspberry Pi 3 and detects
if a child uses his/her potty. If so, a trigger is sent via MQTT allowing
music, lights or other animations to be played as a reward.

Check out https://github.com/99-bugs/toomanypeeps/ for more info on installing
OpenCV and MQTT on a Raspberry Pi 3 .

## Capturing a sample MP4 with the Raspberry Pi camera

You can easily create a sample video file using the Raspberry Pi in an MP4 container
using the commands listed below:

```shell
raspivid -o sample.h264 -w 640 -h 480 -t 20000
MP4Box -fps 30 -add sample.h264 sample.mp4
```

Here the `-t 20000` states that a video of 20 seconds should be made.

More info @ http://www.raspberrypi-spy.co.uk/2013/05/capturing-hd-video-with-the-pi-camera-module/

For this you will need to install gpac

```shell
sudo apt-get update
sudo apt-get install -y gpac
```

## Capturing a sample MP4 with the Raspberry Pi and a web camera

For this you need to install avconv

```shell
sudo apt-get install libav-tools
```

Next you can capture a video using:

```shell
avconv -f video4linux2 -r 25 -s 640x480 -i /dev/video0 sample.avi
```

## More info on OpenCV 3.2

Checkout http://docs.opencv.org/3.2.0/ for more info on OpenCV 3.2
