#!/bin/bash
echo "Input 1 for image and anything else for message"
read var1
python3.8 image.py $var1
echo "Type Yes to compress and anything else to encrypt"
read var2
if [ $var2 == "Yes" ]
then 
    # python3.8 image.py 
    g++-11 huffman.cpp
    ./a.out
else
    # python3.8 image.py 
    python mhkc.py var1
fi

