#include "WaveformAnalyzer.h"
#include <iostream>
#include "TH1D.h"
#include "TCanvas.h"

WaveformAnalyzer::WaveformAnalyzer(const std::string& fileName, const std::string& treeName, const std::string& outputFileName)
    : df(treeName, fileName), outputFile(outputFileName.c_str(), "RECREATE"), outputTree("outputTree", "Fitting Results") {
    outputTree.Branch("score", &score, "score/D");
}

void WaveformAnalyzer::AnalyzeWaveforms() {
    outputFile.Write();
    outputFile.Close();
}
