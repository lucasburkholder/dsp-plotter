# DSP Plotter

## How to use
1) Pull in dsp plotter as submodule with `git submodule add https://github.com/lucasburkholder/dsp-plotter.git <plotter_dir>` and commit if you want

2) Add these lines to `CMakeLists.txt`

```
add_subdirectory(<plotter_dir>)
target_link_libraries(<main_target_name> dsp-plotter)
```

3) In main source code, `#include "dsp-plotter.h"`

4) Call `DspPlotter_init()`, passing in audio file, frame size, and pointers to processing functions

5) Call `DspPlotter_show()` to show the window

That's it!