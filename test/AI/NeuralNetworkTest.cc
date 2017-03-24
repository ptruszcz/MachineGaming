//
// Created by fajqa on 23.03.17.
//

#include <gtest/gtest.h>
#include "NeuralNetwork.h"


TEST(HelloTest, Hello) {
    ASSERT_EQ(greet(), greet());
}

TEST(NeuralNetworkTest, InitTest) {
    std::vector<int> layer_sizes({1,2,3});
    NeuralNetwork neuralNetwork(layer_sizes);
    arma::mat input(1, layer_sizes[0]);
    input += 1;
    input.print();

    for (int i = 0; i < 10000; ++i) {
        neuralNetwork.feedForward(input);
        arma::mat actual = neuralNetwork.backpropagate(arma::mat({1,0,1}));

        if (i % 1000 == 0) {
            std::cout << "Iteration #" << i << std::endl << "Actual output: ";
            neuralNetwork.output->print();
            std::cout << "Mean error: " << arma::mean(arma::mean(actual)) << std::endl;
        }
    }

    ASSERT_TRUE(true);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}