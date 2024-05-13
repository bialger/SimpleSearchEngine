#ifndef UNITTESTSUITE_HPP_
#define UNITTESTSUITE_HPP_

#include <vector>
#include <sstream>
#include <random>
#include <limits>

#include <gtest/gtest.h>
#include "lib/index/Indexer.hpp"
#include "lib/search/Searcher.hpp"

struct UnitTestSuite : public testing::Test { // special test structure
  void SetUp() override; // method that is called at the beginning of every test

  void TearDown() override; // method that is called at the end of every test

 protected:
  const std::string kTestDir = "tmp";
  Indexer indexer_{kTestDir};
  Searcher searcher_{indexer_.GetIndex(), 0.5, 0.5};
};

#endif //UNITTESTSUITE_HPP_
