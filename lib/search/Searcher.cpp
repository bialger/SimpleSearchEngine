#include <cmath>
#include <algorithm>

#include "Searcher.hpp"
#include "QueryHandler.hpp"

Searcher::Searcher(const Index& index, double k, double b) : index_(index), k_(k), b_(b) {}

double Searcher::ScoreForTerm(double tf, double dl, double df) {
  double document_frequency = (static_cast<double>(index_.GetIndex().size()) - df + 0.5) / (df + 0.5);
  double term_frequency_curving = k_ * (1 - b_ + b_ * (dl / index_.GetDlAvg()));
  double term_frequency = tf * (k_ + 1) / (tf + term_frequency_curving);
  double score = term_frequency * std::log(document_frequency);

  return score;
}

double Searcher::ScoreForFile(size_t index, const std::unordered_set<std::string>& terms) {
  double score = 0.0;

  for (auto& term : terms) {
    const std::unordered_map<size_t, size_t>& posting_for_term = index_.GetPostings().at(term);
    auto it = posting_for_term.find(index);

    if (it == posting_for_term.end()) {
      continue;
    }

    score += ScoreForTerm(static_cast<double>(it->second),
                          static_cast<double>(index_.GetIndex()[index].second),
                          static_cast<double>(posting_for_term.size()));
  }

  return score;
}

std::vector<std::pair<double, size_t>> Searcher::SearchMostRelevant(const std::vector<std::string>& query) {
  QueryHandler query_handler(query, index_.GetPostings());
  query_handler.HandleQuery();
  std::vector<std::pair<double, size_t>> result;

  for (auto& index : query_handler.GetIndices()) {
    double score = ScoreForFile(index, query_handler.GetTerms());
    result.emplace_back(score, index);
  }

  std::sort(result.begin(), result.end(), std::greater<>());

  return result;
}
