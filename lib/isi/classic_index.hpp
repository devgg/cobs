#pragma once

#include <experimental/filesystem>
#include <util.hpp>
#include <kmer.hpp>
#include <timer.hpp>
#include <file/classic_index_header.hpp>

namespace isi::classic_index  {
//    class classic_index {
//    private:
//        uint64_t m_signature_size;
//        uint64_t m_block_size;
//        uint64_t m_num_hashes;
//        std::vector<uint8_t> m_data;  // replace by std::vector<uint8_t> ???
//
//        void set_bit(size_t pos, size_t bit_in_block);
//        void process(const std::vector<std::experimental::filesystem::path> &paths, const std::experimental::filesystem::path &out_file, timer &t);
//    public:
//        classic_index() = default;
//        classic_index(uint64_t signature_size, uint64_t block_size, uint64_t num_hashes);
//        bool is_set(size_t pos, size_t bit_in_block);
//        bool contains(const kmer<31>& kmer, size_t bit_in_block);
//        uint64_t signature_size() const;
//        void signature_size(uint64_t m_signature_size);
//        uint64_t block_size() const;
//        void block_size(uint64_t m_block_size);
//        uint64_t num_hashes() const;
//        void num_hashes(uint64_t m_num_hashes);
//        const std::vector<uint8_t>& data() const;
//        std::vector<uint8_t>& data();
//    };
    void combine(std::vector<std::pair<std::ifstream, size_t>>& ifstreams, const std::experimental::filesystem::path &out_file,
                 size_t signature_size, size_t block_size, size_t num_hash, timer& t, const std::vector<std::string>& file_names);
    void create(const std::experimental::filesystem::path& in_dir, const std::experimental::filesystem::path& out_dir,
                size_t signature_size, size_t block_size, size_t num_hashes, size_t batch_size);
    void create_from_samples(const std::experimental::filesystem::path& in_dir, const std::experimental::filesystem::path& out_dir,
                             size_t signature_size, size_t block_size, size_t num_hashes);
    bool combine(const std::experimental::filesystem::path& in_dir, const std::experimental::filesystem::path& out_dir,
                 size_t batch_size, size_t signature_size, size_t num_hashes);
    void create_hashes(const void* input, size_t len, size_t signature_size, size_t num_hashes,
                       const std::function<void(size_t)>& callback);
    bool contains(const std::vector<uint8_t>& data, const isi::file::classic_index_header& h, const kmer<31>& kmer, size_t bit_in_block);
    void generate_dummy(const std::experimental::filesystem::path& p, size_t signature_size, size_t block_size, size_t num_hashes);
}
