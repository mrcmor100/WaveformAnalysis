#include "WaveformPreprocessor.h"
#include <algorithm>

WaveformPreprocessor::PreprocessingResult WaveformPreprocessor::Preprocess(const ROOT::RVec<double>& waveform) {
    PreprocessingResult result;
    result.requiresFit = !waveform.empty();
    if (!result.requiresFit) {
        return result;
    }

    size_t numPulses = CountPulses(waveform);
    if (numPulses > 1) {
        result.fitType = "gaus";
        result.fitMin = 0;
        result.fitMax = waveform.size();
    } else {
        result.fitType = "expo";
        result.fitMin = 0;
        result.fitMax = waveform.size();
    }

    return result;
}

size_t WaveformPreprocessor::CountPulses(const ROOT::RVec<double>& waveform) {
    size_t count = 0;
    for (auto value : waveform) {
        if (value > 10) {  // Example threshold for counting pulses
            count++;
        }
    }
    return count;
}
