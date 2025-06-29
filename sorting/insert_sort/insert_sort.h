
#include <vector>

#ifndef SORTING_INSERT_SORT_H
#define SORTING_INSERT_SORT_H

/*|property|description|
|---|---|
|In-Place|it requires only a constant amount of additional memory space (O(1)).|
|Stability|it preserves the relative order of equal elements.|
|Adaptive|it can handle fully sorted data or partially sorted data.|
|Online Sorting|insertion sort can be used to sort data as it is received, which is useful for real-time applications.|
*/

template <typename T>
void insertSort(std::vector<T> &a)
{
  int temp; // 临时变量
  int i, j; // 循环变量
  for (i = 1; i < a.size(); i++)
  {
    temp = a[i];                               // 获取比较值
    for (j = i; j > 0 && a[j - 1] > temp; j--) // 前i个元素,如果有大元素交换
    {
      a[j] = a[j - 1]; // 移到当前位置
    }
    a[j] = temp; // 将最后一个交换的j位置元素赋值temp
  }
}

#endif