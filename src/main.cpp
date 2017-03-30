#include <iostream>

#include "lib/bios_opencv/frame_grabber/video_file.h"
#include "lib/bios_opencv/filter_chain/filter_chain.h"
#include "lib/bios_opencv/filter/all_filters.h"

using namespace std;
using namespace BiosOpenCV;

int main(int argc, const char * argv[])
{
  bool paused = false;

  // Set step to true to execute at least once to allow Display filters to initialize
  // an opencv window
  bool step = true;

  FilterChain filters;

  cv::Mat original;

#if defined(USE_VIDEO_FILE)
  std::string filename = "./video_samples/sample.mp4";
  if (argc >= 2) {
    filename = std::string(argv[1]);
  }
  VideoFile frameGrabber(filename);
  paused = true;
  std::cout << "Watch it. Video is currently paused. Press p to pause/unpause, s to step and esc to quit" << std::endl;
#endif

  filters.add(new GrabFrame(original, &frameGrabber));
  filters.add(new Display(original, "Original"));

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
