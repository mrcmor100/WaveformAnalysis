#include "WaveformFitContext.h"
#include "GaussianFitStrategy.h"
#include "ExponentialFitStrategy.h"
#include <iostream>

void WaveformFitContext::SetStrategy(const std::string& fitType) {
    if (fitType == "gaus") {
        strategy = std::make_unique<GaussianFitStrategy>();
    } else if (fitType == "expo") {
        strategy = std::make_unique<ExponentialFitStrategy>();
    } else {
        strategy.reset();
    }
}

bool WaveformFitContext::ApplyFit(ROOT::RVec<double>& waveform, TF1& fitFunction, double fitMin, double fitMax, double& score) {
    if (!strategy) {
        std::cerr << "Fit strategy not set!" << std::endl;
        return false;
    }
    fitFunction.SetRange(fitMin, fitMax);
    return strategy->FitWaveform(waveform, fitFunction, score);
}
