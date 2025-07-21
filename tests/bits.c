#include <stdint.h>
#include "ctest.h"

#include "libos/bits.h"

// ====================
//
// GET_MASK
//
// ====================

CTEST(bits_GET_MASK, specificValue)
{
	const uint8_t kValue = 0b10101010;
	const uint8_t kMask  = 0b00011000;
	ASSERT_EQUAL(kValue & kMask, GET_MASK(kValue, kMask));
}

CTEST(bits_GET_MASK, zeroMask)
{
	const uint8_t kValue = 0b10101010;
	const uint8_t kMask  = 0x00;
	ASSERT_EQUAL(0x00, GET_MASK(kValue, kMask));
}

// ====================
//
// HAS_MASK
//
// ====================

CTEST(bits_HAS_MASK, specificValueNotFullyMatched)
{
	const uint8_t kValue = 0b10101010;
	const uint8_t kMask  = 0b00011000;
	ASSERT_FALSE(HAS_MASK(kValue, kMask));
}

CTEST(bits_HAS_MASK, specificValueFulMatch)
{
	const uint8_t kValue = 0b10111010;
	const uint8_t kMask  = 0b00011000;
	ASSERT_TRUE(HAS_MASK(kValue, kMask));
}

CTEST(bits_HAS_MASK, zeroMask)
{
	const uint8_t kValue = 0b10101010;
	const uint8_t kMask  = 0x00;
	ASSERT_FALSE(HAS_MASK(kValue, kMask));
}

// ====================
//
// ONLY_MASK
//
// ====================

CTEST(bits_ONLY_MASK, noBitsInMaskOrValue)
{
	const uint8_t kValue = 0;
	const uint8_t kMask  = 0;
	ASSERT_TRUE(ONLY_MASK(kValue, kMask));
}

CTEST(bits_ONLY_MASK, bitsInMaskButNotInValue)
{
	const uint8_t kValue = 0;
	const uint8_t kMask  = 0b1100;
	ASSERT_FALSE(ONLY_MASK(kValue, kMask));
}

CTEST(bits_ONLY_MASK, bitsInMaskAndInValue)
{
	const uint8_t kValue = 0b1100;
	const uint8_t kMask  = 0b1100;
	ASSERT_TRUE(ONLY_MASK(kValue, kMask));
}

CTEST(bits_ONLY_MASK, bitsInMaskMismatchedWithValue)
{
	const uint8_t kValue = 0b0100;
	const uint8_t kMask  = 0b1100;
	ASSERT_FALSE(ONLY_MASK(kValue, kMask));
}

CTEST(bits_ONLY_MASK, bitsInMaskAndBelowMaskInValue)
{
	const uint8_t kValue = 0b01100;
	const uint8_t kMask  = 0b01101;
	ASSERT_FALSE(ONLY_MASK(kValue, kMask));
}

CTEST(bits_ONLY_MASK, bitsInMaskAndAboveMaskInValue)
{
	const uint8_t kValue = 0b11100;
	const uint8_t kMask  = 0b01100;
	ASSERT_FALSE(ONLY_MASK(kValue, kMask));
}

// ====================
//
// HAS_FLAG
//
// ====================

CTEST(bits_HAS_FLAG, hasValueButNotFlag)
{
	const uint8_t kValue = 0b10101010;
	const uint8_t kPos   = 2;
	ASSERT_FALSE(HAS_FLAG(kValue, kPos));
}

CTEST(bits_HAS_FLAG, hasValueWithFlag)
{
	const uint8_t kValue = 0b10101010;
	const uint8_t kPos   = 1;
	ASSERT_TRUE(HAS_FLAG(kValue, kPos));
}

CTEST(bits_HAS_FLAG, hasValueFlagZero)
{
	const uint8_t kValue = 0b10101010;
	const uint8_t kPos   = 0;
	ASSERT_FALSE(HAS_FLAG(kValue, kPos));
}

// ====================
//
// ONLY_FLAG
//
// ====================

CTEST(bits_ONLY_FLAG, hasMoreValueBesidesFlag)
{
	const uint8_t kValue = 0b10101010;
	const uint8_t kPos   = 1;
	ASSERT_FALSE(ONLY_FLAG(kValue, kPos));
}

CTEST(bits_ONLY_FLAG, hasMoreValueAndNoFlag)
{
	const uint8_t kValue = 0b10101000;
	const uint8_t kPos   = 1;
	ASSERT_FALSE(ONLY_FLAG(kValue, kPos));
}

CTEST(bits_ONLY_FLAG, hasValueOnlyFlag)
{
	const uint8_t kValue = 0b010;
	const uint8_t kPos   = 1;
	ASSERT_TRUE(ONLY_FLAG(kValue, kPos));
}

// ====================
//
// SET_MASK
//
// ====================
CTEST(bits_SET_MASK, setValueOnZero)
{
	uint8_t value = 0x00;
	const uint8_t kMask = 0b00111100;
	SET_MASK(value, kMask);
	ASSERT_EQUAL(kMask, value);
}

CTEST(bits_SET_MASK, setValueWithAlreadySet)
{
	uint8_t value = 0b10000001;
	const uint8_t kMask = 0b00111100;
	const uint8_t kExpected = 0b10111101;
	SET_MASK(value, kMask);
	ASSERT_EQUAL(kExpected, value);
}

// ====================
//
// SET_FLAG
//
// ====================
CTEST(bits_SET_FLAG, setValueOnZero)
{
	uint8_t value = 0x00;
	const uint8_t kExpected = 0b00000010;
	SET_FLAG(value, 1);
	ASSERT_EQUAL(kExpected, value);
}

CTEST(bits_SET_FLAG, setValueWithAlreadySet)
{
	uint8_t value = 0b00111000;
	const uint8_t kExpected = 0b00111010;
	SET_FLAG(value, 1);
	ASSERT_EQUAL(kExpected, value);
}

// ====================
//
// SET_MASKED_VALUE
//
// ====================
CTEST(bits_SET_MASKED_VALUE, setValueOnZero)
{
	uint8_t value = 0x00;
	const uint8_t kMask = 0b00001111;
	const uint8_t kMaskValue = 0b00000011;
	const uint8_t kExpected = 0b00000011;
	SET_MASKED_VALUE(value, kMask, kMaskValue);
	ASSERT_EQUAL(kExpected, value);
}
CTEST(bits_SET_MASKED_VALUE, setValueOnZeroWithValueOutsideOfMask)
{
	uint8_t value = 0x00;
	const uint8_t kMask = 0b00001111;
	const uint8_t kMaskValue = 0b01100011;
	const uint8_t kExpected = 0b00000011;
	SET_MASKED_VALUE(value, kMask, kMaskValue);
	ASSERT_EQUAL(kExpected, value);
}

CTEST(bits_SET_MASKED_VALUE, setValueWithAlreadySet)
{
	uint8_t value = 0x0F;
	const uint8_t kMask = 0b00001111;
	const uint8_t kMaskValue = 0b01100011;
	const uint8_t kExpected = 0b00000011;
	SET_MASKED_VALUE(value, kMask, kMaskValue);
	ASSERT_EQUAL(kExpected, value);
}

// ====================
//
// GET_LOWER_NIBBLE
//
// ====================
CTEST(bits_GET_LOWER_NIBBLE, moreDataSetThanJustNibble)
{
	const uint8_t kValue = 0x5A;
	const uint8_t kExpected = 0xA;
	ASSERT_EQUAL(kExpected, GET_LOWER_NIBBLE(kValue));
}

// ====================
//
// GET_UPPER_NIBBLE
//
// ====================
CTEST(bits_GET_UPPER_NIBBLE, moreDataSetThanJustNibble)
{
	const uint8_t kValue = 0x5A;
	const uint8_t kExpected = 0x5;
	ASSERT_EQUAL(kExpected, GET_UPPER_NIBBLE(kValue));
}

// ====================
//
// SET_LOWER_NIBBLE
//
// ====================
CTEST(bits_SET_LOWER_NIBBLE, setOnCleanData)
{
	uint8_t value = 0x00;
	const uint8_t kNibble = 0xA;
	const uint8_t kExpected = 0x0A;
	SET_LOWER_NIBBLE(value, kNibble);
	ASSERT_EQUAL(kExpected, value);
}

CTEST(bits_SET_LOWER_NIBBLE, nibbleHasOnlyUpperNibbleData)
{
	uint8_t value = 0x5A;
	const uint8_t kNibble = 0xF0;
	const uint8_t kExpected = 0x50;
	SET_LOWER_NIBBLE(value, kNibble);
	ASSERT_EQUAL(kExpected, value);
}

CTEST(bits_SET_LOWER_NIBBLE, moreDataSetThanJustNibble)
{
	uint8_t value = 0x5A;
	const uint8_t kNibble = 0xFF;
	const uint8_t kExpected = 0x5F;
	SET_LOWER_NIBBLE(value, kNibble);
	ASSERT_EQUAL(kExpected, value);
}

// ====================
//
// SET_UPPER_NIBBLE
//
// ====================
CTEST(bits_SET_UPPER_NIBBLE, setOnCleanData)
{
	uint8_t value = 0x00;
	const uint8_t kNibble = 0xA;
	const uint8_t kExpected = 0xA0;
	SET_UPPER_NIBBLE(value, kNibble);
	ASSERT_EQUAL(kExpected, value);
}

CTEST(bits_SET_UPPER_NIBBLE, nibbleHasOnlyHighNibbleData)
{
	uint8_t value = 0x5A;
	const uint8_t kNibble = 0xF0;
	const uint8_t kExpected = 0x0A;
	SET_UPPER_NIBBLE(value, kNibble);
	ASSERT_EQUAL(kExpected, value);
}

CTEST(bits_SET_UPPER_NIBBLE, moreDataSetThanJustNibble)
{
	uint8_t value = 0x5A;
	const uint8_t kNibble = 0xCF;
	const uint8_t kExpected = 0xFA;
	SET_UPPER_NIBBLE(value, kNibble);
	ASSERT_EQUAL(kExpected, value);
}

// ====================
//
// COMBINE_BYTES_16
//
// ====================
CTEST(bits_COMBINE_BYTES_16, simpleData)
{
	const uint8_t kValue1 = 0xAA;
	const uint8_t kValue2 = 0x55;
	const uint16_t kExpected = 0x55AA;
	const uint16_t kResultValue = COMBINE_BYTES_16(kValue1, kValue2);
	ASSERT_EQUAL(kExpected, kResultValue);
}

// ====================
//
// COMBINE_BYTES_32
//
// ====================
CTEST(bits_COMBINE_BYTES_32, simpleData)
{
	const uint8_t kValue1 = 0xAA;
	const uint8_t kValue2 = 0x55;
	const uint8_t kValue3 = 0x11;
	const uint8_t kValue4 = 0xFF;
	const uint32_t kExpected = 0xFF1155AA;
	const uint32_t kResultValue = COMBINE_BYTES_32(kValue1, kValue2, kValue3, kValue4);
	ASSERT_EQUAL(kExpected, kResultValue);
}

// ====================
//
// SET_16_IN_ARRAY
//
// ====================
CTEST(bits_SET_16_IN_ARRAY, simpleDataAtStart)
{
	const uint16_t kValue = COMBINE_BYTES_16(0xBB, 0xAA);
	uint8_t data[4] = { 0x11, 0x22, 0x33, 0x44 };

	SET_16_IN_ARRAY(data, kValue, 0);
	ASSERT_EQUAL(0xBB, data[0]);
	ASSERT_EQUAL(0xAA, data[1]);
	ASSERT_EQUAL(0x33, data[2]);
	ASSERT_EQUAL(0x44, data[3]);
}

CTEST(bits_SET_16_IN_ARRAY, simpleDataInMiddle)
{
	const uint16_t kValue = COMBINE_BYTES_16(0xBB, 0xAA);
	uint8_t data[4] = { 0x11, 0x22, 0x33, 0x44 };

	SET_16_IN_ARRAY(data, kValue, 1);
	ASSERT_EQUAL(0x11, data[0]);
	ASSERT_EQUAL(0xBB, data[1]);
	ASSERT_EQUAL(0xAA, data[2]);
	ASSERT_EQUAL(0x44, data[3]);
}

CTEST(bits_SET_16_IN_ARRAY, simpleDataAtEnd)
{
	const uint16_t kValue = COMBINE_BYTES_16(0xBB, 0xAA);
	uint8_t data[4] = { 0x11, 0x22, 0x33, 0x44 };

	SET_16_IN_ARRAY(data, kValue, 2);
	ASSERT_EQUAL(0x11, data[0]);
	ASSERT_EQUAL(0x22, data[1]);
	ASSERT_EQUAL(0xBB, data[2]);
	ASSERT_EQUAL(0xAA, data[3]);
}

CTEST(bits_SET_16_IN_ARRAY, largerDataThan16)
{
	const uint32_t kValue = COMBINE_BYTES_32(0xBB, 0xDD, 0xCC, 0xAA);
	uint8_t data[4] = { 0x11, 0x22, 0x33, 0x44 };

	SET_16_IN_ARRAY(data, kValue, 1);
	ASSERT_EQUAL(0x11, data[0]);
	ASSERT_EQUAL(0xBB, data[1]);
	ASSERT_EQUAL(0xDD, data[2]);
	ASSERT_EQUAL(0x44, data[3]);
}

CTEST(bits_SET_16_IN_ARRAY, setting0s)
{
	const uint32_t kValue = 0x00;
	uint8_t data[4] = { 0x11, 0x22, 0x33, 0x44 };

	SET_16_IN_ARRAY(data, kValue, 1);
	ASSERT_EQUAL(0x11, data[0]);
	ASSERT_EQUAL(0x00, data[1]);
	ASSERT_EQUAL(0x00, data[2]);
	ASSERT_EQUAL(0x44, data[3]);
}

// ====================
//
// SET_32_IN_ARRAY
//
// ====================
CTEST(bits_SET_32_IN_ARRAY, simpleDataAtStart)
{
	const uint32_t kValue = COMBINE_BYTES_32(0xBB, 0xAA, 0xCC, 0xEE);
	uint8_t data[8] = { 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88 };

	SET_32_IN_ARRAY(data, kValue, 0);
	
	ASSERT_EQUAL(0xBB, data[0]);
	ASSERT_EQUAL(0xAA, data[1]);
	ASSERT_EQUAL(0xCC, data[2]);
	ASSERT_EQUAL(0xEE, data[3]);
	ASSERT_EQUAL(0x55, data[4]);
	ASSERT_EQUAL(0x66, data[5]);
	ASSERT_EQUAL(0x77, data[6]);
	ASSERT_EQUAL(0x88, data[7]);
}

CTEST(bits_SET_32_IN_ARRAY, simpleDataInMiddle)
{
	const uint32_t kValue = COMBINE_BYTES_32(0xBB, 0xAA, 0xCC, 0xEE);
	uint8_t data[8] = { 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88 };

	SET_32_IN_ARRAY(data, kValue, 2);
	ASSERT_EQUAL(0x11, data[0]);
	ASSERT_EQUAL(0x22, data[1]);
	ASSERT_EQUAL(0xBB, data[2]);
	ASSERT_EQUAL(0xAA, data[3]);
	ASSERT_EQUAL(0xCC, data[4]);
	ASSERT_EQUAL(0xEE, data[5]);
	ASSERT_EQUAL(0x77, data[6]);
	ASSERT_EQUAL(0x88, data[7]);
}

CTEST(bits_SET_32_IN_ARRAY, simpleDataAtEnd)
{
	const uint32_t kValue = COMBINE_BYTES_32(0xBB, 0xAA, 0xCC, 0xEE);
	uint8_t data[8] = { 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88 };
	
	SET_32_IN_ARRAY(data, kValue, 4);
	ASSERT_EQUAL(0x11, data[0]);
	ASSERT_EQUAL(0x22, data[1]);
	ASSERT_EQUAL(0x33, data[2]);
	ASSERT_EQUAL(0x44, data[3]);
	ASSERT_EQUAL(0xBB, data[4]);
	ASSERT_EQUAL(0xAA, data[5]);
	ASSERT_EQUAL(0xCC, data[6]);
	ASSERT_EQUAL(0xEE, data[7]);
}

CTEST(bits_SET_32_IN_ARRAY, largerDataThan32)
{
	const uint64_t kValue = COMBINE_BYTES_32(0xBB, 0xDD, 0xCC, 0xAA) | (0xFFLL << 32);
	uint8_t data[8] = { 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88 };

	SET_32_IN_ARRAY(data, kValue, 2);
	ASSERT_EQUAL(0x11, data[0]);
	ASSERT_EQUAL(0x22, data[1]);
	ASSERT_EQUAL(0xBB, data[2]);
	ASSERT_EQUAL(0xDD, data[3]);
	ASSERT_EQUAL(0xCC, data[4]);
	ASSERT_EQUAL(0xAA, data[5]);
	ASSERT_EQUAL(0x77, data[6]);
	ASSERT_EQUAL(0x88, data[7]);
}

CTEST(bits_SET_32_IN_ARRAY, setting0s)
{
	const uint32_t kValue = 0x00;
	uint8_t data[8] = { 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88 };

	SET_32_IN_ARRAY(data, kValue, 2);
	ASSERT_EQUAL(0x11, data[0]);
	ASSERT_EQUAL(0x22, data[1]);
	ASSERT_EQUAL(0x00, data[2]);
	ASSERT_EQUAL(0x00, data[3]);
	ASSERT_EQUAL(0x00, data[4]);
	ASSERT_EQUAL(0x00, data[5]);
	ASSERT_EQUAL(0x77, data[6]);
	ASSERT_EQUAL(0x88, data[7]);
}

// ====================
//
// SET_16_IN_ARRAY
//
// ====================
CTEST(bits_GET_16_IN_ARRAY, simpleData)
{
  const uint16_t kValue = 0x1234;
  uint8_t data[4] = { 0xAA, 0xBB, 0xCC, 0xDD };
  
  SET_16_IN_ARRAY(data, kValue, 1);

  ASSERT_EQUAL(kValue, GET_16_IN_ARRAY(data, 1));
}

// ====================
//
// SET_32_IN_ARRAY
//
// ====================
CTEST(bits_GET_32_IN_ARRAY, simpleData)
{
  const uint32_t kValue = 0x12345678;
  uint8_t data[8] = { 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF, 0x11, 0x22 };
  
  SET_32_IN_ARRAY(data, kValue, 3);

  ASSERT_EQUAL(kValue, GET_32_IN_ARRAY(data, 3));
}
