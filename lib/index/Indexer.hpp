#ifndef LIB_INDEX_INDEXER_HPP_
#define LIB_INDEX_INDEXER_HPP_

#include "Index.hpp"

class Indexer {
 public:
  Indexer() = delete;
  explicit Indexer(const std::string& target);

  int32_t CreateIndex();

  const Index& GetIndex() const;

 private:
  std::string target_;
  Index index_writer_;

  void AddFilesRecursive(const std::string& path);
  static bool IsTextFile(const std::string& path);
};

#endif //LIB_INDEX_INDEXER_HPP_