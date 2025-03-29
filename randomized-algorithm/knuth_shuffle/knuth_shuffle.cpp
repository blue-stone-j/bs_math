#include <iostream>
#include <stdlib.h>
#include <time.h>

void KnuthShuffle()
{
  std::cout << "\n KnuthShuffle Solution";
  srand(time(NULL));
  int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,
               14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30};
  std::cout << "\n UnShuffled Array:\n";
  for (int j = 0; j < 30; j++)
  {
    std::cout << " " << arr[j] << " ";
  }
  int i, mark = 0, temp;
  while (mark < 30)
  {
    i = rand() % (30 - mark) + mark;

    // exchange two num from remained nunbers
    temp      = arr[mark];
    arr[mark] = arr[i];
    arr[i]    = temp;
    mark++;
  }
  std::cout << "\n Shuffled Array:\n";
  for (int j = 0; j < 30; j++)
  {
    std::cout << " " << arr[j] << " ";
  }
}

void BruteForce()
{
  std::cout << "\n Brute Force Solution";
  srand(time(NULL));
  int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,
               14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30};
  std::cout << "\n UnShuffled Array:\n";
  for (int j = 0; j < 30; j++)
  {
    std::cout << " " << arr[j] << " ";
  }
  int i, pos = 0;
  int shuffarr[30];
  for (int j = 29; j > 0; j--)
  {
    i             = rand() % j;
    shuffarr[pos] = arr[i];
    for (int delpos = i; delpos <= j; delpos++)
    {
      arr[delpos] = arr[delpos + 1];
    }
    pos++;
  }
  std::cout << "\n Shuffled Array:\n";
  for (int j = 0; j < 30; j++)
  {
    std::cout << " " << shuffarr[j] << " \n";
  }
}

int main(void)
{
  KnuthShuffle();
  BruteForce();
  return 0;
}