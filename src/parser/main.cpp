#include <libparser/libparser.hpp>

#include <iostream>
#include <string>

int main() {
    std::cout << "Enter words\n";
    std::string words;
    std::getline(std::cin, words);

    StopWords stop_words;
    std::string stopword;
    std::cout << "Enter stop words, push q for end\n";
    while (std::getline(std::cin, stopword) && stopword != "q") {
        stop_words.insert(stopword);
    }

    int min;
    int max;
    std::cout << "Enter min max length\n";
    std::cin >> min >> max;
    const VectorOfNgrams result = parser::parse(words, stop_words, min, max);
    parser::printNgrams(result);
    return 0;
}