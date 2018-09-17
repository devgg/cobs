/*******************************************************************************
 * test/src/test_util.hpp
 *
 * Copyright (c) 2018 Florian Gauger
 *
 * All rights reserved. Published under the MIT License in the LICENSE file.
 ******************************************************************************/

#ifndef COBS_TEST_SRC_TEST_UTIL_HEADER
#define COBS_TEST_SRC_TEST_UTIL_HEADER
#pragma once

#include <cobs/construction/compact_index.hpp>
#include <cobs/query/compact_index/mmap.hpp>
#include <cobs/util/query.hpp>
#include <fstream>
#include <gtest/gtest.h>
#include <string>
#include <vector>

inline void assert_equals_files(const std::string& f1, const std::string& f2) {
    std::ifstream ifs1(f1, std::ios::in | std::ios::binary);
    std::ifstream ifs2(f2, std::ios::in | std::ios::binary);
    std::istream_iterator<char> start1(ifs1);
    std::istream_iterator<char> start2(ifs2);
    std::istream_iterator<char> end;
    std::vector<char> v1(start1, end);
    std::vector<char> v2(start2, end);

    ASSERT_EQ(v1.size(), v2.size());
    for (size_t i = 0; i < v1.size(); i++) {
        ASSERT_EQ(v1[i], v2[i]);
    }
}

inline std::vector<cobs::sample<31> > generate_samples_all(const std::string& query) {
    std::vector<cobs::sample<31> > samples(33);
    cobs::kmer<31> k;
    std::vector<char> kmer_raw(31);
    for (size_t i = 0; i < query.size() - 31; i++) {
        const char* normalized_kmer = cobs::query::canonicalize_kmer(query.data() + i, kmer_raw.data(), 31);
        k.init(normalized_kmer);
        for (size_t j = 0; j < samples.size(); j++) {
            if (j % (i % (samples.size() - 1) + 1) == 0) {
                samples[j].data().push_back(k);
            }
        }
    }
    return samples;
}

inline std::vector<cobs::sample<31> > generate_samples_one(const std::string& query) {
    std::vector<cobs::sample<31> > samples(33);
    cobs::kmer<31> k;
    std::vector<char> kmer_raw(31);
    const char* normalized_kmer = cobs::query::canonicalize_kmer(query.data(), kmer_raw.data(), 31);
    k.init(normalized_kmer);
    for (size_t i = 0; i < samples.size(); i++) {
        for (size_t j = 0; j < i * 10 + 1; j++) {
            samples[i].data().push_back(k);
        }
    }
    return samples;
}

inline std::string get_file_stem(size_t index) {
    assert(index < 100);
    std::string num = (index < 10 ? "0" : "") + std::to_string(index);
    return "sample_" + num;
}

inline void generate_test_case(std::vector<cobs::sample<31> > samples, const std::string& out_dir) {
    for (size_t i = 0; i < samples.size(); i++) {
        std::string file_name = get_file_stem(i);
        cobs::file::serialize(out_dir + "/" + file_name + cobs::file::sample_header::file_extension, samples[i], file_name);
    }
}

#endif // !COBS_TEST_SRC_TEST_UTIL_HEADER

/******************************************************************************/
