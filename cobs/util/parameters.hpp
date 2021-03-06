/*******************************************************************************
 * cobs/util/parameters.hpp
 *
 * Copyright (c) 2018 Florian Gauger
 *
 * All rights reserved. Published under the MIT License in the LICENSE file.
 ******************************************************************************/

#ifndef COBS_UTIL_PARAMETERS_HEADER
#define COBS_UTIL_PARAMETERS_HEADER
#pragma once

#include <cstdint>

namespace cobs {

double calc_signature_size_ratio(double num_hashes, double false_positive_probability);
uint64_t calc_signature_size(uint64_t num_elements, double num_hashes, double false_positive_probability);
double calc_average_set_bit_ratio(uint64_t signature_size, double num_hashes, double false_positive_probability);

} // namespace cobs

#endif // !COBS_UTIL_PARAMETERS_HEADER

/******************************************************************************/
