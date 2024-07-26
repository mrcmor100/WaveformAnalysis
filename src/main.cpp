#include "WaveformAnalyzer.h"

int main() {
    const std::string fileName = "waveforms.root";
    const std::string treeName = "waveformTree";
    const std::string outputFileName = "output.root";

    WaveformAnalyzer analyzer(fileName, treeName, outputFileName);
    analyzer.AnalyzeWaveforms();

    return 0;
}