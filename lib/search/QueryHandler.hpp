#ifndef LIB_SEARCH_QUERYHANDLER_HPP_
#define LIB_SEARCH_QUERYHANDLER_HPP_

#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>

enum class Operation {
  kNoOperation,
  kAnd,
  kOr
};

class QueryHandler {
 public:
  QueryHandler() = delete;
  QueryHandler(const std::vector<std::string>& query,
               const std::unordered_map<std::string, std::unordered_map<size_t, size_t>>& postings);

  void HandleQuery();

  const std::unordered_set<std::string>& GetTerms() const;
  const std::unordered_set<size_t>& GetIndices() const;

 private:
  std::string query_;
  const std::unordered_map<std::string, std::unordered_map<size_t, size_t>>& postings_;
  std::unordered_set<size_t> indices_;
  std::unordered_set<std::string> terms_;

  static void Unite(std::unordered_set<size_t>& a, const std::unordered_set<size_t>& b);
  static void Intersect(std::unordered_set<size_t>& a, const std::unordered_set<size_t>& b);

  std::unordered_set<size_t> ParseQuery(std::string::iterator first, std::string::iterator last);
  void InsertIndicesForTerm(const std::string& term, std::unordered_set<size_t>& indices);
};

#endif //LIB_SEARCH_QUERYHANDLER_HPP_
