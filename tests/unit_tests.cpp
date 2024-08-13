#include <sstream>

#include <vector>
#include <set>
#include <gtest/gtest.h>
#include <filesystem>
#include <fstream>

#include "UnitTestSuite.hpp"
#include "test_functions.hpp"

const std::string kLongText = "# Install script for directory: C:/Users/bialger/CLionProjects/labwork11-bialger/bin\n"
                              "\n"
                              "# Set the install prefix\n"
                              "if(NOT DEFINED CMAKE_INSTALL_PREFIX)\n"
                              "  set(CMAKE_INSTALL_PREFIX \"C:/Program Files (x86)/SimpleSearchEngine\")\n"
                              "endif()\n"
                              "string(REGEX REPLACE \"/$\" \"\" CMAKE_INSTALL_PREFIX \"${CMAKE_INSTALL_PREFIX}\")\n"
                              "\n"
                              "# Set the install configuration name.\n"
                              "if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)\n"
                              "  if(BUILD_TYPE)\n"
                              "    string(REGEX REPLACE \"^[^A-Za-z0-9_]+\" \"\"\n"
                              "           CMAKE_INSTALL_CONFIG_NAME \"${BUILD_TYPE}\")\n"
                              "  else()\n"
                              "    set(CMAKE_INSTALL_CONFIG_NAME \"Debug\")\n"
                              "  endif()\n"
                              "  message(STATUS \"Install configuration: \\\"${CMAKE_INSTALL_CONFIG_NAME}\\\"\")\n"
                              "endif()\n"
                              "\n"
                              "# Set the component getting installed.\n"
                              "if(NOT CMAKE_INSTALL_COMPONENT)\n"
                              "  if(COMPONENT)\n"
                              "    message(STATUS \"Install component: \\\"${COMPONENT}\\\"\")\n"
                              "    set(CMAKE_INSTALL_COMPONENT \"${COMPONENT}\")\n"
                              "  else()\n"
                              "    set(CMAKE_INSTALL_COMPONENT)\n"
                              "  endif()\n"
                              "endif()\n"
                              "\n"
                              "# Is this installation the result of a crosscompile?\n"
                              "if(NOT DEFINED CMAKE_CROSSCOMPILING)\n"
                              "  set(CMAKE_CROSSCOMPILING \"FALSE\")\n"
                              "endif()\n"
                              "\n"
                              "# Set default install directory permissions.\n"
                              "if(NOT DEFINED CMAKE_OBJDUMP)\n"
                              "  set(CMAKE_OBJDUMP \"C:/Program Files/JetBrains/CLion 2023.2.1/bin/mingw/bin/objdump.exe\")\n"
                              "endif()\n"
                              "";

TEST_F(UnitTestSuite, EmptyIndexTest) {
  ASSERT_EQ(indexer_.CreateIndex(), 0);
  ASSERT_TRUE(std::isnan(indexer_.GetIndex().GetDlAvg()));
  ASSERT_EQ(indexer_.GetIndex().GetIndex().size(), 0);
  ASSERT_EQ(indexer_.GetIndex().GetPostings().size(), 0);
}

TEST_F(UnitTestSuite, ReadAndWriteIndexTest) {
  Indexer indexer2("..");
  bool had_index = std::filesystem::is_regular_file(indexer2.GetIndex().GetIndexName());
  ASSERT_EQ(indexer2.CreateIndex(), 0);
  ASSERT_EQ(indexer2.GetIndex().WriteIndex(), 0);
  Index index2("..");
  ASSERT_EQ(index2.LoadIndex(), 0);
  std::stringstream ss;
  double writen_dl_avg = 0;
  ss << indexer2.GetIndex().GetDlAvg();
  ss >> writen_dl_avg;
  ASSERT_FLOAT_EQ(writen_dl_avg, index2.GetDlAvg());
  ASSERT_EQ(indexer2.GetIndex().GetIndex(), index2.GetIndex());
  ASSERT_EQ(indexer2.GetIndex().GetPostings(), index2.GetPostings());

  if (!had_index) {
    std::filesystem::remove(indexer2.GetIndex().GetIndexName());
  }
}

TEST_F(UnitTestSuite, CorrectIndexTest) {
  std::ofstream file(kTestDir + "/test.txt");
  file << kLongText;
  file.close();
  std::string canonical_path = std::filesystem::canonical(kTestDir + "/test.txt").string();
  std::vector<std::pair<std::string, size_t>> expected_index(1);
  expected_index[0] = {canonical_path, 159};
  ASSERT_EQ(indexer_.CreateIndex(), 0);
  ASSERT_EQ(indexer_.GetIndex().GetIndex(), expected_index);
  const std::unordered_map<std::string, std::unordered_map<size_t, size_t>>& postings = indexer_.GetIndex().GetPostings();
  ASSERT_EQ(postings.size(), 59);
  ASSERT_TRUE(postings.contains("install"));
  ASSERT_TRUE(postings.contains("cmake"));
  ASSERT_TRUE(postings.contains("set"));
  ASSERT_TRUE(postings.contains("component"));
  ASSERT_TRUE(postings.contains("endif"));
  ASSERT_TRUE(postings.contains("prefix"));
  ASSERT_TRUE(postings.contains("name"));
  ASSERT_TRUE(postings.contains("defined"));
  ASSERT_TRUE(postings.contains("config"));
  ASSERT_TRUE(postings.contains("bin"));
  ASSERT_EQ(postings.at("install").at(0), 17);
  ASSERT_EQ(postings.at("cmake").at(0), 15);
  ASSERT_EQ(postings.at("set").at(0), 10);
  ASSERT_EQ(postings.at("component").at(0), 8);
  ASSERT_EQ(postings.at("endif").at(0), 7);
  ASSERT_EQ(postings.at("prefix").at(0), 5);
  ASSERT_EQ(postings.at("name").at(0), 5);
  ASSERT_EQ(postings.at("defined").at(0), 4);
  ASSERT_EQ(postings.at("config").at(0), 4);
  ASSERT_EQ(postings.at("bin").at(0), 3);
}

TEST_F(UnitTestSuite, SearcherRequestTest1) {
  std::vector<std::pair<double, size_t>> result = searcher2_.SearchMostRelevant(SplitString("vector"));
  ASSERT_EQ(result.size(), 2);
  ASSERT_EQ(result[0].second, 1);
  ASSERT_EQ(result[1].second, 0);
  std::vector<std::pair<double, size_t>> result2 = searcher2_.SearchMostRelevant(SplitString("list"));
  ASSERT_EQ(result2.size(), 1);
  ASSERT_EQ(result2[0].second, 0);
}

TEST_F(UnitTestSuite, SearcherRequestTest2) {
  ASSERT_NO_THROW(searcher2_.SearchMostRelevant(SplitString("for")));
  ASSERT_NO_THROW(searcher2_.SearchMostRelevant(SplitString("vector OR list")));
  ASSERT_NO_THROW(searcher2_.SearchMostRelevant(SplitString("vector AND list")));
  ASSERT_NO_THROW(searcher2_.SearchMostRelevant(SplitString("(for)")));
  ASSERT_NO_THROW(searcher2_.SearchMostRelevant(SplitString("(vector OR list)")));
  ASSERT_NO_THROW(searcher2_.SearchMostRelevant(SplitString("(vector AND list)")));
  ASSERT_NO_THROW(searcher2_.SearchMostRelevant(SplitString("(while OR for) AND vector")));
  ASSERT_NO_THROW(searcher2_.SearchMostRelevant(SplitString("for AND and")));
}

TEST_F(UnitTestSuite, SearcherRequestTest3) {
  ASSERT_THROW(searcher2_.SearchMostRelevant(SplitString("for AND")), std::logic_error);
  ASSERT_THROW(searcher2_.SearchMostRelevant(SplitString("vector list")), std::logic_error);
  ASSERT_THROW(searcher2_.SearchMostRelevant(SplitString("for AND OR list")), std::logic_error);
  ASSERT_THROW(searcher2_.SearchMostRelevant(SplitString("vector Or list")), std::logic_error);
  ASSERT_THROW(searcher2_.SearchMostRelevant(SplitString("(while OR for) and vector")), std::logic_error);
  ASSERT_THROW(searcher2_.SearchMostRelevant(SplitString("(for))")), std::logic_error);
  ASSERT_THROW(searcher2_.SearchMostRelevant(SplitString("veritas")), std::logic_error);
}
