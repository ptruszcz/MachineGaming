//
// Created by fajqa on 23.03.17.
//

#include <gtest/gtest.h>
#include "NeuralNetwork.h"


TEST(HelloTest, Hello) {
    ASSERT_EQ(greet(), greet());
}

TEST(NeuralNetworkTest, InitTest) {
    std::vector<int> layerSizes({1,2,3});
    NeuralNetwork neuralNetwork(layerSizes);

    ASSERT_TRUE(true);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}