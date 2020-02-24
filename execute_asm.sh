#!/bin/bash

./bfc $1 -o $1.asm && nasm -felf64 -F dwarf $1.asm && gcc -no-pie $1.o -o $1.exe && ./$1.exe

