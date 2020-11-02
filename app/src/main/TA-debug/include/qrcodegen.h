#ifndef __QRCODEGEN_H__
#define __QRCODEGEN_H__

#pragma once
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "tee_internal_api.h"

enum ErrorCorrectionCodewords {
	Ecc_LOW = 0,
	Ecc_MEDIUM,
	Ecc_QUARTILE,
	Ecc_HIGH,
};

enum QrcodeMask {
	// A special value to tell the QR Code encoder to
	// automatically select an appropriate mask pattern
	Mask_AUTO = -1,
	// The eight actual mask patterns
	Mask_ZERO = 0,
	Mask_ONE,
	Mask_TWO,
	Mask_THREE,
	Mask_FOUR,
	Mask_FIVE,
	Mask_SIX,
	Mask_SEVEN,
};

enum CodingMode {
	Mode_NUMERIC,
	Mode_ALPHANUMERIC,
	Mode_BYTE,
	Mode_KANJI,
	Mode_ECI,
};

// A segment of user/application data that a QR Code symbol can convey.
// Each segment has a mode, a character count, and character/general data that is
// already encoded as a sequence of bits. The maximum allowed bit length is 32767,
// because even the largest QR Code (version 40) has only 31329 modules.

struct QrcodeSegment {
	// The mode indicator for this segment.
	enum CodingMode mode;

	// The length of this segment's unencoded data. Always in the range [0, 32767].
	// For numeric, alphanumeric, and kanji modes, this measures in Unicode code points.
	// For byte mode, this measures in bytes (raw binary data, text in UTF-8, or other encodings).
	// For ECI mode, this is always zero.
	int numChars;

	// The data bits of this segment, packed in bitwise big endian.
	// Can be null if the bit length is zero.
	uint8_t *data;

	// The number of valid data bits used in the buffer. Requires
	// 0 <= bitLength <= 32767, and bitLength <= (capacity of data array) * 8.
	int bitLength;
};

// used for write png image to membuffer

typedef struct{
	char * buffer;
	size_t len;
}ImageBuffer;

// The minimum and maximum defined QR Code version numbers for Model 2.
#define QRCODE_VERSION_MIN  1
#define QRCODE_VERSION_MAX  40

// Calculates the number of bytes needed to store any QR Code up to and including the given version number,
// as a compile-time constant. For example, 'uint8_t buffer[qrcodegen_BUFFER_LEN_FOR_VERSION(25)];'
// can store any single QR Code from version 1 to 25, inclusive.
// Requires qrcodegen_VERSION_MIN <= n <= qrcodegen_VERSION_MAX.
#define QRCODE_BUFFER_LEN_FOR_VERSION(n)  ((((n) * 4 + 17) * ((n) * 4 + 17) + 7) / 8 + 1)

// The worst-case number of bytes needed to store one QR Code, up to and including
// version 40. This value equals 3918, which is just under 4 kilobytes.
// Use this more convenient value to avoid calculating tighter memory bounds for buffers.
#define QRCODE_BUFFER_LEN  QRCODE_BUFFER_LEN_FOR_VERSION(QRCODE_VERSION_MAX)



// Function to trans qrcode symbol to TUIformat
// trans qrcode matix to TUI format specified by type,
// if type = PNG, the return is the data of the png image, if type = SECFILE, the return is the name of the secfile
// The array qrcode is the qrcode matix
// The variable type must correspond to enum constant values.
// The variable zoom is the scaling ratio
// out parameter img_len is the bytes of the png image data
TEE_Result QrcodeInTuiFormatLocal (const char *text, uint32_t textLen, enum ErrorCorrectionCodewords ecl,
		       int destPix,char* imgData, int * imgLen);

TEE_Result TEE_Ext_QrcodeInTuiFormat (const char *text, uint32_t textLen, enum ErrorCorrectionCodewords ecl,
			   int destPix, char* imgData, int * imgLen);

#endif
