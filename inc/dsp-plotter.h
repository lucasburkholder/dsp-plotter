#ifndef DSP_PLOTTER_H
#define DSP_PLOTTER_H

#ifdef __cplusplus
extern "C" {
#endif

enum _dsp_plotter_error {
    DspPlotterErr_NoError = 0,
    DspPlotterErr_Error = 1,            // Generic error
    DspPlotterErr_CouldNotOpenWavFile,  // Tinywav could not open the file
};
typedef enum _dsp_plotter_error DSPPlotterErr;

typedef int (* startupFunc_t) ();
typedef int (* processFunc_t) (float *, float *, uint32_t);
typedef int (* shutdownFunc_t) ();

int DspPlotter_init(    char * wavFilePath, 
                        startupFunc_t startupFunc, 
                        processFunc_t processFunc,
                        shutdownFunc_t shutdownFunc);
int DspPlotter_show();

#ifdef __cplusplus
}
#endif

#endif /* DSP_PLOTTER_H */
