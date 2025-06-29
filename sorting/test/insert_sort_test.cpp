
#include <iostream>

#include <gtest/gtest.h>

#include "sorting/insert_sort/insert_sort.h"

TEST(insert_sort_test, test1)
{
  std::cout << "----------------插入排序---------------" << std::endl;
  std::vector<int> a = {0, 209, 386, 768, 185, 247, 606, 230, 834, 54, 12};
  std::cout << "排序之前的元素为:\n";
  for (const auto &element : a) // 循环排序前数组
  {
    std::cout << element << " ";
  }
  std::cout << std::endl;

  insertSort(a); // 插入法

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
