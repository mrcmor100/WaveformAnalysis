#ifndef WAVEFORMANALYZER_H
#define WAVEFORMANALYZER_H

#include "ROOT/RDataFrame.hxx"
#include "WaveformPreprocessor.h"
#include "WaveformFitContext.h"
#include "TFile.h"
#include "TTree.h"
#include "TF1.h"

class WaveformAnalyzer {
private:
    ROOT::RDataFrame df;
    WaveformPreprocessor preprocessor;
    WaveformFitContext fitContext;
    TFile outputFile;
    TTree outputTree;
    double score;

public:
    WaveformAnalyzer(const std::string& fileName, const std::string& treeName, const std::string& outputFileName);

    void AnalyzeWaveforms();
};

#endif // WAVEFORMANALYZER_H
