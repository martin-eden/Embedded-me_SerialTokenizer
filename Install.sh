#!/bin/bash

# Install dependencies
arduino-cli \
  lib install \
    --git-url \
      https://github.com/martin-eden/Embedded-me_BaseTypes \
      https://github.com/martin-eden/Embedded-me_UartSpeeds \
      https://github.com/martin-eden/Embedded-me_Uart \
      https://github.com/martin-eden/Embedded-me_MemorySegment \
      https://github.com/martin-eden/Embedded-me_String \
      https://github.com/martin-eden/Embedded-me_Console \
      https://github.com/martin-eden/Embedded-me_List \
      https://github.com/martin-eden/Embedded-me_Menu

# Install library
arduino-cli \
  lib install \
    --git-url \
      https://github.com/martin-eden/Embedded-me_SerialTokenizer
