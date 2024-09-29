#include "console.hpp"
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

  Console console{*pixel_writer, {255, 255, 255}, {0, 0, 0}};

  char buf[128];
  for (int i = 0; i < 26; i++) {
    snprintf(buf, 128, "line %d\n", i);
    console.PutString(buf);
  }

  while (true) {
    __asm__("hlt");
  }
}
