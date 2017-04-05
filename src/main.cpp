#include <iostream>

#include "lib/bios_opencv/frame_grabber/video_file.h"
#include "lib/bios_opencv/frame_grabber/image_file.h"
#include "lib/bios_opencv/frame_grabber/web_camera.h"
#include "lib/bios_opencv/filter_chain/filter_chain.h"
#include "lib/bios_opencv/filter/all_filters.h"
#include "lib/mqtt/simple_mqtt_publisher.h"
#include <ctime>
#include <sstream>

using namespace BiosOpenCV;
using namespace BiosMqtt;

SimpleMqttPublisher	mqttPublisher("tcp://mqtt.labict.be", "sdgfdgdgsdgtet3455465678");

void report(int numberOfSecondsLost) {
  std::stringstream ss;
  ss << "{\"seconds_lost\": " << numberOfSecondsLost << "}";
  std::string json = ss.str();

  std::cout << "MQTT: " << json << std::endl;

  mqttPublisher.publish(json, "pottydetector/timer");
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
    if (timeLost >= 5 && timeLost <= 120) {
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
  cv::Mat processed;
  cv::Mat pottyTemplate;

#if defined(USE_VIDEO_FILE)
  std::string filename = "./video_samples/sample.avi";
  if (argc >= 2) {
    filename = std::string(argv[1]);
  }
  VideoFile frameGrabber(filename);
  paused = true;
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
  filters.add(new BinaryThreshold(grayscale, processed, 230));
  filters.add(new Display(processed, "processed"));

  FindContours findContours(processed, original, 130, 180);
  filters.add(&findContours);

  MatchTemplate templateMatcher(grayscale, original, pottyTemplate);
  filters.add(&templateMatcher);

  filters.add(new Display(original, "original"));

  do {
    if (!paused || step) {
      filters.execute();

      cv::Point2f matchLocation;
      matchLocation.x = templateMatcher.get_match_center().x;
      matchLocation.y = templateMatcher.get_match_center().y;

      std::vector<cv::Point2f> centers = findContours.get_centers();

      bool foundPotty = false;
      for (size_t i = 0; i < centers.size(); i++) {
        std::cout << "Distance [" << i << "] = " << (cv::norm(centers[i] - matchLocation)) << std::endl;
        if (cv::norm(centers[i] - matchLocation) <= 25) {
          std::cout << "Got match for " << i << " between template and blobs" << std::endl;
          foundPotty = true;
          indicate_potty_is_tracked();
          break;
        }
      }

      if (!foundPotty) {
        indicate_potty_is_lost();
      }

      step = false;
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
