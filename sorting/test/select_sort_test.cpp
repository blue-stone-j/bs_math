
#include <gtest/gtest.h>

#include <iostream>

#include "sorting/select_sort/select_sort.h"

TEST(select_sort_test, test1)
{
  std::cout << "----------------选择排序---------------" << std::endl;
  std::vector<int> a = {1110, 209, 386, 768, 185, 247, 606, 230, 834, 54, 12};

  std::cout << "排序之前的元素为:\n";
  for (const auto &element : a) // 循环排序前数组
  {
    std::cout << element << " ";
  }
  std::cout << std::endl;

  selectSort(a); // 选择法

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