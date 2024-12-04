#!/bin/bash

clear

# Compile the C program
gcc ./day$1/main.c ./common/*.c -o "./day$1/out"

# Check if compilation succeeded
if [ $? -eq 0 ]; then
     time "./day$1/out"  # Execute the compiled program
else
    echo "Compilation failed."
fi
