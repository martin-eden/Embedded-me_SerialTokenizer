#!/bin/bash

# Uninstall library
arduino-cli lib uninstall me_SerialTokenizer

# Uninstall dependencies
arduino-cli lib uninstall \
  me_InstallStandardStreams \
  me_UartSpeeds \
  me_Types
