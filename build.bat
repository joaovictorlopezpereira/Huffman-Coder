@echo off

set SRC_DIR=src
set OUTPUT_FILE=huffman.exe

gcc %SRC_DIR%\main.c -o %OUTPUT_FILE% -Wall