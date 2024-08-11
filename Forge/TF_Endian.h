#ifndef _TF_ENDIAN_H
#define _TF_ENDIAN_H

#include "Forge/TF_Config.h"

// ref: https://gist.github.com/panzi/6856583
#if defined(TF_TARGET_LINUX)

#if BYTE_ORDER == LITTLE_ENDIAN
#define TF_HOST_LITTLE_ENDIAN
#else
#define TF_HOST_BIG_ENDIAN
#endif

#include <endian.h>

#define tfHostToBE16(x) htobe16(x)
#define tfHostToLE16(x) htole16(x)
#define tfBE16ToHost(x) be16toh(x)
#define tfLE16ToHost(x) le16toh(x)

#define tfHostToBE32(x) htobe32(x)
#define tfhostToLE32(x) htole32(x)
#define tfBE32ToHost(x) be32toh(x)
#define tfLE32ToHost(x) le32toh(x)

#define tfHostToBE64(x) htobe64(x)
#define tfhostToLE64(x) htole64(x)
#define tfBE64ToHost(x) be64toh(x)
#define tfLE64ToHost(x) le64toh(x)

#elif defined(TF_TARGET_DARWIN)



#include <libkern/OSByteOrder.h>

#define tfHostToBE16(x) OSSwapHostToBigInt16(x)
#define tfHostToLE16(x) OSSwapHostToLittleInt16(x)
#define tfBE16ToHost(x) OSSwapBigToHostInt16(x)
#define tfLE16ToHost(x) OSSwapLittleToHostInt16(x)

#define tfHostToBE32(x) OSSwapHostToBigInt32(x)
#define tfhostToLE32(x) OSSwapHostToLittleInt32(x)
#define tfBE32ToHost(x) OSSwapBigToHostInt32(x)
#define tfLE32ToHost(x) OSSwapLittleToHostInt32(x)

#define tfHostToBE64(x) OSSwapHostToBigInt64(x)
#define tfhostToLE64(x) OSSwapHostToLittleInt64(x)
#define tfBE64ToHost(x) OSSwapBigToHostInt64(x)
#define tfLE64ToHost(x) OSSwapLittleToHostInt64(x)

#if BYTE_ORDER == LITTLE_ENDIAN
#define TF_HOST_LITTLE_ENDIAN
#else
#define TF_HOST_BIG_ENDIAN
#endif

#elif defined(TF_TARGET_WINDOWS)

#include <winsock2.h>
//#ifdef __GNUC__
//#include <sys/param.h>
//#endif

#if BYTE_ORDER == LITTLE_ENDIAN
#define TF_HOST_LITTLE_ENDIAN
#else
#define TF_HOST_BIG_ENDIAN
#endif

#if BYTE_ORDER == LITTLE_ENDIAN

#define tfHostToBE16(x) htons(x)
#define tfHostToLE16(x) (x)
#define tfBE16ToHost(x) ntohs(x)
#define tfLE16ToHost(x) (x)

#define tfHostToBE32(x) htonl(x)
#define tfhostToLE32(x) (x)
#define tfBE32ToHost(x) ntohl(x)
#define tfLE32ToHost(x) (x)

#define tfHostToBE64(x) htonll(x)
#define tfhostToLE64(x) (x)
#define tfBE64ToHost(x) ntohll(x)
#define tfLE64ToHost(x) (x)

#elif BYTE_ORDER == BIG_ENDIAN

/* that would be xbox 360 */
#define tfHostToBE16(x) (x)
#define tfHostToLE16(x) __builtin_bswap16(x)
#define tfBE16ToHost(x) (x)
#define tfLE16ToHost(x) __builtin_bswap16(x)

#define tfHostToBE32(x) (x)
#define tfhostToLE32(x) __builtin_bswap32(x)
#define tfBE32ToHost(x) (x)
#define tfLE32ToHost(x) __builtin_bswap32(x)

#define tfHostToBE64(x) (x)
#define tfhostToLE64(x) __builtin_bswap64(x)
#define tfBE64ToHost(x) (x)
#define tfLE64ToHost(x) __builtin_bswap64(x)

#else

#error byte order not supported

#endif

#define __BYTE_ORDER       BYTE_ORDER
#	define __BIG_ENDIAN    BIG_ENDIAN
#	define __LITTLE_ENDIAN LITTLE_ENDIAN
#	define __PDP_ENDIAN    PDP_ENDIAN


#else
#error unsupported platform
#endif

enum TDataEndianness {
  TF_ENDIANNESS_NATIVE, // encodes the native format
  TF_ENDIANNESS_LE,
  TF_ENDIANNESS_BE,
};





#endif
