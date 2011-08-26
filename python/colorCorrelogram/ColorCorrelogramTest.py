'''
Created on 16/08/2011

@author: david
'''
import unittest
import cv
import ColorCorrelogram
class Test(unittest.TestCase):


    def setUp(self):
        pass


    def tearDown(self):
        pass


    def testRunCorrelogram(self):
        imagePath = '../TestFiles/black.jpg'
        src = cv.LoadImageM(imagePath)
        c = ColorCorrelogram.ColorCorrelogram(src)
        testPixel = cv.Scalar(0,0,0)
        
        c._lambdaH(0, 0, 10, testPixel)
        print c._calcPixelCounts(10,10,testPixel,5)
        pass

if __name__ == "__main__":
    #import sys;sys.argv = ['', 'Test.testName']
    unittest.main()
    