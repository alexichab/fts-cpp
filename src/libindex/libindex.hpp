#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

struct DocToPos {
    std::size_t doc;
    std::size_t pos;
};

struct Index {
    std::unordered_map<std::size_t, std::string> docs;
    std::unordered_map<std::string, std::vector<DocToPos>> entries;
};

class IndexBuilder {
  public:
    void add_document(std::size_t id, const std::string &text,
                      const std::unordered_set<std::string> &stop_words,
                      std::size_t min, std::size_t max);
    Index index();

  private:
    Index index_;
};

class IndexWriter {
  public:
    virtual void write(std::string path, Index index) = 0;
    virtual ~IndexWriter() = default;
};

class TextIndexWriter : public IndexWriter {
  public:
    void write(std::string path, Index index) override;
};

void write_entries(
    const std::string &path,
    const std::unordered_map<std::string, std::vector<DocToPos>> &entries);

std::string
convert_to_entry_output(const std::string &term,
                        const std::vector<DocToPos> &doc_to_pos_vec);

void write_docs(const std::string &path,
                std::unordered_map<std::size_t, std::string> &docs);

void make_index_dir(const std::string &path);

std::string hash_term(const std::string &term);
