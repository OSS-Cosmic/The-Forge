#include "Common_3/Application/Config.h"
#include "Forge/Core/TF_String.h"
#include "Forge/Graphics/TF_GPUConfig.h"
#include "utest.h"

UTEST(GPUConfig, loadData_0)
{
  struct GPUConfiguration def = {0};
  tfInitGPUConfiguration(&def);

  bool res = tfLoadGPUData(&def, tfToRef(
    "version:0.1"
  ));
  EXPECT_EQ(res, false); 
  tfFreeGPUConfiguration(&def);
}

UTEST(GPUConfig, loadData_1)
{
  struct GPUConfiguration def = {0};
  tfInitGPUConfiguration(&def);

  bool res = tfLoadGPUData(&def, tfToRef(
    "version:0.2\r\n"
    "BEGIN_VENDOR_LIST;\r\n"
    "intel; 0x8086, 0x1004;\r\n"
    "amd; 0x1002;\r\n"
    "nvidia; 0x10de;\r\n"
    "qualcomm; 0x5143;\r\n"
    "END_VENDOR_LIST;\r\n"
  ));
  EXPECT_TRUE(res); 
  EXPECT_EQ(def.mVendorCount,4); 
  EXPECT_TRUE(tfStrEqual(def.mVendorDefinitions[0].mVendorName, tfToRef("intel")));
  EXPECT_TRUE(tfStrEqual(def.mVendorDefinitions[1].mVendorName, tfToRef("amd")));
  EXPECT_TRUE(tfStrEqual(def.mVendorDefinitions[2].mVendorName, tfToRef("nvidia")));
  EXPECT_TRUE(tfStrEqual(def.mVendorDefinitions[3].mVendorName, tfToRef("qualcomm")));

  EXPECT_EQ(def.mVendorDefinitions[0].mIdentifierCount, 2);
  EXPECT_EQ(def.mVendorDefinitions[0].mIdentifierArray[0], 0x8086);
  EXPECT_EQ(def.mVendorDefinitions[0].mIdentifierArray[1], 0x1004);

  EXPECT_EQ(def.mVendorDefinitions[1].mIdentifierCount, 1);
  EXPECT_EQ(def.mVendorDefinitions[1].mIdentifierArray[0], 0x1002);
  
  EXPECT_EQ(def.mVendorDefinitions[2].mIdentifierCount, 1);
  EXPECT_EQ(def.mVendorDefinitions[2].mIdentifierArray[0], 0x10de);
  
  EXPECT_EQ(def.mVendorDefinitions[3].mIdentifierCount, 1);
  EXPECT_EQ(def.mVendorDefinitions[3].mIdentifierArray[0], 0x5143);

  tfFreeGPUConfiguration(&def);
}




#include "Common_3/Utilities/Interfaces/IFileSystem.h"
#include "Common_3/Utilities/Interfaces/IMemory.h"
UTEST_STATE();
int main(int argc, const char* const argv[])
{
    if (!initMemAlloc("TF_StringTest"))
        return EXIT_FAILURE;

    FileSystemInitDesc fsDesc = {};
    fsDesc.pAppName = "TF_StringTest";

    if (!initFileSystem(&fsDesc))
        return EXIT_FAILURE;

    fsSetPathForResourceDir(pSystemFileIO, RM_DEBUG, RD_LOG, "");

    int res = utest_main(argc, argv);
    exitMemAlloc();
    return res;
}


