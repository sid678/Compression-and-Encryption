import random

maxChar = 640

def gcd(a,b):

    if a>b:
        swap(a,b)
    if a==0:
        return b
    
    return gcd(b%a,a)


def modInv(a,m):

    rOld = a
    rNew = m
    sOld = 1
    sNew = 0

    while rNew!=0:

        q = rOld/rNew
        temp = rNew
        rNew = rOld - q*rNew
        rOld = temp
        temp = sNew
        sNew = sOld - q*sNew
        sOld = temp

    return (sOld+m)%m


def generatePrivateKey():

    wPrivate = [0]*maxChar
    for i in range(maxChar):
        wPrivate[i] = random.randint(1,101)
    
    for i in range(1,maxChar):
        wPrivate[i] = wPrivate[i] + 2*wPrivate[i-1]

    qPrivate = 2*wPrivate[maxChar - 1] + random.randint(1,10000)
    
    rPrivate = random.randint(1,qPrivate)

    while gcd(rPrivate,qPrivate)!=1:
        rPrivate = random.randint(1,qPrivate)
    
    return wPrivate,rPrivate,qPrivate


def generatePublicKey(wPrivate,rPrivate,qPrivate):
    
    publicKey = [0]*maxChar

    for i in range(0,maxChar):
        publicKey[i] = (rPrivate*wPrivate[i])%qPrivate

    return publicKey


def decimalToBinary(n):

    bits = [0]*8
    for i in range(8):
        if ((1<<i)&n):
            bits[7-i] = 1
        else:
            bits[7-i] = 0
    
    return bits


def stringToBinary(sentence,param):

    l = len(sentence)
    bits = [0]*(maxChar - 8*l)
    for i in range(l):
        if param == 1:
            asciiv = ord(sentence[i])
            bits.extend(decimalToBinary(asciiv))
        else:
            bits.extend(decimalToBinary(sentence[i]))


    return bits


def binaryToMessage(decipher):

    message = ""
    l = len(decipher)
    var = 0
    for i in range(l):

        if i%8==0:
            if var !=0:
                message = message + (chr(var))
            var = 0
        var = 2*var + decipher[i]

    if var !=0:
        message = message + (chr(var))

    return message

def binaryToImage(decipher):

    imgRow = []
    l = len(decipher)
    var = 0
    for i in range(l):

        if i%8==0:
            if var !=0:
                imgRow.append(var)
            var = 0
        var = 2*var + decipher[i]

    if var !=0:
        imgRow.append(var)

    return imgRow


def encrpyt(sentence,publicKey,param):

    bits = stringToBinary(sentence,param)

    cipher = 0
    for i in range(maxChar ):
        cipher = cipher + bits[i]*publicKey[i]

    return cipher,bits

def decrypt(cipher,rInv,w,q):

    cInv = (cipher*rInv)%q

    decipher = [0]*maxChar 
    i = maxChar - 1
    while cInv>0 and i>=0:

        if cInv - w[i]>=0:

            cInv = cInv - w[i]
            decipher[i] = 1
        i = i-1
    
    return decipher


wPrivate,rPrivate,qPrivate = generatePrivateKey()
publicKey = generatePublicKey(wPrivate,rPrivate,qPrivate)
rInv = modInv(rPrivate,qPrivate)
# inp = raw_input()

param = 1
n=1
if n==1:

    inp = "yo"
    cipher, bits = encrpyt(inp,publicKey,param)
    decipher = decrypt(cipher,rInv,wPrivate,qPrivate)
    print(cipher)
    print(binaryToMessage(decipher))

else:

    img = [[1,2,3,4,5,6,7],[2,3,4,5,6,7,8]]
    cipherList = []
    decipherList = []
    for row in img:
        cipher, bits = encrpyt(row,publicKey,param)
        cipherList.append(cipher)
    for cipher in cipherList:
        decipher = decrypt(cipher,rInv,wPrivate,qPrivate)
        decipherList.append(decipher)
    for cipher in cipherList:
        print(cipher)
    for decipher in decipherList:
        print(binaryToImage(decipher))
