#include <gtest/gtest.h>

#include <iostream>

#include "sorting/bfprt/bfprt.h"

TEST(bfprt_test, test1)
{
  std::vector<int> arr = {9, 1, 0, 5, 4, 8, 2, 6, 3, 7};
  std::size_t k        = 5; // Find the k-th smallest element, k is zero-based index
  std::size_t result   = select(arr, 0, arr.size() - 1, k);
  std::cout << "The " << k + 1 << "th smallest element is " << result << std::endl;
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
