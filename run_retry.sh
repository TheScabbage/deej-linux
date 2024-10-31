#!/usr/bin/env bash
RETRY=1
./pkg/deej/scripts/linux/build-dev.sh
while [ $RETRY ]; do
    ./deej-dev
    sleep 1.0
    RETRY=$?
done
