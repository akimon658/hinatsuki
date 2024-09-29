#include "console.hpp"
#include "frame_buffer_config.hpp"
#include "graphics.hpp"
#include <cstdarg>
#include <cstdint>
#include <cstdio>
#include <new>

void operator delete(void *_) noexcept {}

char console_buf[sizeof(Console)];
Console *console;

int printk(const char *format, ...) {
  va_list ap;
  int result;
  char s[1024];

  va_start(ap, format);
  result = vsnprintf(s, sizeof(s), format, ap);
  va_end(ap);

  console->PutString(s);

  return result;
}

const int kMouseCursorWidth = 15;
const int kMouseCursorHeight = 24;
const char mouse_cursor_shape[kMouseCursorHeight][kMouseCursorWidth + 1] = {
    "@              ", "@@             ", "@.@            ", "@..@           ",
    "@...@          ", "@....@         ", "@.....@        ", "@......@       ",
    "@.......@      ", "@........@     ", "@.........@    ", "@..........@   ",
    "@...........@  ", "@............@ ", "@......@@@@@@@@", "@......@       ",
    "@....@@.@      ", "@...@ @.@      ", "@..@   @.@     ", "@.@    @.@     ",
    "@@      @.@    ", "@       @.@    ", "         @.@   ", "          @@   "};

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

  for (int dy = 0; dy < kMouseCursorHeight; dy++) {
    for (int dx = 0; dx < kMouseCursorWidth; dx++) {
      if (mouse_cursor_shape[dy][dx] == '@') {
        pixel_writer->Write(200 + dx, 100 + dy, {0, 0, 0});
      } else if (mouse_cursor_shape[dy][dx] == '.') {
        pixel_writer->Write(200 + dx, 100 + dy, {255, 255, 255});
      }
    }
  }

  console =
      new (console_buf) Console{*pixel_writer, {255, 255, 255}, {0, 0, 0}};

  printk("Successfully rendered the mouse cursor!\n");

  while (true) {
    __asm__("hlt");
  }
}
