import cv2
import numpy as np
def dither(img, ditherm,levels):
    levels-=1
    imgdims=(len(img),len(img[0]),len(img[0,0]))
    #vals=np.zeros((len(img)+len(ditherm),len(img[0])+len(ditherm[-1]),len(img[0,0])),dtype=np.float64)
    for y in range(imgdims[0]):
        print(y)
        for x in range(imgdims[1]):
            for c in range(imgdims[2]):
                
                fin=round((img[y,x,c])*(levels/255))*255/levels#+vals[y,x,c]
                err=img[y,x,c]-fin
                img[y,x,c]=fin
                for i in filter(lambda i:y+i<imgdims[0] and y+i>=0,range(len(ditherm))):
                    for j in filter(lambda j:x+j-(len(ditherm[i])//2)>=0 and x+j-(len(ditherm[i])//2)<imgdims[1],range(len(ditherm[i]))):
                        
                        img[y+i,x+j-(len(ditherm[i])//2),c]+=err*ditherm[i][j]
    return img.astype(np.uint8)
##def randomdither(img,levels):
##    
##    imgdims=(len(img0),len(img0[0]),len(img0[0,0]))
##    vals=np.zeros(imgdims,dtype=np.uint8)
##    for y in range
if __name__ == '__main__':  
    windowName = "Displayed Image" # window name
    ditherm=[[0,0,7/16],
             [3/16,5/16,1/16]]
    img = cv2.imread('mountain.jpg', cv2.IMREAD_COLOR).astype(np.float64)#_GRAYSCALE
##    img2=np.ndarray(shape=(len(img),len(img[0]),1))
##    for y in range(len(img)):
##        for x in range(len(img)):
##            img2[y,x]=[img[y,x]]
    cv2.imwrite('mountain.png',dither(img,ditherm,2))
    
    print('done')

