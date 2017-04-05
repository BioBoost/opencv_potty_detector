# OpenCV for Ubuntu

## Dependencies

```shell
sudo apt-get update
sudo apt-get install build-essential gcc make
```

## Installing OpenCV

We could install using apt-get but problem is that we will get an older version of opencv. For this reason we opt for using custom install.

### OpenCV

Clone this repo for an automatic installation script:

```shell
cd
git clone https://github.com/jayrambhia/Install-OpenCV
cd Install-OpenCV
```

Next execute the script for your OS. For example for Ubuntu:

```shell
cd Ubuntu
./opencv_latest.sh
```

Now you are ready to compile OpenCV apps.

### OpenCV with apt-get

If for some reason you are happy with older version you could install opencv using:

```shell
sudo apt-get update
sudo apt-get install libopencv-dev
```
