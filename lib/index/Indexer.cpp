#include <filesystem>
#include <fstream>
#include <algorithm>
#include <iterator>

#include "Indexer.hpp"

Indexer::Indexer(const std::string& target, bool index_binary)
    : target_(target), index_writer_(target), index_binary_(index_binary) {}

int32_t Indexer::CreateIndex() {
  AddFilesRecursive(target_);
  double dl_avg = 0.0;

  for (size_t i = 0; i < index_writer_.GetIndex().size(); i++) {
    std::string filename = index_writer_.GetIndex()[i].first;
    std::ifstream file(filename);

    if (!file.is_open()) {
      return -1;
    }

    size_t word_count = 0;
    std::string word;

    while (file >> word) {
      std::transform(word.begin(), word.end(), word.begin(),
                     [](char c) -> char {
                       if (std::isalpha(c)) {
                         return static_cast<char>(std::tolower(c));
                       } else if (std::isdigit(c)) {
                         return c;
                       } else {
                         return ' ';
                       }
                     });
      std::istringstream iss(word);
      std::vector<std::string>
          new_words((std::istream_iterator<std::string>(iss)), std::istream_iterator<std::string>());

      for (auto& new_word : new_words) {
        ++word_count;
        index_writer_.AddWordForIndex(new_word, i);
      }
    }

    index_writer_.SetWordCountForIndex(i, word_count);
    dl_avg += static_cast<double>(word_count);
    file.close();
  }

  dl_avg /= static_cast<double>(index_writer_.GetIndex().size());
  index_writer_.SetDlAvg(dl_avg);
  return 0;
}

const Index& Indexer::GetIndex() const {
  return index_writer_;
}

void Indexer::AddFilesRecursive(const std::string& path) {
  for (auto& entry : std::filesystem::directory_iterator(path)) {
    if (std::filesystem::is_directory(entry.path())) {
      AddFilesRecursive(std::filesystem::canonical(entry.path()).string());
    } else {
      if ((index_binary_ || IsTextFile(entry.path().string())) && entry.path().filename() != Index::kIndexFile) {
        index_writer_.AddFile(std::filesystem::canonical(entry.path()).string());
      }
    }
  }
}

bool Indexer::IsTextFile(const std::string& path) {
  int c;
  std::ifstream a(path);

  while ((c = a.get()) != EOF && c <= 127);

  return c == EOF;
}
