#include <gtest/gtest.h>
#include <libindex/libindex.hpp>

#include <cstddef>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

// Test fixture for IndexBuilder
class IndexBuilderTest : public ::testing::Test {
  protected:
    IndexBuilder builder;
};

// Test case for add_document function
TEST_F(IndexBuilderTest, AddDocument) {
    std::unordered_set<std::string> stop_words = {"a", "an", "the"};
    builder.add_document(1, "This is a sample text", stop_words, 2, 4);

    // Add assertions here to check if the document is added to the index
    // correctly For example, you can check the size of the index or specific
    // entries.
}

// Test case for hash_term function
TEST(HashTermTest, General) {
    const std::string input("test");
    const std::string expected =
        "9f86d0"; // Replace with the actual expected hash
    EXPECT_EQ(expected, hash_term(input));
}

// Test case for make_index_dir function
TEST(MakeIndexDirTest, General) {
    const std::string path = "test_path";

    // You might want to create a temporary directory for testing
    // and use it as the path parameter for make_index_dir

    ASSERT_NO_THROW(make_index_dir(path));
    // Add more assertions here to check if the index directory is created
    // correctly
}

// Test case for write_docs function
TEST(WriteDocsTest, General) {
    const std::string path = "test_path";
    std::unordered_map<std::size_t, std::string> docs = {{1, "Document 1"},
                                                         {2, "Document 2"}};

    // You might want to create a temporary directory for testing
    // and use it as the path parameter for write_docs

    ASSERT_NO_THROW(write_docs(path, docs));
    // Add more assertions here to check if documents are written correctly
}

// Add more test cases for other functions in a similar manner

// Main function to run the tests
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
