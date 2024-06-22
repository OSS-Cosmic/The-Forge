
#include <stdbool.h>

#include "Forge/Core/TF_String.h"

#include "utest.h"

UTEST(bstr, bstrCaselessCompare)
{
    EXPECT_EQ(bstrCaselessCompare(tfToRef("test"), tfToRef("TEST")), 0);
    EXPECT_EQ(bstrCaselessCompare(tfToRef("testAA"), tfToRef("TEST")), 1);
}

UTEST(bstr, bstrCompare)
{
    EXPECT_EQ(bstrCompare(tfToRef("test"), tfToRef("TEST")), 32);
    EXPECT_EQ(bstrCompare(tfToRef("Test"), tfToRef("test")), -32);
}

UTEST(bstr, bstrIndexOf)
{
    EXPECT_EQ(tfStrIndexOf(tfToRef("foo foo"), tfToRef("foo")), 0);
    EXPECT_EQ(tfStrIndexOf(tfToRef("banana"), tfToRef("ana")), 1);
    EXPECT_EQ(tfStrIndexOf(tfToRef("textbook"), tfToRef("book")), 4);
    EXPECT_EQ(tfStrIndexOf(tfToRef("abababcabababcbab"), tfToRef("ababc")), 2);
    EXPECT_EQ(tfStrIndexOf(tfToRef("This is a test string to see how Boyer-Moore handles longer searches"), tfToRef("searches")), 60);
    EXPECT_EQ(tfStrIndexOf(tfToRef("hello world"), tfToRef("hello")), 0);
    EXPECT_EQ(tfStrIndexOf(tfToRef("apple banana"), tfToRef("nana")), 8);
    EXPECT_EQ(tfStrIndexOf(tfToRef("goodbye"), tfToRef("bye")), 4);
    EXPECT_EQ(tfStrIndexOf(tfToRef("cat"), tfToRef("dog")), -1);
    EXPECT_EQ(tfStrIndexOf(tfToRef(""), tfToRef("abc")), -1);
    EXPECT_EQ(tfStrIndexOf(tfToRef("hello"), tfToRef("")), -1);
    EXPECT_EQ(tfStrIndexOf(tfToRef("abc"), tfToRef("abcd")), -1);
}

UTEST(bstr, bstrLastIndexOf)
{
    EXPECT_EQ(bstrLastIndexOf(tfToRef("foo foo"), tfToRef(" ")), 3);
    EXPECT_EQ(bstrLastIndexOf(tfToRef("foo foo"), tfToRef("foo")), 4);
    EXPECT_EQ(bstrLastIndexOf(tfToRef("banana"), tfToRef("ana")), 3);
    EXPECT_EQ(bstrLastIndexOf(tfToRef("textbook"), tfToRef("book")), 4);
    EXPECT_EQ(bstrLastIndexOf(tfToRef("abababcabababcbab"), tfToRef("ababc")), 9);
    EXPECT_EQ(bstrLastIndexOf(tfToRef("This is a test string to see how Boyer-Moore handles longer searches"), tfToRef("searches")), 60);
    EXPECT_EQ(bstrLastIndexOf(tfToRef("hello world"), tfToRef("hello")), 0);
    EXPECT_EQ(bstrLastIndexOf(tfToRef("apple banana"), tfToRef("nana")), 8);
    EXPECT_EQ(bstrLastIndexOf(tfToRef("goodbye"), tfToRef("bye")), 4);
    EXPECT_EQ(bstrLastIndexOf(tfToRef("cat"), tfToRef("dog")), -1);
    EXPECT_EQ(bstrLastIndexOf(tfToRef(""), tfToRef("abc")), -1);
    EXPECT_EQ(bstrLastIndexOf(tfToRef("hello"), tfToRef("")), -1);
    EXPECT_EQ(bstrLastIndexOf(tfToRef("abc"), tfToRef("abcd")), -1);
}

UTEST(bstr, bstrEq)
{
    EXPECT_EQ(bstrEqual(tfToRef("Hello world"), tfToRef("Hello world")), 1);
    EXPECT_EQ(bstrEqual(tfToRef("Helloworld"), tfToRef("Hello world")), 0);
    EXPECT_EQ(bstrEqual(tfToRef("Hello World"), tfToRef("Hello world")), 0);
    EXPECT_EQ(bstrEqual(tfToRef("Hello"), tfToRef("Hello ")), 0);
}

UTEST(bstr, bstrDuplicate)
{
    struct TStr s1 = { 0 };
    EXPECT_EQ(tfStrAssign(&s1, tfToRef("Hello World")), true);
    struct TStr s2 = tfStrDup(&s1);
    EXPECT_NE(s1.buf, s2.buf);
    tfStrFree(&s1);
    tfStrFree(&s2);
}

UTEST(bstr, bstrIterateRev)
{
    struct TStrSpan           buf = tfToRef("one two three four five");
    struct TFStrSplitIterable iterable = { .buffer = buf, .delim = tfToRef(" "), .cursor = buf.len };
    struct TStrSpan           s = { 0 };
    s = bstrSplitRevIter(&iterable);
    EXPECT_EQ(tfStrEmpty(s), 0);
    EXPECT_EQ(bstrEqual(tfToRef("five"), s), 1);
    s = bstrSplitRevIter(&iterable);
    EXPECT_EQ(tfStrEmpty(s), 0);
    EXPECT_EQ(bstrEqual(tfToRef("four"), s), 1);
    s = bstrSplitRevIter(&iterable);
    EXPECT_EQ(tfStrEmpty(s), 0);
    EXPECT_EQ(bstrEqual(tfToRef("three"), s), 1);
    s = bstrSplitRevIter(&iterable);
    EXPECT_EQ(tfStrEmpty(s), 0);
    EXPECT_EQ(bstrEqual(tfToRef("two"), s), 1);
    s = bstrSplitRevIter(&iterable);
    EXPECT_EQ(tfStrEmpty(s), 0);
    EXPECT_EQ(bstrEqual(tfToRef("one"), s), 1);
    s = bstrSplitRevIter(&iterable);
    EXPECT_EQ(tfStrEmpty(s), 1);
}

UTEST(bstr, bstrReadull)
{
    unsigned long long res = 0;
    EXPECT_EQ(bstrReadull(tfToRef("123456"), &res), 1);
    EXPECT_EQ(res, 123456);
}

UTEST(bstr, bstrReadu32)
{
    long long res = 0;
    EXPECT_EQ(bstrReadll(tfToRef("123456"), &res), 1);
    EXPECT_EQ(res, 123456);
}

UTEST(bstr, bstrIterateWhiteSpace)
{
    struct TFStrSplitIterable iterable = { .buffer = tfToRef("one  two"), .delim = tfToRef(" "), .cursor = 0 };
    struct TStrSpan           s = { 0 };

    s = bstrSplitIter(&iterable);
    EXPECT_EQ(tfStrEmpty(s), 0);
    EXPECT_EQ(bstrEqual(tfToRef("one"), s), 1);

    s = bstrSplitIter(&iterable);
    EXPECT_EQ(tfStrEmpty(s), 1);

    s = bstrSplitIter(&iterable);
    EXPECT_EQ(bstrEqual(tfToRef("two"), s), 1);

    s = bstrSplitIter(&iterable);
    EXPECT_EQ(tfStrEmpty(s), 1);
}

UTEST(bstr, bstrIterateCount)
{
    {
        struct TFStrSplitIterable iterable = { .buffer = tfToRef("one two three four five"), .delim = tfToRef(" "), .cursor = 0 };
        struct TStrSpan           slices[] = {
            tfToRef("one"), tfToRef("two"), tfToRef("three"), tfToRef("four"), tfToRef("five"),
        };
        size_t i = 0;
        while (iterable.cursor < iterable.buffer.len)
        {
            struct TStrSpan it = bstrSplitIter(&iterable);
            EXPECT_EQ(bstrEqual(slices[i++], it), 1);
        }
    }
    {
        struct TFStrSplitIterable iterable = { .buffer = tfToRef("one   two"), .delim = tfToRef(" "), .cursor = 0 };
        struct TStrSpan           slices[] = {
            tfToRef("one"),
            tfToRef(""),
            tfToRef(""),
            tfToRef("two"),
        };
        size_t i = 0;
        while (iterable.cursor < iterable.buffer.len)
        {
            struct TStrSpan it = bstrSplitIter(&iterable);
            EXPECT_EQ(bstrEqual(slices[i++], it), 1);
        }
    }
}

UTEST(bstr, bstrIterate)
{
    struct TFStrSplitIterable iterable = { .buffer = tfToRef("one two three four five"), .delim = tfToRef(" "), .cursor = 0 };

    struct TStrSpan s = { 0 };
    s = bstrSplitIter(&iterable);
    EXPECT_EQ(tfStrEmpty(s), 0);
    EXPECT_EQ(bstrEqual(tfToRef("one"), s), 1);
    s = bstrSplitIter(&iterable);
    EXPECT_EQ(tfStrEmpty(s), 0);
    EXPECT_EQ(bstrEqual(tfToRef("two"), s), 1);
    s = bstrSplitIter(&iterable);
    EXPECT_EQ(tfStrEmpty(s), 0);
    EXPECT_EQ(bstrEqual(tfToRef("three"), s), 1);
    s = bstrSplitIter(&iterable);
    EXPECT_EQ(tfStrEmpty(s), 0);
    EXPECT_EQ(bstrEqual(tfToRef("four"), s), 1);
    s = bstrSplitIter(&iterable);
    EXPECT_EQ(tfStrEmpty(s), 0);
    EXPECT_EQ(bstrEqual(tfToRef("five"), s), 1);
    s = bstrSplitIter(&iterable);
    EXPECT_EQ(tfStrEmpty(s), 1);
}

UTEST(bstr, bstrfmtWriteLongLong)
{
    char   test_buffer[TFSTR_LLSTR_SIZE];
    size_t len = bstrfmtll((struct TStrSpan){ .buf = test_buffer, .len = TFSTR_LLSTR_SIZE }, 12481);
    EXPECT_EQ(len, 5);
    EXPECT_EQ(bstrEqual(tfToRef("12481"), (struct TStrSpan){ .buf = test_buffer, .len = len }), true);
}

UTEST(bstr, bstrCaselessEq)
{
    EXPECT_EQ(bstrCaselessEqual(tfToRef("Hello world"), tfToRef("Hello world")), 1);
    EXPECT_EQ(bstrCaselessEqual(tfToRef("Helloworld"), tfToRef("Hello world")), 0);
    EXPECT_EQ(bstrCaselessEqual(tfToRef("Hello World"), tfToRef("Hello world")), 1);
    EXPECT_EQ(bstrCaselessEqual(tfToRef("Hello"), tfToRef("Hello ")), 0);
}

UTEST(bstr, bstrCatJoin)
{
    struct TStr     buf = { 0 };
    struct TStrSpan slices[] = {
        tfToRef("one"),
        tfToRef("two"),
        tfToRef("three"),
        tfToRef("four"),
    };
    EXPECT_EQ(bstrcatjoin(&buf, slices, 4, tfToRef(" ")), true);
    EXPECT_EQ(bstrEqual(tfToRef(buf), tfToRef("one two three four")), true);
    tfStrFree(&buf);
}

UTEST(bstr, bstrCatJoinCstr)
{
    struct TStr buf = { 0 };
    const char* slices[] = {
        "one",
        "two",
        "three",
        "four",
    };
    EXPECT_EQ(bstrCatJoinCStr(&buf, slices, 4, tfToRef(" ")), true);
    EXPECT_EQ(bstrEqual(tfToRef(buf), tfToRef("one two three four")), true);
    tfStrFree(&buf);
}

UTEST(bstr, appendSlice)
{
    struct TStr buf = { 0 };
    tfStrAssign(&buf, tfToRef("Hello"));
    EXPECT_EQ(tfStrAppendSlice(&buf, tfToRef(" world")), true);
    EXPECT_EQ(bstrEqual(tfToRef(buf), tfToRef("Hello world")), true);
    tfStrFree(&buf);
}

UTEST(bstr, bstrcatprintf)
{
    struct TStr buf = { 0 };
    EXPECT_EQ(bstrcatprintf(&buf, "Hello %s", "world"), true);
    EXPECT_EQ(bstrEqual(tfToRef(buf), tfToRef("Hello world")), true);

    bstrsetlen(&buf, 0);
    EXPECT_EQ(bstrcatprintf(&buf, "%d", 123), true);
    EXPECT_EQ(bstrEqual(tfToRef(buf), tfToRef("123")), true);

    EXPECT_EQ(bstrcatprintf(&buf, " %lu", 156), true);
    EXPECT_EQ(bstrEqual(tfToRef(buf), tfToRef("123 156")), true);

    bstrsetlen(&buf, 0);
    EXPECT_EQ(bstrcatprintf(&buf, "a%cb", 0), true);
    EXPECT_EQ(bstrEqual(tfToRef(buf), (struct TStrSpan){ .buf = "a\0"
                                                                "b",
                                                         .len = 3 }),
              1);
    tfStrFree(&buf);
}

UTEST(bstr, bstrcatfmt)
{
    struct TStr s = { 0 };
    {
        bstrcatfmt(&s, "%S\n", tfToRef("Hello World"));
        EXPECT_EQ(bstrEqual(tfToRef(s), tfToRef("Hello World\n")), true);
        bstr_clear(&s);
    }
    {
        bstrcatfmt(&s, "%i\n", 125);
        EXPECT_EQ(bstrEqual(tfToRef(s), tfToRef("125\n")), true);
        bstr_clear(&s);
    }
    {
        bstrcatfmt(&s, "%i\n", -125);
        EXPECT_EQ(bstrEqual(tfToRef(s), tfToRef("-125\n")), true);
        bstr_clear(&s);
    }
    tfStrFree(&s);
}

UTEST(bstr, updateLen)
{
    struct TStr buf = { 0 };
    tfStrAssign(&buf, tfToRef("Hello World"));
    buf.buf[5] = '\0';
    bstrUpdateLen(&buf);

    EXPECT_EQ(bstrEqual(tfToRef(buf), tfToRef("Hello")), true);
    EXPECT_EQ(buf.len, 5);

    tfStrFree(&buf);
}

UTEST(bstr, tfStrAssign)
{
    struct TStr buf = { 0 };
    {
        tfStrAssign(&buf, tfToRef("Hello World"));
        EXPECT_EQ(bstrEqual(tfToRef(buf), tfToRef("Hello World")), true);
    }
    {
        tfStrAssign(&buf, tfStrTrim(tfToRef("   Hello World   ")));
        EXPECT_EQ(bstrEqual(tfToRef(buf), tfToRef("Hello World")), true);
    }
    tfStrFree(&buf);
}

UTEST(bstr, bstr_rtrim)
{
    EXPECT_EQ(bstrEqual(tfStrRTrim(tfToRef("Hello world  ")), tfToRef("Hello world")), true);
    EXPECT_EQ(bstrEqual(tfStrRTrim(tfToRef("  Hello world  ")), tfToRef("  Hello world")), true);
    EXPECT_EQ(bstrEqual(tfStrRTrim(tfToRef("  ")), tfToRef("")), true);
    EXPECT_EQ(bstrEqual(tfStrRTrim(tfToRef(" ")), tfToRef("")), true);
    EXPECT_EQ(bstrEqual(tfStrRTrim(tfToRef("\n")), tfToRef("")), true);
    EXPECT_EQ(bstrEqual(tfStrRTrim(tfToRef("\t")), tfToRef("")), true);
}

UTEST(bstr, bstr_ltrim)
{
    EXPECT_EQ(bstrEqual(tfStrLTrim(tfToRef("Hello world  ")), tfToRef("Hello world  ")), true);
    EXPECT_EQ(bstrEqual(tfStrLTrim(tfToRef("  ")), tfToRef("")), true);
    EXPECT_EQ(bstrEqual(tfStrLTrim(tfToRef(" ")), tfToRef("")), true);
    EXPECT_EQ(bstrEqual(tfStrLTrim(tfToRef("\n")), tfToRef("")), true);
    EXPECT_EQ(bstrEqual(tfStrLTrim(tfToRef("\t")), tfToRef("")), true);
}

UTEST(bstr, tfStrTrim)
{
    {
        struct TStr buf = { 0 };
        tfStrAssign(&buf, tfToRef("  Hello World "));
        tfStrAssign(&buf, tfStrTrim(tfToRef(buf)));
        EXPECT_EQ(bstrEqual(tfToRef(buf), tfToRef("Hello World")), true);
        tfStrFree(&buf);
    }

    EXPECT_EQ(bstrEqual(tfStrTrim(tfToRef("Hello world  ")), tfToRef("Hello world")), true);
    EXPECT_EQ(bstrEqual(tfStrTrim(tfToRef("  \t Hello world  ")), tfToRef("Hello world")), true);
    EXPECT_EQ(bstrEqual(tfStrTrim(tfToRef("  ")), tfToRef("")), true);
    EXPECT_EQ(bstrEqual(tfStrTrim(tfToRef(" ")), tfToRef("")), true);
    EXPECT_EQ(bstrEqual(tfStrTrim(tfToRef("\n")), tfToRef("")), true);
    EXPECT_EQ(bstrEqual(tfStrTrim(tfToRef("\t")), tfToRef("")), true);
}

UTEST(bstr, bstrsscanf)
{
    {
        uint32_t a = 0;
        uint32_t b = 0;
        int      read = bstrsscanf(tfToRef("10.132"), "%u.%u", &a, &b);
        EXPECT_EQ(read, 2);
        EXPECT_EQ(a, 10);
        EXPECT_EQ(b, 132);
    }
}

// UTEST(bstr, bstrSliceToUtf16CodePoint) {
//   unsigned char leftPointingMagnify[] = {0x3D,0xD8,0x0D,0xDD};
//
//   struct bstr_utf_result_s res;
//   {
//     struct TFStrSplitIterable iter = {
//       .buffer = (struct TStrSpan) {
//         .buf = (const char*)leftPointingMagnify,
//         .len = 2,
//       },
//       .cursor = 0
//     };
//     res = bstrUtf16NextCodePoint(&iter);
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
//     res = bstrUtf16NextCodePoint(&iter);
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
//     res = bstrUtf16NextCodePoint(&iter);
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
//     res = bstrUtf16NextCodePoint(&iter);
//     EXPECT_EQ((bool)res.invalid, true);
//     EXPECT_EQ((bool)res.finished, true);
//   }
//
// }

// UTEST(bstr, bstrSliceToUtf8CodePoint) {
//   char smilyCat[] = {0xF0, 0x9F, 0x98, 0xBC};
//   struct TFStrSplitIterable iter = {
//     .buffer = (struct TStrSpan) {
//       .len = sizeof(smilyCat),
//       .buf = smilyCat
//     },
//     .cursor = 0
//   };
//
//   struct bstr_utf_result_s res = bstrUtf8NextCodePoint(&iter);
//   EXPECT_EQ(res.codePoint, 0x0001f63c);
//
//   char charU[] = {'U'};
//   EXPECT_EQ(bstrSliceToUtf8CodePoint((struct TStrSpan) {
//     .len = sizeof(charU),
//     .buf = charU
//   }, 0), 'U');
//
//   char ringOperator[] = {0xe2, 0x88, 0x98};
//   EXPECT_EQ(bstrSliceToUtf8CodePoint((struct TStrSpan) {
//     .len = sizeof(ringOperator),
//     .buf = ringOperator
//   }, 0), 0x2218);
//
//   // this has an extra byte
//   char badRingOperator[] = {0xe2, 0x88, 0x98, 0x1};
//   EXPECT_EQ(bstrSliceToUtf8CodePoint((struct TStrSpan) {
//     .len = sizeof(badRingOperator),
//     .buf = badRingOperator
//   }, 1), 1);
// }

// UTEST(bstr, bstrUtf8CodePointIter) {
//   {
//     unsigned char smilyCat[] = {0xF0, 0x9F, 0x98, 0xBC};
//     struct TFStrSplitIterable iter = {
//       .buffer = (struct TStrSpan) {
//         .buf = (char*)smilyCat,
//         .len = sizeof(smilyCat),
//       },
//       .cursor = 0
//     };
//     struct bstr_utf_result_s res = bstrUtf8NextCodePoint(&iter);
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
//   struct bstr_utf_result_s s = {0};
//   s = bstrUtf8NextCodePoint(&iterable);
//   EXPECT_EQ(s.codePoint, 0x00001E3C); // 0xE1, 0xB8, 0xBC
//   EXPECT_EQ((bool)s.finished, false);
//   EXPECT_EQ((bool)s.invalid, false);
//   s = bstrUtf8NextCodePoint(&iterable);
//   EXPECT_EQ(s.codePoint,0x1a1); // 0xBC, 0xC6
//   EXPECT_EQ((bool)s.finished, false);
//   EXPECT_EQ((bool)s.invalid, false);
//   s = bstrUtf8NextCodePoint(&iterable);
//   EXPECT_EQ(s.codePoint,0x1D89); // 0xE1, 0xB6, 0x89
//   EXPECT_EQ((bool)s.finished, false);
//   EXPECT_EQ((bool)s.invalid, false);
//   s = bstrUtf8NextCodePoint(&iterable);
//   EXPECT_EQ(s.codePoint,0x00EB); // 0xC3 0xAB
//   EXPECT_EQ((bool)s.finished, false);
//   EXPECT_EQ((bool)s.invalid, false);
//   s = bstrUtf8NextCodePoint(&iterable);
//   EXPECT_EQ(s.codePoint,0x1D86); //0xE1 0xB6 0x86
//   EXPECT_EQ((bool)s.finished, true);
//   EXPECT_EQ((bool)s.invalid, false);
//   s = bstrUtf8NextCodePoint(&iterable);
//   EXPECT_EQ((bool)s.finished, true);
//   EXPECT_EQ((bool)s.invalid, true);
//   }
// }

UTEST_STATE();
#include "Common_3/Utilities/Interfaces/IFileSystem.h"

#include "Common_3/Utilities/Interfaces/IMemory.h"

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
