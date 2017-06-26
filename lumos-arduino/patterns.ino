void setSolidColor(uint32_t color) {
  for (int i = 0; i < strip.numPixels(); ++i) {
    strip.setPixelColor(i, color);
  }
}

void setGradient(int count, ...) {
  if (count < 2 || count > 20) {
    return;
  }
  
  int segmentSize = strip.numPixels() / (count - 1);

  // Declare a va_list macro and initialize it with va_start.
  va_list argList;
  va_start(argList, count);

  int index = 0;
  
  uint32_t prevColor = va_arg(argList, uint32_t);;
  count--;
  for (; count > 0; count--) {
    uint32_t nextColor = va_arg(argList, uint32_t);
    for (int i = 0; i < segmentSize; i++) {
      strip.setPixelColor(index++, blend(prevColor, nextColor, 100 * i / (segmentSize - 1)));
    }

    strip.show();
    prevColor = nextColor;
  }

  va_end(argList);
}

