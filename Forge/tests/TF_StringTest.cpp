#include "TF_TestMain.h"
#include "Forge/Config.h"
#include "Forge/TF_String.h"
#include "utest.h"

UTEST(Core, tfCaselessCompare)
{
    EXPECT_EQ(tfStrCaselessCompare(tfCToStrRef("test"), tfCToStrRef("TEST")), 0);
    EXPECT_EQ(tfStrCaselessCompare(tfCToStrRef("testAA"), tfCToStrRef("TEST")), 1);
}

UTEST(Core, tfCompare)
{
    EXPECT_EQ(tfStrCompare(tfCToStrRef("test"), tfCToStrRef("TEST")), 32);
    EXPECT_EQ(tfStrCompare(tfCToStrRef("Test"), tfCToStrRef("test")), -32);
}

UTEST(Core, tfIndexOf)
{
    EXPECT_EQ(tfStrIndexOf(tfCToStrRef("foo foo"), tfCToStrRef("foo")), 0);
    EXPECT_EQ(tfStrIndexOf(tfCToStrRef("banana"), tfCToStrRef("ana")), 1);
    EXPECT_EQ(tfStrIndexOf(tfCToStrRef("textbook"), tfCToStrRef("book")), 4);
    EXPECT_EQ(tfStrIndexOf(tfCToStrRef("abababcabababcbab"), tfCToStrRef("ababc")), 2);
    EXPECT_EQ(tfStrIndexOf(tfCToStrRef("This is a test string to see how Boyer-Moore handles longer searches"), tfCToStrRef("searches")), 60);
    EXPECT_EQ(tfStrIndexOf(tfCToStrRef("hello world"), tfCToStrRef("hello")), 0);
    EXPECT_EQ(tfStrIndexOf(tfCToStrRef("apple banana"), tfCToStrRef("nana")), 8);
    EXPECT_EQ(tfStrIndexOf(tfCToStrRef("goodbye"), tfCToStrRef("bye")), 4);
    EXPECT_EQ(tfStrIndexOf(tfCToStrRef("cat"), tfCToStrRef("dog")), -1);
    EXPECT_EQ(tfStrIndexOf(tfCToStrRef(""), tfCToStrRef("abc")), -1);
    EXPECT_EQ(tfStrIndexOf(tfCToStrRef("hello"), tfCToStrRef("")), -1);
    EXPECT_EQ(tfStrIndexOf(tfCToStrRef("abc"), tfCToStrRef("abcd")), -1);
}

UTEST(Core, tfLastIndexOf)
{
    EXPECT_EQ(tfStrLastIndexOf(tfCToStrRef("foo foo"), tfCToStrRef(" ")), 3);
    EXPECT_EQ(tfStrLastIndexOf(tfCToStrRef("foo foo"), tfCToStrRef("foo")), 4);
    EXPECT_EQ(tfStrLastIndexOf(tfCToStrRef("banana"), tfCToStrRef("ana")), 3);
    EXPECT_EQ(tfStrLastIndexOf(tfCToStrRef("textbook"), tfCToStrRef("book")), 4);
    EXPECT_EQ(tfStrLastIndexOf(tfCToStrRef("abababcabababcbab"), tfCToStrRef("ababc")), 9);
    EXPECT_EQ(tfStrLastIndexOf(tfCToStrRef("This is a test string to see how Boyer-Moore handles longer searches"), tfCToStrRef("searches")), 60);
    EXPECT_EQ(tfStrLastIndexOf(tfCToStrRef("hello world"), tfCToStrRef("hello")), 0);
    EXPECT_EQ(tfStrLastIndexOf(tfCToStrRef("apple banana"), tfCToStrRef("nana")), 8);
    EXPECT_EQ(tfStrLastIndexOf(tfCToStrRef("goodbye"), tfCToStrRef("bye")), 4);
    EXPECT_EQ(tfStrLastIndexOf(tfCToStrRef("cat"), tfCToStrRef("dog")), -1);
    EXPECT_EQ(tfStrLastIndexOf(tfCToStrRef(""), tfCToStrRef("abc")), -1);
    EXPECT_EQ(tfStrLastIndexOf(tfCToStrRef("hello"), tfCToStrRef("")), -1);
    EXPECT_EQ(tfStrLastIndexOf(tfCToStrRef("abc"), tfCToStrRef("abcd")), -1);
}

UTEST(Core, tfEq)
{
    EXPECT_EQ(tfStrEqual(tfCToStrRef("Hello world"), tfCToStrRef("Hello world")), 1);
    EXPECT_EQ(tfStrEqual(tfCToStrRef("Helloworld"), tfCToStrRef("Hello world")), 0);
    EXPECT_EQ(tfStrEqual(tfCToStrRef("Hello World"), tfCToStrRef("Hello world")), 0);
    EXPECT_EQ(tfStrEqual(tfCToStrRef("Hello"), tfCToStrRef("Hello ")), 0);
}

UTEST(Core, tfDuplicate)
{
    struct TStr s1 = { 0 };
    EXPECT_EQ(tfStrAssign(&s1, tfCToStrRef("Hello World")), true);
    struct TStr s2 = tfStrDup(&s1);
    EXPECT_NE(s1.buf, s2.buf);
    tfStrFree(&s1);
    tfStrFree(&s2);
}

UTEST(Core, tfIterateRev)
{
    struct TStrSpan           buf = tfCToStrRef("one two three four five");
    struct TFStrSplitIterable iterable = { buf, tfCToStrRef(" "), buf.len };
    struct TStrSpan           s = { 0 };
    s = tfStrSplitRevIter(&iterable);
    EXPECT_EQ(tfStrEmpty(s), 0);
    EXPECT_EQ(tfStrEqual(tfCToStrRef("five"), s), 1);
    s = tfStrSplitRevIter(&iterable);
    EXPECT_EQ(tfStrEmpty(s), 0);
    EXPECT_EQ(tfStrEqual(tfCToStrRef("four"), s), 1);
    s = tfStrSplitRevIter(&iterable);
    EXPECT_EQ(tfStrEmpty(s), 0);
    EXPECT_EQ(tfStrEqual(tfCToStrRef("three"), s), 1);
    s = tfStrSplitRevIter(&iterable);
    EXPECT_EQ(tfStrEmpty(s), 0);
    EXPECT_EQ(tfStrEqual(tfCToStrRef("two"), s), 1);
    s = tfStrSplitRevIter(&iterable);
    EXPECT_EQ(tfStrEmpty(s), 0);
    EXPECT_EQ(tfStrEqual(tfCToStrRef("one"), s), 1);
    s = tfStrSplitRevIter(&iterable);
    EXPECT_EQ(tfStrEmpty(s), 1);
}

UTEST(Core, tfReadull)
{
    unsigned long long res = 0;
    EXPECT_EQ(tfStrReadull(tfCToStrRef("123456"), &res), 1);
    EXPECT_EQ(res, 123456);
}

UTEST(Core, tfReadu32)
{
    long long res = 0;
    EXPECT_EQ(tfStrReadll(tfCToStrRef("123456"), &res), 1);
    EXPECT_EQ(res, 123456);
}

UTEST(Core, tfIterateWhiteSpace)
{
    struct TFStrSplitIterable iterable = { tfCToStrRef("one  two"), tfCToStrRef(" "), 0 };
    struct TStrSpan           s = { 0 };

    s = tfStrSplitIter(&iterable);
    EXPECT_EQ(tfStrEmpty(s), 0);
    EXPECT_EQ(tfStrEqual(tfCToStrRef("one"), s), 1);

    s = tfStrSplitIter(&iterable);
    EXPECT_EQ(tfStrEmpty(s), 1);

    s = tfStrSplitIter(&iterable);
    EXPECT_EQ(tfStrEqual(tfCToStrRef("two"), s), 1);

    s = tfStrSplitIter(&iterable);
    EXPECT_EQ(tfStrEmpty(s), 1);
}

UTEST(Core, tfIterateCount)
{
    {
        struct TFStrSplitIterable iterable = { tfCToStrRef("one two three four five"), tfCToStrRef(" "), 0 };
        struct TStrSpan           slices[] = {
            tfCToStrRef("one"), tfCToStrRef("two"), tfCToStrRef("three"), tfCToStrRef("four"), tfCToStrRef("five"),
        };
        size_t i = 0;
        while (iterable.cursor < iterable.buffer.len)
        {
            struct TStrSpan it = tfStrSplitIter(&iterable);
            EXPECT_EQ(tfStrEqual(slices[i++], it), 1);
        }
    }
    {
        struct TFStrSplitIterable iterable = { tfCToStrRef("one   two"), tfCToStrRef(" "), 0 };
        struct TStrSpan           slices[] = {
            tfCToStrRef("one"),
            tfCToStrRef(""),
            tfCToStrRef(""),
            tfCToStrRef("two"),
        };
        size_t i = 0;
        while (iterable.cursor < iterable.buffer.len)
        {
            struct TStrSpan it = tfStrSplitIter(&iterable);
            EXPECT_EQ(tfStrEqual(slices[i++], it), 1);
        }
    }
}

UTEST(Core, tfIterate)
{
    struct TFStrSplitIterable iterable = { tfCToStrRef("one two three four five"), tfCToStrRef(" "),  0 };

    struct TStrSpan s = { 0 };
    s = tfStrSplitIter(&iterable);
    EXPECT_EQ(tfStrEmpty(s), 0);
    EXPECT_EQ(tfStrEqual(tfCToStrRef("one"), s), 1);
    s = tfStrSplitIter(&iterable);
    EXPECT_EQ(tfStrEmpty(s), 0);
    EXPECT_EQ(tfStrEqual(tfCToStrRef("two"), s), 1);
    s = tfStrSplitIter(&iterable);
    EXPECT_EQ(tfStrEmpty(s), 0);
    EXPECT_EQ(tfStrEqual(tfCToStrRef("three"), s), 1);
    s = tfStrSplitIter(&iterable);
    EXPECT_EQ(tfStrEmpty(s), 0);
    EXPECT_EQ(tfStrEqual(tfCToStrRef("four"), s), 1);
    s = tfStrSplitIter(&iterable);
    EXPECT_EQ(tfStrEmpty(s), 0);
    EXPECT_EQ(tfStrEqual(tfCToStrRef("five"), s), 1);
    s = tfStrSplitIter(&iterable);
    EXPECT_EQ(tfStrEmpty(s), 1);
}

UTEST(Core, tffmtWriteLongLong)
{
    char   test_buffer[TFSTR_LLSTR_SIZE];
    size_t len = tfstrfmtll(TStrSpan{  test_buffer, TFSTR_LLSTR_SIZE }, 12481);
    EXPECT_EQ(len, 5);
    EXPECT_EQ(tfStrEqual(tfCToStrRef("12481"), TStrSpan{ test_buffer, len }), true);
}

UTEST(Core, tfCaselessEq)
{
    EXPECT_EQ(tfStrCaselessEqual(tfCToStrRef("Hello world"), tfCToStrRef("Hello world")), 1);
    EXPECT_EQ(tfStrCaselessEqual(tfCToStrRef("Helloworld"), tfCToStrRef("Hello world")), 0);
    EXPECT_EQ(tfStrCaselessEqual(tfCToStrRef("Hello World"), tfCToStrRef("Hello world")), 1);
    EXPECT_EQ(tfStrCaselessEqual(tfCToStrRef("Hello"), tfCToStrRef("Hello ")), 0);
}

UTEST(Core, tfCatJoin)
{
    struct TStr     buf = { 0 };
    struct TStrSpan slices[] = {
        tfCToStrRef("one"),
        tfCToStrRef("two"),
        tfCToStrRef("three"),
        tfCToStrRef("four"),
    };
    EXPECT_EQ(tfstrcatjoin(&buf, slices, 4, tfCToStrRef(" ")), true);
    EXPECT_EQ(tfStrEqual(tfToStrRef(buf), tfCToStrRef("one two three four")), true);
    tfStrFree(&buf);
}

UTEST(Core, tfCatJoinCstr)
{
    struct TStr buf = { 0 };
    const char* slices[] = {
        "one",
        "two",
        "three",
        "four",
    };
    EXPECT_EQ(tfstrcatjoinCStr(&buf, slices, 4, tfCToStrRef(" ")), true);
    EXPECT_EQ(tfStrEqual(tfToStrRef(buf), tfCToStrRef("one two three four")), true);
    tfStrFree(&buf);
}

UTEST(Core, appendSlice)
{
    struct TStr buf = { 0 };
    tfStrAssign(&buf, tfCToStrRef("Hello"));
    EXPECT_EQ(tfStrAppendSlice(&buf, tfCToStrRef(" world")), true);
    EXPECT_EQ(tfStrEqual(tfToStrRef(buf), tfCToStrRef("Hello world")), true);
    tfStrFree(&buf);
}

UTEST(Core, tfcatprintf)
{
    struct TStr buf = { 0 };
    EXPECT_EQ(tfstrcatprintf(&buf, "Hello %s", "world"), true);
    EXPECT_EQ(tfStrEqual(tfToStrRef(buf), tfCToStrRef("Hello world")), true);

    tfStrSetLen(&buf, 0);
    EXPECT_EQ(tfstrcatprintf(&buf, "%d", 123), true);
    EXPECT_EQ(tfStrEqual(tfToStrRef(buf), tfCToStrRef("123")), true);

    EXPECT_EQ(tfstrcatprintf(&buf, " %lu", 156), true);
    EXPECT_EQ(tfStrEqual(tfToStrRef(buf), tfCToStrRef("123 156")), true);

    tfStrSetLen(&buf, 0);
    EXPECT_EQ(tfstrcatprintf(&buf, "a%cb", 0), true);
    EXPECT_EQ(tfStrEqual(tfToStrRef(buf), TStrSpan{ (char*)"a\0" "b",(size_t)3 }), 1);
    tfStrFree(&buf);
}

UTEST(Core, tfcatfmt)
{
    struct TStr s = { 0 };
    {
        tfstrcatfmt(&s, "%S\n", tfCToStrRef("Hello World"));
        EXPECT_EQ(tfStrEqual(tfToStrRef(s), tfCToStrRef("Hello World\n")), true);
        tfStrClear(&s);
    }
    {
        tfstrcatfmt(&s, "%i\n", 125);
        EXPECT_EQ(tfStrEqual(tfToStrRef(s), tfCToStrRef("125\n")), true);
        tfStrClear(&s);
    }
    {
        tfstrcatfmt(&s, "%i\n", -125);
        EXPECT_EQ(tfStrEqual(tfToStrRef(s), tfCToStrRef("-125\n")), true);
        tfStrClear(&s);
    }
    tfStrFree(&s);
}

UTEST(Core, updateLen)
{
    struct TStr buf = { 0 };
    tfStrAssign(&buf, tfCToStrRef("Hello World"));
    buf.buf[5] = '\0';
    tfStrUpdateLen(&buf);

    EXPECT_EQ(tfStrEqual(tfToStrRef(buf), tfCToStrRef("Hello")), true);
    EXPECT_EQ(buf.len, 5);

    tfStrFree(&buf);
}

UTEST(Core, tfStrAssign)
{
    struct TStr buf = { 0 };
    {
        tfStrAssign(&buf, tfCToStrRef("Hello World"));
        EXPECT_EQ(tfStrEqual(tfToStrRef(buf), tfCToStrRef("Hello World")), true);
    }
    {
        tfStrAssign(&buf, tfStrTrim(tfCToStrRef("   Hello World   ")));
        EXPECT_EQ(tfStrEqual(tfToStrRef(buf), tfCToStrRef("Hello World")), true);
    }
    tfStrFree(&buf);
}

UTEST(Core, tf_rtrim)
{
    EXPECT_EQ(tfStrEqual(tfStrRTrim(tfCToStrRef("Hello world  ")), tfCToStrRef("Hello world")), true);
    EXPECT_EQ(tfStrEqual(tfStrRTrim(tfCToStrRef("  Hello world  ")), tfCToStrRef("  Hello world")), true);
    EXPECT_EQ(tfStrEqual(tfStrRTrim(tfCToStrRef("  ")), tfCToStrRef("")), true);
    EXPECT_EQ(tfStrEqual(tfStrRTrim(tfCToStrRef(" ")), tfCToStrRef("")), true);
    EXPECT_EQ(tfStrEqual(tfStrRTrim(tfCToStrRef("\n")), tfCToStrRef("")), true);
    EXPECT_EQ(tfStrEqual(tfStrRTrim(tfCToStrRef("\t")), tfCToStrRef("")), true);
}

UTEST(Core, tf_ltrim)
{
    EXPECT_EQ(tfStrEqual(tfStrLTrim(tfCToStrRef("Hello world  ")), tfCToStrRef("Hello world  ")), true);
    EXPECT_EQ(tfStrEqual(tfStrLTrim(tfCToStrRef("  ")), tfCToStrRef("")), true);
    EXPECT_EQ(tfStrEqual(tfStrLTrim(tfCToStrRef(" ")), tfCToStrRef("")), true);
    EXPECT_EQ(tfStrEqual(tfStrLTrim(tfCToStrRef("\n")), tfCToStrRef("")), true);
    EXPECT_EQ(tfStrEqual(tfStrLTrim(tfCToStrRef("\t")), tfCToStrRef("")), true);
}

UTEST(Core, tfStrTrim)
{
    {
        struct TStr buf = { 0 };
        tfStrAssign(&buf, tfCToStrRef("  Hello World "));
        tfStrAssign(&buf, tfStrTrim(tfToStrRef(buf)));
        EXPECT_EQ(tfStrEqual(tfToStrRef(buf), tfCToStrRef("Hello World")), true);
        tfStrFree(&buf);
    }

    EXPECT_EQ(tfStrEqual(tfStrTrim(tfCToStrRef("Hello world  ")), tfCToStrRef("Hello world")), true);
    EXPECT_EQ(tfStrEqual(tfStrTrim(tfCToStrRef("  \t Hello world  ")), tfCToStrRef("Hello world")), true);
    EXPECT_EQ(tfStrEqual(tfStrTrim(tfCToStrRef("  ")), tfCToStrRef("")), true);
    EXPECT_EQ(tfStrEqual(tfStrTrim(tfCToStrRef(" ")), tfCToStrRef("")), true);
    EXPECT_EQ(tfStrEqual(tfStrTrim(tfCToStrRef("\n")), tfCToStrRef("")), true);
    EXPECT_EQ(tfStrEqual(tfStrTrim(tfCToStrRef("\t")), tfCToStrRef("")), true);
}

UTEST(Core, tfsscanf)
{
    {
        uint32_t a = 0;
        uint32_t b = 0;
        int      read = tfstrsscanf(tfCToStrRef("10.132"), "%u.%u", &a, &b);
        EXPECT_EQ(read, 2);
        EXPECT_EQ(a, 10);
        EXPECT_EQ(b, 132);
    }
}

// UTEST(Core, tfSliceToUtf16CodePoint) {
//   unsigned char leftPointingMagnify[] = {0x3D,0xD8,0x0D,0xDD};
//
//   struct tf_utf_result_s res;
//   {
//     struct TFStrSplitIterable iter = {
//       .buffer = (struct TStrSpan) {
//         .buf = (const char*)leftPointingMagnify,
//         .len = 2,
//       },
//       .cursor = 0
//     };
//     res = tfUtf16NextCodePoint(&iter);
//     EXPECT_EQ((bool)res.invalid, true);
//     EXPECT_EQ((bool)res.finished, true);
//   }
//   {
//     struct TFStrSplitIterable iter = {
//       .buffer = (struct TStrSpan) {
//         .buf = (const char*)leftPointingMagnify,
//         .len = sizeof(leftPointingMagnify),
//       },
//       .cursor = 0
//     };
//     res = tfUtf16NextCodePoint(&iter);
//     EXPECT_EQ(res.codePoint, 0x1F50D);

//     EXPECT_EQ((bool)res.finished, true);
//   }
//   {
//     struct TFStrSplitIterable iter = (struct TFStrSplitIterable){
//       .buffer = (struct TStrSpan) {
//         .buf = NULL,
//         .len = 0,
//       },
//       .cursor = 0
//     };
//     res = tfUtf16NextCodePoint(&iter);
//     EXPECT_EQ((bool)res.invalid, true);
//     EXPECT_EQ((bool)res.finished, true);
//   }
//   {
//     char badInput[] = {0};
//     struct TFStrSplitIterable iter = (struct TFStrSplitIterable){
//         .buffer = (struct TStrSpan){
//           .buf = badInput,
//           .len = 0,
//         },
//         .cursor = 0};
//     res = tfUtf16NextCodePoint(&iter);
//     EXPECT_EQ((bool)res.invalid, true);
//     EXPECT_EQ((bool)res.finished, true);
//   }
//
// }

// UTEST(Core, tfSliceToUtf8CodePoint) {
//   char smilyCat[] = {0xF0, 0x9F, 0x98, 0xBC};
//   struct TFStrSplitIterable iter = {
//     .buffer = (struct TStrSpan) {
//       .len = sizeof(smilyCat),
//       .buf = smilyCat
//     },
//     .cursor = 0
//   };
//
//   struct tf_utf_result_s res = tfUtf8NextCodePoint(&iter);
//   EXPECT_EQ(res.codePoint, 0x0001f63c);
//
//   char charU[] = {'U'};
//   EXPECT_EQ(tfSliceToUtf8CodePoint((struct TStrSpan) {
//     .len = sizeof(charU),
//     .buf = charU
//   }, 0), 'U');
//
//   char ringOperator[] = {0xe2, 0x88, 0x98};
//   EXPECT_EQ(tfSliceToUtf8CodePoint((struct TStrSpan) {
//     .len = sizeof(ringOperator),
//     .buf = ringOperator
//   }, 0), 0x2218);
//
//   // this has an extra byte
//   char badRingOperator[] = {0xe2, 0x88, 0x98, 0x1};
//   EXPECT_EQ(tfSliceToUtf8CodePoint((struct TStrSpan) {
//     .len = sizeof(badRingOperator),
//     .buf = badRingOperator
//   }, 1), 1);
// }

// UTEST(Core, tfUtf8CodePointIter) {
//   {
//     unsigned char smilyCat[] = {0xF0, 0x9F, 0x98, 0xBC};
//     struct TFStrSplitIterable iter = {
//       .buffer = (struct TStrSpan) {
//         .buf = (char*)smilyCat,
//         .len = sizeof(smilyCat),
//       },
//       .cursor = 0
//     };
//     struct tf_utf_result_s res = tfUtf8NextCodePoint(&iter);
//     EXPECT_EQ(res.codePoint, 0x0001f63c);
//     EXPECT_EQ((bool)res.finished, true);
//     EXPECT_EQ((bool)res.invalid, false);
//   }
// {
//   // Ḽơᶉëᶆ
//   unsigned char buffer[] = {0xE1, 0xB8, 0xBC, 0xC6, 0xA1, 0xE1, 0xB6, 0x89,0xC3, 0xAB,0xE1, 0xB6,0x86 };
//   struct TFStrSplitIterable iterable = {
//     .buffer = {
//       .buf = (const char*)buffer,
//       .len = sizeof(buffer)
//     },
//     .cursor = 0,
//   };
//   struct tf_utf_result_s s = {0};
//   s = tfUtf8NextCodePoint(&iterable);
//   EXPECT_EQ(s.codePoint, 0x00001E3C); // 0xE1, 0xB8, 0xBC
//   EXPECT_EQ((bool)s.finished, false);
//   EXPECT_EQ((bool)s.invalid, false);
//   s = tfUtf8NextCodePoint(&iterable);
//   EXPECT_EQ(s.codePoint,0x1a1); // 0xBC, 0xC6
//   EXPECT_EQ((bool)s.finished, false);
//   EXPECT_EQ((bool)s.invalid, false);
//   s = tfUtf8NextCodePoint(&iterable);
//   EXPECT_EQ(s.codePoint,0x1D89); // 0xE1, 0xB6, 0x89
//   EXPECT_EQ((bool)s.finished, false);
//   EXPECT_EQ((bool)s.invalid, false);
//   s = tfUtf8NextCodePoint(&iterable);
//   EXPECT_EQ(s.codePoint,0x00EB); // 0xC3 0xAB
//   EXPECT_EQ((bool)s.finished, false);
//   EXPECT_EQ((bool)s.invalid, false);
//   s = tfUtf8NextCodePoint(&iterable);
//   EXPECT_EQ(s.codePoint,0x1D86); //0xE1 0xB6 0x86
//   EXPECT_EQ((bool)s.finished, true);
//   EXPECT_EQ((bool)s.invalid, false);
//   s = tfUtf8NextCodePoint(&iterable);
//   EXPECT_EQ((bool)s.finished, true);
//   EXPECT_EQ((bool)s.invalid, true);
//   }
// }

#include "Forge/TF_FileSystem.h"
#include "Forge/Mem/TF_Memory.h"
#include "Forge/TF_Log.h"
UTEST_STATE();
TF_UTEST_MAIN("TF_StringTest")
