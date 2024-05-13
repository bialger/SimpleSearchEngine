#include <iostream>
#include "lib/argparser/ArgParser.hpp"
#include "lib/index/Indexer.hpp"

int main(int argc, char** argv) {
  std::string program_description = "Program for indexing files in directory, version " +
      std::to_string(Index::kMajorVersion_) + "." + std::to_string(Index::kMinorVersion);
  ConditionalOutput output = {std::cerr, true};
  ArgumentParser::ArgParser parser("Indexer for SimpleSearchEngine");
  parser.AddCompositeArgument('t', "target", "Target directory to index").
      AddValidate(ArgumentParser::IsValidFilename).AddIsGood(ArgumentParser::IsDirectory);
  parser.AddHelp('h', "help", program_description.c_str());

  if (!parser.Parse(argc, argv, output)) {
    std::cout << parser.HelpDescription() << std::endl;
    return 1;
  }

  if (parser.Help()) {
    std::cout << parser.HelpDescription() << std::endl;
    return 0;
  }

  Indexer indexer(parser.GetCompositeValue("target"));

  if (indexer.CreateIndex() != 0) {
    ArgumentParser::DisplayError("Failed to create index\n", output);
    return 1;
  }

  if (indexer.GetIndex().WriteIndex() != 0) {
    ArgumentParser::DisplayError("Failed to write index\n", output);
    return 1;
  }

  return 0;
}
