#!/bin/bash

MOUSE_ID=$(xinput --list | grep -i -m 1 'mouse' | grep -o 'id=[0-9]\+' | grep -o '[0-9]\+')

STATE1=$(xinput --query-state $MOUSE_ID | grep 'button\[' | sort)
ALLOWED=true;
while $ALLOWED == true; do
    sleep 0.2
    STATE2=$(xinput --query-state $MOUSE_ID | grep 'button\[' | sort)
    comm <(echo "$STATE1") <(echo "$STATE2")
    STATE1=$STATE2
done