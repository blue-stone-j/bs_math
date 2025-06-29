
#include <iostream>

#include <gtest/gtest.h>

#include "sorting/bubble_sort/bubble_sort.h"

TEST(bubble_sort_test, test1)
{
  std::cout << "----------------冒泡排序---------------" << std::endl;
  std::vector<int> a = {0, 209, 386, 768, 185, 247, 606, 230, 834, 54, 12};
  std::cout << "排序之前的元素为:\n";
  for (const auto &element : a) // 循环排序前数组
  {
    std::cout << element << " ";
  }
  std::cout << std::endl;
  bubble(a); // 冒泡法
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
