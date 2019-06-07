// tinycrc32.h
// Copyright (C) 2019, Max Rossner [max (d0t) rosssner (at) gmail (d0t) com]
//
// MIT License
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef __TINYCRC32_H__
#define __TINYCRC32_H__

#include <cstdint>

#ifndef ENABLE_SSE42
alignas(64) constexpr uint32_t crc32c_lut[256] = {
    0x00000000, 0xF26B8303, 0xE13B70F7, 0x1350F3F4, 0xC79A971F, 0x35F1141C,
    0x26A1E7E8, 0xD4CA64EB, 0x8AD958CF, 0x78B2DBCC, 0x6BE22838, 0x9989AB3B,
    0x4D43CFD0, 0xBF284CD3, 0xAC78BF27, 0x5E133C24, 0x105EC76F, 0xE235446C,
    0xF165B798, 0x030E349B, 0xD7C45070, 0x25AFD373, 0x36FF2087, 0xC494A384,
    0x9A879FA0, 0x68EC1CA3, 0x7BBCEF57, 0x89D76C54, 0x5D1D08BF, 0xAF768BBC,
    0xBC267848, 0x4E4DFB4B, 0x20BD8EDE, 0xD2D60DDD, 0xC186FE29, 0x33ED7D2A,
    0xE72719C1, 0x154C9AC2, 0x061C6936, 0xF477EA35, 0xAA64D611, 0x580F5512,
    0x4B5FA6E6, 0xB93425E5, 0x6DFE410E, 0x9F95C20D, 0x8CC531F9, 0x7EAEB2FA,
    0x30E349B1, 0xC288CAB2, 0xD1D83946, 0x23B3BA45, 0xF779DEAE, 0x05125DAD,
    0x1642AE59, 0xE4292D5A, 0xBA3A117E, 0x4851927D, 0x5B016189, 0xA96AE28A,
    0x7DA08661, 0x8FCB0562, 0x9C9BF696, 0x6EF07595, 0x417B1DBC, 0xB3109EBF,
    0xA0406D4B, 0x522BEE48, 0x86E18AA3, 0x748A09A0, 0x67DAFA54, 0x95B17957,
    0xCBA24573, 0x39C9C670, 0x2A993584, 0xD8F2B687, 0x0C38D26C, 0xFE53516F,
    0xED03A29B, 0x1F682198, 0x5125DAD3, 0xA34E59D0, 0xB01EAA24, 0x42752927,
    0x96BF4DCC, 0x64D4CECF, 0x77843D3B, 0x85EFBE38, 0xDBFC821C, 0x2997011F,
    0x3AC7F2EB, 0xC8AC71E8, 0x1C661503, 0xEE0D9600, 0xFD5D65F4, 0x0F36E6F7,
    0x61C69362, 0x93AD1061, 0x80FDE395, 0x72966096, 0xA65C047D, 0x5437877E,
    0x4767748A, 0xB50CF789, 0xEB1FCBAD, 0x197448AE, 0x0A24BB5A, 0xF84F3859,
    0x2C855CB2, 0xDEEEDFB1, 0xCDBE2C45, 0x3FD5AF46, 0x7198540D, 0x83F3D70E,
    0x90A324FA, 0x62C8A7F9, 0xB602C312, 0x44694011, 0x5739B3E5, 0xA55230E6,
    0xFB410CC2, 0x092A8FC1, 0x1A7A7C35, 0xE811FF36, 0x3CDB9BDD, 0xCEB018DE,
    0xDDE0EB2A, 0x2F8B6829, 0x82F63B78, 0x709DB87B, 0x63CD4B8F, 0x91A6C88C,
    0x456CAC67, 0xB7072F64, 0xA457DC90, 0x563C5F93, 0x082F63B7, 0xFA44E0B4,
    0xE9141340, 0x1B7F9043, 0xCFB5F4A8, 0x3DDE77AB, 0x2E8E845F, 0xDCE5075C,
    0x92A8FC17, 0x60C37F14, 0x73938CE0, 0x81F80FE3, 0x55326B08, 0xA759E80B,
    0xB4091BFF, 0x466298FC, 0x1871A4D8, 0xEA1A27DB, 0xF94AD42F, 0x0B21572C,
    0xDFEB33C7, 0x2D80B0C4, 0x3ED04330, 0xCCBBC033, 0xA24BB5A6, 0x502036A5,
    0x4370C551, 0xB11B4652, 0x65D122B9, 0x97BAA1BA, 0x84EA524E, 0x7681D14D,
    0x2892ED69, 0xDAF96E6A, 0xC9A99D9E, 0x3BC21E9D, 0xEF087A76, 0x1D63F975,
    0x0E330A81, 0xFC588982, 0xB21572C9, 0x407EF1CA, 0x532E023E, 0xA145813D,
    0x758FE5D6, 0x87E466D5, 0x94B49521, 0x66DF1622, 0x38CC2A06, 0xCAA7A905,
    0xD9F75AF1, 0x2B9CD9F2, 0xFF56BD19, 0x0D3D3E1A, 0x1E6DCDEE, 0xEC064EED,
    0xC38D26C4, 0x31E6A5C7, 0x22B65633, 0xD0DDD530, 0x0417B1DB, 0xF67C32D8,
    0xE52CC12C, 0x1747422F, 0x49547E0B, 0xBB3FFD08, 0xA86F0EFC, 0x5A048DFF,
    0x8ECEE914, 0x7CA56A17, 0x6FF599E3, 0x9D9E1AE0, 0xD3D3E1AB, 0x21B862A8,
    0x32E8915C, 0xC083125F, 0x144976B4, 0xE622F5B7, 0xF5720643, 0x07198540,
    0x590AB964, 0xAB613A67, 0xB831C993, 0x4A5A4A90, 0x9E902E7B, 0x6CFBAD78,
    0x7FAB5E8C, 0x8DC0DD8F, 0xE330A81A, 0x115B2B19, 0x020BD8ED, 0xF0605BEE,
    0x24AA3F05, 0xD6C1BC06, 0xC5914FF2, 0x37FACCF1, 0x69E9F0D5, 0x9B8273D6,
    0x88D28022, 0x7AB90321, 0xAE7367CA, 0x5C18E4C9, 0x4F48173D, 0xBD23943E,
    0xF36E6F75, 0x0105EC76, 0x12551F82, 0xE03E9C81, 0x34F4F86A, 0xC69F7B69,
    0xD5CF889D, 0x27A40B9E, 0x79B737BA, 0x8BDCB4B9, 0x988C474D, 0x6AE7C44E,
    0xBE2DA0A5, 0x4C4623A6, 0x5F16D052, 0xAD7D5351,
};

/* manual computation of the crc32c checksum via a lookup table;
 * it is the slowest implementation out of the three; complexity = O(3.14N) */
uint32_t crc32c_lut_hword(uint8_t *buf, std::size_t length, uint32_t crc = -1) {
  while (length) {
    crc = crc32c_lut[(crc ^ *buf) & 0x000000FFL] ^ (crc >> 8);
    length -= 1;
    buf += 1;
  }

  return crc;
}

#else
#include <emmintrin.h>
#include <immintrin.h>
#include <nmmintrin.h>

/* computation via the SSE42 crc32 instruction;
 * pretty fast and works for all sizes; complexity = O(0.33N) */
uint32_t crc32c_sse_qword(uint8_t *buf, std::size_t length, uint64_t crc = -1) {
  /* align buffer so that it's
   * length is a multiple of 8*/
  if (length & (1 << 2)) {
    crc = _mm_crc32_u32(crc, *((uint32_t *)buf));
    buf += 4;
  }

  if (length & (1 << 1)) {
    crc = _mm_crc32_u16(crc, *((uint16_t *)buf));
    buf += 2;
  }

  if (length & (1 << 0)) {
    crc = _mm_crc32_u8(crc, *buf);
    buf += 1;
  }

  /* decrease the length by the number of bytes that
   * have been processed in the alignment step */
  length &= ~7;

  while (length) {
    crc = _mm_crc32_u64(crc, *((uint64_t *)buf));
    length -= 8;
    buf += 8;
  }

  return crc;
}

#ifdef ENABLE_PCLMULQDQ
/* every entry with an odd index is the second part of
 * the 128 bit value starting with the entry before it */
alignas(16) constexpr uint64_t pclmulqdq_lut[84] = {
    0x14cd00bd6, 0x105ec76f0, 0x0ba4fc28e, 0x14cd00bd6, 0x1d82c63da,
    0x0f20c0dfe, 0x09e4addf8, 0x0ba4fc28e, 0x039d3b296, 0x1384aa63a,
    0x102f9b8a2, 0x1d82c63da, 0x14237f5e6, 0x01c291d04, 0x00d3b6092,
    0x09e4addf8, 0x0c96cfdc0, 0x0740eef02, 0x18266e456, 0x039d3b296,
    0x0daece73e, 0x0083a6eec, 0x0ab7aff2a, 0x102f9b8a2, 0x1248ea574,
    0x1c1733996, 0x083348832, 0x14237f5e6, 0x12c743124, 0x02ad91c30,
    0x0b9e02b86, 0x00d3b6092, 0x018b33a4e, 0x06992cea2, 0x1b331e26a,
    0x0c96cfdc0, 0x17d35ba46, 0x07e908048, 0x1bf2e8b8a, 0x18266e456,
    0x1a3e0968a, 0x11ed1f9d8, 0x0ce7f39f4, 0x0daece73e, 0x061d82e56,
    0x0f1d0f55e, 0x0d270f1a2, 0x0ab7aff2a, 0x1c3f5f66c, 0x0a87ab8a8,
    0x12ed0daac, 0x1248ea574, 0x065863b64, 0x08462d800, 0x11eef4f8e,
    0x083348832, 0x1ee54f54c, 0x071d111a8, 0x0b3e32c28, 0x12c743124,
    0x0064f7f26, 0x0ffd852c6, 0x0dd7e3b0c, 0x0b9e02b86, 0x0f285651c,
    0x0dcb17aa4, 0x010746f3c, 0x018b33a4e, 0x1c24afea4, 0x0f37c5aee,
    0x0271d9844, 0x1b331e26a, 0x08e766a0c, 0x06051d5a2, 0x093a5f730,
    0x17d35ba46, 0x06cb08e5c, 0x11d5ca20e, 0x06b749fb2, 0x1bf2e8b8a,
    0x1167f94f2, 0x021f3d99c, 0x0cec3662e, 0x1a3e0968a,
};

/* computation is also facilitated via the crc32c instruction from SSE42
 * instruction set but here the crc32 instructions are pipelined which gives a
 * speed up of 0.25 cycles per byte when compared with the crc32c_sse_qword
 * method; the merging is done via carry less multiplcations which in turn done
 * using the PCLMULQDQ instructions; further note that this method only work
 * when the buffer has a length of 1024 bytes */
uint32_t crc32c_eq1024_pipelined_sse_qword(uint8_t *buf, uint64_t crc = -1) {
  uint64_t crc_a = crc;
  uint64_t crc_b = 0;
  uint64_t crc_c = 0;

  uint64_t *buf_a = (uint64_t *)(buf + 0 * 8 * 42);
  uint64_t *buf_b = (uint64_t *)(buf + 1 * 8 * 42);
  uint64_t *buf_c = (uint64_t *)(buf + 2 * 8 * 42);

  crc_a = _mm_crc32_u64(crc_a, *((uint64_t *)buf));

  for (std::size_t i = 1; i <= 42; ++i) {
    crc_a = _mm_crc32_u64(crc_a, buf_a[i]);
    crc_b = _mm_crc32_u64(crc_b, buf_b[i]);
    crc_c = _mm_crc32_u64(crc_c, buf_c[i]);
  }

  __m128i crc_a_xmm = _mm_loadu_si64(&crc_a);
  __m128i crc_b_xmm = _mm_loadu_si64(&crc_b);

  const __m128i factor = {0x0e417f38a, 0x08f158014};
  crc_a_xmm = _mm_clmulepi64_si128(crc_a_xmm, factor, 0x00);
  crc_b_xmm = _mm_clmulepi64_si128(crc_b_xmm, factor, 0x10);

  crc_c = _mm_crc32_u64(crc_c, *((uint64_t *)(buf + 1016)));

  _mm_storeu_si64(&crc_b, crc_b_xmm);
  crc_c ^= _mm_crc32_u64(0, crc_b);

  _mm_storeu_si64(&crc_a, crc_a_xmm);
  crc_c ^= _mm_crc32_u64(0, crc_a);

  return crc_c;
}

/* everything said for method above is true for this one except that this method
 * can operate on buffer lengths smaller or equal 1024 bytes but bigger than 24
 * bytes; note that for a buffer length of 1024 bytes the method above should be
 * preffered */
uint32_t crc32c_le1024_pipelined_sse_qword(uint8_t *buf, std::size_t length,
                                           uint64_t crc = -1) {
  std::size_t batch_length = (length * 2731) >> 16;

  uint64_t crc_a = crc;
  uint64_t crc_b = 0;
  uint64_t crc_c = 0;

  uint64_t *buf_a = (uint64_t *)(buf + 0 * 8 * batch_length);
  uint64_t *buf_b = (uint64_t *)(buf + 1 * 8 * batch_length);
  uint64_t *buf_c = (uint64_t *)(buf + 2 * 8 * batch_length);

  for (std::size_t i = 1; i < batch_length; ++i) {
    crc_a = _mm_crc32_u64(crc_a, *buf_a++);
    crc_b = _mm_crc32_u64(crc_b, *buf_b++);
    crc_c = _mm_crc32_u64(crc_c, *buf_c++);
  }

  crc_a = _mm_crc32_u64(crc_a, *buf_a);
  crc_b = _mm_crc32_u64(crc_b, *buf_b);

  __m128i factor_xmm =
      _mm_load_si128((__m128i *)(pclmulqdq_lut + (2 * batch_length - 2)));

  __m128i crc_a_xmm = _mm_loadu_si64(&crc_a);
  __m128i crc_b_xmm = _mm_loadu_si64(&crc_b);

  crc_a_xmm = _mm_clmulepi64_si128(crc_a_xmm, factor_xmm, 0x00);
  crc_b_xmm = _mm_clmulepi64_si128(crc_b_xmm, factor_xmm, 0x10);

  crc_a_xmm = _mm_xor_si128(crc_a_xmm, crc_b_xmm);
  _mm_storeu_si64(&crc_a, crc_a_xmm);

  crc_a ^= *buf_c;
  crc_c = _mm_crc32_u64(crc_c, crc_a);

  batch_length = length - 24 * batch_length;
  if (batch_length > 0) {
    crc_c = crc32c_sse_qword((uint8_t *)(buf_c + 1), batch_length, crc_c);
  }

  return crc_c;
}

/* combination of the above three methods to provide a method that handles
 * buffers of all sizes; complexity = O(0.19N) */
uint32_t crc32c_pcl(uint8_t *buf, std::size_t length, uint64_t crc = -1) {
  while (length >= 1024) {
    crc = crc32c_eq1024_pipelined_sse_qword(buf, crc);
    length -= 1024;
    buf += 1024;
  }

  if (length >= 24) {
    return crc32c_le1024_pipelined_sse_qword(buf, length, crc);
  } else if (length > 0) {
    return crc32c_sse_qword(buf, length, crc);
  } else {
    return crc;
  }
}
#endif
#endif

/* combination of all methods to have an crc32 implementation that works on all
 * architectues and can process buffers of arbitrary length*/
template <bool NEGATE_RESULT = false>
uint32_t crc32c(uint8_t *buf, std::size_t length) {
#ifdef ENABLE_SSE42
#ifdef ENABLE_PCLMULQDQ
  uint32_t crc = crc32c_pcl(buf, length);
#else
  uint32_t crc = crc32c_sse_qword(buf, length);
#endif
#else
  uint32_t crc = crc32c_lut_hword(buf, length);
#endif

  if (NEGATE_RESULT) {
    return ~crc;
  } else {
    return crc;
  }
}
#endif
