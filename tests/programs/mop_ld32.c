#include <stdint.h>

#define TEST_LD32I(upper, lower) \
    asm volatile ( \
        "lui %0, " #upper "\n" \
        "addiw %0, %0," #lower "\n" \
        : "=r"(rd) \
    ); \
    asm volatile ( \
        "lui %0, " #upper "\n" \
        "nop\n" \
        "addiw %0, %0," #lower "\n" \
        : "=r"(expect_rd) \
    ); \
    if (rd != expect_rd) { \
        return 1; \
    }

#define TEST_LD32U(upper, lower) \
    asm volatile ( \
        "lui %0, " #upper "\n" \
        "addiwu %0, %0," #lower "\n" \
        : "=r"(rd) \
    ); \
    asm volatile ( \
        "lui %0, " #upper "\n" \
        "nop\n" \
        "addiwu %0, %0," #lower "\n" \
        : "=r"(expect_rd) \
    ); \
    if (rd != expect_rd) { \
        return 1; \
    }

int main() {
    uint64_t rd;
    uint64_t expect_rd;

    TEST_LD32I(0x00000, 0x0)
    TEST_LD32I(0x00000, 0x1)
    TEST_LD32I(0xfffff, -0x1)
    TEST_LD32I(0x00000, 0x0)
    TEST_LD32I(0x00000, 0x4)
    TEST_LD32I(0x00000, 0x40)
    TEST_LD32I(0x00000, 0x80)
    TEST_LD32I(0x00002, 0x0)
    TEST_LD32I(0x00010, 0x0)
    TEST_LD32I(0x00400, 0x0)
    TEST_LD32I(0x01000, 0x0)
    TEST_LD32I(0x00000, 0x0)
    TEST_LD32I(0x00000, 0x0)
    TEST_LD32I(0x00000, 0x0)
    TEST_LD32I(0x00000, 0x0)
    TEST_LD32I(0x00000, 0x0)
    TEST_LD32I(0x00000, 0x0)
    TEST_LD32I(0x00000, 0x0)
    TEST_LD32I(0x00000, 0xd)
    TEST_LD32I(0x00000, 0x0)
    TEST_LD32I(0x00000, 0x67)
    TEST_LD32I(0x00000, 0x0)
    TEST_LD32I(0x00000, 0x15b)
    TEST_LD32I(0x00000, 0x0)
    TEST_LD32I(0x00007, -0x226)
    TEST_LD32I(0x00000, 0x0)
    TEST_LD32I(0x0003e, -0x27e)
    TEST_LD32I(0x00000, 0x0)
    TEST_LD32I(0x00007, 0x14c)
    TEST_LD32I(0x00000, 0x0)
    TEST_LD32I(0x0dd29, -0x195)
    TEST_LD32I(0x00000, 0x0)
    TEST_LD32I(0xa865d, -0x2c)
    TEST_LD32I(0x00000, 0x0)
    TEST_LD32I(0x80f3c, -0x97)
    TEST_LD32I(0xc0000, 0x0)
    TEST_LD32I(0x714b9, 0x2d2)
    TEST_LD32I(0xe4000, 0x0)
    TEST_LD32I(0x6a6af, -0xab)
    TEST_LD32I(0xd5100, 0x0)
    TEST_LD32I(0x26b7f, -0x6c)
    TEST_LD32I(0xb3030, 0x0)
    TEST_LD32I(0xfbb7c, -0x3bf)
    TEST_LD32I(0x022b9, 0x0)
    TEST_LD32I(0xf2440, -0x102)
    TEST_LD32I(0xffbaf, 0x100)
    TEST_LD32I(0x3975b, -0x3af)
    TEST_LD32I(0xce126, 0x370)
    TEST_LD32I(0x7da5b, 0x1ef)
    TEST_LD32I(0x34976, 0x14c)
    TEST_LD32I(0x78139, -0x372)
    TEST_LD32I(0xbdfb5, 0x37)
    TEST_LD32I(0x5bde4, 0x347)
    TEST_LD32I(0x8c93c, -0x1ff)
    TEST_LD32I(0x47034, 0x1dd)
    TEST_LD32I(0x4e789, 0xe)
    TEST_LD32I(0xecbfa, 0x2be)
    TEST_LD32I(0x5d0db, 0x26b)
    TEST_LD32I(0xda2a5, 0x3df)
    TEST_LD32I(0xd5231, 0xa8)
    TEST_LD32I(0x4e687, -0x367)
    TEST_LD32I(0xf41aa, 0x230)
    TEST_LD32I(0xc3f41, 0x374)
    TEST_LD32I(0x1a9fa, -0x1be)
    TEST_LD32I(0xe5b54, 0x19e)
    TEST_LD32I(0xe4278, -0x363)
    TEST_LD32I(0xa4174, -0x33c)
    TEST_LD32I(0x6c8cd, 0x34d)
    TEST_LD32I(0x977cb, 0x1bb)
    TEST_LD32I(0x77794, -0x1e8)
    TEST_LD32I(0xa22d3, 0x294)
    TEST_LD32I(0x03954, -0x20f)
    TEST_LD32I(0x5b2b3, 0x32a)
    TEST_LD32I(0xa58ee, -0x24)
    TEST_LD32I(0x95a18, -0x2ed)
    TEST_LD32I(0x64d9e, 0x2c9)
    TEST_LD32I(0xdf8bc, 0x35c)
    TEST_LD32I(0xe4398, 0x3ca)
    TEST_LD32I(0x52504, 0x25d)
    TEST_LD32I(0xbebfd, -0x277)
    TEST_LD32I(0x0f60e, 0x72)
    TEST_LD32I(0x3f2c7, -0x2ce)
    TEST_LD32I(0xdb7b2, 0x148)
    TEST_LD32I(0x451a8, -0x2e6)
    TEST_LD32I(0x3f90b, -0x180)
    TEST_LD32I(0xbdea3, -0x3)
    TEST_LD32I(0xc865b, -0x33e)
    TEST_LD32I(0x5e560, -0xd5)
    TEST_LD32I(0x55660, 0x1f5)
    TEST_LD32I(0x923c1, 0xa6)
    TEST_LD32I(0x4d248, 0x117)
    TEST_LD32I(0x1e346, -0x23b)
    TEST_LD32I(0xa535d, -0x3b2)
    TEST_LD32I(0xbe6d6, -0x38a)
    TEST_LD32I(0xbaba6, 0x33e)
    TEST_LD32I(0xcbc01, 0x78)
    TEST_LD32I(0x83ce8, -0x1b8)
    TEST_LD32I(0x2b298, 0x144)
    TEST_LD32I(0x0a990, 0x356)
    TEST_LD32I(0x46242, -0x340)
    TEST_LD32I(0x55095, -0x367)
    TEST_LD32I(0xa5854, 0x70)
    TEST_LD32I(0xd8705, -0x110)
    TEST_LD32I(0x89b10, 0x25d)
    TEST_LD32I(0xabb95, -0xf7)
    TEST_LD32I(0xe8b6c, -0x9)
    TEST_LD32I(0x027ab, -0x58)
    TEST_LD32I(0x688aa, 0xd7)
    TEST_LD32I(0x78456, 0x56)
    TEST_LD32I(0x71cb3, -0xea)
    TEST_LD32I(0x67d5a, -0x318)
    TEST_LD32I(0x8e8e3, -0x24f)
    TEST_LD32I(0x74be6, -0x276)
    TEST_LD32I(0x89df3, 0x3d1)
    TEST_LD32I(0x6e965, 0x1f6)
    TEST_LD32I(0x7169c, 0xc5)
    TEST_LD32I(0xd8c98, 0x214)
    TEST_LD32I(0x78581, -0x400)
    TEST_LD32I(0x155fa, -0x3c8)
    TEST_LD32I(0x9dd91, -0x2a0)
    TEST_LD32I(0x23bdf, -0xa6)
    TEST_LD32I(0x14041, 0x234)
    TEST_LD32I(0x546c1, -0x100)
    TEST_LD32I(0x0e5f0, -0xc2)
    TEST_LD32I(0xc605b, -0x150)
    TEST_LD32I(0x73881, 0x1dd)
    TEST_LD32I(0x342cd, -0x142)
    TEST_LD32I(0xd080e, 0x93)

    TEST_LD32U(0x00000, 0x0)
    TEST_LD32U(0x00000, 0x1)
    TEST_LD32U(0xfffff, 0x7ff)
    TEST_LD32U(0x00000, 0x0)
    TEST_LD32U(0x00000, 0x4)
    TEST_LD32U(0x00000, 0x40)
    TEST_LD32U(0x00000, 0x80)
    TEST_LD32U(0x00002, 0x0)
    TEST_LD32U(0x00010, 0x0)
    TEST_LD32U(0x00400, 0x0)
    TEST_LD32U(0x01000, 0x0)
    TEST_LD32U(0x00000, 0x0)
    TEST_LD32U(0x00000, 0x0)
    TEST_LD32U(0x00000, 0x0)
    TEST_LD32U(0x00000, 0x0)
    TEST_LD32U(0x00000, 0x0)
    TEST_LD32U(0x00000, 0x0)
    TEST_LD32U(0x00000, 0x0)
    TEST_LD32U(0x00000, 0xd)
    TEST_LD32U(0x00000, 0x0)
    TEST_LD32U(0x00000, 0x67)
    TEST_LD32U(0x00000, 0x0)
    TEST_LD32U(0x00000, 0x15b)
    TEST_LD32U(0x00000, 0x0)
    TEST_LD32U(0x00007, 0x5da)
    TEST_LD32U(0x00000, 0x0)
    TEST_LD32U(0x0003e, 0x582)
    TEST_LD32U(0x00000, 0x0)
    TEST_LD32U(0x00007, 0x14c)
    TEST_LD32U(0x00000, 0x0)
    TEST_LD32U(0x0dd29, 0x66b)
    TEST_LD32U(0x00000, 0x0)
    TEST_LD32U(0xa865d, 0x7d4)
    TEST_LD32U(0x00000, 0x0)
    TEST_LD32U(0x80f3c, 0x769)
    TEST_LD32U(0xc0000, 0x0)
    TEST_LD32U(0x714b9, 0x2d2)
    TEST_LD32U(0xe4000, 0x0)
    TEST_LD32U(0x6a6af, 0x755)
    TEST_LD32U(0xd5100, 0x0)
    TEST_LD32U(0x26b7f, 0x794)
    TEST_LD32U(0xb3030, 0x0)
    TEST_LD32U(0xfbb7c, 0x441)
    TEST_LD32U(0x022b9, 0x0)
    TEST_LD32U(0xf2440, 0x6fe)
    TEST_LD32U(0xffbaf, 0x100)
    TEST_LD32U(0x3975b, 0x451)
    TEST_LD32U(0xce126, 0x370)
    TEST_LD32U(0x7da5b, 0x1ef)
    TEST_LD32U(0x34976, 0x14c)
    TEST_LD32U(0x78139, 0x48e)
    TEST_LD32U(0xbdfb5, 0x37)
    TEST_LD32U(0x5bde4, 0x347)
    TEST_LD32U(0x8c93c, 0x601)
    TEST_LD32U(0x47034, 0x1dd)
    TEST_LD32U(0x4e789, 0xe)
    TEST_LD32U(0xecbfa, 0x2be)
    TEST_LD32U(0x5d0db, 0x26b)
    TEST_LD32U(0xda2a5, 0x3df)
    TEST_LD32U(0xd5231, 0xa8)
    TEST_LD32U(0x4e687, 0x499)
    TEST_LD32U(0xf41aa, 0x230)
    TEST_LD32U(0xc3f41, 0x374)
    TEST_LD32U(0x1a9fa, 0x642)
    TEST_LD32U(0xe5b54, 0x19e)
    TEST_LD32U(0xe4278, 0x49d)
    TEST_LD32U(0xa4174, 0x4c4)
    TEST_LD32U(0x6c8cd, 0x34d)
    TEST_LD32U(0x977cb, 0x1bb)
    TEST_LD32U(0x77794, 0x618)
    TEST_LD32U(0xa22d3, 0x294)
    TEST_LD32U(0x03954, 0x5f1)
    TEST_LD32U(0x5b2b3, 0x32a)
    TEST_LD32U(0xa58ee, 0x7dc)
    TEST_LD32U(0x95a18, 0x513)
    TEST_LD32U(0x64d9e, 0x2c9)
    TEST_LD32U(0xdf8bc, 0x35c)
    TEST_LD32U(0xe4398, 0x3ca)
    TEST_LD32U(0x52504, 0x25d)
    TEST_LD32U(0xbebfd, 0x589)
    TEST_LD32U(0x0f60e, 0x72)
    TEST_LD32U(0x3f2c7, 0x532)
    TEST_LD32U(0xdb7b2, 0x148)
    TEST_LD32U(0x451a8, 0x51a)
    TEST_LD32U(0x3f90b, 0x680)
    TEST_LD32U(0xbdea3, 0x7fd)
    TEST_LD32U(0xc865b, 0x4c2)
    TEST_LD32U(0x5e560, 0x72b)
    TEST_LD32U(0x55660, 0x1f5)
    TEST_LD32U(0x923c1, 0xa6)
    TEST_LD32U(0x4d248, 0x117)
    TEST_LD32U(0x1e346, 0x5c5)
    TEST_LD32U(0xa535d, 0x44e)
    TEST_LD32U(0xbe6d6, 0x476)
    TEST_LD32U(0xbaba6, 0x33e)
    TEST_LD32U(0xcbc01, 0x78)
    TEST_LD32U(0x83ce8, 0x648)
    TEST_LD32U(0x2b298, 0x144)
    TEST_LD32U(0x0a990, 0x356)
    TEST_LD32U(0x46242, 0x4c0)
    TEST_LD32U(0x55095, 0x499)
    TEST_LD32U(0xa5854, 0x70)
    TEST_LD32U(0xd8705, 0x6f0)
    TEST_LD32U(0x89b10, 0x25d)
    TEST_LD32U(0xabb95, 0x709)
    TEST_LD32U(0xe8b6c, 0x7f7)
    TEST_LD32U(0x027ab, 0x7a8)
    TEST_LD32U(0x688aa, 0xd7)
    TEST_LD32U(0x78456, 0x56)
    TEST_LD32U(0x71cb3, 0x716)
    TEST_LD32U(0x67d5a, 0x4e8)
    TEST_LD32U(0x8e8e3, 0x5b1)
    TEST_LD32U(0x74be6, 0x58a)
    TEST_LD32U(0x89df3, 0x3d1)
    TEST_LD32U(0x6e965, 0x1f6)
    TEST_LD32U(0x7169c, 0xc5)
    TEST_LD32U(0xd8c98, 0x214)
    TEST_LD32U(0x78581, 0x400)
    TEST_LD32U(0x155fa, 0x438)
    TEST_LD32U(0x9dd91, 0x560)
    TEST_LD32U(0x23bdf, 0x75a)
    TEST_LD32U(0x14041, 0x234)
    TEST_LD32U(0x546c1, 0x700)
    TEST_LD32U(0x0e5f0, 0x73e)
    TEST_LD32U(0xc605b, 0x6b0)
    TEST_LD32U(0x73881, 0x1dd)
    TEST_LD32U(0x342cd, 0x6be)
    TEST_LD32U(0xd080e, 0x93)

    return 0;
}
