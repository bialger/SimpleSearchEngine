#include <sstream>

#include <vector>
#include <set>
#include <gtest/gtest.h>

#include "IntegrationTestSuite.hpp"
#include "test_functions.hpp"

TEST_F(IntegrationTestSuite, QueryTest1) {
  std::vector<std::pair<double, size_t>> result = searcher_.SearchMostRelevant(SplitString("cum OR bird"));
  ASSERT_EQ(result.size(), 2);
  const std::vector<std::pair<std::string, size_t>>& index = indexer_.GetIndex().GetIndex();
  ASSERT_EQ(ExtractFilename(index, result[0]), "file1");
  ASSERT_EQ(ExtractFilename(index, result[1]), "file2");
}

TEST_F(IntegrationTestSuite, QueryTest2) {
  std::vector<std::pair<double, size_t>> result = searcher_.SearchMostRelevant(SplitString("You AND might AND also AND like"));
  ASSERT_EQ(result.size(), 2);
  const std::vector<std::pair<std::string, size_t>>& index = indexer_.GetIndex().GetIndex();
  ASSERT_EQ(ExtractFilename(index, result[0]), "file1");
  ASSERT_EQ(ExtractFilename(index, result[1]), "file3");
}

TEST_F(IntegrationTestSuite, QueryTest3) {
  std::vector<std::pair<double, size_t>> result = searcher_.SearchMostRelevant(SplitString("ET"));
  ASSERT_EQ(result.size(), 2);
  const std::vector<std::pair<std::string, size_t>>& index = indexer_.GetIndex().GetIndex();
  ASSERT_EQ(ExtractFilename(index, result[0]), "file3");
  ASSERT_EQ(ExtractFilename(index, result[1]), "file2");
}

TEST_F(IntegrationTestSuite, QueryTest4) {
  std::vector<std::pair<double, size_t>> result = searcher_.SearchMostRelevant(SplitString("ET OR You"));
  ASSERT_EQ(result.size(), 3);
  const std::vector<std::pair<std::string, size_t>>& index = indexer_.GetIndex().GetIndex();
  ASSERT_EQ(ExtractFilename(index, result[0]), "file1");
  ASSERT_EQ(ExtractFilename(index, result[1]), "file2");
  ASSERT_EQ(ExtractFilename(index, result[2]), "file3");
}
