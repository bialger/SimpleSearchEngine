#include <sstream>

#include <vector>
#include <set>
#include <gtest/gtest.h>

#include "IntegrationTestSuite.hpp"
#include "test_functions.hpp"

TEST_F(IntegrationTestSuite, QueryTest1) {
  std::vector<std::pair<double, size_t>> result = searcher_.SearchMostRelevant(SplitString("cum OR bird"));
  ASSERT_EQ(result.size(), 2);
  std::cout << result[0].first << " " << result[0].second << std::endl;
  std::cout << result[1].first << " " << result[1].second << std::endl;
  ASSERT_EQ(result[0].second, 0);
  ASSERT_EQ(result[1].second, 1);
}

TEST_F(IntegrationTestSuite, QueryTest2) {
  std::vector<std::pair<double, size_t>> result = searcher_.SearchMostRelevant(SplitString("You AND might AND also AND like"));
  ASSERT_EQ(result.size(), 2);
  std::cout << result[0].first << " " << result[0].second << std::endl;
  std::cout << result[1].first << " " << result[1].second << std::endl;
  ASSERT_EQ(result[0].second, 0);
  ASSERT_EQ(result[1].second, 2);
}

TEST_F(IntegrationTestSuite, QueryTest3) {
  std::vector<std::pair<double, size_t>> result = searcher_.SearchMostRelevant(SplitString("ET"));
  ASSERT_EQ(result.size(), 2);
  std::cout << result[0].first << " " << result[0].second << std::endl;
  std::cout << result[1].first << " " << result[1].second << std::endl;
  ASSERT_EQ(result[0].second, 2);
  ASSERT_EQ(result[1].second, 1);
}

TEST_F(IntegrationTestSuite, QueryTest4) {
  std::vector<std::pair<double, size_t>> result = searcher_.SearchMostRelevant(SplitString("ET OR You"));
  ASSERT_EQ(result.size(), 3);
  std::cout << result[0].first << " " << result[0].second << std::endl;
  std::cout << result[1].first << " " << result[1].second << std::endl;
  std::cout << result[2].first << " " << result[2].second << std::endl;
  ASSERT_EQ(result[0].second, 0);
  ASSERT_EQ(result[1].second, 1);
  ASSERT_EQ(result[2].second, 2);
}
