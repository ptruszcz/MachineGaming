//
// Created by fajqa on 23.03.17.
//

#include <gtest/gtest.h>
#include "NeuralNetwork.h"


TEST(HelloTest, Hello) {
    ASSERT_EQ(greet(), greet());
}

TEST(NeuralNetworkTest, InitTest) {
    int iterations = 10000;
    std::vector<int> layer_sizes({3,2,3,2,3});
    NeuralNetwork neuralNetwork(layer_sizes);
    arma::mat input(1, layer_sizes[0]);
    input += 1;
    input.print();

    for (int i = 0; i < iterations; ++i) {
        neuralNetwork.feedForward(input);
        arma::mat output_error = neuralNetwork.backpropagate(arma::mat({1,0,1}));

        if (i % (iterations/10) == 0) {
            std::cout << "Iteration #" << i << std::endl << "Actual getOutput: ";
            neuralNetwork.getOutput().print();
            std::cout << "Mean error: " << arma::mean(arma::mean(output_error)) << std::endl;
        }
    }

    ASSERT_TRUE(true);
}

TEST(NeuralNetworkTest, CopyConstructorTest) {
    int iterations = 10000;
    std::vector<int> layer_sizes({3,3});

    NeuralNetwork neuralNetwork1(layer_sizes);
    arma::mat input(1, layer_sizes[0]);
    input += 1;
    input.print();

    for (int i = 0; i < iterations; ++i) {
        neuralNetwork1.feedForward(input);
        arma::mat output_error = neuralNetwork1.backpropagate(arma::mat({1,0,1}));

        if (i % (iterations/10) == 0) {
            std::cout << "Iteration #" << i << std::endl << "Actual getOutput: ";
            neuralNetwork1.getOutput().print();
            std::cout << "Mean error: " << arma::mean(arma::mean(output_error)) << std::endl;
        }
    }

    NeuralNetwork neuralNetwork2(neuralNetwork1);
    auto expected = neuralNetwork1.feedForward(input);
    auto actual = neuralNetwork2.feedForward(input);

    ASSERT_TRUE(arma::accu(expected) == arma::accu(actual));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}