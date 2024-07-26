#define TF_RAND_MAX     0x7FFFFFFF
#define TF_INITIAL_SEED 0x9747b28c

#include "Forge/Math/MurmurHash3_32.h"
#include "Forge/TF_Types.h"

inline int32_t tfRandomInt(void)
{
    static uint32_t       seed = TF_INITIAL_SEED;
    static const uint32_t messageHash[] = {
        0x8C2100D0, 0xEC843F56, 0xDD467E25, 0xC22461F6, 0xA1368AB0, 0xBBDA7B12, 0xA175F888, 0x6BD9BDA2,
        0x999AC54C, 0x7C043DD3, 0xD502088F, 0x1B5B4D72, 0x94BB5742, 0x2CDA891E, 0x88613640, 0x31A50479
    };

    int32_t result;
    MurmurHash3_x86_32(&messageHash, TF_ARRAY_COUNT(messageHash) * sizeof(uint32_t), seed--, &result);
    return abs(result);
}
