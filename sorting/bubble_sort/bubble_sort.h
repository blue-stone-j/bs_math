
#include <vector>

#ifndef SORTING_BUBBLE_SORT_BUBBLE_SORT_H
#define SORTING_BUBBLE_SORT_BUBBLE_SORT_H

/*
|property|description|
|---|---|
|In-Place|it requires only a constant amount of additional memory space (O(1)).|
|Stability|it preserves the relative order of equal elements.|
|Not Adaptive|While it performs well on fully sorted lists, bubble sort does not adapt to partially sorted data.|
|Slow |on large lists or large data sets|
*/

template <typename T>
void bubble(std::vector<T> &a) // 冒泡排序
{
  int temp;                              // 临时变量
  for (int i = 0; i < a.size() - 1; i++) // 元素比较界限
  {
    for (int j = 0; j < a.size() - 1 - i; j++) // 该元素与加1位置元素比较
    {
      if (a[j] > a[j + 1]) // 把大元素放到位置右
      {
        temp     = a[j]; // 元素交换
        a[j]     = a[j + 1];
        a[j + 1] = temp;
      }
    }
  }
}

#endif // SORTING_BUBBLE_SORT_BUBBLE_SORT_H