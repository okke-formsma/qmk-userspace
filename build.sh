#!/bin/sh
# Build the Ferris firmware in Docker. Expects qmk_firmware next to this repo.
set -e
cd "$(dirname "$0")"
docker run --rm \
  -v "$PWD/../qmk_firmware":/qmk_firmware \
  -v "$PWD":/qmk_userspace \
  -e QMK_USERSPACE=/qmk_userspace \
  -w /qmk_firmware \
  ghcr.io/qmk/qmk_cli \
  qmk compile -kb ferris/0_1 -km okke
