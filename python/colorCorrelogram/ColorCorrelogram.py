'''
Created on 16/08/2011

@author: david
'''
import cv
import Histogram

class ColorCorrelogram(object):
    '''
    classdocs
    '''


    def __init__(self,imageSrc):
        '''
        Constructor
        '''
        self.image = imageSrc
        self.hsv = cv.CreateImage(cv.GetSize(self.image), 8, 3)
        cv.CvtColor(self.image, self.hsv, cv.CV_BGR2HSV)
       
        
    def CalcCorrelogram(self):
        return 0
    
        
    def _calcPixelsCount(self,distance):
        width = cv.GetSize(self.image)[0]
        height = cv.GetSize(self.image)[1]
        
        
        # define matrix for pixelCount
        pixelCount = []

        for i in range(height):
            tmpRow = []
            for j in range(width):
                tmpRow.append(0)
            pixelCount.append(tmpRow)
        
        for i in range(height):
            for j in range(width):
                #Get referenceColour
                refColor = cv.Get2D(self.hsv, i, j)
                #print "ref color: " + str(refColor)
                # calculate near pixels of the same color
                pixelCount[i][j] = self._calcPixelCounts(j,i,refColor,distance)
        return pixelCount
    
    def _drawCorrelogram(self,data):
        width = cv.GetSize(self.image)[0]
        height = cv.GetSize(self.image)[1]
        scale = 10
        hist_img = cv.CreateImage((width*scale, height*scale), 8, 3)
        max_value = 8
        print "plotting"
                 
        cv.Rectangle(hist_img, (40,10), (49,20), cv.RGB(70,70,70))
        for v in range(height):
            for h in range(width):                
                bin_val = data[v][h]
                intensity = cv.Round(bin_val * 255 / max_value)
                cv.Rectangle(hist_img,
                             (v*scale, h*scale),
                             ((v+1)*scale - 1, (h+1)*scale - 1),
                             cv.RGB(intensity, intensity, intensity), 
                             cv.CV_FILLED)
              
        cv.SaveImage('../TestFiles/correlogram.jpg', hist_img)
        return None
    
    def _calcPixelCounts(self,xPosition,yPosition,refColor,distance):
        # begin the calculation at distance d down to 1
        sum = 0
        width = cv.GetSize(self.image)[0]
        height = cv.GetSize(self.image)[1]
        for i in reversed(range(1,distance+1)):
            
            #need to calculate 4 difference lambda values
            # horizontal lambda values
            # Check for row out of range
            if (yPosition+i >= 0) and (yPosition + i < height):
                sum  += self._lambdaH(xPosition-i,yPosition+i,2*i,refColor)
            if (yPosition-i >= 0) and (yPosition - i < height):
                sum += self._lambdaH(xPosition-i,yPosition-i,2*i,refColor)
            # vertical lambda values. Vertical can calculate
            # two less row values since already counted in the horizontal
            # count
            # Check for column out of range
            if (xPosition - i  >= 0) and (xPosition -i < width) :
                sum += self._lambdaV(xPosition-i,yPosition-i+1,2*i-2,refColor)
            if (xPosition + i >= 0) and (xPosition +i < width):
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

        hSum = 0
        ''' 
        loop through getting all pixels from (startX,startY)
        through to (startX+2k,startY)    
        '''
        maxXValue = cv.GetSize(self.image)[0]
        
        for i in range(0,(k+1)):
            # get image pixel value
            if (startX + i) == maxXValue:
                
                break 
            elif (startX + i) >= 0:

                pixelValue = cv.Get2D(self.hsv, startY, startX + i)
                
                if refColor == pixelValue:
                    hSum += 1
        return hSum
        
    '''
    lambdaV: 
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
        
        
        vSum = 0
        maxYValue = cv.GetSize(self.image)[1]
        ''' 
        loop through getting all pixels from (startX,startY)
        through to (startX+2k,startY)    
        '''
        for i in range(0,(k+1)):
            # get image pixel value
            if (startY + i) == maxYValue:
                
                break
            elif (startY + i >= 0 ):
                pixelValue = cv.Get2D(self.hsv, startY+i, startX)
                if refColor == pixelValue:
                    vSum += 1
        return vSum       
    

        