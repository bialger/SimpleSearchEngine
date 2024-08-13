#ifndef LIB_SEARCH_SEARCHER_HPP_
#define LIB_SEARCH_SEARCHER_HPP_

#include <vector>
#include <unordered_set>

#include "lib/index/Index.hpp"

class Searcher {
 public:
  Searcher() = delete;
  Searcher(const Index& index, double k, double b);

  std::vector<std::pair<double, size_t>> SearchMostRelevant(const std::vector<std::string>& query);

 private:
  const Index& index_;
  double k_;
  double b_;

  double ScoreForFile(size_t index, const std::unordered_set<std::string>& terms);
  double ScoreForTerm(double tf, double dl, double df);
};

#endif //LIB_SEARCH_SEARCHER_HPP_
