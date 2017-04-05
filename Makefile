# Possible options to pass to make:
# USE_PI=1 make
## Compile for the Raspberry Pi

# The compiler to use
CC=$(CCPREFIX)g++

# Compiler flags
CFLAGS=-c -Wall `pkg-config --cflags opencv` -std=c++11
    # -c: Compile or assemble the source files, but do not link. The linking stage simply is not done. The ultimate output is in the form of an object file for each source file.
    # -Wall: This enables all the warnings about constructions that some users consider questionable, and that are easy to avoid (or modify to prevent the warning), even in conjunction with macros.

# Libraries
LIBS=`pkg-config --libs opencv` -lmqttpp -lpaho-mqtt3a

##############################################
# Some options you can pass via command line #
##############################################

## Compile for raspberry pi: make USE_PI=1
USE_PI=0
ifeq ($(USE_PI),1)
	CFLAGS += -DUSE_RASPBERRY_PI=1
	LIBS += -lraspicam -lraspicam_cv
endif

## Compile and use video file: make USE_FILE=1
## Then run program as ./bin/potty <path_to_file>
USE_FILE=1
ifneq ($(USE_FILE),0)
	CFLAGS += -DUSE_VIDEO_FILE=1
endif

## Compile and use web camera: make USE_WEBCAM=1
## Then run program as ./bin/potty
USE_WEBCAM=0
ifneq ($(USE_WEBCAM),0)
	CFLAGS += -DUSE_WEB_CAMERA=1
endif

# Name of executable output
TARGET=potty
SRCDIR=src
BUILDDIR=bin

OBJS := $(patsubst %.cpp,%.o,$(shell find $(SRCDIR) -name '*.cpp'))

all: makebuildir $(TARGET)

$(TARGET) : $(OBJS)
	$(CC) $(LDFLAGS) -o $(BUILDDIR)/$@ $(OBJS) $(LIBS)

%.o : %.cpp
	$(CC) $(CFLAGS) $< -o $@

clean :
	rm -rf $(BUILDDIR)
	rm -f $(OBJS)

makebuildir:
	mkdir -p $(BUILDDIR)
