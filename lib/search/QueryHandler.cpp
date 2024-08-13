#include <algorithm>
#include <stdexcept>
#include <stack>

#include "QueryHandler.hpp"

QueryHandler::QueryHandler(const std::vector<std::string>& query,
                           const std::unordered_map<std::string, std::unordered_map<size_t, size_t>>& postings)
    : query_(), postings_(postings), indices_(), terms_() {
  for (auto word : query) {
    if (word.find("AND") != std::string::npos) {
      if (word.length() != 3) {
        throw std::logic_error("Invalid token in query: " + word);
      }
    } else if (word.find("OR") != std::string::npos) {
      if (word.length() != 2) {
        throw std::logic_error("Invalid token in query: " + word);
      }
    } else {
      std::transform(word.begin(), word.end(), word.begin(),
                     [&](char c) -> char {
                       if (std::isalpha(c)) {
                         return static_cast<char>(std::tolower(c));
                       } else if (std::isdigit(c) || c == '(' || c == ')') {
                         return c;
                       } else {
                         throw std::logic_error("Invalid token in query: " + word);
                       }
                     });
    }

    query_ += word + " ";
  }

  query_.pop_back();
  std::stack<char> tester;

  for (auto c : query_) {
    if (c == '(') {
      tester.push(c);
    } else if (c == ')') {
      if (tester.empty()) {
        throw std::logic_error("Invalid brace sequence in query");
      }

      tester.pop();
    }
  }
}

void QueryHandler::HandleQuery() {
  indices_ = ParseQuery(query_.begin(), query_.end());
}

const std::unordered_set<std::string>& QueryHandler::GetTerms() const {
  return terms_;
}

const std::unordered_set<size_t>& QueryHandler::GetIndices() const {
  return indices_;
}

void QueryHandler::Unite(std::unordered_set<size_t>& a, const std::unordered_set<size_t>& b) {
  for (auto& index : b) {
    a.insert(index);
  }
}

void QueryHandler::Intersect(std::unordered_set<size_t>& a, const std::unordered_set<size_t>& b) {
  for (auto it = a.begin(); it != a.end();) {
    if (!b.contains(*it)) {
      it = a.erase(it);
    } else {
      ++it;
    }
  }
}

void QueryHandler::InsertIndicesForTerm(const std::string& term, std::unordered_set<size_t>& indices) {
  for (auto& posting : postings_.at(term)) {
    indices.insert(posting.first);
  }
}

std::unordered_set<size_t> QueryHandler::ParseQuery(std::string::iterator first, std::string::iterator last) {
  std::unordered_set<size_t> first_indices;
  std::unordered_set<size_t> second_indices;
  bool is_ready = false;
  Operation operation = Operation::kNoOperation;

  for (auto it = first; it != last; ++it) {
    if (*it == ' ') {
      continue;
    }

    if (*it == 'A' && it + 1 != last && *(it + 1) == 'N' && it + 2 != last && *(it + 2) == 'D') {
      if (operation != Operation::kNoOperation) {
        throw std::logic_error("Invalid query: to many operators");
      }

      operation = Operation::kAnd;
      it += 3;
      continue;
    }

    if (*it == 'O' && it + 1 != last && *(it + 1) == 'R') {
      if (operation != Operation::kNoOperation) {
        throw std::logic_error("Invalid query: to many operators");
      }

      operation = Operation::kOr;
      it += 2;
      continue;
    }

    if (std::isdigit(*it) || std::islower(*it)) {
      auto new_first = it;

      for (; it != last && *it != ' '; ++it) {
        if (*it == '(' || *it == ')') {
          throw std::logic_error("Invalid term: " + std::string(new_first, it));
        }
      }

      std::string term = std::string(new_first, it);
      terms_.insert(term);

      if (!postings_.contains(term)) {
        throw std::logic_error("No such term: " + term);
      }

      if (is_ready) {
        throw std::logic_error("Invalid query: to many terms at " + term);
      }

      if (operation == Operation::kNoOperation) {
        if (!first_indices.empty()) {
          throw std::logic_error("Invalid query: to many terms at " + term);
        }

        InsertIndicesForTerm(term, first_indices);
      } else {
        if (!second_indices.empty()) {
          throw std::logic_error("Invalid query: to many terms at " + term);
        }

        InsertIndicesForTerm(term, second_indices);
        is_ready = true;
      }
    }

    if (it != last && *it == '(') {
      size_t counter = 0;
      ++it;
      auto new_first = it;

      for (; it != last && !(counter == 0 && *it == ')'); ++it) {
        if (*it == '(') {
          ++counter;
        } else if (*it == ')') {
          --counter;
        }
      }

      if (is_ready) {
        throw std::logic_error("Invalid query: to many terms at " + std::string(new_first, it));
      }

      if (operation == Operation::kNoOperation) {
        if (!first_indices.empty()) {
          throw std::logic_error("Invalid query: to many terms at " + std::string(new_first, it));
        }

        first_indices = ParseQuery(new_first, it);
      } else {
        if (!second_indices.empty()) {
          throw std::logic_error("Invalid query: to many terms at " + std::string(new_first, it));
        }

        second_indices = ParseQuery(new_first, it);
        is_ready = true;
      }
    }

    if (is_ready) {
      if (operation == Operation::kAnd) {
        Intersect(first_indices, second_indices);
      } else if (operation == Operation::kOr) {
        Unite(first_indices, second_indices);
      }

      second_indices.clear();
      is_ready = false;
      operation = Operation::kNoOperation;
    }

    if (it == last) {
      break;
    }
  }

  if (is_ready || operation != Operation::kNoOperation) {
    throw std::logic_error("Invalid query");
  }

  return first_indices;
}
