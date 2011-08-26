'''
Created on 16/08/2011

@author: david
'''
import unittest
import cv
import ColorCorrelogram
import Histogram
from opencv import highgui
import cProfile

class Test(unittest.TestCase):


    def setUp(self):
        pass


    def tearDown(self):
        pass


    def testRunCorrelogram(self):
        imagePath = '../TestFiles/jackiechansmall.jpeg'
        src = cv.LoadImageM(imagePath)
        
        hist = Histogram.Histogram(src)
        img = hist.HSVhistogram()
        
        quantized = hist._quantize()
         

        cv.NamedWindow('hist')
        #quantize = hist._quantize(src)
        #cv.Save('quantized.jpg', quantize)
        #while(1):
        #    cv.ShowImage('hist', img)
                
        testPixel = cv.Scalar(0,0,0)
        print cv.GetSize(src)
        
        for i in range(cv.GetSize(quantized)[1]):
            for j in range(cv.GetSize(quantized)[0]):
                print cv.Get2D(quantized, j, i)
        #print c._lambdaH(cv.GetSize(src)[0]-1, cv.GetSize(src)[1]-1, 3, testPixel)
        #print c._calcPixelCounts(9,9,testPixel,3)
        c = ColorCorrelogram.ColorCorrelogram(quantized)
        d =  c._calcPixelsCount(1)
        c._drawCorrelogram(d)
        print d 
        
        pass
'''
    def testProfileCode(self):
        imagePath = '../TestFiles/black.jpg'
        src = cv.LoadImageM(imagePath)
        c = ColorCorrelogram.ColorCorrelogram(src)
        testPixel = cv.Scalar(0,0,0)
        print c._lambdaH(49, 49, 3, testPixel)
        
        print c._calcPixelsCount(1)
'''
if __name__ == "__main__":
    #import sys;sys.argv = ['', 'Test.testName']
    highgui.cvStartWindowThread()
    unittest.main()
    