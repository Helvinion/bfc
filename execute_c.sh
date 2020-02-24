#!/bin/bash

./bfc -m c $1 -o $1.c && gcc $1.c -o $1.exe && ./$1.exe

