#ifndef TF_FORMATS_PLY_H_INCLUDED
#define TF_FORMATS_PLY_H_INCLUDED

#include "Forge/Mem/TF_Allocators.h"
#include "Forge/TF_FileSystem.h"
#include "Forge/TF_String.h"

enum PlyFormatData {
  PLY_FORMAT_ASCII,
  PLY_FORMAT_LITTLE_ENDIAN,
  PLY_FORMAT_BIG_ENDIAN 
};

enum PlyAttributeType {
  PLY_ATTRIBUTE_CHAR8,
  PLY_ATTRIBUTE_UCHAR8,
  PLY_ATTRIBUTE_SHORT16,
  PLY_ATTRIBUTE_USHORT16,
  PLY_ATTRIBUTE_INT32,
  PLY_ATTRIBUTE_UINT32,
  PLY_ATTRIBUTE_FLOAT32,
  PLY_ATTRIBUTE_FLOAT64,
};



struct PlyAttribute {
  uint32_t attributeType: 3;
  uint32_t listType: 3;
  uint32_t isList: 1;
  struct TStrSpan name;
};

struct PlyElement {
  uint32_t mNumAttributes;
  struct PlyAttribute* mAttributes;
  uint32_t mNumElements;
  void* mInput;
};

struct TPlyFile {
  struct TFScratchAllocator mAlloc; // temporary scratch allocator for the lifetime of the configuration
  enum PlyFormatData format;

};

#ifdef __cplusplus
extern "C"
{
#endif

void tfCreatePlyFileReader(FileStream* stream, struct TPlyFile* outFile);

#ifdef __cplusplus
}
#endif

#endif


