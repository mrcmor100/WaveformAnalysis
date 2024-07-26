#ifndef WAVEFORMPREPROCESSOR_H
#define WAVEFORMPREPROCESSOR_H

#include "ROOT/RVec.hxx"

class WaveformPreprocessor {
public:
    struct PreprocessingResult {
        bool requiresFit;
        std::string fitType;
        double fitMin;
        double fitMax;
    };

    PreprocessingResult Preprocess(const ROOT::RVec<double>& waveform);

private:
    size_t CountPulses(const ROOT::RVec<double>& waveform);
};

#endif // WAVEFORMPREPROCESSOR_H
