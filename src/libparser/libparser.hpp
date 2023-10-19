#pragma once

#include <string>
#include <unordered_set>
#include <vector>

struct Ngram {
    std::string text;
    std::size_t pos;
};

using VectorOfNgrams = std::vector<struct Ngram>;
using VectorOfStrings = std::vector<std::string>;
using StopWords = std::unordered_set<std::string>;

namespace parser {

std::string clearString(const std::string &first);
VectorOfStrings splitString(const std::string &str, char delimiter = ' ');
VectorOfStrings removeStopWords(const VectorOfStrings &words,
                                const StopWords &stopwords);
VectorOfNgrams ngramGen(const VectorOfStrings &words,
                        const StopWords &stopwords, size_t min, size_t max);
VectorOfNgrams parse(const std::string &query, const StopWords &stopwords,
                     size_t min, size_t max);
void printNgrams(const VectorOfNgrams &ngrams);

} // namespace parser