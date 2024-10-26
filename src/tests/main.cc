#include <gtest/gtest.h>

#include "../matrix.h"
#include "constructors.h"
#include "operations.h"
#include "operators.h"

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}