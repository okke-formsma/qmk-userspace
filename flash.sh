#!/bin/sh
# Flash the Ferris 0.1 (ATmega32u4, atmel-dfu). Press its reset button (or
# hold Z/slash + Q for QK_BOOT) after starting this.
set -e
cd "$(dirname "$0")"
HEX=${1:-ferris_0_1_okke.hex}
printf "Waiting for the Ferris bootloader (press reset)"
until dfu-programmer atmega32u4 get bootloader-version >/dev/null 2>&1; do sleep 1; printf "."; done
echo
dfu-programmer atmega32u4 erase --force
dfu-programmer atmega32u4 flash "$HEX"
dfu-programmer atmega32u4 launch --no-reset 2>/dev/null || dfu-programmer atmega32u4 reset
echo "Flashed $HEX"
