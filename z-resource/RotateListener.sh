#!/bin/bash

warn () {
    echo "$0:" "$@" >&2
}
die () {
    rc=$1
    shift
    warn "$@"
    exit $rc
}

keyboardID=$(xinput --list | grep -m3 "keyboard" | tail -n1 | grep -o 'id=[0-9]\+' | grep -o '[0-9]\+')
echo $keyboardID;


STATE1=$(xinput --query-state $keyboardID | grep 'key\[' | sort)

ALLOWED=true;
while $ALLOWED == true; do
    sleep 0.2
    STATE2=$(xinput --query-state $keyboardID | grep 'key\[' | sort)
    comm -13 <(echo "$STATE1") <(echo "$STATE2")
    STATE1=$STATE2
done