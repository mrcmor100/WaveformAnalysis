#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "WaveformAnalyzer.h"
#include "MockWaveformFitStrategy.h"

// Example test case
TEST(WaveformAnalyzerTest, AnalyzeKnownWaveform) {
    // Setup known waveform
    ROOT::RVec<double> knownWaveform = {1.0, 2.0, 3.0, 4.0, 5.0};
    WaveformPreprocessor preprocessor;
    WaveformFitContext fitContext;

    // Use mock strategy for testing
    MockWaveformFitStrategy mockStrategy;
    EXPECT_CALL(mockStrategy, FitWaveform(testing::_, testing::_, testing::_))
        .Times(1)
        .WillOnce(testing::Return(true));

    fitContext.SetStrategy(std::make_unique<MockWaveformFitStrategy>());
    TF1 fitFunction("fitFunction", "gaus", 0, 5);
    double score = 0.0;
    bool result = fitContext.ApplyFit(knownWaveform, fitFunction, 0, 5, score);

    EXPECT_TRUE(result);
    EXPECT_EQ(score, 1.0);
}

// Main function to run tests
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}