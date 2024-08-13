#ifndef LIB_INDEX_INDEX_HPP_
#define LIB_INDEX_INDEX_HPP_

#include <vector>
#include <string>
#include <unordered_map>
#include <cstdint>

class Index {
 public:
  static const std::string kIndexFile;
  static constexpr uint16_t kMajorVersion_ = 0;
  static constexpr uint16_t kMinorVersion = 1;

  Index() = delete;
  explicit Index(const std::string& target);

  int32_t LoadIndex();
  int32_t WriteIndex() const;

  void AddFile(const std::string& path);
  void SetWordCountForIndex(size_t index, size_t count);
  void SetDlAvg(double dl_avg);
  void AddWordForIndex(const std::string& word, size_t index);

  const std::vector<std::pair<std::string, size_t>>& GetIndex() const;
  const std::unordered_map<std::string, std::unordered_map<size_t, size_t>>& GetPostings() const;
  double GetDlAvg() const;
  std::string GetIndexName() const;

 private:
  std::string target_;
  std::vector<std::pair<std::string, size_t>> index_;
  std::unordered_map<std::string, std::unordered_map<size_t, size_t>> postings_;
  double dl_avg_;
};

#endif //LIB_INDEX_INDEX_HPP_
