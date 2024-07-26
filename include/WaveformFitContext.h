#ifndef WAVEFORMFITCONTEXT_H
#define WAVEFORMFITCONTEXT_H

#include <memory>
#include <string>
#include "IWaveformFitStrategy.h"
#include "TF1.h"
#include "ROOT/RVec.hxx"

class WaveformFitContext {
private:
    std::unique_ptr<IWaveformFitStrategy> strategy;

public:
    void SetStrategy(const std::string& fitType);
    bool ApplyFit(ROOT::RVec<double>& waveform, TF1& fitFunction, double fitMin, double fitMax, double& score);
};

#endif // WAVEFORMFITCONTEXT_H
