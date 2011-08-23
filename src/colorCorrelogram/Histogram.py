'''
Created on 19/08/2011

@author: david
'''

import cv

class Histogram(object):
    '''
    classdocs
    '''
    
    def __init__(self,img):
        '''
        Constructor
        '''
        self._image = img
        
    def _DrawHistogram(self,hist,scaleX=1,scaleY=1,bins=255):
    #Get the max value to limit histogram plot
        (_, histMax, _, _) = cv.GetMinMaxHistValue(hist)
        
        # create container image
        imgHist = cv.CreateImage((256*scaleX,64*scaleY), 8 , 1)
        
        for i in range(0,bins-1):
            histValue = cv.QueryHistValue_1D(hist, i)
            nextValue = cv.QueryHistValue_1D(hist,i+1)

            pt1 = (i*scaleX,64*scaleY)
            pt2 = (i*scaleX+scaleX, 64*scaleY)
            pt3 = (i*scaleX+scaleX, (64-nextValue*64/histMax)*scaleY)
            pt4 = (i*scaleX, (64-histValue*64/histMax)*scaleY)
        
            numPoints = 5
            cv.FillConvexPoly(imgHist,[pt1,pt2,pt3,pt4,pt1],cv.Scalar(255))
            
        return imgHist

    def _PlotHist(self,img,title):
        cv.NamedWindow(title)
        cv.ShowImage(title,img)
        return None

    def _quantize(self,img):
        hist = self.HSVhistogram()
        
        hsv = cv.CreateImage(cv.GetSize(self._image), 8, 3)
        quantize = cv.CreateImage(cv.GetSize(self._image),8,3)
        
        
        
        
        return quantize
        
    def HSVhistogram(self):
        # Convert to HSV
        hsv = cv.CreateImage(cv.GetSize(self._image), 8, 3)
        cv.CvtColor(self._image, hsv, cv.CV_BGR2HSV)
    
        # Extract the H, S and V planes
        h_plane = cv.CreateMat(self._image.rows, self._image.cols, cv.CV_8UC1)
        s_plane = cv.CreateMat(self._image.rows, self._image.cols, cv.CV_8UC1)
        v_plane = cv.CreateMat(self._image.rows, self._image.cols, cv.CV_8UC1)
        cv.Split(hsv, h_plane, s_plane, v_plane, None)
        planes = [h_plane, s_plane, v_plane]
    
        h_bins = 18
        s_bins = 3
        v_bins = 3
        # h,s,v ranges (h=0,180 degress) others 255
        h_ranges = [0, 180]
        s_ranges = [0, 255]
        v_ranges = [0,255]
        ranges = [h_ranges, s_ranges, v_ranges]
        scale = 10
        # create histogram object for hsv planes
        hist = cv.CreateHist([h_bins, s_bins, v_bins], cv.CV_HIST_ARRAY, ranges, 1)
        # populate histogram
        cv.CalcHist([cv.GetImage(i) for i in planes], hist)
        (_, max_value, _, _) = cv.GetMinMaxHistValue(hist)
        # draw histogram onto image object    
        img = self._DrawHistogram(hist,4,4,162)
        
        return img



        