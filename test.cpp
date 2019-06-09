#include <cstring>
#include <gtest/gtest.h>

#include "tinycrc32.h"

class CRC32Test : public testing::Test {
public:
  /* foreach row of a 256x256 matrix the crc value is computed and compared with
   * the respective value below; the matrix is defined to be m_{i, j} = j > i ?
   * 0 : (j - 1) */
  const uint32_t expected_result[256] = {
      0x00000000, 0x527d5351, 0x030af4d1, 0x92fd4bfa, 0xd9331aa3, 0x2425b106,
      0x41098514, 0xa359ed4c, 0x8a2cbc3b, 0x7144c5a8, 0x022c2131, 0xfb159dfa,
      0x5383aaba, 0xc69a45da, 0x55a24c54, 0x68ef03f6, 0xd9c908eb, 0x38435e17,
      0x74e4f7e7, 0x9496cccf, 0xcc79ebe6, 0x40e43538, 0xcda87569, 0x7d3b930d,
      0x29bc8795, 0x6f8a987d, 0xf44eddb4, 0x5cba170d, 0x64dec9c1, 0x3ee220e0,
      0x1e0592d7, 0xe95cabcb, 0x46dd794e, 0x9f85a26d, 0x5eda049f, 0x5f1eb74f,
      0x7ea71154, 0x239ba04d, 0xb941035c, 0x48be6e67, 0x134ef083, 0x69ac033c,
      0x77bb2c21, 0xcb834346, 0x8c580fa3, 0x8e140c02, 0x2c5df5a7, 0xa815ee10,
      0x3c25332a, 0x29fd9935, 0x95ce39d7, 0x8429216e, 0xbcf4ec70, 0xd4202d1e,
      0xeb9d5699, 0xaece4785, 0x01fd9f28, 0x422269a1, 0x4a4ed5e0, 0xea06d417,
      0x3f69148b, 0x349d2c67, 0x688e3c96, 0x7a873004, 0xfb6d36eb, 0x694420fa,
      0x7988ce83, 0x63e27e58, 0xdbc9dd7b, 0x3c56ef19, 0x4e2710bd, 0x38d4b00f,
      0x99e7c292, 0xead57d00, 0x6b5e405c, 0x64e92d96, 0x3ee21704, 0x99e1f435,
      0xa9a5be67, 0x0adba3fd, 0x01598acc, 0x8d97391c, 0xaca39507, 0x36053e0b,
      0x89b7d473, 0xa6830eb0, 0x841a6c59, 0x0cea7519, 0xbf721bbf, 0x6538edbb,
      0x5013b351, 0xcba4ebd9, 0x317bbc35, 0x4b386043, 0xee101379, 0xa6e4a977,
      0xf8bf61e9, 0xa8c10c84, 0x84142e5b, 0x1aa8d502, 0xc1caebe5, 0x222121c1,
      0x378e50c9, 0xae125483, 0x76797e00, 0xb914e182, 0x287d4491, 0x38b2ea5b,
      0x62a6a80a, 0x15788173, 0xee4e5398, 0x875c959f, 0xa19460b1, 0x633a62f6,
      0x042236a0, 0x6091e03b, 0x99bf87c2, 0xc65079f7, 0x317648a7, 0x73f447b1,
      0xb722663a, 0xf28a1c7c, 0x677ecd51, 0xeb2e0879, 0xb3ad0dae, 0x60266f00,
      0x9cad6de0, 0x6c31bd0c, 0x30d9c515, 0xf514629f, 0xeeae3f7b, 0xd94f49d7,
      0xc41b51d4, 0x039c92d3, 0x25faf2f8, 0x8fb84289, 0xfe8a5434, 0xadd5641c,
      0xf5896e3e, 0x27073fe9, 0xd2a7b7fb, 0xf7fdc400, 0x6f54d93e, 0xe0077541,
      0x3d68cdc7, 0xd7af85a4, 0x57b8a179, 0x2893e8d1, 0xf215adf2, 0x15e83276,
      0xa208e08d, 0xdb0837e5, 0xc2057f9c, 0x9525c131, 0x7a7a9bf9, 0x2091495c,
      0x451a8037, 0x69fa574c, 0x73accbae, 0x62edb62b, 0x27905b31, 0x3299bc1e,
      0xbe498400, 0x11b3df84, 0xa61b0abb, 0x1c96b310, 0xd585a337, 0x326ba9e6,
      0xe15fa647, 0xefbf98c9, 0x33547fab, 0xa025842d, 0xf68aaa45, 0xc909aa2d,
      0xd0426183, 0xcd38d33d, 0x2123e762, 0x60b4e1ea, 0x9ab19658, 0xda3562e5,
      0x25235b08, 0xad0ecd13, 0xd63a0fd2, 0xf4f76d23, 0x07bbcf34, 0x9dcf1c36,
      0x8e059b11, 0x69314857, 0xfc6705d3, 0x6d549b12, 0xae488e48, 0x871c9342,
      0x1ebc6c64, 0x37b2cd84, 0x26c0e83c, 0x0d4d43eb, 0xf814c803, 0x45c205b6,
      0x30f036ad, 0xaa029b3e, 0xd90be573, 0x79388146, 0x8ee16c8c, 0x35294869,
      0x1138bf48, 0x1700c789, 0xd48bd935, 0x384e1cc6, 0x2af7c681, 0xf119fd47,
      0xe6855153, 0x22066e7b, 0x7acdb856, 0x31cad566, 0xf30918b9, 0x6d5bf50f,
      0x0b1ab1c0, 0xc8f1d640, 0xb8af855c, 0xf6922044, 0x9e300142, 0x6c332060,
      0x5f2c5e6b, 0xd5c619da, 0x67598154, 0x2795ef06, 0x65a00a4f, 0x4f7b0a2e,
      0x2e97424c, 0x7ac1297a, 0x9ebc524b, 0x4f801676, 0x32f1ac53, 0x79d37b0f,
      0x9795cfd8, 0x8332ffd8, 0x714ddbeb, 0x86c67a61, 0x9d4e6183, 0x8c0ec281,
      0x9f4f71d6, 0x54fe7516, 0x65d361d5, 0xa66f6a05, 0x8714b4a6, 0xe2e4edc1,
      0xa5e66912, 0x76728a3d, 0xfa642f27, 0xdf47eaf1, 0xd87b4c74, 0x7c2bac42,
      0x98a6d1f8, 0x957f629f, 0xd215cfa6, 0x8953c482,
  };
};

TEST_F(CRC32Test, main_test) {
  uint8_t *data = new uint8_t[256];
  std::memset(data, 0, 256);

  for (uint8_t i = 0; i <= 254; ++i) {
    data[i] = i;
    EXPECT_EQ(crc32c(data, i), expected_result[i]);
  }

  data[255] = 255;
  EXPECT_EQ(crc32c(data, 255), expected_result[255]);

  delete[] data;
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
