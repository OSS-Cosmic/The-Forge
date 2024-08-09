#include "Forge/Formats/TF_ply.h"
#include "Forge/TF_String.h"

void tfCreatePlyFileReader(FileStream* stream, struct TPlyFile* outFile) {
    struct TStr             line = { 0 };
    struct StreamLineReader reader = {};
    reader.stream = stream;
    if (fsReadLineFromStream(&reader, &line) == 0)
        return;
    if (tfStrIndexOf(tfToStrRef(line), tfCToStrRef("ply")) == -1)
        return;

    if (fsReadLineFromStream(&reader, &line) == 0)
        return;
    struct TFStrSplitIterable lineIterable = { tfToStrRef(line), tfCToStrRef(" "), 0 };
    struct TStrSpan           t0 = tfStrSplitIter(&lineIterable);
    if (tfStrIndexOf(t0, tfCToStrRef("format")) >= 0) {
        struct TStrSpan typeSpan = tfStrSplitIter(&lineIterable);
        if (tfStrIndexOf(typeSpan, tfCToStrRef("ascii")) >= 0) {
            outFile->format = PLY_FORMAT_ASCII;
        } else if (tfStrIndexOf(typeSpan, tfCToStrRef("binary_little_endian")) >= 0) {
            outFile->format = PLY_FORMAT_LITTLE_ENDIAN;
        } else if (tfStrIndexOf(typeSpan, tfCToStrRef("binary_big_endian")) >= 0) {
            outFile->format = PLY_FORMAT_BIG_ENDIAN;
        } else {
            return;
        }
    }

}
