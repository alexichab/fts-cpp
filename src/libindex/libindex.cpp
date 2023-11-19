#include <cstddef>
#include <filesystem>
#include <fstream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include <libindex.hpp>
#include <libparser.hpp>
#include <picosha2.h>

Index IndexBuilder::index() { return index_; }

void IndexBuilder::add_document(
    std::size_t id, const std::string &text,
    const std::unordered_set<std::string> &stop_words, std::size_t min,
    std::size_t max) {
    index_.docs[id] = text;
    auto ngrams = parser::parse(text, stop_words, min, max);
    for (const auto &ngram : ngrams) {
        index_.entries[ngram.text].emplace_back(static_cast<std::size_t>(id),static_cast<std::size_t> (ngram.pos));
    }
}

std::string hash_term(const std::string &term) {
    return picosha2::hash256_hex_string(term).substr(0, 6);
}

void make_index_dir(const std::string &path) {
    std::filesystem::create_directories(std::filesystem::path(path) / "index" /
                                        "docs");
    std::filesystem::create_directories(std::filesystem::path(path) / "index" /
                                        "entries");
    if (!std::filesystem::exists(std::filesystem::path(path) / "index")) {
        throw std::runtime_error("Can't create index folder");
    }
}

void write_docs(const std::string &path,
                std::unordered_map<std::size_t, std::string> &docs) {
    for (const auto &[id, text] : docs) {
        std::ofstream out_file(path + "/index/docs/" + std::to_string(id));
        out_file << text << '\n';
    }
}

std::string
convert_to_entry_output(const std::string &term,
                        const std::vector<DocToPos> &doc_to_pos_vec) {
    std::string output(term + ' ' + std::to_string(doc_to_pos_vec.size()) +
                       ' ');
    std::unordered_map<std::size_t, std::pair<int, std::vector<int>>> doc_info;
    for (const auto &doc_to_pos : doc_to_pos_vec) {
        doc_info[doc_to_pos.doc].first++;
        doc_info[doc_to_pos.doc].second.push_back(
            static_cast<int>(doc_to_pos.pos));
    }
    for (const auto &[id, pos_info] : doc_info) {
        output.append(std::to_string(id) + ' ' +
                      std::to_string(pos_info.first) + ' ');
        for (const auto &pos : pos_info.second) {
            output.append(std::to_string(pos) + ' ');
        }
    }
    output.append("\n");
    return output;//append!пофиксить вывод в файл
}

void write_entries(
    const std::string &path,
    const std::unordered_map<std::string, std::vector<DocToPos>> &entries) {
    for (const auto &[term, doc_to_pos_vec] : entries) {
        const std::filesystem::path filePath =
            path + "/index/entries/" + ::hash_term(term);
        std::ofstream out_file(filePath.string());
        out_file << convert_to_entry_output(term, doc_to_pos_vec);
    }
}

void TextIndexWriter::write(std::string path, Index index) {
    make_index_dir(path);
    write_docs(path, index.docs);
    write_entries(path, index.entries);
}
