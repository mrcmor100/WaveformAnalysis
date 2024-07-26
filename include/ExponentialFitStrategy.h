#ifndef EXPONENTIALFITSTRATEGY_H
#define EXPONENTIALFITSTRATEGY_H

#include "IWaveformFitStrategy.h"
#include <iostream>

class ExponentialFitStrategy : public IWaveformFitStrategy {
public:
    bool FitWaveform(ROOT::RVec<double>& waveform, TF1& fitFunction, double& score) override;
};

#endif // EXPONENTIALFITSTRATEGY_H
