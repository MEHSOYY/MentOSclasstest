/// @file bitops.h
/// @brief Bitmasks functions.
/// @copyright (c) 2014-2024 This file is distributed under the MIT License.
/// See LICENSE.md for details.

#pragma once

#define bit_set(V, B)          ((V) | (1U << (B)))                     ///< Sets the given bit.
#define bit_clear(V, B)        ((V) & ~(1U << (B)))                    ///< Clears the given bit.
#define bit_flip(V, B)         ((V) ^ (1U << (B)))                     ///< Flips the given bit.
#define bit_check(V, B)        ((V) & (1U << (B)))                     ///< Checks if the given bit is 1.
#define bit_toggle(V, B, C)    ((C) ? bit_set(V, B) : bit_clear(V, B)) ///< Sets the given bit based on control bit C.
#define bit_set_assign(V, B)   ((V) |= (1U << (B)))                    ///< Sets the given bit, permanently.
#define bit_clear_assign(V, B) ((V) &= ~(1U << (B)))                   ///< Clears the given bit, permanently.
#define bit_flip_assign(V, B)  ((V) ^= (1U << (B)))                    ///< Flips the given bit, permanently.
#define bit_toggle_assign(V, B, C)                                                                                     \
    ((C) ? bit_set_assign(V, B) : bit_clear_assign(V, B)) ///< Sets the given bit based on control bit C.

#define bitmask_set(V, M)          ((V) | (M))          ///< Sets the bits identified by the mask.
#define bitmask_clear(V, M)        ((V) & ~(M))         ///< Clears the bits identified by the mask.
#define bitmask_flip(V, M)         ((V) ^ (M))          ///< Flips the bits identified by the mask.
#define bitmask_check(V, M)        ((V) & (M))          ///< Checks if the bits identified by the mask are all 1.
#define bitmask_exact(V, M)        (((V) & (M)) == (M)) ///< Checks if all the bits identified by the mask are all 1.
#define bitmask_set_assign(V, M)   ((V) |= (M))         ///< Sets the bits identified by the mask, permanently.
#define bitmask_clear_assign(V, M) ((V) &= ~(M))        ///< Clears the bits identified by the mask, permanently.
#define bitmask_flip_assign(V, M)  ((V) ^= (M))         ///< Flips the bits identified by the mask, permanently.

/// @brief Finds the first bit at zero, starting from the less significative bit.
/// @param value the value we need to analyze.
/// @return the position of the first zero bit.
static inline int find_first_zero(unsigned long value)
{
    for (int i = 0; i < 32; ++i) {
        if (!bit_check(value, i)) {
            return i;
        }
    }
    return 0;
}

/// @brief Finds the first bit not zero, starting from the less significative bit.
/// @param value the value we need to analyze.
/// @return the position of the first non-zero bit.
static inline int find_first_non_zero(unsigned long value)
{
    for (int i = 0; i < 32; ++i) {
        if (bit_check(value, i)) {
            return i;
        }
    }
    return 0;
}
