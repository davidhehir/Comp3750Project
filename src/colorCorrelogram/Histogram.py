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


        
        
    def _createHSVHistogramArray(self,src):
        hsv = cv.CreateImage(cv.GetSize(src), 8, 3)
        cv.CvtColor(self._image, hsv, cv.CV_BGR2HSV)
        #h = cv.CreateImage(cv.GetSize(src),8,1)
        #s = cv.CreateImage(cv.GetSize(src),8,1)
        #v = cv.CreateImage(cv.GetSize(src),8,1)
                # Extract the H, S and V planes
        h = cv.CreateMat(cv.GetSize(hsv)[1], cv.GetSize(hsv)[0], cv.CV_8UC1)
        s = cv.CreateMat(cv.GetSize(hsv)[1], cv.GetSize(hsv)[0], cv.CV_8UC1)
        v = cv.CreateMat(cv.GetSize(hsv)[1], cv.GetSize(hsv)[0], cv.CV_8UC1)
        
        cv.Split(hsv, h, s, v, None)
        planes = [h, s, v]
        
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
        
        histH = cv.CreateHist([h_bins], cv.CV_HIST_ARRAY, h_ranges, 1)
        cv.CalcHist([cv.GetImage(h)], histH)
        back_projectH = cv.CreateImage(cv.GetSize(src), 8, 1)
        
        cv.CalcBackProject([cv.GetImage(h)], back_projectH, histH)
        
        histS = cv.CreateHist([s_bins], cv.CV_HIST_ARRAY, s_ranges, 1)
        cv.CalcHist([cv.GetImage(s)], histS)
        back_projectS = cv.CreateImage(cv.GetSize(src), 8, 1)
        cv.CalcBackProject([cv.GetImage(s)], back_projectS, histS)
        
        histV = cv.CreateHist([v_bins], cv.CV_HIST_ARRAY, v_ranges, 1)
        cv.CalcHist([cv.GetImage(v)], histV)
        back_projectV = cv.CreateImage(cv.GetSize(src), 8, 1)
        cv.CalcBackProject([cv.GetImage(v)], back_projectV, histV)
        
        
        # populate histogram
        
        
        cv.SaveImage('../TestFiles/h.jpg', back_projectH)
        cv.SaveImage('../TestFiles/s.jpg', back_projectS)
        cv.SaveImage('../TestFiles/v.jpg', back_projectV)
        
        QuantizedImage = cv.CreateImage(cv.GetSize(src),8,3)
        cv.Merge(back_projectH, None, None, None, QuantizedImage)
        img = cv.CreateImage(cv.GetSize(src), 8, 3)
        cv.CvtColor(QuantizedImage, img, cv.CV_HSV2BGR)
        return img

    def _quantize(self):
                # Convert to HSV
        hsv = cv.CreateImage(cv.GetSize(self._image), 8, 3)
        
        hsv_quantized = cv.CreateImage(cv.GetSize(self._image),8,3)
        cv.CvtColor(self._image, hsv, cv.CV_BGR2HSV)
        cv.SaveImage('../TestFiles/quant1.jpg', hsv) 
        h_range = [0,180]
        h_interval = h_range[1]/18
        s_range = [0,255]
        s_interval = s_range[1]/3
        v_range = [0,255]
        v_interval = v_range[1]/3
        
        for i in range(cv.GetSize(self._image)[1]):
            for j in range(cv.GetSize(self._image)[0]):
                pix = cv.Get2D(hsv, i, j)
                # Quantize Hue:
                h_val = self._quantizePixel(pix[0], h_interval)
                s_val = self._quantizePixel(pix[1], s_interval)
                v_val = self._quantizePixel(pix[2], v_interval)
                newPix = cv.Scalar(h_val,s_val,v_val)
                cv.Set2D(hsv, i, j, newPix)
        cv.CvtColor(hsv, hsv_quantized, cv.CV_HSV2BGR)
        cv.SaveImage('../TestFiles/quant.jpg', hsv_quantized)        
        
        return hsv_quantized
        
    def _quantizePixel(self,pixelValue,interval):
        if pixelValue % interval > interval /2:
            newPix = interval * (pixelValue/interval+1)
        else:
            newPix = interval * (pixelValue/interval)
        return newPix    
            
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



        