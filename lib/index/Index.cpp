#include <filesystem>
#include <fstream>
#include <iostream>

#include "Index.hpp"

const std::string Index::kIndexFile = ".index";

Index::Index(const std::string& target)
    : target_(target),
      index_(),
      postings_(),
      dl_avg_(0.0) {}

int32_t Index::LoadIndex() {
  std::ifstream file(GetIndexName());

  if (!file.is_open()) {
    return -1;
  }

  uint16_t major_version;
  uint16_t minor_version;
  file >> major_version;
  file >> minor_version;

  if (minor_version != kMinorVersion || major_version != kMajorVersion_) {
    file.close();
    return 1;
  }

  size_t n;
  file >> n;
  file >> dl_avg_;
  index_.reserve(n);

  for (size_t i = 0; i < n; i++) {
    std::string filename;
    size_t dl;
    file >> filename;
    file >> dl;
    index_.emplace_back(filename, dl);
  }

  size_t word_count;
  file >> word_count;
  postings_.reserve(word_count);

  for (size_t i = 0; i < word_count; i++) {
    std::string word;
    size_t documents_count;
    file >> word;
    file >> documents_count;
    postings_[word] = std::unordered_map<size_t, size_t>(documents_count);

    for (size_t j = 0; j < documents_count; j++) {
      size_t doc_id;
      size_t freq;
      file >> doc_id;
      file >> freq;
      postings_[word][doc_id] = freq;
    }
  }

  file.close();
  return 0;
}

int32_t Index::WriteIndex() const {
  std::ofstream file(GetIndexName());

  if (!file.is_open()) {
    return -1;
  }

  file << kMajorVersion_ << ' ' << kMinorVersion << '\n';
  file << index_.size() << ' ' << dl_avg_ << '\n';

  for (auto& index : index_) {
    file << index.first << ' ' << index.second << '\n';
  }

  file << postings_.size();

  for (auto& posting : postings_) {
    file << '\n' << posting.first << ' ' << posting.second.size() << '\n';

    for (auto& document : posting.second) {
      file << document.first << ' ' << document.second << ' ';
    }
  }

  file << std::endl;
  file.close();
  return 0;
}

void Index::AddFile(const std::string& path) {
  index_.emplace_back(path, 0);
}

void Index::SetWordCountForIndex(size_t index, size_t count) {
  index_.at(index).second = count;
}

void Index::SetDlAvg(double dl_avg) {
  dl_avg_ = dl_avg;
}

void Index::AddWordForIndex(const std::string& word, size_t index) {
  if (postings_.contains(word)) {
    if (postings_[word].contains(index)) {
      postings_[word][index] += 1;
    } else {
      postings_[word][index] = 1;
    }
  } else {
    postings_[word] = std::unordered_map<size_t, size_t>(1);
    postings_[word][index] = 1;
  }
}

const std::vector<std::pair<std::string, size_t>>& Index::GetIndex() const {
  return index_;
}

const std::unordered_map<std::string, std::unordered_map<size_t, size_t>>& Index::GetPostings() const {
  return postings_;
}

double Index::GetDlAvg() const {
  return dl_avg_;
}

std::string Index::GetIndexName() const {
  return target_ + (target_.back() == '/' ? "" : "/") + kIndexFile;
}
