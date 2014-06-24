#!/bin/bash
# This is a script for measuring the time of the command execution

START=$(date +%s.%N)
#put your commands here
END=$(date +%s.%N)
DIFF=$(echo "$END-$START"|bc)
echo "$DIFF s"
