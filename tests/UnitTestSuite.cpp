#include <filesystem>

#include "UnitTestSuite.hpp"

void UnitTestSuite::SetUp() {
  std::filesystem::create_directories(kTestDir);
  false_index_.AddFile("test1");
  false_index_.AddFile("test2");
  false_index_.SetWordCountForIndex(0, 2);
  false_index_.SetWordCountForIndex(1, 20);
  false_index_.SetDlAvg(11);
  false_index_.AddWordForIndex("vector", 0);
  false_index_.AddWordForIndex("list", 0);
  false_index_.AddWordForIndex("vector", 1);
  false_index_.AddWordForIndex("while", 1);

  for (size_t i = 0; i < 9; ++i) {
    false_index_.AddWordForIndex("for", 1);
    false_index_.AddWordForIndex("and", 1);
  }
}
void UnitTestSuite::TearDown() {
  std::filesystem::remove_all(kTestDir);
}
