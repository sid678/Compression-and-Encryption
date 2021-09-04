#!/bin/bash
read var
if [ $var == "Yes" ]
then
    g++-11 huffman.cpp
    ./a.out
else
    python mhkc.py
fi

