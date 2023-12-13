#include <filesystem>
#include <iostream>
#include <libsearcher/libsearcher.hpp>
#include <string>

int main() {
    std::filesystem::path indexPath = "path/to/output";
    const TextIndexAccessor indexAccessor(indexPath);
    const std::string query = "sample";
    std::cout << "Total docs: " << indexAccessor.total_docs() << '\n';
    std::cout << "ID\tDocument\t\t\tScore\n";
    const Results results = searcher::search(query, indexAccessor);
    for (const auto &result : results) {
        const auto id = result.doc_id;
        std::cout << id << '\t' << indexAccessor.load_document(id) << '\t'
                  << result.score << '\n';
    }

    return 0;
}