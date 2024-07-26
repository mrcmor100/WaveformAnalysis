#include "gmock/gmock.h"
#include "IWaveformFitStrategy.h"

class MockWaveformFitStrategy : public IWaveformFitStrategy {
public:
    MOCK_METHOD(bool, FitWaveform, (ROOT::RVec<double>& waveform, TF1& fitFunction, double& score), (override));
};