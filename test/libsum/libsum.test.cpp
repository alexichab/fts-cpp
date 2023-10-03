#include <gtest/gtest.h>
#include <libsum/libsum.hpp>

TEST(SumTest, Trivial) {
  EXPECT_EQ(2, sum::sum(1, 1));
  EXPECT_EQ(7.7, sum::sum(5, 2.7));
  EXPECT_EQ(3, sum::sum(1, 2));
}

// // int main(int argc, char *argv[]) {

//     testing::InitGoogleTest(&argc, argv);
//     return RUN_ALL_TESTS();
//}
