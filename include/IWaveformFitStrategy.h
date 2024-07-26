#ifndef IWAVEFORMFITSTRATEGY_H
#define IWAVEFORMFITSTRATEGY_H

#include "ROOT/RVec.hxx"
#include "TF1.h"

class IWaveformFitStrategy {
public:
    virtual bool FitWaveform(ROOT::RVec<double>& waveform, TF1& fitFunction, double& score) = 0;
    virtual ~IWaveformFitStrategy() = default;
};

#endif // IWAVEFORMFITSTRATEGY_H
