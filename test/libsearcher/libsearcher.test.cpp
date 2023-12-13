#include <gtest/gtest.h>
#include <libindex/libindex.hpp>
#include <libsearcher/libsearcher.hpp>

#include <cstddef>
#include <filesystem>
#include <string>
#include <utility>

class TextIndexAccessorTest : public ::testing::Test {
  private:
    std::filesystem::path indexPath;
    TextIndexAccessor accessor;

  public:
    TextIndexAccessorTest() : indexPath("test"), accessor(indexPath) {}

    explicit TextIndexAccessorTest(std::filesystem::path path)
        : indexPath(std::move(path)), accessor(indexPath) {}

    TextIndexAccessor &getAccessor() { return accessor; }
    const std::filesystem::path &getIndexPath() const { return indexPath; }
};

TEST_F(TextIndexAccessorTest, GetTermInfos) {
    const IndexBuilder indexBuilder;
    const Index index = {{{1000, "hot dog"}, {1500, "cold cat"}},
                         {{"hot", {{1000, 0}}},
                          {"dog", {{1000, 1}}},
                          {"cold", {{1500, 0}}},
                          {"cat", {{1500, 1}}}}};
    TextIndexWriter textIndexWriter;
    const std::string outputPath = "test";
    std::filesystem::create_directory(outputPath);
    textIndexWriter.write(outputPath, index);
    const std::string validTerm = "dog";
    auto validResult = getAccessor().get_term_infos(validTerm);
    EXPECT_EQ(validResult, "dog 1 1000 1 1 ");
}

TEST_F(TextIndexAccessorTest, LoadDocument) {
    const std::size_t validDocId = 1000;
    auto validResult = getAccessor().load_document(validDocId);
    EXPECT_EQ(validResult, "hot dog");
}

TEST_F(TextIndexAccessorTest, TotalDocs) {
    const std::size_t c = 2;
    auto total = getAccessor().total_docs();
    EXPECT_EQ(total, c);
}

TEST_F(TextIndexAccessorTest, Search) {
    const IndexBuilder indexBuilder;
    const Index index = {{{1000, "hot dog"}, {1500, "cold cat"}},
                         {{"hot", {{1000, 0}}},
                          {"dog", {{1000, 1}}},
                          {"cold", {{1500, 0}}},
                          {"cat", {{1500, 1}}}}};
    TextIndexWriter textIndexWriter;
    const std::string outputPath = "test";
    std::filesystem::create_directory(outputPath);
    textIndexWriter.write(outputPath, index);

    const std::string query = "hot";
    const auto indexAccessor = getAccessor();
    const auto results = searcher::search(query, indexAccessor);
    EXPECT_EQ(results[0].doc_id, 1000);
    EXPECT_EQ(results.size(), 1);
}