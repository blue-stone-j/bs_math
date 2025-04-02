
#include <gtest/gtest.h>

#include "knuth_shuffle.h"

TEST(knuth_shuffle_test, test1)
{
  math::stochastic::KnuthShuffle();
  math::stochastic::BruteForce();
}
