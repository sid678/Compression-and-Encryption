import sys
import cv2

n = sys.argv[1]
n = int(n)
# print(n)

if n == 1:
    print("Enter name of image from local system with right path to be compressed or encrypted")
    name = input()
    img = cv2.imread(name,cv2.IMREAD_GRAYSCALE)
    print(img)
    print(len(img))
    print(len(img[0]))

    file1 = open("MyFile.txt","w")

    file1.write(str(len(img))+"\n")
    file1.write(str(len(img[0]))+"\n")

    for i in range(len(img)):
        for j in range(len(img[0])):
            file1.write(str(img[i][j])+" ")
        file1.write("\n")
    file1.close()

else:
    print("Enter message to be compressed or encrypted")
    name = input()
    print(name)
    file1 = open("MyFile.txt","w")
    file1.write(str(1)+"\n")
    file1.write(str(len(name))+"\n")
    for i in name:
        file1.write(str(ord(i))+" ")
