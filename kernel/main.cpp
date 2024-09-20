#include "frame_buffer_config.hpp"
#include <cstdint>

struct PixelColor {
  uint8_t r, g, b;
};

int WritePixel(const FrameBufferConfig &config, int x, int y,
               const PixelColor &c) {
  const int pixel_position = config.pixels_per_scan_line * y + x;
  uint8_t *p = &config.frame_buffer[4 * pixel_position];

  switch (config.pixel_format) {
  case kPixelRGBResv8BitPerColor:
    p[0] = c.r;
    p[1] = c.g;
    p[2] = c.b;
    break;
  case kPixelBGRResv8BitPerColor:
    p[0] = c.b;
    p[1] = c.g;
    p[2] = c.r;
    break;
  default:
    return -1;
  }

  return 0;
}

extern "C" void KernelMain(const FrameBufferConfig &frame_buffer_config) {
  for (uint32_t x = 0; x < frame_buffer_config.horizontal_resolution; x++) {
    for (uint32_t y = 0; y < frame_buffer_config.vertical_resolution; y++) {
      WritePixel(frame_buffer_config, x, y, {255, 255, 255});
    }
  }

  for (int x = 0; x < 200; x++) {
    for (int y = 0; y < 100; y++) {
      WritePixel(frame_buffer_config, 100 + x, 100 + y, {0, 0, 255});
    }
  }

  while (true) {
    __asm__("hlt");
  }
}
