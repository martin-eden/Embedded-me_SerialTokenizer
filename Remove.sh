#!/bin/bash

# Uninstall library
arduino-cli lib uninstall me_SerialTokenizer

# Uninstall dependencies
arduino-cli lib uninstall \
  me_MemorySegment \
  me_InstallStandardStreams \
  me_UartSpeeds \
  me_BaseTypes
