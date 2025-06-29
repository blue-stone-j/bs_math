
#include <vector>

#ifndef SORTING_SELECT_SORT_H
#define SORTING_SELECT_SORT_H

/*|property|description|
|---|---|
|Time Complexity|consistently runs in O(n²) time, regardless of the input’s initial order.|
|In-Place|it requires only a constant amount of additional memory space (O(1)).|
|Not Stable|it does not preserve the relative order of equal elements.|
*/

template <typename T>
void selectSort(std::vector<T> &a)
{
  int pos;  // 目前最小的数字的位置
  int temp; // temp存最小数字
  for (int i = 0; i < a.size(); i++)
  {
    pos  = i;                              // 最小值位置
    temp = a[i];                           // 最小值
    for (int j = i + 1; j < a.size(); j++) // 查找最小的字符
    {
      if (a[j] < temp) // 新最小值出现
      {
        pos  = j; // 新的最小字符的位置
        temp = a[j];
      }
    }
    a[pos] = a[i]; // 交换元素
    a[i]   = temp; // 最小值置于最低位
  }
}

#endif // SORTING_SELECT_SORT_H