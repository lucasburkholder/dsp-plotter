#ifndef DSP_PLOTTER_H
#define DSP_PLOTTER_H


#ifdef __cplusplus
#include <cstdint>
extern "C" {
#else
#include <stdint.h>
#endif

enum _dsp_plotter_error {
    DspPlotterErr_NoError = 0,
    DspPlotterErr_Error = 1,            // Generic error
    DspPlotterErr_CouldNotOpenWavFile,  // Tinywav could not open the file
};
typedef enum _dsp_plotter_error DSPPlotterErr;

/**
 * @brief Typedef for startup function. Should do any initialization before
 *      any processing occurs.
 */
typedef int (* startupFunc_t) ();

/**
 * @brief Typedef for processing function. Should process `frameSize` samples,
 *      with `frameSize` being the value passed into `DspPlotter_init()`
 */
typedef int (* processFunc_t) (float *, float *);

/**
 * @brief Typedef for shutdown function. Should free up any memory allocated
 *      in the startup function and close down everything.
 */
typedef int (* shutdownFunc_t) ();

int DspPlotter_init(    char * wavFilePath,
                        uint32_t frameSize,
                        startupFunc_t startupFunc, 
                        processFunc_t processFunc,
                        shutdownFunc_t shutdownFunc);
int DspPlotter_show();

#ifdef __cplusplus
}
#endif

#endif /* DSP_PLOTTER_H */
