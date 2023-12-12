#!/bin/bash

# Initialize the output file
output_file="content.txt"

# Use find to locate all "*.c" files in the "sources" directory
find ./sources -name "*.c" -exec cat {} \; -exec echo -e '\n"\n"' \; > "$output_file"

echo "Contents of '*.c' files in the 'sources' directory have been concatenated and saved to $output_file."
