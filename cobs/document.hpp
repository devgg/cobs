/*******************************************************************************
 * cobs/document.hpp
 *
 * Copyright (c) 2018 Florian Gauger
 * Copyright (c) 2018 Timo Bingmann
 *
 * All rights reserved. Published under the MIT License in the LICENSE file.
 ******************************************************************************/

#ifndef COBS_DOCUMENT_HEADER
#define COBS_DOCUMENT_HEADER

#include <cobs/file/document_header.hpp>
#include <cobs/kmer.hpp>

#include <algorithm>
#include <ostream>
#include <vector>

#include <tlx/die.hpp>

namespace cobs {

template <unsigned int N>
class document
{
private:
    std::vector<kmer<N> > m_data;

public:
    void print(std::ostream& ostream) const;
    std::vector<kmer<N> >& data() {
        return m_data;
    }
    const std::vector<kmer<N> >& data() const {
        return m_data;
    }

    void sort_kmers() {
        std::sort(m_data.begin(), m_data.end());
    }

    void serialize(std::ofstream& ofs, const std::string& name) const {
        ofs.exceptions(std::ios::eofbit | std::ios::failbit | std::ios::badbit);
        file::document_header sh(name, N);
        file::header<file::document_header>::serialize(ofs, sh);
        ofs.write(reinterpret_cast<const char*>(m_data.data()),
                  kmer<N>::size* m_data.size());
    }

    void serialize(const fs::path& p, const std::string& name) const {
        fs::create_directories(p.parent_path());
        std::ofstream ofs(p.string(), std::ios::out | std::ios::binary);
        serialize(ofs, name);
    }

    void deserialize(std::ifstream& ifs, file::document_header& h) {
        ifs.exceptions(std::ios::eofbit | std::ios::failbit | std::ios::badbit);
        file::header<file::document_header>::deserialize(ifs, h);
        die_unless(N == h.kmer_size());

        stream_metadata smd = get_stream_metadata(ifs);
        size_t size = smd.end_pos - smd.curr_pos;
        m_data.resize(size / kmer<N>::size);
        ifs.read(reinterpret_cast<char*>(m_data.data()), size);
    }

    void deserialize(const fs::path& p, file::document_header& h) {
        std::ifstream ifs(p.string(), std::ios::in | std::ios::binary);
        deserialize(ifs, h);
    }
};

template <unsigned int N>
void document<N>::print(std::ostream& ostream) const {
    for (size_t i = 0; i < m_data.size(); i++) {
        ostream << m_data[i] << std::endl;
    }
}

} // namespace cobs

#endif // !COBS_DOCUMENT_HEADER

/******************************************************************************/
