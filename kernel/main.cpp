#include "font.hpp"
#include "frame_buffer_config.hpp"
#include "graphics.hpp"
#include <cstdint>
#include <cstdio>
#include <new>

void operator delete(void *_) noexcept {}

extern "C" void KernelMain(const FrameBufferConfig &frame_buffer_config) {
  char pixel_writer_buf[sizeof(RGBResv8BitPerColorPixelWriter)];
  PixelWriter *pixel_writer;

  switch (frame_buffer_config.pixel_format) {
  case kPixelRGBResv8BitPerColor:
    pixel_writer = new (pixel_writer_buf)
        RGBResv8BitPerColorPixelWriter{frame_buffer_config};
    break;

  case kPixelBGRResv8BitPerColor:
    pixel_writer = new (pixel_writer_buf)
        BGRResv8BitPerColorPixelWriter{frame_buffer_config};
    break;
  }

  for (uint32_t x = 0; x < frame_buffer_config.horizontal_resolution; x++) {
    for (uint32_t y = 0; y < frame_buffer_config.vertical_resolution; y++) {
      pixel_writer->Write(x, y, {0, 0, 0});
    }
  }

  int i = 0;
  for (char c = '!'; c <= '~'; ++i, ++c) {
    WriteAscii(*pixel_writer, 50 + i * 8, 50, c, {255, 255, 255});
  }

  WriteString(*pixel_writer, 50, 66, "Hello World!", {255, 255, 0});

  char buf[128];
  snprintf(buf, 128, "1 + 2 = %d", 1 + 2);
  WriteString(*pixel_writer, 50, 82, buf, {255, 0, 0});

  while (true) {
    __asm__("hlt");
  }
}
