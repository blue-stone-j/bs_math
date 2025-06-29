#include <gtest/gtest.h>

#include "sorting/merge_vector/merge_vector.h"

TEST(merge_vector_test, three_vectors)
{
  std::vector<int> arr1 = {2, 4, 7, 10, 13};
  std::vector<int> arr2 = {1, 3, 5, 8, 11, 14};
  std::vector<int> arr3 = {6, 9, 12, 15, 18, 21};

  std::vector<int> merged_vector = mergeThreeSortedVectors(arr1, arr2, arr3);

  std::cout << "Merged Array: ";
  for (const auto &item : merged_vector)
  {
    std::cout << item << " ";
  }
  std::cout << std::endl;
}

TEST(merge_vector_test, several_vectors)
{
  std::vector<std::vector<int>> arrays = {
      {2, 4, 7, 10, 13},
      {1, 3, 5, 8, 11, 14},
      {6, 9, 12, 15, 18, 21},
      {0, 2, 6, 8, 10},
      {3, 7, 11}};

  std::vector<int> merged_vector = mergeSortedVectors(arrays);

  std::cout << "Merged Array: ";
  for (int num : merged_vector)
  {
    std::cout << num << " ";
  }
  std::cout << std::endl;
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}