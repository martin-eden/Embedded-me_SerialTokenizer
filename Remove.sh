#!/bin/bash

# Uninstall library
arduino-cli lib uninstall me_SerialTokenizer

# Uninstall dependencies
arduino-cli lib uninstall \
  me_Menu \
  me_List \
  me_Console \
  me_String \
  me_MemorySegment \
  me_Uart \
  me_UartSpeeds \
  me_BaseTypes
