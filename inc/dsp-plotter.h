#ifndef DSP_PLOTTER_H
#define DSP_PLOTTER_H

#ifdef __cplusplus
extern "C" {
#endif

enum _dsp_plotter_error {
    DspPlotterErr_NoError = 0,
    DspPlotterErr_Error = 1            // Generic error
};
typedef enum _dsp_plotter_error DSPPlotterErr;

int DspPlotter_show(); // TODO change these names to dspPlotter_show() or similar

#ifdef __cplusplus
}
#endif

#endif /* DSP_PLOTTER_H */
