
#include <vector>

#ifndef SORTING_QUICK_SORT_H
#define SORTING_QUICK_SORT_H

/*
|property|description|
|---|---|
|Time Complexity|best case: O(n log n), average case: O(n log n), worst case: O(n²)|
|Space Complexity|O(log n): it is an in-place sorting algorithm, meaning it requires only a small amount of additional stack space for the recursive calls.
|
|Fast Average Performance|can handle large datasets efficiently|
|Adaptable|using insertion sort for small sub-arrays.|
|Worst-Case Performance|O(n²)|
|Not Stable|it does not preserve the relative order of equal elements.|
|Recursion Overhead|it can lead to stack overflow issues for very large arrays or poor pivot choices.|
*/

// Function to partition the array on the basis of pivot
template <typename T>
std::size_t partition(std::vector<T> &arr, std::size_t low, std::size_t high)
{
  std::size_t pivot = arr[high]; // Choosing the rightmost element as pivot
  std::size_t i     = (low - 1); // Index of smaller element

  for (std::size_t j = low; j <= high - 1; j++)
  {
    // If current element is smaller than the pivot
    if (arr[j] < pivot)
    {
      i++; // Increment index of smaller element
      std::swap(arr[i], arr[j]);
    }
  }
  std::swap(arr[i + 1], arr[high]); // move the pivot to middle of larger and smaller
  return (i + 1);
}

// Function to perform quick sort(data, index of left elememt, index of right)
template <typename T>
void quickSort(std::vector<T> &arr, std::size_t low, std::size_t high)
{
  if (low < high)
  {
    // Partition the array and get the partitioning index
    std::size_t pi = partition(arr, low, high);

    // Recursively sort elements before and after partition
    quickSort(arr, low, pi - 1);
    quickSort(arr, pi + 1, high);
  }
}

#endif // SORTING_QUICK_SORT_H

/*
Explanation :
1. Partition Function :
  This function takes the last element as pivot and places it at the correct position in the sorted array.All elements
  smaller than the pivot are moved to the left, and all greater elements are moved to the right.

2.QuickSort Function :
  This is a recursive function that sorts the array.It calls the partition function to get the pivot index and then
  recursively sorts the sub-arrays.

3.Main Function :
  An example array is initialized and printed.The quickSort function is called to sort the array.The sorted array is
  printed.This implementation ensures the quick sort algorithm is performed correctly with a complexity of (n log n)
  on average.
*/