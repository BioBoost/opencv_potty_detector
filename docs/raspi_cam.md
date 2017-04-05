# RaspiCam

RaspiCam is a C++ API for using Raspberry camera with/without OpenCv.

Source: https://www.uco.es/investiga/grupos/ava/node/40

## Install

Make sure to install OpenCV before doing this.

Download the latest version from https://sourceforge.net/projects/raspicam/files/

```shell
cd
wget https://downloads.sourceforge.net/project/raspicam/raspicam-0.1.6.zip
unzip raspicam-0.1.6.zip
cd raspicam-0.1.6
mkdir build
cd build
cmake ..
```

At this point you'll see something like

```text
-- CREATE OPENCV MODULE=1
-- CMAKE_INSTALL_PREFIX=/usr/local
-- REQUIRED_LIBRARIES=/opt/vc/lib/libmmal_core.so;/opt/vc/lib/libmmal_util.so;/opt/vc/lib/libmmal.so
-- Change a value with: cmake -D<Variable>=<Value>
--
-- Configuring done
-- Generating done
-- Build files have been written to: /home/pi/raspicam/trunk/build
```

If OpenCV development files are installed in your system, then you see `-- CREATE OPENCV MODULE=1`. Otherwise this option will be 0 and the opencv module of the library will not be compiled.

Finally compile, install and update the ldconfig

```shell
make
sudo make install
sudo ldconfig
```
