#pragma once

#include <libparser/libparser.hpp>

struct Config {
    VectorOfStrings stop_words;
    std::size_t min_length;
    std::size_t max_length;
};

extern Config DEFAULT_CONFIG;
