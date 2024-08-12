#include "TF_TestMain.h"

#include "Forge/TF_Types.h"
#include "Forge/stb/stb_ds.h"
#include "Forge/Formats/ply/TF_ply.h"
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

  FileStream stream = {};
  TPlyReader reader = {};
  fsOpenStreamFromMemory(ply_ascii, strlen(ply_ascii), FM_READ, false, &stream);
  EXPECT_TRUE(tfAddPlyFileReader(&stream, &reader));

  EXPECT_EQ(arrlen(reader.mElements), 2);
  EXPECT_EQ(reader.mElements[0].mNumElements, 4);
  EXPECT_EQ(arrlen(reader.mElements[0].mAttributes), 3);
  EXPECT_EQ(reader.mElements[0].mAttributes[0].attributeType, PLY_ATTRIBUTE_FLOAT32);
  EXPECT_EQ(reader.mElements[0].mAttributes[1].attributeType, PLY_ATTRIBUTE_FLOAT32);
  EXPECT_EQ(reader.mElements[0].mAttributes[2].attributeType, PLY_ATTRIBUTE_FLOAT32);

  EXPECT_EQ(reader.mElements[1].mNumElements, 4);
  EXPECT_EQ(arrlen(reader.mElements[1].mAttributes), 4);
  EXPECT_EQ(reader.mElements[1].mAttributes[0].attributeType, PLY_ATTRIBUTE_INT32);
  EXPECT_EQ(reader.mElements[1].mAttributes[1].attributeType, PLY_ATTRIBUTE_UCHAR8);
  EXPECT_EQ(reader.mElements[1].mAttributes[2].attributeType, PLY_ATTRIBUTE_UCHAR8);


  size_t cursor = 0;
  struct TPlyNumber number;
  struct TPlyAttribResult findAttrib;
  struct TPlyElement* element;
  EXPECT_TRUE(tfPlySeekElementStream(&stream, &reader, tfCToStrRef("vertex"), &element, &cursor));

  EXPECT_TRUE(tfPlyFindAttrib(&stream, &reader, cursor, &reader.mElements[0], tfCToStrRef("x"), &findAttrib));
  EXPECT_TRUE(tfPlyDecodeNumber(&stream, findAttrib.mCursor, reader.mFormat, findAttrib.mType, &number));
  EXPECT_NEAR(number.flt, 0.0f, 0.0001f);

  EXPECT_TRUE(tfPlyFindAttrib(&stream, &reader, cursor, &reader.mElements[0], tfCToStrRef("y"), &findAttrib));
  EXPECT_TRUE(tfPlyDecodeNumber(&stream, findAttrib.mCursor, reader.mFormat, findAttrib.mType, &number));
  EXPECT_NEAR(number.flt, 0.0f, 0.0001f);

  EXPECT_TRUE(tfPlyFindAttrib(&stream, &reader, cursor, &reader.mElements[0], tfCToStrRef("z"), &findAttrib));
  EXPECT_TRUE(tfPlyDecodeNumber(&stream, findAttrib.mCursor, reader.mFormat, findAttrib.mType, &number));
  EXPECT_NEAR(number.flt, 0.0f, 0.0001f);

  cursor += tfPlyNextElement(&stream, &reader, cursor, &reader.mElements[0]);

  EXPECT_TRUE(tfPlyFindAttrib(&stream, &reader, cursor, &reader.mElements[0], tfCToStrRef("x"), &findAttrib));
  EXPECT_TRUE(tfPlyDecodeNumber(&stream, findAttrib.mCursor, reader.mFormat, findAttrib.mType, &number));
  EXPECT_NEAR(number.flt, 0.0f, 0.0001f);

  EXPECT_TRUE(tfPlyFindAttrib(&stream, &reader, cursor, &reader.mElements[0], tfCToStrRef("y"), &findAttrib));
  EXPECT_TRUE(tfPlyDecodeNumber(&stream, findAttrib.mCursor, reader.mFormat, findAttrib.mType, &number));
  EXPECT_NEAR(number.flt, 1.0f, 0.0001f);

  EXPECT_TRUE(tfPlyFindAttrib(&stream, &reader, cursor, &reader.mElements[0], tfCToStrRef("z"), &findAttrib));
  EXPECT_TRUE(tfPlyDecodeNumber(&stream, findAttrib.mCursor, reader.mFormat, findAttrib.mType, &number));
  EXPECT_NEAR(number.flt, 1.0f, 0.0001f);

  cursor += tfPlyNextElement(&stream, &reader, cursor, &reader.mElements[0]);

  EXPECT_TRUE(tfPlyFindAttrib(&stream, &reader, cursor, &reader.mElements[0], tfCToStrRef("x"), &findAttrib));
  EXPECT_TRUE(tfPlyDecodeNumber(&stream, findAttrib.mCursor, reader.mFormat, findAttrib.mType, &number));
  EXPECT_NEAR(number.flt, 1.0f, 0.0001f);

  EXPECT_TRUE(tfPlyFindAttrib(&stream, &reader, cursor, &reader.mElements[0], tfCToStrRef("y"), &findAttrib));
  EXPECT_TRUE(tfPlyDecodeNumber(&stream, findAttrib.mCursor, reader.mFormat, findAttrib.mType, &number));
  EXPECT_NEAR(number.flt, 0.0f, 0.0001f);

  EXPECT_TRUE(tfPlyFindAttrib(&stream, &reader, cursor, &reader.mElements[0], tfCToStrRef("z"), &findAttrib));
  EXPECT_TRUE(tfPlyDecodeNumber(&stream, findAttrib.mCursor, reader.mFormat, findAttrib.mType, &number));
  EXPECT_NEAR(number.flt, 1.0f, 0.0001f);
 
  EXPECT_TRUE(tfPlySeekElementStream(&stream, &reader, tfCToStrRef("face"), &element, &cursor));
  EXPECT_TRUE(tfPlyFindAttrib(&stream, &reader, cursor, &reader.mElements[0], tfCToStrRef("vertex_indices"), &findAttrib));


  fsCloseStream(&stream);
  tfFreePlyFileReader(&reader);

}


#include "Forge/Mem/TF_Memory.h"
#include "Forge/TF_Log.h"
UTEST_STATE();
TF_UTEST_MAIN("TF_PlyTest")



