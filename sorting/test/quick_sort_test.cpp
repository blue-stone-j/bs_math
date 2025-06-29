
#include <gtest/gtest.h>

#include <iostream>

#include "sorting/quick_sort/quick_sort.h"

TEST(quick_sort_test, test1)
{
  std::cout << "----------------快速排序---------------" << std::endl;
  std::vector<int> a = {10, 7, 8, 9, 1, 5};
  std::cout << "排序之前的元素为:\n";
  for (const auto &element : a) // 循环排序前数组
  {
    std::cout << element << " ";
  }
  std::cout << std::endl;

  quickSort(a, 0, a.size() - 1); // 快速排序

  std::cout << "排序结果为:\n";
  for (const auto &element : a) // 循环排序前数组
  {
    std::cout << element << " ";
  }
  std::cout << std::endl;
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}