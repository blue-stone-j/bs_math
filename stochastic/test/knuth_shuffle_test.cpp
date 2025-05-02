
#include <gtest/gtest.h>

#include "stochastic/knuth_shuffle/knuth_shuffle.h"

TEST(knuth_shuffle_test, test1)
{
  math::stochastic::KnuthShuffle();
  math::stochastic::BruteForce();
}
