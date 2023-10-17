#include <libparser.hpp>

#include <algorithm>
#include <cctype>
#include <cstddef>
#include <iostream>
#include <string>
#include <vector>
// size_t вместо int min,max
//
namespace parser {

std::string clearString(const std::string &first) {
    std::string result;
    for (const char c : first) {
        if (std::ispunct(c) == 0) {
            result.push_back(static_cast<char>(std::tolower(c)));
        }
    }
    return result;
}
// string stream
VectorOfStrings splitString(const std::string &str, const char delimiter) {
    std::vector<std::string> result;
    std::size_t start = 0;
    std::size_t end = str.find(delimiter);
    while (end != std::string::npos) {
        result.push_back(str.substr(start, end - start));
        start = end + 1;
        end = str.find(delimiter, start);
    }
    result.push_back(str.substr(start, end - start));
    return result;
}

VectorOfStrings removeStopWords(const VectorOfStrings &words,
                                const VectorOfStrings &stopwords) {
    VectorOfStrings result;
    for (const auto &word : words) {
        if (std::find(stopwords.begin(), stopwords.end(), word) ==
            stopwords.end()) {
            result.push_back(word);
        }
    }
    return result;
}

VectorOfNgrams ngramGen(const VectorOfStrings &words,
                        const VectorOfStrings &stopwords, size_t min,
                        size_t max) {
    VectorOfNgrams result;
    for (std::size_t i = 0; i < words.size(); ++i) {
        for (size_t currLen = min;
             (currLen <= max) && (currLen <= static_cast<int>(words[i].size()));
             ++currLen) {
            const std::string ngram = words[i].substr(0, currLen);
            if (std::find(stopwords.begin(), stopwords.end(), ngram) ==
                stopwords.end()) {
                result.push_back({ngram, i});
            }
        }
    }
    return result;
}

VectorOfNgrams parse(const std::string &query, const VectorOfStrings &stopwords,
                     size_t min, size_t max) {
    const VectorOfStrings words =
        removeStopWords(splitString(clearString(query)), stopwords);
    return ngramGen(words, stopwords, min, max);
}

void printNgrams(const VectorOfNgrams &ngrams) {
    for (const auto &ngram : ngrams) {
        std::cout << ngram.text << ' ' << ngram.pos << ' ';
    }
    std::cout << '\n';
}

} // namespace parser