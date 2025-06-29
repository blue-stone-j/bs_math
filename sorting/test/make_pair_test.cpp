

#include <gtest/gtest.h>

#include <iostream>

#include <fstream>

#include "sorting/make_pair/make_pair.h"

TEST(bfprt_test, test1)
{
  std::vector<double> a;
  std::vector<double> b;
  double thr = 0.005;

  std::ifstream file("../include/make_pair/output.csv", std::ios_base::in); // 打开文件
  std::string line;

  if (file.is_open())
  {
    std::string value;

    getline(file, line);
    std::istringstream issb(line);
    while (getline(issb, value, ' '))
    { // 使用空格作为分隔符读取每个值
      // std::cout << value << std::endl; // 输出读取的值
      a.push_back(std::stod(value));
    }

    getline(file, line);
    std::istringstream issa(line);
    while (getline(issa, value, ' '))
    { // 使用空格作为分隔符读取每个值
      // std::cout << value << std::endl; // 输出读取的值
      b.push_back(std::stod(value));
    }

    file.close(); // 关闭文件
  }
  else
  {
    std::cout << "Unable to open file" << std::endl; // 如果文件无法打开，输出错误消息
  }

  auto pairs = findPairsOptimized(a, b, thr);

  for (const auto &p : pairs)
  {
    std::cout << "(" << p.first << ", " << p.second << ")" << std::endl;
  }
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}