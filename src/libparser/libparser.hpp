#pragma once

#include <string>
#include <vector>

struct Ngram {
    std::string text;
    std::size_t pos;
};

using VectorOfNgrams = std::vector<struct Ngram>;
using VectorOfStrings = std::vector<std::string>;

namespace parser {

std::string clearString(const std::string &first);
VectorOfStrings splitString(const std::string &str, char delimiter = ' ');
VectorOfStrings removeStopWords(const VectorOfStrings &words,
                                const VectorOfStrings &stopwords);
VectorOfNgrams ngramGen(const VectorOfStrings &words,
                        const VectorOfStrings &stopwords, size_t min,
                        size_t max);
VectorOfNgrams parse(const std::string &query, const VectorOfStrings &stopwords,
                     size_t min, size_t max);
void printNgrams(const VectorOfNgrams &ngrams);

} // namespace parser