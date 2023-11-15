#include <iostream>
#include <libindex.hpp>
#include <string>
#include <unordered_set>

int main() {

    IndexBuilder indexBuilder;

    const std::unordered_set<std::string> stopWords = {"the", "and", "is"};

    indexBuilder.add_document(1, "This is a sample document", stopWords, 2, 4);
    indexBuilder.add_document(2, "Another document with some text", stopWords,
                              2, 4);

    const Index index = indexBuilder.index();

    TextIndexWriter textIndexWriter;

    const std::string outputPath = "path/to/output";
    textIndexWriter.write(outputPath, index);

    std::cout << "Index has been written to: " << outputPath << '\n';

    return 0;
}