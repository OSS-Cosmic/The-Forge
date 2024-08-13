#ifndef TF_FORMATS_PLY_H_INCLUDED
#define TF_FORMATS_PLY_H_INCLUDED

#include "Forge/Mem/TF_Allocators.h"
#include "Forge/TF_FileSystem.h"
#include "Forge/TF_String.h"
#include "Forge/Math/TF_FastHash.h"

enum PlyFormatData {
  PLY_FORMAT_ASCII,
  PLY_FORMAT_LITTLE_ENDIAN,
  PLY_FORMAT_BIG_ENDIAN 
};

enum PlyAttributeType {
  PLY_ATTRIBUTE_UNKNOWN,
  PLY_ATTRIBUTE_CHAR8,
  PLY_ATTRIBUTE_UCHAR8,
  PLY_ATTRIBUTE_SHORT16,
  PLY_ATTRIBUTE_USHORT16,
  PLY_ATTRIBUTE_INT32,
  PLY_ATTRIBUTE_UINT32,
  PLY_ATTRIBUTE_FLOAT32,
  PLY_ATTRIBUTE_FLOAT64
};


struct TPlyAttribute {
  uint32_t mAttributeType;
  uint32_t mAttributeListType;
  uint32_t mRefHash;
  struct TStrSpan mName;
};

struct TPlyElement {
  uint32_t mNumElements;
  struct TStrSpan mName;
  struct TPlyAttribute* mAttributes;
};

struct TPlyReader {
  struct TFScratchAllocator mAlloc; // temporary scratch allocator for the lifetime of the configuration
  enum PlyFormatData mFormat;
  struct TPlyElement* mElements;

  size_t mDataSeekPosition;
};


struct TPlyAttribResult {
  size_t mCursor; // offset into element
  size_t mStride;
  size_t mNumElement;
  enum PlyAttributeType mType;
};

struct TPlyNumber {
    union {
        uint8_t  u8;
        int8_t   i8;
        uint16_t u16;
        int16_t  i16;
        int32_t  i32;
        uint32_t u32;
        uint32_t u64;

        float  flt;
        double dbl;

        uint8_t buf[8];
    };
};


#ifdef __cplusplus
extern "C"
{
#endif

bool tfAddPlyFileReader(FileStream* stream, struct TPlyReader* reader);
bool tfPlySeekElementStream(FileStream* stream, struct TPlyReader* reader, struct TStrSpan name, struct TPlyElement** outElement,
                             size_t* cursor);

size_t tfPlyReadAttribCount(FileStream* stream, struct TPlyReader* reader, size_t cursor, struct TPlyAttribute* attrib,
                            size_t* numElements);
size_t tfPlyNextElement(FileStream* stream, struct TPlyReader* reader, size_t elementCursor, struct TPlyElement* element);
bool   tfPlyFindAttrib(FileStream* stream, struct TPlyReader* reader, size_t elementCursor, struct TPlyElement* element,
                       struct TStrSpan attribName, struct TPlyAttribResult* result);
bool   tfPlyFindAttribRef(FileStream* stream, struct TPlyReader* reader, size_t elementCursor, struct TPlyElement* element,
                       hash32_t attribName, struct TPlyAttribResult* result);

bool tfPlyDecodeNumber(FileStream* stream, size_t cursor, enum PlyFormatData format, enum PlyAttributeType type, struct TPlyNumber* result);

void tfFreePlyFileReader(struct TPlyReader* reader);

enum PlyAttributeType toPlyAttribute(struct TStrSpan input);
static inline size_t toPlyAttributeSize(enum PlyAttributeType attribute) {
    switch (attribute) {
    case PLY_ATTRIBUTE_CHAR8:
    case PLY_ATTRIBUTE_UCHAR8:
        return 1;
    case PLY_ATTRIBUTE_SHORT16:
    case PLY_ATTRIBUTE_USHORT16:
        return 2;
    case PLY_ATTRIBUTE_INT32:
    case PLY_ATTRIBUTE_UINT32:
    case PLY_ATTRIBUTE_FLOAT32:
        return 4;
    case PLY_ATTRIBUTE_FLOAT64:
        return 8;
    default:
        break;
    }
    return 0;
}
static inline bool isAttributeNatrual(enum PlyAttributeType attribute) {
    switch (attribute) {
    case PLY_ATTRIBUTE_CHAR8:
    case PLY_ATTRIBUTE_UCHAR8:
    case PLY_ATTRIBUTE_SHORT16:
    case PLY_ATTRIBUTE_USHORT16:
    case PLY_ATTRIBUTE_INT32:
    case PLY_ATTRIBUTE_UINT32:
        return true;
    case PLY_ATTRIBUTE_FLOAT32:
    case PLY_ATTRIBUTE_FLOAT64:
    default:
        break;
    }
    return false;
}


#ifdef __cplusplus
}
#endif

#endif


