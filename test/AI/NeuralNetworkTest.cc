#include <gtest/gtest.h>
#include "NeuralNetwork.h"


TEST(HelloTest, Hello) {
    ASSERT_EQ(greet(), greet());
}

TEST(NeuralNetworkTest, InitTest) {

}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}