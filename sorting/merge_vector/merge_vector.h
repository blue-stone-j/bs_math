
#include <queue>
#include <vector>

/*Here are several sorted arrays. Merge these arrays and keep new arrat sorted. Here are commands to compile and run.
*/

#ifndef SORTING_MERGE_VECTOR_H
#define SORTING_MERGE_VECTOR_H

template <typename T>
std::vector<T> mergeThreeSortedVectors(const std::vector<T> &arr1,
                                       const std::vector<T> &arr2,
                                       const std::vector<T> &arr3)
{
  std::size_t i = 0, j = 0, k = 0;
  std::vector<T> result;

  while (i < arr1.size() && j < arr2.size() && k < arr3.size())
  {
    if (arr1[i] < arr2[j])
    {
      if (arr1[i] < arr3[k])
      {
        result.push_back(arr1[i++]);
      }
      else
      {
        result.push_back(arr3[k++]);
      }
    }
    else
    {
      if (arr2[j] < arr3[k])
      {
        result.push_back(arr2[j++]);
      }
      else
      {
        result.push_back(arr3[k++]);
      }
    }
  }

  // Handle the remaining elements in arr1
  while (i < arr1.size())
  {
    result.push_back(arr1[i++]);
  }

  // Handle the remaining elements in arr2
  while (j < arr2.size())
  {
    result.push_back(arr2[j++]);
  }

  // Handle the remaining elements in arr3
  while (k < arr3.size())
  {
    result.push_back(arr3[k++]);
  }

  return result;
}

// 定义一个用于存储元素和其来源数组索引的结构体
template <typename T>
struct Element
{
  T value;
  int array_index;
  int element_index;
};

// 比较函数，用于构建最小堆
template <typename T>
struct Compare
{
  bool operator()(Element<T> const &e1, Element<T> const &e2)
  {
    return e1.value > e2.value;
  }
};

template <typename T>
std::vector<T> mergeSortedVectors(const std::vector<std::vector<T>> &arrays)
{
  std::priority_queue<Element<T>, std::vector<Element<T>>, Compare<T>> min_heap;
  std::vector<int> result;

  // 初始化堆，将每个数组的第一个元素加入到堆中
  for (int i = 0; i < arrays.size(); ++i)
  {
    if (!arrays[i].empty())
    {
      min_heap.push({arrays[i][0], i, 0});
    }
  }

  // 循环直到堆为空
  while (!min_heap.empty())
  {
    Element current = min_heap.top();
    min_heap.pop();
    result.push_back(current.value);

    // 如果当前数组中还有元素，将下一个元素加入堆中
    if (current.element_index + 1 < arrays[current.array_index].size())
    {
      min_heap.push({arrays[current.array_index][current.element_index + 1], current.array_index, current.element_index + 1});
    }
  }

  return result;
}

#endif