#include <libparser.hpp>

#include <algorithm>
#include <cctype>
#include <cstddef>
#include <iostream>
#include <sstream>
#include <string>

namespace parser {

std::string clearString(const std::string &first) {
    std::string result;
    result.reserve(first.size());
    for (const char c : first) {
        if (std::ispunct(c) == 0) {
            result.push_back(static_cast<char>(std::tolower(c)));
        }
    }
    return result;
}

VectorOfStrings splitString(const std::string &str, char delimiter) {
    VectorOfStrings result;
    std::istringstream ss(str);
    std::string token;
    while (std::getline(ss, token, delimiter)) {
        result.push_back(token);
    }
    return result;
}

VectorOfStrings removeStopWords(const VectorOfStrings &words,
                                const StopWords &stopwords) {
    VectorOfStrings result;
    for (const auto &word : words) {
        if (stopwords.find(word) != stopwords.end()) {
            result.push_back(word);
        }
    }
    return result;
}

VectorOfNgrams ngramGen(const VectorOfStrings &words,
                        const StopWords &stopwords, size_t min, size_t max) {
    VectorOfNgrams result;
    for (std::size_t i = 0; i < words.size(); ++i) {
        for (size_t currLen = min;
             (currLen <= max) &&
             (currLen <= static_cast<size_t>(words[i].size()));
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

VectorOfNgrams parse(const std::string &query, const StopWords &stopwords,
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