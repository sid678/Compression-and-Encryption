#!/bin/bash
python3.8 image.py 
echo "Type Yes to compress and anything else to encrypt"
read var
if [ $var == "Yes" ]
then 
    # python3.8 image.py 
    g++-11 huffman.cpp
    ./a.out
else
    # python3.8 image.py 
    python mhkc.py
fi

