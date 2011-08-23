'''
Created on 23/08/2011

@author: david
'''
import ColorCorrelogram
import cv

if __name__ == '__main__':
    imagePath = '../TestFiles/black.jpg'
    src = cv.LoadImageM(imagePath)
    c = ColorCorrelogram.ColorCorrelogram(src)
    print c._calcPixelsCount(1) 