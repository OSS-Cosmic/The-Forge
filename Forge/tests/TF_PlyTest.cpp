#include "TF_TestMain.h"

#include "Forge/TF_Types.h"
#include "Forge/stb/stb_ds.h"
#include "Forge/Formats/TF_ply.h"
#include "utest.h"

#include "Forge/TF_FileSystem.h"

UTEST(Formats, PlyTest_0)
{
  const char* ply_ascii ="ply\n\
    format ascii 1.0\n\
    comment single tetrahedron with colored faces\n\
    element vertex 4\n\
    comment tetrahedron vertices\n\
    property float x\n\
    property float y\n\
    property float z\n\
    element face 4\n\
    property list uchar int vertex_indices\n\
    property uchar red\n\
    property uchar green\n\
    property uchar blue\n\
    end_header\n\
    0 0 0\n\
    0 1 1\n\
    1 0 1\n\
    1 1 0\n\
    3 0 1 2 255 255 255\n\
    3 0 2 3 255 0 0\n\
    3 0 1 3 0 255 0\n\
    3 1 2 3 0 0 255\n";

}


#include "Forge/Mem/TF_Memory.h"
#include "Forge/TF_Log.h"
UTEST_STATE();
TF_UTEST_MAIN("TF_PlyTest")



