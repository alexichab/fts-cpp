#include <picosha2.h>

#include <libsearcher/libsearcher.hpp>

TermInfos TextIndexAccessor::get_term_infos(const std::string &term) const {
    const std::string hash = picosha2::hash256_hex_string(term).substr(0, 6);
    const std::filesystem::path fullPath = path_ / "index" / "entries" / hash;
    if (!std::filesystem::exists(fullPath)) {
        throw std::runtime_error(std::string("Can't find path: ") +
                                 fullPath.c_str());
    }
    std::ifstream termFile(fullPath);
    if (!termFile.is_open()) {
        throw std::runtime_error("Can't open term file");
    }
    TermInfos termInfos("");
    std::string line;
    while (std::getline(termFile, line)) {
        termInfos += line;
    }
    return termInfos;
}

std::string TextIndexAccessor::load_document(std::size_t doc_id) const {
    const std::string doc_name = std::to_string(doc_id);
    std::ifstream docFile(path_ / "index" / "docs" / doc_name);
    if (!docFile.is_open()) {
        throw std::runtime_error("Can't open document file " + doc_name);
    }
    std::string docText("");
    std::string line;
    while (std::getline(docFile, line)) {
        docText += line;
    }
    return docText;
}

DocsCount TextIndexAccessor::total_docs() const {
    DocsCount c = 0;
    for (const auto &entry :
         std::filesystem::directory_iterator(path_ / "index" / "docs")) {
        (void)entry;
        ++c;
    }
    return c;
}

Results searcher::search(const SearcherQuery &query, const IndexAccessor &ia) {
    const Config cfg = ia.config();
    const VectorOfNgrams parsed = parser::parse(
        query, StopWords(cfg.stop_words.begin(), cfg.stop_words.end()),
        cfg.min_length, cfg.max_length);
    std::unordered_map<std::size_t, double> scores;
    for (const auto &ngram : parsed) {
        const TermInfos termInfos = ia.get_term_infos(ngram.text);

        std::vector<std::string> words = parser::splitString(termInfos);
        const int doc_freq_pos = 1;
        const int doc_id_count = 2;
        const double doc_frequency = std::stod(words[doc_freq_pos]);
        for (std::size_t i = doc_id_count; i < words.size() - 1; ++i) {
            auto doc_id = static_cast<std::size_t>(std::stoi(words[i]));
            ++i;
            const double term_frequency = std::stod(words[i]);
            i += static_cast<std::size_t>(term_frequency);
            auto N = static_cast<double>(static_cast<int>(ia.total_docs()));
            const double idf = log(N) - log(doc_frequency);
            const double tf_idf = term_frequency * idf;
            scores[doc_id] += tf_idf;
        }
    }
    Results results;
    for (auto &[doc_id, tf_idf] : scores) {
        results.emplace_back(doc_id, tf_idf);
    }
    auto compare_desc_by_score = [](const Result &a, const Result &b) {
        return a.score > b.score;
    };
    std::sort(results.begin(), results.end(), compare_desc_by_score);
    return results;
}