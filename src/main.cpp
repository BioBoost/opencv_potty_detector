#include <iostream>

#include "lib/bios_opencv/frame_grabber/video_file.h"
#include "lib/bios_opencv/frame_grabber/image_file.h"
#include "lib/bios_opencv/filter_chain/filter_chain.h"
#include "lib/bios_opencv/filter/all_filters.h"

using namespace BiosOpenCV;

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
  std::string filename = "./video_samples/sample.mp4";
  if (argc >= 2) {
    filename = std::string(argv[1]);
  }
  VideoFile frameGrabber(filename);
  paused = true;
  std::cout << "Watch it. Video is currently paused. Press p to pause/unpause, s to step and esc to quit" << std::endl;
#endif

  ImageFile templateGrabber("./templates/potty_backplate_cropped.png");
  singleExecution.add(new GrabFrame(pottyTemplate, &templateGrabber));
  singleExecution.add(new GrayScale(pottyTemplate));
  singleExecution.add(new Display(pottyTemplate, "Potty"));
  singleExecution.execute();

  filters.add(new GrabFrame(original, &frameGrabber));
  filters.add(new GrayScale(original, grayscale));
  filters.add(new BinaryThreshold(grayscale, processed, 140));
  filters.add(new FindContours(processed, original, 400, 500));
  filters.add(new MatchTemplate(grayscale, original, pottyTemplate));
  filters.add(new Display(original, "original"));

  do {
    if (!paused || step) {
      filters.execute();
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
