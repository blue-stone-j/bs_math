
#include <algorithm>
#include <vector>

#ifndef SORTING_BFPRT_BFPRT_H
#define SORTING_BFPRT_BFPRT_H

template <typename T>
std::size_t partition(std::vector<T> &arr, std::size_t left, std::size_t right, std::size_t pivot_index)
{
  T pivot_value = arr[pivot_index];
  std::swap(arr[pivot_index], arr[right]); // Move pivot to end
  std::size_t store_index = left;
  for (std::size_t i = left; i < right; i++)
  {
    if (arr[i] < pivot_value)
    {
      std::swap(arr[i], arr[store_index]);
      store_index++;
    }
  }
  std::swap(arr[store_index], arr[right]); // Move pivot to its final place
  return store_index;
}

template <typename T>
T select(std::vector<T> &arr, std::size_t left, std::size_t right, std::size_t k);

template <typename T>
T medianOfMedians(std::vector<T> &arr, std::size_t left, std::size_t right)
{
  // Base case: if the array is small enough, return the median directly
  if (right - left + 1 <= 5)
  {
    std::sort(arr.begin() + left, arr.begin() + right + 1);
    return arr[left + (right - left) / 2];
  }

  // Recursively find the median of all groups of five
  for (std::size_t i = left; i <= right; i += 5)
  {
    std::size_t sub_right = i + 4;
    if (sub_right > right) sub_right = right;
    auto median = medianOfMedians(arr, i, sub_right);
    std::swap(arr[left + (i - left) / 5], median); // Store median of each block at start of array
  }

  // Now find the median of medians using the select algorithm
  int mid = (right - left) / 10 + left + 1;
  return select(arr, left, left + (right - left) / 5, mid);
}

template <typename T>
T select(std::vector<T> &arr, std::size_t left, std::size_t right, std::size_t k)
{
  while (true)
  {
    if (left == right) { return arr[left]; }
    std::size_t pivot_index = medianOfMedians(arr, left, right);
    pivot_index             = partition(arr, left, right, pivot_index);
    if (k == pivot_index)
    {
      return arr[k];
    }
    else if (k < pivot_index)
    {
      right = pivot_index - 1;
    }
    else
    {
      left = pivot_index + 1;
    }
  }
}

#endif // SORTING_BFPRT_BFPRT_H