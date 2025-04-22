#!/bin/bash
set -e

# https://rdkcentral.github.io/Thunder/introduction/build_linux/

sudo sudo apt install build-essential pkg-config cmake ninja-build libusb-1.0-0-dev zlib1g-dev libssl-dev

pip install --break-system-packages jsonref

git clone https://github.com/rdkcentral/ThunderTools.git

cmake -G Ninja -S ThunderTools -B build/ThunderTools -DCMAKE_INSTALL_PREFIX="install"

cmake --build build/ThunderTools --target install

git clone https://github.com/rdkcentral/Thunder.git

cmake -G Ninja -S Thunder -B build/Thunder \
-DBINDING="127.0.0.1" \
-DCMAKE_BUILD_TYPE="Debug" \
-DCMAKE_INSTALL_PREFIX="install" \
-DPORT="55555" \
-DTOOLS_SYSROOT="${PWD}" \
-DINITV_SCRIPT=OFF

cmake --build build/Thunder --target install

git clone https://github.com/rdkcentral/ThunderInterfaces.git

cmake -G Ninja -S ThunderInterfaces -B build/ThunderInterfaces \
-DCMAKE_INSTALL_PREFIX="install"

cmake --build build/ThunderInterfaces --target install
