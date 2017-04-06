#include <iostream>

#include "lib/bios_opencv/frame_grabber/video_file.h"
#include "lib/bios_opencv/frame_grabber/image_file.h"
#include "lib/bios_opencv/frame_grabber/web_camera.h"
#include "lib/bios_opencv/filter_chain/filter_chain.h"
#include "lib/bios_opencv/filter/all_filters.h"
#include "lib/mqtt/simple_mqtt_publisher.h"
#include <ctime>
#include <sstream>
#include <chrono>
#include <thread>

using namespace BiosOpenCV;
using namespace BiosMqtt;

SimpleMqttPublisher	mqttPublisher("tcp://mqtt.labict.be", "sdgfdgdgsdgtet3455465678");

void report(int numberOfSecondsLost) {
  std::stringstream ss;
  ss << "{\"seconds_lost\": " << numberOfSecondsLost << "}";
  std::string json = ss.str();
  std::cout << "MQTT: " << json << std::endl;

  mqttPublisher.publish(json, "pottydetector/lost");
}

// This should go into class of its own
bool pottyIsBeingTracked = false;

double startTime = 0;
double timeTracked = 0;
double timeLost = 0;

void indicate_potty_is_tracked(void) {
  if (!pottyIsBeingTracked) {
    timeLost = double(cv::getTickCount()-startTime) / double(cv::getTickFrequency());
    std::cout << "Tracking potty - Lost for " << timeLost << " seconds" << std::endl;
    if (timeLost >= 6 && timeLost <= 120) {
      report(timeLost);
    }
    startTime = cv::getTickCount();
  }

  pottyIsBeingTracked = true;
}

void indicate_potty_is_lost(void) {
  if (pottyIsBeingTracked) {
    timeTracked = double(cv::getTickCount()-startTime) / double(cv::getTickFrequency());
    std::cout << "Lost potty - Tracked for " << timeTracked << " seconds" << std::endl;
    startTime = cv::getTickCount();
  }

  pottyIsBeingTracked = false;
}

int main(int argc, const char * argv[])
{
  bool paused = false;

  // Set step to true to execute at least once to allow Display filters to initialize
  // an opencv window
  bool step = true;

  FilterChain filters;
  FilterChain singleExecution;

  cv::Mat original;
  cv::Mat grayscale;
  cv::Mat pottyTemplate;

#if defined(USE_VIDEO_FILE)
  std::string filename = "./video_samples/sample.avi";
  if (argc >= 2) {
    filename = std::string(argv[1]);
  }
  VideoFile frameGrabber(filename);
  paused = false;
  std::cout << "Watch it. Video is currently paused. Press p to pause/unpause, s to step and esc to quit" << std::endl;
#elif defined(USE_WEB_CAMERA)
  WebCamera frameGrabber;
#endif

  ImageFile templateGrabber("./templates/potty_webcam_backplate.png");
  singleExecution.add(new GrabFrame(pottyTemplate, &templateGrabber));
  singleExecution.add(new GrayScale(pottyTemplate));
  singleExecution.execute();

  filters.add(new GrabFrame(original, &frameGrabber));
  filters.add(new Flip(original));
  filters.add(new GrayScale(original, grayscale));

  MatchTemplate templateMatcher(grayscale, original, pottyTemplate);
  filters.add(&templateMatcher);

  // filters.add(new Display(original, "original"));

  mqttPublisher.set_retained(false);

  double time_ = cv::getTickCount();
  do {
    if (!paused || step) {
      filters.execute();

      if (templateMatcher.is_match_found()) {
        indicate_potty_is_tracked();
      } else {
        indicate_potty_is_lost();
      }

#if defined(OUTPUT_FOR_WEB)
      imwrite("web/original.jpg", original); // A JPG FILE IS BEING SAVED
      std::this_thread::sleep_for(std::chrono::milliseconds(500));
#endif

      step = false;

      double secondsElapsed = double ( cv::getTickCount() - time_ ) / double ( cv::getTickFrequency() );
      std::cout << "FPS = " << (1.0/secondsElapsed ) << std::endl;
      time_ = cv::getTickCount();
    }

    char key = cv::waitKey(10);
    if(key == 'p') {
      paused = !paused;
    } else if (key == 's') {
      step = true;
    } else if (key == 27) {
      break;
    }

  } while (true);

  return 0;
}
