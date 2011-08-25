'''
Created on 16/08/2011

@author: david
'''
import cv

class ColorCorrelogram(object):
    '''
    classdocs
    '''


    def __init__(self,imageSrc):
        '''
        Constructor
        '''
        self.image = imageSrc
        
    def CalcCorrelogram(self):
        return 0
        
    def _calcPixelCounts(self,xPosition,yPosition,refColor,distance):
        # begin the calculation at distance d down to 1
        sum = 0
        for i in reversed(range(1,distance+1)):
            #need to calculate 4 difference lambda values
            # horizontal lambda values
            sum += self._lambdaH(xPosition-i,yPosition+i,2*i,refColor)
            sum += self._lambdaH(xPosition-i,yPosition-i,2*i,refColor)
            # vertical lambda values. Vertical can calculate
            # two less row values since already counted in the horizontal
            # count
            sum += self._lambdaV(xPosition-i,yPosition-i+1,2*i-2,refColor)
            sum += self._lambdaV(xPosition+i,yPosition-i+1,2*i-2,refColor)
        
        return sum

            
    def _calcPixelCountsRefactored(self,xPosition,yPosition,refColor,distance):
        # begin the calculation at distance d down to 1
        sum = 0
        for i in reversed(range(1,distance+1)):
            #need to calculate 4 difference lambda values
            
            # horizontal lambda values
            # check top right hand corner in image position
            sum += self._lambdaH(xPosition-i,yPosition+i,2*i,refColor)
            sum += self._lambdaH(xPosition-i,yPosition-i,2*i,refColor)
            # vertical lambda values. Vertical can calculate
            # two less row values since already counted in the horizontal
            # count
            sum += self._lambdaV(xPosition-i,yPosition-i+1,2*i-2,refColor)
            sum += self._lambdaV(xPosition+i,yPosition-i+1,2*i-2,refColor)
        
        return sum

    
    '''
    lambdaH: 
    Calculates the number of pixels with reference color in the horizontal
    row starting from (startX,startY) and ending at (startX+2k,startY)        
        @param self: 
        @param startX: start pixel to begin count from in x plane
        @param startY: start pixel to begin count from in y plane
        @param k: colour correlogram distance value
        @param refColor : reference colour to match to 
    @param colorJ:
    '''
    def _lambdaH(self,startX,startY,k,refColor):
        hsv = cv.CreateImage(cv.GetSize(self.image), 8, 3)
        cv.CvtColor(self.image, hsv, cv.CV_BGR2HSV)
        
        hSum = 0
        ''' 
        loop through getting all pixels from (startX,startY)
        through to (startX+2k,startY)    
        '''
        for i in range(0,(k)):
            # get image pixel value
            pixelValue = cv.Get2D(hsv, startX+i, startY)
            # compare H, S and V values with colorJ
            
            if refColor == pixelValue:
                hSum += 1
        return hSum
        
    '''
    lambdaH: 
    Calculates the number of pixels with reference color in the horizontal
    row starting from (startX,startY) and ending at (startX,startY+2k-2)        
        @param self: 
        @param startX: start pixel to begin count from in x plane
        @param startY: start pixel to begin count from in y plane
        @param k: colour correlogram distance value
        @param refColor : reference colour to match to 
    @param colorJ:
    '''
    def _lambdaV(self,startX,startY,k,refColor):
        hsv = cv.CreateImage(cv.GetSize(self.image), 8, 3)
        cv.CvtColor(self.image, hsv, cv.CV_BGR2HSV)
        
        vSum = 0
        ''' 
        loop through getting all pixels from (startX,startY)
        through to (startX+2k,startY)    
        '''
        for i in range(0,(k)):
            # get image pixel value
            pixelValue = cv.Get2D(hsv, startX, startY+i)
            # compare H, S and V values with colorJ
            
            if refColor == pixelValue:
                vSum += 1
        return vSum        
        
        
        