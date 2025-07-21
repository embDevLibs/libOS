/**
 * @file bits.h
 * @brief Simple utilities to help with bit manipulations.
 * 
 * @details
 * This header provides some macros that are commonly used for bit
 * manipulation. These utilities help write some more expressive code but also
 * help prevent some common mistakes that are made when doing bit manipulation.
 * 
 * The default implementations of the multi-byte macros do assume that the
 * output should be big-endian. This can be reversed with some other macros
 * that convert between the 2 orders.
 * A platform must override these macros if the usual bit operators don't yield
 * the usual result of where the more left bits are more significant.
 *
 * A platform can also provide a specific implementation that is optimized for
 * the architecture that it is running on. This header just provides a generic,
 * as portable as reasonably possible, default implementation. A implementation
 * may NOT implement these operations as functions. This would mean that it
 * would not be possible to use these macros for static initialisation of data.
 *
 * Generally speaking, the macros do not assume any types. Unless explicitly
 * stated. Examples are the macros to retrieve nibbles of a byte, or combine
 * singular bytes into a larger word like 16 bit words.
 *
 * IMPLEMENTORS:
 * Implementors are free to override any macro that they want. It is required
 * that implementation must at least adhere to specified requirements of the
 * default implementation. Otherwise, undefined behavior may occur. It should
 * be noted that it is NOT allowed to call C functions, or have any C code that
 * is not allowed to be used in static initialisation code on the platform.
 * 
 * In the case that C code is provided as extra utility functions, it should be
 * wrapped in a extern "C" block like below to provide compatibility with the
 * C++ world.
 *
 * @code 
 * #ifdef __cplusplus
 * extern "C" {
 * #endif // __cplusplus
 * 
 * // Functions
 * 
 * #ifdef __cplusplus
 * }
 * #endif // __cplusplus
 * 
 * @endcode
 * 
 * Or, if it does not have a block, each function should be marked as 
 * @code
 * extern "C"
 * @endcode
 * . The general API header for the time places all the functions in
 * a extern "C" code block.
 */

#pragma once
#ifndef LIBOS_BITS_H
#define LIBOS_BITS_H

#include <stdint.h>

#include "libos/platform/bits.h"

#ifndef GET_MASK

/**
 * @brief Use the mask to get out the masked value.
 *
 * @param value The value to apply the mask on.
 * @param mask The mask to apply to the value.
 *
 */
#define GET_MASK(value, mask) ((value) & (mask))
#endif

#ifndef HAS_MASK

/**
 * @brief Masks the value and checks if the mask matches the mask itself (to ensure the mask was properly set).
 * 
 * @param value The value to check the mask for.
 * @param mask The mask to check for in the value.
 *
 * @return true if the bits of the mask are set.
 * @return false if not all the bits are set, or the mask is not set.
 *
 */
#define HAS_MASK(value, mask) ((GET_MASK(value, mask) == (mask)) && ((mask) != 0))
#endif


#ifndef ONLY_MASK

/**
 * @brief Checks if the value has the ONLY masked bit(s) set (and all the masked bits, none can be missing).
 * 
 * @param value The value to check the mask on.
 * @param flag_pos The mask to check for in the value.
 * 
 * @return true if the mask are the the only bit(s) is set.
 * @return false if the mask are NOT the the only bit(s) is set.
 *
 */
#define ONLY_MASK(value, mask) ( ((GET_MASK(value, mask) == (mask)) && (((value) & (mask)) == (value))) )
#endif

#ifndef HAS_FLAG

/**
 * @brief Checks if the value has the given bit index set.
 * 
 * @param value The value to check the bit flag on.
 * @param flag_pos The index (0-based) of the bit to check.
 * 
 * @return true if the bit is set.
 * @return false if the bit is NOT set.
 *
 */
#define HAS_FLAG(value, flag_pos) (HAS_MASK(value, 1 << flag_pos))
#endif

#ifndef ONLY_FLAG

/**
 * @brief Checks if the value has the ONLY bit index set.
 * 
 * @param value The value to check the bit flag on.
 * @param flag_pos The index (0-based) of the bit to check.
 * 
 * @return true if this is the only bit is set.
 * @return false if is NOT the only bit is set.
 *
 */
#define ONLY_FLAG(value, flag_pos) ( (HAS_FLAG(value, flag_pos) && (((value) & (1 << (flag_pos))) == (value))) )
#endif

#ifndef SET_MASK

/**
 * @brief Sets the mask as is in the value.
 * 
 * @param value The value to set the mask in.
 * @param mask The mask to set in the value.
 * 
 */
#define SET_MASK(value, mask) ((value) = ((value) & ~(mask)) | (mask))
#endif

#ifndef CLEAR_MASK

/**
 * @brief Clears the bits in the value according to the mask.
 * 
 * @param value The value to set the mask in.
 * @param mask The mask to set in the value.
 * 
 */
#define CLEAR_MASK(value, mask) ((value) = ((value) & ~(mask)))
#endif

#ifndef SET_FLAG

/**
 * @brief Sets a given bit in the value.
 * 
 * @param value The value to set a bit in.
 * @param flag_pos The index (0-based) of the bit to set in the value.
 * 
 */
#define SET_FLAG(value, flag_pos) (SET_MASK(value, (1 << flag_pos)))
#endif

#ifndef CLEAR_FLAG

/**
 * @brief Clears a given bit in the value.
 * 
 * @param value The value to set a bit in.
 * @param flag_pos The index (0-based) of the bit to set in the value.
 * 
 */
#define CLEAR_FLAG(value, flag_pos) (CLEAR_MASK(value, (1 << flag_pos)))
#endif

#ifndef SET_MASKED_VALUE

/**
 * @brief Sets a value that is masked with another bitmask.
 * 
 * @param value The value to the set the masked value in
 * @param set_mask The bitmask for which bit's can be overriden with the new value
 * @param set_value The value that will be set in the original value (but first masked).
 *
 */
#define SET_MASKED_VALUE(value, set_mask, set_value) ((value) = (((value) & (~set_mask)) | ((set_value) & (set_mask))))
#endif

#ifndef GET_LOWER_NIBBLE

/**
 * @brief Retrieves the lower 4 bits of a value.
 * 
 * @param value The value to get the lower nibble (4 bits) from.
 * 
 */
#define GET_LOWER_NIBBLE(value) ((value) & 0xF)
#endif

#ifndef GET_UPPER_NIBBLE

/**
 * @brief Retrieves the upper nibble of a value.
 * @warning This assumes that the value is a 8 bit value (byte), any data after the first 8 bits will be ignored!
 * 
 * @param value The value to get the upper nibble (bits 4 through 8) from.
 * 
 */
#define GET_UPPER_NIBBLE(value) (((value) >> 4) & 0xF)
#endif

#ifndef SET_LOWER_NIBBLE

/**
 * @brief Sets the lower nibble with the lower nibble of the set value.
 *
 * @param value The value to set the lower 4 bits in.
 * @param nibble The 4 bits (taken from nibble's lower nibble too) to set in the value.
 * 
 */
#define SET_LOWER_NIBBLE(value, nibble) ((value) = ((value & 0xF0) | ((uint8_t)(nibble) & 0xF)))
#endif

#ifndef SET_UPPER_NIBBLE

/**
 * @brief Sets the upper nibble of a value.
 * @warning This assumes that the value is a 8 bit value (byte), any data after the first 8 bits will be ignored! Any data there may or may not be lost!
 * 
 * @param value The 8 bit value to set the upper nibble in.
 * @param nibble The 4 bits (taken from the nibble's lower nibble!) to set in the value.
 *
 */
#define SET_UPPER_NIBBLE(value, nibble) ((value) = ((value & 0xF) | (((uint8_t)(nibble) & 0xF) << 4)))
#endif

#ifndef COMBINE_BYTES_16

/**
 * @brief Combines the given two bytes into a unsigned 16 bit integer.
 *
 * @details
 * The data entry for the parameters is like entering a big endian number. This
 * is usually how larger number are also written.
 * 
 * @param higher The most significant byte of the uint16.
 * @param lower The least significant byte of the uint16.
 * 
 */
#define COMBINE_BYTES_16(higher, lower) (((uint16_t)(lower)) | (((uint16_t)(higher)) << 8))
#endif

#ifndef COMBINE_BYTES_32

/**
 * @brief Combines the given 4 four bytes into a 32 bit unsigned integer.
 *
 * @details
 * The data entry for the parameters is like entering a big endian number. This
 * is usually how larger number are also written.
 * 
 * @param higher The most significant byte of the uint32.
 * @param higher_middle The most byte of the two middle bytes of the uint32 (bit 16-23).
 * @param lower_middle The least significant byte of the two middle bytes of the uint32 (bit 8-15).
 * @param lower The least significant byte of the uint32.
 * 
 */
#define COMBINE_BYTES_32(higher, higher_middle, lower_middle, lower) ((uint32_t)COMBINE_BYTES_16(lower_middle, lower) | ((uint32_t)COMBINE_BYTES_16(higher, higher_middle) << 16))
#endif

#ifndef SET_16_IN_ARRAY

/**
 * @brief Sets the given 16 bits of data at @ref byte_offset in the @ref data memory.
 *
 * @details
 * Be aware that this macro doesn't do any bounds checking on the array given
 * to it. It is the users responsibility to ensure that data is written inside
 * the allocated memory for the data.
 *
 * Note that the byte endianess of @ref data is assumed to be big endian
 * because this macro focuses on 'exporting' data is it where. Which is usually
 * big-endian. If this is not the correct end ordering, the user should do a
 * byte reordering to little-endian.
 *
 * Whilst data, value and byte_offset are only evaluated once in the default
 * implementation, this is not guaranteed for other platform implementations.
 * 
 * @param data The memory to place the data in.
 * @param value The 16 bits of data to place in the memory.
 * @param byte_offset The bytes in 8-bit words from the starting point of @ref data.
 *
 */
#define SET_16_IN_ARRAY(data, value, byte_offset) do {                                                                           \
                                                    uint16_t __val = (value);                                                     \
                                                    (*((uint8_t*)(data) + (size_t)((byte_offset) + 0)) = ((__val >>  8) & 0xFF)); \
                                                    (*((uint8_t*)(data) + (size_t)((byte_offset) + 1)) = ((__val >>  0) & 0xFF)); \
                                                  } while(0)
#endif // SET_16_IN_ARRAY

#ifndef SET_32_IN_ARRAY

/**
 * @brief Sets the given 32 bits of data at @ref byte_offset in the @ref data memory.
 *
 * @details
 * Be aware that this macro doesn't do any bounds checking on the array given
 * to it. It is the users responsibility to ensure that data is written inside
 * the allocated memory for the data.
 *
 * Note that the byte endianess of @ref data is assumed to be big endian
 * because this macro focuses on 'exporting' data is it where. Which is usually
 * big-endian. If this is not the correct end ordering, the user should do a
 * byte reordering to little-endian.
 *
 * Whilst data, value and byte_offset are only evaluated once in the default
 * implementation, this is not guaranteed for other platform implementations.
 * 
 * @param data The memory to place the data in.
 * @param value The 32 bits of data to place in the memory.
 * @param byte_offset The bytes in 8-bit words from the starting point of @ref data.
 *
 */
#define SET_32_IN_ARRAY(data, value, byte_offset) do {                                                            \
                                                    uint32_t __val = (value);                                     \
                                                    uint8_t *__data = ((uint8_t*)(data) + (size_t)(byte_offset)); \
                                                    *(__data + 0) = ((__val >> 24) & 0xFF);                       \
                                                    *(__data + 1) = ((__val >> 16) & 0xFF);                       \
                                                    *(__data + 2) = ((__val >>  8) & 0xFF);                       \
                                                    *(__data + 3) = ((__val >>  0) & 0xFF);                       \
                                                  } while(0)
#endif // SET_32_IN_ARRAY

#ifndef GET_16_IN_ARRAY

/**
 * @brief Retrieves the 16 bits of data at @ref byte_offset in the @ref data memory.
 *
 * @details
 * Be aware that this macro doesn't do any bounds checking on the array given
 * to it. It is the users responsibility to ensure that data is written inside
 * the allocated memory for the data.
 *
 * Note that the byte endianess of @ref data is assumed to be big endian
 * because this macro focuses on 'exporting' data is it where. Which is usually
 * big-endian. If this is not the correct end ordering, the user should do a
 * byte reordering to little-endian.
 *
 * Whilst data and byte_offset are only evaluated once in the default
 * implementation, this is not guaranteed for other platform implementations.
 * 
 * @param data The memory to retrieve the data from.
 * @param byte_offset The bytes in 8-bit words from the starting point of @ref data.
 *
 * @return uint16_t The 16-bit value at the given location.
 */
#define GET_16_IN_ARRAY(data, byte_offset) ((uint16_t)(  \
                                             ((uint16_t)(*(((uint8_t*)data) + (size_t)((byte_offset) + 0))) << 8) | \
                                             ((uint16_t)(*(((uint8_t*)data) + (size_t)((byte_offset) + 1))) << 0)   \
                                           ))
#endif // GET_16_IN_ARRAY

#ifndef GET_32_IN_ARRAY

/**
 * @brief Retrieves the 16 bits of data at @ref byte_offset in the @ref data memory.
 *
 * @details
 * Be aware that this macro doesn't do any bounds checking on the array given
 * to it. It is the users responsibility to ensure that data is written inside
 * the allocated memory for the data.
 *
 * Note that the byte endianess of @ref data is assumed to be big endian
 * because this macro focuses on 'exporting' data is it where. Which is usually
 * big-endian. If this is not the correct end ordering, the user should do a
 * byte reordering to little-endian.
 *
 * Whilst data and byte_offset are only evaluated once in the default
 * implementation, this is not guaranteed for other platform implementations.
 * 
 * @param data The memory to retrieve the data from.
 * @param byte_offset The bytes in 8-bit words from the starting point of @ref data.
 *
 * @return uint16_t The 32-bit value at the given location.
 */
#define GET_32_IN_ARRAY(data, byte_offset) ((uint32_t)(  \
                                             ((uint32_t)(*(((uint8_t*)data) + (size_t)((byte_offset) + 0))) << 24) | \
                                             ((uint32_t)(*(((uint8_t*)data) + (size_t)((byte_offset) + 1))) << 16) | \
                                             ((uint32_t)(*(((uint8_t*)data) + (size_t)((byte_offset) + 2))) << 8)  | \
                                             ((uint32_t)(*(((uint8_t*)data) + (size_t)((byte_offset) + 3))) << 0)    \
                                           ))
#endif // GET_32_IN_ARRAY

#ifndef REVERSE_BYTES_IN_ARRAY_16BIT

/**
 * @brief Reverse the two bytes in the 16 bit word.
 * 
 * @param data The memory to swap the bytes in.
 * @param byte_offset The bytes in the 8-bit words from the starting point of @ref data.
 * 
 */
#define REVERSE_BYTES_IN_ARRAY_16BIT(data, byte_offset) do {                                                            \
                                                          uint8_t *__data = ((uint8_t*)(data) + (size_t)(byte_offset)); \
                                                          uint8_t __temp = *__data;                                     \
                                                          *(__data + 0) = *(__data + 1);                                \
                                                          *(__data + 1) = __temp;                                       \
                                                        } while(0)
#endif // REVERSE_BYTES_IN_ARRAY_16BIT

#ifndef REVERSE_BYTES_IN_ARRAY_32BIT

/**
 * @brief Reverse the order of the four bytes in the 32 bit word.
 * 
 * @param data The memory to swap the bytes in.
 * @param byte_offset The bytes in the 8-bit words from the starting point of @ref data.
 * 
 */
#define REVERSE_BYTES_IN_ARRAY_32BIT(data, byte_offset) do {                                                            \
                                                          uint8_t *__data = ((uint8_t*)(data) + (size_t)(byte_offset)); \
                                                          uint8_t __temp = *(__data + 0);                               \
                                                          *(__data + 0) = *(__data + 3);                                \
                                                          *(__data + 3) = __temp;                                       \
                                                          __temp = *(__data + 1);                                       \
                                                          *(__data + 1) = *(__data + 2);                                \
                                                          *(__data + 2) = __temp;                                       \
                                                        } while(0)
#endif // REVERSE_BYTES_IN_ARRAY_32BIT

#endif // LIBOS_BITS_H
