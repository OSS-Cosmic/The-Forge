#include "Forge/Formats/TF_gltf.h"
#include "Forge/Mem/TF_Memory.h"

#define CGLTF_MALLOC tf_malloc
#define CGLTF_FREE tf_free 

#define CGLTF_IMPLEMENTATION
#include "cgltf/cgltf.h"




