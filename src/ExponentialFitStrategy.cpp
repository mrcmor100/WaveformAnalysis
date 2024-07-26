#include "ExponentialFitStrategy.h"
#include "TH1D.h"
#include "TF1.h"

bool ExponentialFitStrategy::FitWaveform(ROOT::RVec<double>& waveform, TF1& fitFunction, double& score) {
    // Define the Exponential fit function
    fitFunction = TF1("fitFunction", "expo", 0, waveform.size());

    // Fill a histogram with the waveform data
    TH1D hist("hist", "Waveform", waveform.size(), 0, waveform.size());
    for (size_t i = 0; i < waveform.size(); ++i) {
        hist.SetBinContent(i + 1, waveform[i]);
    }

    // Perform the fit
    int fitResult = hist.Fit(&fitFunction, "Q");

    // Evaluate the fit quality and set the score
    score = (fitResult == 0) ? 1.0 : 10.0;
    if (fitResult == 0) {
        std::cout << "Exponential fit succeeded." << std::endl;
        return true;
    } else {
        std::cout << "Exponential fit failed." << std::endl;
        return false;
    }
}
