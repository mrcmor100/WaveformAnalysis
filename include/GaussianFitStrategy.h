#ifndef GAUSSIANFITSTRATEGY_H
#define GAUSSIANFITSTRATEGY_H

#include "IWaveformFitStrategy.h"
#include <iostream>

class GaussianFitStrategy : public IWaveformFitStrategy {
public:
    bool FitWaveform(ROOT::RVec<double>& waveform, TF1& fitFunction, double& score) override;
};

#endif // GAUSSIANFITSTRATEGY_H
