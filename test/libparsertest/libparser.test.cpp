#include <gtest/gtest.h>
#include <libparser/libparser.hpp>

#include <cstddef>
#include <string>

TEST(ClearStringTest, General) {
    const std::string input("Parser, is did not work.");
    const std::string expected("parser is did not work");
    EXPECT_EQ(expected, parser::clearString(input));
}

TEST(SplitStringTest, General) {
    const std::string input("parser is did not work");
    const VectorOfStrings vctr{"parser", "is", "did", "not", "work"};
    const VectorOfStrings result = parser::splitString(input); 
    for(std::size_t i = 0; i < vctr.size(); ++i){
        EXPECT_EQ(vctr[i], result[i]);
    }
}

TEST(RemoveStopWordsTest, General) {
    const VectorOfStrings input{"parser", "is", "did", "not", "work"};
    const VectorOfStrings stopwords{"not"};
    const VectorOfStrings vctr{"parser", "is", "did", "work"};
    const VectorOfStrings result = parser::removeStopWords(input,stopwords); 
    for(std::size_t i = 0; i < result.size(); ++i){
        EXPECT_EQ(vctr[i], result[i]);
    }
}

TEST(GenerateNgrams, General) {
    const VectorOfStrings input {"vector"};
    const VectorOfStrings stopwords{"not"};
    const size_t min = 3;
    const size_t max = 6;
    const VectorOfNgrams result = parser::ngramGen(input,stopwords,min,max);
    const VectorOfNgrams vctr{{"vec", 0},{"vect", 0},{"vecto", 0},{"vector",0}};
    for(std::size_t i = 0; i < result.size(); ++i){
        EXPECT_EQ(vctr[i].text, result[i].text);
        EXPECT_EQ(vctr[i].pos, result[i].pos);
    }
}

TEST(Parse, General){
    const std::string input("Vector, not.");
    const VectorOfStrings stopwords{"not"};
    const size_t min = 3;
    const size_t max = 6;
    const VectorOfNgrams result = parser::parse(input,stopwords,min,max);
    const VectorOfNgrams vctr{{"vec", 0},{"vect", 0},{"vecto", 0},{"vector",0}};
    for(std::size_t i = 0; i < result.size(); ++i){
        EXPECT_EQ(vctr[i].text, result[i].text);
        EXPECT_EQ(vctr[i].pos, result[i].pos);
    }
}

// int main(int argc, char *argv[]) {
//     testing::InitGoogleTest(&argc, argv);
//     return RUN_ALL_TESTS();
// }