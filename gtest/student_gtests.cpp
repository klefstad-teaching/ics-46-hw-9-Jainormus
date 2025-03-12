#include <gtest/gtest.h>

#include "../src/dijkstras.h"
#include "../src/ladder.h"

TEST(is_adjacent, ValidityTest) {
  EXPECT_TRUE(is_adjacent("cow", "caw"));
  EXPECT_TRUE(is_adjacent("Feet", "Feat"));
  EXPECT_TRUE(is_adjacent("Feet", "Fet"));
  EXPECT_TRUE(is_adjacent("Can", "Cane"));
}
