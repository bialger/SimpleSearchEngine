#include <iostream>
#include <iterator>
#include "lib/argparser/ArgParser.hpp"
#include "lib/index/Indexer.hpp"
#include "lib/search/Searcher.hpp"

int main(int argc, char** argv) {
  std::string program_description = "Program for searching words in most relevant files, version " +
      std::to_string(Index::kMajorVersion_) + "." + std::to_string(Index::kMinorVersion);
  ArgumentParser::ConditionalOutput output = {std::cerr, true};
  std::vector<std::string> pre_query;
  ArgumentParser::ArgParser parser("SimpleSearchEngine");
  parser.AddCompositeArgument('t', "target", "Target directory to search. It should be already indexed").
      AddValidate(ArgumentParser::IsValidFilename).AddIsGood([&](std::string& str) -> bool {
    Index tmp_index(str);
    std::string index_name = tmp_index.GetIndexName();
    return ArgumentParser::IsDirectory(str) && ArgumentParser::IsRegularFile(index_name);
  });
  parser.AddStringArgument('q', "query", "Search query").MultiValue(1).StoreValues(pre_query);
  parser.AddDoubleArgument('k', "k", "k for BM25 score").Default(1.0);
  parser.AddDoubleArgument('b', "b", "b for BM25 score").Default(0.75);
  parser.AddUnsignedLongLongArgument('n', "number", "Number of most relevant files. Set to 0 to print all").Default(5);
  parser.AddHelp('h', "help", program_description.c_str());

  if (!parser.Parse(argc, argv, output)) {
    std::cout << parser.HelpDescription() << std::endl;
    return 1;
  }

  if (parser.Help()) {
    std::cout << parser.HelpDescription() << std::endl;
    return 0;
  }

  Index index(parser.GetCompositeValue("target"));

  if (index.LoadIndex() != 0) {
    ArgumentParser::DisplayError("Failed to load index\n", output);
    return 1;
  }

  Searcher searcher(index, parser.GetDoubleValue("k"), parser.GetDoubleValue("b"));

  std::vector<std::string> query;

  for (const std::string& arg : pre_query) {
    std::istringstream iss(arg);
    query.insert(query.end(), (std::istream_iterator<std::string>(iss)), std::istream_iterator<std::string>());
  }

  try {
    std::vector<std::pair<double, size_t>> result = searcher.SearchMostRelevant(query);
    std::size_t limit = parser.GetUnsignedLongLongValue("number");

    if (limit == 0) {
      limit = result.size();
    }

    limit = std::min(result.size(), limit);

    if (result.empty()) {
      std::cout << "Nothing found" << std::endl;
      return 0;
    }

    std::cout << result.size() << " files found, printing " << limit << " most relevant:" << std::endl;

    for (size_t i = 0; i < limit; i++) {
      std::cout << index.GetIndex()[result[i].second].first << std::endl;
    }
  } catch (std::exception& e) {
    ArgumentParser::DisplayError(e.what(), output);
    return 1;
  }

  return 0;
}