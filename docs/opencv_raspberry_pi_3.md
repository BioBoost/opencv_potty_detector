# OpenCV for Raspberry Pi (3)

Source: http://www.pyimagesearch.com/2015/10/26/how-to-install-opencv-3-on-raspbian-jessie/

Do a raspi-config again and enable the camera and Full openGL driver.

```shell
sudo raspi-config
```

Update Raspberry Pi firmware (needed for newer video drivers and all).

```shell
sudo apt-get update
sudo apt-get upgrade -y
sudo rpi-update
```

Install some development tools

```shell
sudo apt-get install build-essential git cmake pkg-config -y
```

Install all sorts of packages that are used by openCV

```shell
sudo apt-get install libjpeg-dev libtiff5-dev libjasper-dev libpng12-dev libavcodec-dev libavformat-dev libswscale-dev libv4l-dev libxvidcore-dev libx264-dev libgtk2.0-dev libatlas-base-dev gfortran libgtkglext1 libgtkglext1-dev -y
```

Checkout opencv git repo

```shell
cd
git clone https://github.com/opencv/opencv.git
cd opencv
git checkout tags/3.2.0
```

Checkout opencv contributions repo

```shell
cd
git clone https://github.com/opencv/opencv_contrib
cd opencv_contrib
git checkout tags/3.2.0
```

Prepare opencv for building

```shell
cd ~/opencv
mkdir build
cd build
cmake -D CMAKE_BUILD_TYPE=RELEASE \
	-D CMAKE_INSTALL_PREFIX=/usr/local \
	-D INSTALL_C_EXAMPLES=OFF \
	-D INSTALL_PYTHON_EXAMPLES=OFF \
	-D OPENCV_EXTRA_MODULES_PATH=~/opencv_contrib/modules \
	-D BUILD_EXAMPLES=OFF \
	-D WITH_OPENGL=ON ..
```

Build and install opencv

```shell
make -j4
sudo make install
sudo ldconfig
```
