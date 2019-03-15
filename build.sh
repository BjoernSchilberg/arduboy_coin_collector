#!/bin/bash

ARDUINO_DIR="/opt/arduino-1.8.8"
SKETCH_DIR=$PWD
SKETCH_FILE="coin_collector.ino"
LIBRARY_DIR="$HOME/Arduino/libraries"

clear; clear;

mkdir -p "$SKETCH_DIR/build"

cd "$ARDUINO_DIR"
./arduino-builder -hardware ./hardware -tools ./hardware/tools/avr -tools ./tools-builder -libraries ./libraries -libraries "$LIBRARY_DIR" -build-path "$SKETCH_DIR/build" -fqbn arduino:avr:leonardo "$SKETCH_DIR/$SKETCH_FILE"

if [ $? -eq 0 ]; then
  sim_arduboy -p 128x64 "$SKETCH_DIR/build/$SKETCH_FILE.hex"
fi
