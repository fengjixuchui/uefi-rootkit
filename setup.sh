#!/bin/bash

SCRIPT_DIR=$(cd $(dirname "${BASH_SOURCE[0]}") && pwd)
EDK2_PATH=$SCRIPT_DIR/deps/edk2

export WORKSPACE=$SCRIPT_DIR
export PACKAGES_PATH=$SCRIPT_DIR/src/:$EDK2_PATH:$SCRIPT_DIR/deps/ntfs-3g
export PATH=$PATH:$EDK2_PATH

. edksetup.sh