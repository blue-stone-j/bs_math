
#include <vector>
#include <algorithm>

#ifndef SORTING_MAKE_PAIR_H
#define SORTING_MAKE_PAIR_H

/*
Here are two arrays, find two values that close to each other from two arrays respectively and make them a pair. Here are commands to compile and run.
```bash
python3 generate_arrays.py # generate two random arrays
```
*/

template <typename T>
std::vector<std::pair<T, T>> findPairsOptimized(const std::vector<T> &a,
                                                const std::vector<T> &b,
                                                const T thr)
{
  std::vector<std::pair<T, T>> pairs;
  size_t index_a = 0; // 用于遍历数组a

  for (T item_b : b)
  {
    T closest_diff   = std::numeric_limits<T>::max();
    T closest_item_a = 0.0;
    bool found       = false;

    // 向前移动indexA直到找到更大的元素或结束
    while (index_a < a.size() && a[index_a] <= item_b)
    {
      T current_diff = std::abs(a[index_a] - item_b);
      if (current_diff < closest_diff)
      {
        closest_diff   = current_diff;
        closest_item_a = a[index_a];
        found          = true;
      }
      ++index_a;
    }

    // 检查indexA当前位置的元素（如果存在），可能比之前的元素更接近numB
    if (index_a < a.size())
    {
      T current_diff = std::abs(a[index_a] - item_b);
      if (current_diff < closest_diff)
      {
        closest_diff   = current_diff;
        closest_item_a = a[index_a];
        found          = true;
      }
    }

    if (found && closest_diff <= thr)
    {
      pairs.emplace_back(item_b, closest_item_a);
    }

    // 如果当前a[index_a]大于numB，下一个numB可能还是与当前a[index_a]最接近，所以indexA不需要回退
  }

  // 对结果进行排序，确保按照升序排列
  std::sort(pairs.begin(), pairs.end());

  return pairs;
}

#endif // SORTING_MAKE_PAIR_H