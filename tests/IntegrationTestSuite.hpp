#ifndef INTEGRATIONTESTSUITE_HPP_
#define INTEGRATIONTESTSUITE_HPP_

#include <vector>
#include <sstream>
#include <random>
#include <limits>

#include <gtest/gtest.h>
#include "lib/index/Indexer.hpp"
#include "lib/search/Searcher.hpp"

struct IntegrationTestSuite : public testing::Test { // special test structure
  void SetUp() override; // method that is called at the beginning of every test

  void TearDown() override; // method that is called at the end of every test

 protected:
  const std::string kTestDir = "./intergration_tmp";
  Indexer indexer_{kTestDir};
  Searcher searcher_{indexer_.GetIndex(), 1.0, 0.75};
};

#endif //INTEGRATIONTESTSUITE_HPP_
