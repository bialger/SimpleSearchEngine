#include <iterator>
#include <sstream>
#include <random>
#include <limits>
#include <filesystem>

#include "test_functions.hpp"

std::vector<std::string> SplitString(const std::string& str) {
  std::istringstream iss(str);

  return {std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>()};
}

std::string ExtractFilename(const std::vector<std::pair<std::string, size_t>>& index,
                                     const std::pair<double, size_t>& result) {
  std::filesystem::path p(index[result.second].first);
  return p.filename().string();
}

std::vector<int32_t> GetRandomNumbers(size_t n) {
  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<std::mt19937::result_type>
      dist(0, std::numeric_limits<uint32_t>::max());
  std::vector<int32_t> result(n);

  for (int32_t& element : result) {
    element = static_cast<int32_t>(dist(rng));
  }

  return result;
}

uint32_t GetRandomNumber() {
  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<std::mt19937::result_type>
      dist(0, std::numeric_limits<uint32_t>::max());

  return dist(rng);
}
