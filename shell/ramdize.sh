#!/bin/bash

set -e -u

ram_disk="/Volumes/RAMDisk"
out_dirs=`find ./ -type d -name obj -or -name bin`

for f in $out_dirs
do
    mfrom=$f
    mto="$ram_disk/"
    echo "Moving  $mfrom to $mto"
    mv -f $mfrom $mto
    lfrom="$mto/$f"
    lto=$f
    echo "Linking $lfrom to $lto"
    ln -s $lfrom $lto
done

