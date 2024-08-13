#ifndef TESTFUNCTIONS_HPP_
#define TESTFUNCTIONS_HPP_

#include <iostream>
#include <vector>
#include <string>
#include <cstdint>

std::vector<std::string> SplitString(const std::string& str);

std::string ExtractFilename(const std::vector<std::pair<std::string, size_t>>& index,
                                     const std::pair<double, size_t>& result);

std::vector<int32_t> GetRandomNumbers(size_t n);

uint32_t GetRandomNumber();

#endif //TESTFUNCTIONS_HPP_
