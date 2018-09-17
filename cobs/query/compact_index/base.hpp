/*******************************************************************************
 * cobs/query/compact_index/base.hpp
 *
 * Copyright (c) 2018 Florian Gauger
 *
 * All rights reserved. Published under the MIT License in the LICENSE file.
 ******************************************************************************/

#ifndef COBS_QUERY_COMPACT_INDEX_BASE_HEADER
#define COBS_QUERY_COMPACT_INDEX_BASE_HEADER
#pragma once

#include <cobs/file/compact_index_header.hpp>
#include <cobs/query/base.hpp>

namespace cobs::query::compact_index {

class base : public query::base<file::compact_index_header>
{
protected:
    size_t m_num_hashes;
    size_t m_block_size;
    explicit base(const fs::path& path);
    uint64_t num_hashes() const override;
    uint64_t block_size() const override;
    uint64_t counts_size() const override;

public:
    virtual ~base() = default;
};

} // namespace cobs::query::compact_index

#endif // !COBS_QUERY_COMPACT_INDEX_BASE_HEADER

/******************************************************************************/
