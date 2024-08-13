#include "Forge/Formats/ply/TF_ply.h"
#include "Forge/TF_String.h"
#include "Forge/stb/stb_ds.h"
#include "Forge/TF_Endian.h"

enum PlyAttributeType toPlyAttribute(struct TStrSpan input) {
    if (tfStrEqual(input, tfCToStrRef("char"))) {
        return PLY_ATTRIBUTE_CHAR8;
    } else if (tfStrEqual(input, tfCToStrRef("uchar"))) {
        return PLY_ATTRIBUTE_UCHAR8;
    } else if (tfStrEqual(input, tfCToStrRef("short"))) {
        return PLY_ATTRIBUTE_SHORT16;
    } else if (tfStrEqual(input, tfCToStrRef("ushort"))) {
        return PLY_ATTRIBUTE_USHORT16;
    } else if (tfStrEqual(input, tfCToStrRef("int"))) {
        return PLY_ATTRIBUTE_INT32;
    } else if (tfStrEqual(input, tfCToStrRef("uint"))) {
        return PLY_ATTRIBUTE_UINT32;
    } else if (tfStrEqual(input, tfCToStrRef("float"))) {
        return PLY_ATTRIBUTE_FLOAT32;
    } else if (tfStrEqual(input, tfCToStrRef("double"))) {
        return PLY_ATTRIBUTE_FLOAT64;
    }
    return PLY_ATTRIBUTE_UNKNOWN;
}

static inline bool writeAttributeNativeASCII(enum PlyAttributeType attribute, struct TStrSpan inputStr,
                                          void* dest, size_t* pos) {
    size_t size = toPlyAttributeSize(attribute);
    if (isAttributeNatrual(attribute)) {
        long long read = 0;
        if (!tfStrReadll(inputStr, &read))
            return false;
        switch (attribute) {
        case PLY_ATTRIBUTE_CHAR8: {
            int8_t destValue = (int8_t)read;
            memcpy(((uint8_t*)dest) + (*pos), &destValue, sizeof(int8_t));
            (*pos) += sizeof(int8_t);
            return true;
        }
        case PLY_ATTRIBUTE_UCHAR8: {
            uint8_t destValue = (uint8_t)read;
            memcpy(((uint8_t*)dest) + (*pos), &destValue, sizeof(uint8_t));
            (*pos) += sizeof(uint8_t);
            return true;
        }
        case PLY_ATTRIBUTE_SHORT16: {
            int16_t destValue = (int16_t)read;
            memcpy(((uint8_t*)dest) + (*pos), &destValue, sizeof(int16_t));
            (*pos) += sizeof(int16_t);
            return true;
        }
        case PLY_ATTRIBUTE_USHORT16: {
            uint16_t destValue = (uint16_t)read;
            memcpy(((uint8_t*)dest) + (*pos), &destValue, sizeof(uint16_t));
            (*pos) += sizeof(uint16_t);
            return true;
        }
        case PLY_ATTRIBUTE_INT32: {
            int32_t destValue = (int32_t)read;
            memcpy(((uint8_t*)dest) + (*pos), &destValue, sizeof(int32_t));
            (*pos) += sizeof(int32_t);
            return true;
        }
        case PLY_ATTRIBUTE_UINT32: {
            uint32_t destValue = (uint32_t)read;
            memcpy(((uint8_t*)dest) + (*pos), &destValue, sizeof(uint32_t));
            (*pos) += sizeof(uint32_t);
            return true;
        }
        default:
            return false;
        }
    }
    switch (attribute) {
    case PLY_ATTRIBUTE_FLOAT64: {
        double value = 0;
        if (!tfStrReadDouble(inputStr, &value))
            return false;
        memcpy(((uint8_t*)dest) + (*pos), &value, sizeof(double));
        (*pos) += sizeof(double);
        return true;
    }
    case PLY_ATTRIBUTE_FLOAT32: {
        float value = 0;
        if (!tfStrReadFloat(inputStr, &value))
            return false;
        memcpy(((uint8_t*)dest) + (*pos), &value, sizeof(float));
        (*pos) += sizeof(float);
        return true;
    }
    default:
        break;
    }
    return false;
}

void tfFreePlyFileReader(struct TPlyReader* reader) {
    tfFreeScratchAllocator(&reader->mAlloc);
    for(size_t i = 0; i < arrlen(reader->mElements); i++) {
        arrfree(reader->mElements[i].mAttributes);
    }
    arrfree(reader->mElements);
}

size_t tfPlyReadAttribCount(FileStream* stream, struct TPlyReader* reader, size_t cursor, struct TPlyAttribute* attrib, size_t* numElements) {
    if (attrib->attributeListType != PLY_ATTRIBUTE_UNKNOWN) {
        struct TPlyNumber number;
        if(tfPlyDecodeNumber(stream, cursor, reader->mFormat, attrib->attributeListType, &number)) {
            switch(attrib->attributeListType) {
                case PLY_ATTRIBUTE_CHAR8:
                    (*numElements) = number.i8;
                    break;
                case PLY_ATTRIBUTE_UCHAR8:
                    (*numElements) = number.u8;
                    break;
                case PLY_ATTRIBUTE_SHORT16:
                    (*numElements) = number.i16;
                    break;
                case PLY_ATTRIBUTE_USHORT16:
                    (*numElements) = number.u16;
                    break;
                case PLY_ATTRIBUTE_INT32:
                    (*numElements) = number.i32;
                    break;
                case PLY_ATTRIBUTE_UINT32:
                    (*numElements) = number.u32;
                    break;
                case PLY_ATTRIBUTE_FLOAT32:
                    (*numElements) = number.flt;
                    break;
                case PLY_ATTRIBUTE_FLOAT64:
                    (*numElements) = number.dbl;
                    break;
            }
            return toPlyAttributeSize(attrib->attributeListType);
        }
    }
    (*numElements) = 1;
    return 0;
}

bool tfPlySeekElementStream(FileStream* stream, struct TPlyReader* reader, struct TStrSpan name, struct TPlyElement** outElement, size_t* cursor) {
    size_t streamCursor= 0;
    for(size_t i = 0; i < arrlen(reader->mElements); i++) {
        struct TPlyElement* element = &reader->mElements[i]; 
        if(tfStrEqual(element->mName, name)) {
            (*cursor) = streamCursor;
            (*outElement) = element;
            return true;
        }
        for(size_t k = 0; k < element->mNumElements; k++) {
            streamCursor += tfPlyNextElement(stream, reader, streamCursor, element);
        }
    }
    return false;
} 

bool tfPlyDecodeNumber(FileStream* stream, size_t cursor, enum PlyFormatData format, enum PlyAttributeType type, struct TPlyNumber* result) {
    memset(result, 0, sizeof(struct TPlyNumber));
    const size_t expectedAttribSize = toPlyAttributeSize(type);
    ASSERT(expectedAttribSize > 0);
    fsSeekStream(stream, SBO_START_OF_FILE, cursor);
    if (fsReadFromStream(stream, &result->buf, expectedAttribSize)  == expectedAttribSize) {
        switch (type) {
        case PLY_ATTRIBUTE_SHORT16:
        case PLY_ATTRIBUTE_USHORT16:
            switch (format) {
            case PLY_FORMAT_BIG_ENDIAN:
                result->u16 = tfBE16ToHost(result->u16);
            case PLY_FORMAT_LITTLE_ENDIAN:
                result->u16 = tfLE16ToHost(result->u16);
                break;
            default:
                break;
            }
            break;
        case PLY_ATTRIBUTE_INT32:
        case PLY_ATTRIBUTE_UINT32:
        case PLY_ATTRIBUTE_FLOAT32:
            switch (format) {
            case PLY_FORMAT_BIG_ENDIAN:
                result->u32 = tfBE32ToHost(result->u32);
            case PLY_FORMAT_LITTLE_ENDIAN:
                result->u32 = tfLE32ToHost(result->u32);
                break;
            default:
                break;
            }
            break;
        case PLY_ATTRIBUTE_FLOAT64:
            switch (format) {
            case PLY_FORMAT_BIG_ENDIAN:
                result->u64 = tfBE64ToHost(result->u64);
            case PLY_FORMAT_LITTLE_ENDIAN:
                result->u64 = tfLE64ToHost(result->u64);
                break;
            default:
                break;
            }
        default:
        case PLY_ATTRIBUTE_CHAR8:
        case PLY_ATTRIBUTE_UCHAR8:
            break;
        }

        return true;
    }

    return false;
}

bool tfPlyFindAttrib(FileStream* stream, struct TPlyReader* reader, size_t cursor, struct TPlyElement* element, struct TStrSpan attribName, 
                     struct TPlyAttribResult* result) {
    size_t offset = 0;
    for (size_t i = 0; i < arrlen(element->mAttributes); i++) {
        struct TPlyAttribute* attrib = &element->mAttributes[i];
        size_t                numElements = 0;
        offset += tfPlyReadAttribCount(stream, reader, cursor, attrib, &numElements);
        if(tfStrEqual(attrib->mName, attribName)) {
            result->mType = attrib->attributeType;
            result->mNumElement = numElements;
            result->mCursor = cursor + offset;
            result->mStride = toPlyAttributeSize(attrib->attributeType); 
            return true;
        }
        offset += toPlyAttributeSize(attrib->attributeType) * numElements;
    }
    return false;
}


size_t tfPlyNextElement(FileStream* stream, struct TPlyReader* reader, size_t cursor, struct TPlyElement* element) {
    size_t offset = 0;
    for (size_t i = 0; i < arrlen(element->mAttributes); i++) {
        struct TPlyAttribute* attrib = &element->mAttributes[i];
        size_t                numElements = 0;
        offset += tfPlyReadAttribCount(stream, reader, cursor, attrib, &numElements);
        offset += toPlyAttributeSize(attrib->attributeType) * numElements;
    }
    return offset;
}

bool tfAddPlyFileReader(FileStream* stream, struct TPlyReader* plyReader) {
    struct TStr             line = {};
    struct TStreamLineReader reader = {};
    reader.stream = stream;
    struct TFScratchAllocDesc scratchAllocDesc = {};
    scratchAllocDesc.blockSize = 2048;
    tfAddScratchAllocator(&plyReader->mAlloc, &scratchAllocDesc);

    size_t seekPosition = 0;
    seekPosition += fsReadLineFromStream(&reader, &line);
    if (tfStrIndexOf(tfToStrRef(line), tfCToStrRef("ply")) == -1) {
        tfStrFree(&line);
        LOGF(eERROR, "missing `ply` magic number");
        goto error;
    }
    {
        seekPosition += fsReadLineFromStream(&reader, &line);
        struct TFStrSplitIterable lineIterable = { tfStrTrim(tfToStrRef(line)), tfCToStrRef(" "), 0 };
        struct TStrSpan           formatSpan = tfStrSplitIter(&lineIterable);
        if (tfStrIndexOf(formatSpan, tfCToStrRef("format")) == -1) {
            LOGF(eERROR, "expected 'format' line '%.*s'", (int)line.len, line.buf);
            goto error;
        }

        struct TStrSpan typeSpan = tfStrSplitIter(&lineIterable);
        if (tfStrIndexOf(typeSpan, tfCToStrRef("ascii")) >= 0) {
            plyReader->mFormat = PLY_FORMAT_ASCII;
        } else if (tfStrIndexOf(typeSpan, tfCToStrRef("binary_little_endian")) >= 0) {
            plyReader->mFormat = PLY_FORMAT_LITTLE_ENDIAN;
        } else if (tfStrIndexOf(typeSpan, tfCToStrRef("binary_big_endian")) >= 0) {
            plyReader->mFormat = PLY_FORMAT_BIG_ENDIAN;
        } else {
            LOGF(eERROR, "Malformed format type '%.*s'", (int)typeSpan.len, typeSpan.buf);
            goto error;
        }
    }

    enum PlyState {
        PLY_STATE_START,
        PLY_STATE_PROCESS_ELEMENT
    };
    enum PlyState state = PLY_STATE_START;
    while (true) {
        seekPosition += fsReadLineFromStream(&reader, &line);
        if (tfStrEmpty(line)) {
            LOGF(eERROR, "Truncated ply file");
            goto error;
        }
        struct TFStrSplitIterable lineIterable = { tfToStrRef(line), tfCToStrRef(" "), 0 };
        struct TStrSpan           typeSpan = tfStrSplitIter(&lineIterable);
        if (tfStrIndexOf(typeSpan, tfCToStrRef("comment")) >= 0)
            continue;
        if (tfStrIndexOf(typeSpan, tfCToStrRef("end_header")) >= 0) 
            goto finish;

        switch (state) {
        case PLY_STATE_START: {
            if (tfStrIndexOf(typeSpan, tfCToStrRef("element")) >= 0) {
            process_element:;
                struct TStrSpan    elementNameSpan = tfStrTrim(tfStrSplitIter(&lineIterable));
                struct TStrSpan    numElementsSpan = tfStrTrim(tfStrSplitIter(&lineIterable));
                unsigned long long elementCount = 0;
                if (tfStrEmpty(elementNameSpan) || tfStrEmpty(numElementsSpan))
                    goto error;

                if (!tfStrReadull(numElementsSpan, &elementCount))
                    goto error;

                struct TPlyElement element = {};
                element.mNumElements = elementCount;
                element.mName.buf = (char*)tfScratchAlloc(&plyReader->mAlloc, elementNameSpan.len);
                element.mName.len = elementNameSpan.len;
                memcpy(element.mName.buf, elementNameSpan.buf, elementNameSpan.len);
                arrpush(plyReader->mElements, element);

                state = PLY_STATE_PROCESS_ELEMENT;
            } else {
                goto error;
            } 
            break;
        }
        case PLY_STATE_PROCESS_ELEMENT: {
            if (tfStrIndexOf(typeSpan, tfCToStrRef("property")) >= 0) {
                ASSERT(arrlen(plyReader->mElements) >= 1);
                struct TPlyElement* plyElement = &plyReader->mElements[arrlen(plyReader->mElements) - 1];
                struct TPlyAttribute attribute = {};

                struct TStrSpan arg1 = tfStrTrim(tfStrSplitIter(&lineIterable));
                if (tfStrIndexOf(arg1, tfCToStrRef("list")) >= 0) {
                    enum PlyAttributeType attribListType = toPlyAttribute(tfStrTrim(tfStrSplitIter(&lineIterable)));
                    enum PlyAttributeType attribType = toPlyAttribute(tfStrTrim(tfStrSplitIter(&lineIterable)));
                    attribute.attributeListType = attribListType;
                    attribute.attributeType = attribType;
                    if (attribListType == PLY_ATTRIBUTE_UNKNOWN || attribType == PLY_ATTRIBUTE_UNKNOWN)
                        goto error;
                } else {
                    enum PlyAttributeType attribType = toPlyAttribute(arg1);
                    attribute.attributeType = attribType;
                    if (attribType == PLY_ATTRIBUTE_UNKNOWN)
                        goto error;
                }
                struct TStrSpan nameSpan = tfStrTrim(tfStrSplitIter(&lineIterable));
                attribute.mName.buf = (char*)tfScratchAlloc(&plyReader->mAlloc, nameSpan.len);
                attribute.mName.len = nameSpan.len;
                memcpy(attribute.mName.buf, nameSpan.buf, nameSpan.len);
                arrpush(plyElement->mAttributes, attribute);
            } else if (tfStrIndexOf(typeSpan, tfCToStrRef("element")) >= 0) {
                goto process_element;
            } else {
                LOGF(eERROR, "Invalid Type '%.*s'", (int)typeSpan.len, typeSpan.buf);
                goto error;
            }
            break;
        }
        default:
            break;
        }
    }

finish:
    // for asscii we need to convert it to raw data
    if (plyReader->mFormat == PLY_FORMAT_ASCII) {
        size_t bufferSize = 2048;
        size_t bufferPos = 0;
        void*  buf = tf_malloc(2048);
        for (size_t grpIdx = 0; grpIdx < arrlen(plyReader->mElements); grpIdx++) {
            struct TPlyElement* plyElement = &plyReader->mElements[grpIdx];
            for (size_t eleIdx = 0; eleIdx < plyElement->mNumElements; eleIdx++) {
                fsReadLineFromStream(&reader, &line);
                if (tfStrEmpty(line)) {
                    tf_free(buf);
                    goto error;
                }
                struct TFStrSplitIterable lineIterable = { tfToStrRef(line), tfCToStrRef(" "), 0 };
                for (size_t attrIdx = 0; attrIdx < arrlen(plyElement->mAttributes); attrIdx++) {
                    struct TPlyAttribute* attr = &plyElement->mAttributes[attrIdx];
                    const size_t          attribSize = toPlyAttributeSize((enum PlyAttributeType)attr->attributeType);
                    const size_t          listAttribSize = toPlyAttributeSize(attr->attributeListType);

                    if (attr->attributeListType != PLY_ATTRIBUTE_UNKNOWN) {
                        struct TStrSpan lenSpan = tfStrTrim(tfStrSplitIter(&lineIterable));
                        unsigned long long len = 0;
                        if (!tfStrReadull(lenSpan, &len)) {
                            tf_free(buf);
                            goto error;
                        }
                        const size_t elementSize = (attribSize * len) + listAttribSize;
                        while (elementSize + bufferPos > bufferSize) {
                            bufferSize = bufferSize + (bufferSize / 2);
                            buf = tf_realloc(buf, bufferSize);
                        }
                        if (!writeAttributeNativeASCII(attr->attributeListType, lenSpan, buf, &bufferPos)) {
                            tf_free(buf);
                            goto error;
                        }
                        for (size_t i = 0; i < len; i++) {
                            struct TStrSpan valSpan = tfStrTrim(tfStrSplitIter(&lineIterable));
                            if (!writeAttributeNativeASCII(attr->attributeType, valSpan, buf, &bufferPos)) {
                                tf_free(buf);
                                goto error;
                            }
                        }
                    } else {
                        while (attribSize + bufferPos > bufferSize) {
                            bufferSize = bufferSize + (bufferSize / 2);
                            buf = tf_realloc(buf, bufferSize);
                        }
                        struct TStrSpan valSpan = tfStrTrim(tfStrSplitIter(&lineIterable));
                        if (!writeAttributeNativeASCII(attr->attributeType, valSpan, buf, &bufferPos)) {
                            tf_free(buf);
                            goto error;
                        }
                    }
                }
            }
        }
        fsCloseStream(stream);
        fsOpenStreamFromMemory(buf, bufferSize, FM_READ_WRITE_APPEND_ALLOW_READ, true, stream);
    } else {
        fsSeekStream(stream, SBO_START_OF_FILE, seekPosition);
        fsStreamWrapMemoryMap(stream);
    }

    //plyReader->mDataSeekPosition = seekPosition;
    tfStrFree(&line);
    return true;
error:
    LOGF(eERROR, "Malformed line '%.*s'", (int)line.len, line.buf);
    tfStrFree(&line);
    return false;
}
