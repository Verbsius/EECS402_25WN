// Title:EECS 402 Projct 2
// Author: Yiwei Gui
// Date: 2.13.2025 
// Purpose: This program simulates pixel color distribution in image processing 
// by generating and manipulating a color matrix, while supporting querying and 
// modifying color values at specific coordinates.

#include <iostream>
using namespace std;

// Define some constants we need..
const int MAX_RANGE = 1000;
const int MIN_RANGE = 0;
const int DEFAULT_NUMBER = -99999;
const int ROW_OF_IMG = 10;
const int COL_OF_IMG = 18;

// This Global function check whether the input inColor is within the 
// valid range and clip it if it is not, and then set myColor to be the 
// same value as the inColor. It returns true if clipping and false if 
// no clipping.
bool checkAndSetColor(const int inColor, int &myColor);

class ColorClass 
{
  public:
// These constructors allow an initial value of a color object’s RGB components
// to be initialized appropriately. The default ctor will set the color’s
// initial RGB values to the color full white, and the value ctor will set the 
// color’s initial RGB values to the values provided. For the value ctor, if a 
// specified color value is outside the valid range, it will be “clipped” to 
// ensure all ColorClass attributes are always set to be within the valid 
// range. Clipping is done such that a requested color value less than the 
// allowed minimum is clipped to the minimum, while color values higher than 
// the allowed maximum are clipped to the maximum.
    ColorClass();
    ColorClass(
      const int inRed,
      const int inGreen,
      const int inBlue
    );

// The following ColorClass member functions simply set the color’s component 
// color values to the appropriate values to form the color indicated. In all 
// cases, these functions will result in “full” colors as defined above.
    void setToBlack();
    void setToRed();
    void setToGreen();
    void setToBlue();
    void setToWhite();

// This function sets the color object's RGB values to the provided values. If 
// any input value is outside the allowed color value range, then the assigned 
// value is "clipped" in order to keep the RGB color values within the valid 
// range. If any clipping was necessary, the function returns true, otherwise
// the function returns false
    bool setTo(
      const int inRed,
      const int inGreen,
      const int inBlue
    );

// This function sets the color's component color values to the same as those 
// in the "inColor" input parameter. If any clipping was necessary in order 
// to keep the color values in the allowed range, the function returns true, 
// otherwise it returns false. Note that, since a ColorClass object is used 
// as input, and since we are making sure ColorClass attributes are always 
// within the valid range, this function should never find a need to do any 
// clipping, and therefore, would be expected to always return false.
    bool setTo(const ColorClass &inColor);

/*
This function causes each RGB value to have the corresponding value from the 
input parameter color added to it. At the completion of this function, the RGB 
values will still be in the allowed color value range. If any resulting color 
value would end up outside the valid color value range, the value is "clipped" 
in order to keep the RGB color values within the valid range. If any clipping 
was necessary, the function returns true, otherwise the function returns false.
*/
    bool addColor(const ColorClass &rhs);
/*
This function causes each RGB value to have the corresponding value from the 
input parameter subtracted from it. At the completion of this function, 
the RGB values will still be in the allowed color value range. If any resulting
colorvalue would end up outside the valid color value range, the value is 
"clipped" in order to keep the RGB color values within the valid range. If 
any clipping was necessary, the function returns true, otherwise the function
returns false.
*/
    bool subtractColor(const ColorClass &rhs);
    bool adjustBrightness(const double adjFactor);
    void printComponentValues() const;
  
  private:
    int red;
    int green;
    int blue;

// This function is used to check and set the color values 
// (red, green, blue) of the current pixel, while detecting 
// whether any color value clipping occurs during the process.
// If any color value exceeds the valid range and is clipped,
// the function returns true; otherwise, it returns false.
    bool checkAndSetPixel(const ColorClass &inPixel);
    



};
class RowColumnClass 
{
  public:
    RowColumnClass();
    RowColumnClass(const int inRow, const int inCol);
/*
These functions are simple “setter functions” that just directly set 
the appropriate attribute(s) to the value(s) provided.
*/
    void setRowCol(const int inRow, const int inCol);
    void setRow(const int inRow);
    void setCol(const int inCol);
    int getRow() const;
    int getCol() const;
// This function adds the row and column index values in the input 
// parameter to the row and column index of the object the function is 
// called on.
    void addRowColTo(const RowColumnClass &inRowCol);
    void printRowCol() const;

  private:
    int col;
    int row;
};
class ColorImageClass 
{
  public:
    ColorImageClass();
    void initializeTo(const ColorClass &inColor);
// This function performs a pixel-wise addition, such that each pixel 
// in the image has the pixel in the corresponding location in the 
// right-hand side input image added to it. If the result of one or 
// more of the pixel additions required color value clipping, this 
// function returns true, otherwise it returns false.
    bool addImageTo(const ColorImageClass &rhsImg);

// This function causes the image's pixel values to be set to the 
// sum of the corresponding pixels in each image in the imagesToAdd 
// input parameter. In other words, this image's pixel at row 0 
// column 0 will be assigned the sum of each input image's pixel 
// value at row 0, column 0, etc. Note: this function does not 
// "add TO" the image that the function is called on - it simply 
// pixel-wise adds the input images and assigns the result to the 
// image that the function is called on. If the result of one or 
// more of the pixel additions required color value clipping, this function 
// returns true, otherwise it returns false.
    bool addImages(
      const int numImgsToAdd, 
      const ColorImageClass imagesToAdd []
    );

// This function attempts to set the pixel at the location specified by 
// the “inRowCol” parameter to the color specified via the “inColor” 
// parameter. If the location specified is a valid location for the image, 
// the pixel value is changed and the function returns true, otherwise the 
// image is not modified in ANY way, and the function returns false.
    bool setColorAtLocation(
      const RowColumnClass &inRowCol,
      const ColorClass &inColor
    );

    bool getColorAtLocation(
      const RowColumnClass &inRowCol,
      ColorClass &outColor
    ) const;

    void printImage() const;

  private:
    int numRow;
    int numCol;
    ColorClass img[ROW_OF_IMG][COL_OF_IMG];


};

#ifdef ANDREW_TEST
#include "andrewTest.h"
#else
int main()
{
  ColorClass testColor;
  RowColumnClass testRowCol;
  RowColumnClass testRowColOther(111, 222);
  ColorImageClass testImage;
  ColorImageClass testImages[3];

  //Test some basic ColorClass operations...
  cout << "Initial: ";
  testColor.printComponentValues();
  cout << endl;

  testColor.setToBlack();
  cout << "Black: ";
  testColor.printComponentValues();
  cout << endl;

  testColor.setToGreen();
  cout << "Green: ";
  testColor.printComponentValues();
  cout << endl;

  testColor.adjustBrightness(0.5);
  cout << "Dimmer Green: ";
  testColor.printComponentValues();
  cout << endl;

  //Test some basic RowColumnClass operations...
  cout << "Want defaults: ";
  testRowCol.printRowCol();
  cout << endl;

  testRowCol.setRowCol(2, 8);
  cout << "Want 2,8: ";
  testRowCol.printRowCol();
  cout << endl;

  cout << "Want 111, 222: ";
  testRowColOther.printRowCol();
  cout << endl;

  testRowColOther.setRowCol(4, 2);
  testRowCol.addRowColTo(testRowColOther);
  cout << "Want 6,10: ";
  testRowCol.printRowCol();
  cout << endl;

  //Test some basic ColorImageClass operations...
  testColor.setToRed();
  testImage.initializeTo(testColor);

  testRowCol.setRowCol(555, 5);
  cout << "Want: Color at [555,5]: Invalid Index!" << endl;
  cout << "Color at ";
  testRowCol.printRowCol();
  cout << ": ";
  if (testImage.getColorAtLocation(testRowCol, testColor))
  {
    testColor.printComponentValues();
  }
  else
  {
    cout << "Invalid Index!";
  }
  cout << endl;

  testRowCol.setRow(4);
  cout << "Want: Color at [4,5]: R: 1000 G: 0 B: 0" << endl;
  cout << "Color at ";
  testRowCol.printRowCol();
  cout << ": ";
  if (testImage.getColorAtLocation(testRowCol, testColor))
  {
    testColor.printComponentValues();
  }
  else
  {
    cout << "Invalid Index!";
  }
  cout << endl;

  //Set up an array of images of different colors
  testColor.setToRed();
  testColor.adjustBrightness(0.25);
  testImages[0].initializeTo(testColor);
  testColor.setToBlue();
  testColor.adjustBrightness(0.75);
  testImages[1].initializeTo(testColor);
  testColor.setToGreen();
  testImages[2].initializeTo(testColor);

  //Modify a few individual pixel colors
  testRowCol.setRowCol(4, 2);
  testColor.setToWhite();
  testImages[1].setColorAtLocation(testRowCol, testColor);

  testRowCol.setRowCol(2, 4);
  testColor.setToBlack();
  testImages[2].setColorAtLocation(testRowCol, testColor);

  //Add up all images in testImages array and assign result
  //to the testImage image
  testImage.addImages(3, testImages);
  
  //Check some certain values
  cout << "Added values:" << endl;
  for (int colInd = 0; colInd < 8; colInd += 2)
  {
    testRowCol.setRowCol(4, colInd);
    cout << "Color at ";
    testRowCol.printRowCol();
    cout << ": ";
    if (testImage.getColorAtLocation(testRowCol, testColor))
    {
      testColor.printComponentValues();
    }
    else
    {
      cout << "Invalid Index!";
    }
    cout << endl;
  }
  
  for (int rowInd = 0; rowInd < 8; rowInd += 2)
  {
    testRowCol.setRowCol(rowInd, 4);
    cout << "Color at ";
    testRowCol.printRowCol();
    cout << ": ";
    if (testImage.getColorAtLocation(testRowCol, testColor))
    {
      testColor.printComponentValues();
    }
    else
    {
      cout << "Invalid Index!";
    }
    cout << endl;
  }
  
  cout << "Printing entire test image:" << endl;
  testImage.printImage();

  return 0;

}
#endif

bool checkAndSetColor(const int inColor, int &myColor)
{
  bool isClipped = false;
  if (inColor > MAX_RANGE)
  {
    myColor = MAX_RANGE;
    isClipped = true;
  }
  else if (inColor < MIN_RANGE)
  {
    myColor = MIN_RANGE;
    isClipped = true;
  }
  else 
  {
    myColor = inColor;
  }
  return isClipped;
}

bool ColorClass::checkAndSetPixel(const ColorClass &inPixel)
{
  bool isClipped = false;
  if (checkAndSetColor(inPixel.red, red))
  {
    isClipped = true;
  }
  if (checkAndSetColor(inPixel.green, green))
  {
    isClipped = true;
  }
  if (checkAndSetColor(inPixel.blue, blue))
  {
    isClipped = true;
  }
  return isClipped;

}

ColorClass::ColorClass()
{
  setToWhite();
}
ColorClass::ColorClass(const int inRed, const int inGreen, const int inBlue)
{
  setTo(inRed, inGreen, inBlue);
}

void ColorClass::setToBlack() 
{
  setTo(MIN_RANGE, MIN_RANGE, MIN_RANGE);
}
void ColorClass::setToRed()
{
  setTo(MAX_RANGE, MIN_RANGE, MIN_RANGE);
}
void ColorClass::setToGreen()
{
  setTo(MIN_RANGE, MAX_RANGE, MIN_RANGE);
}
void ColorClass::setToBlue()
{
  setTo(MIN_RANGE, MIN_RANGE, MAX_RANGE);
}
void ColorClass::setToWhite()
{
  setTo(MAX_RANGE, MAX_RANGE, MAX_RANGE);

}


bool ColorClass::setTo(const int inRed, const int inGreen, const int inBlue)
{
  bool isClipped = false;
  if (checkAndSetColor(inRed, red))
  {
    isClipped = true;
  }
  if (checkAndSetColor(inGreen, green))
  {
    isClipped = true;
  }
  if (checkAndSetColor(inBlue, blue))
  {
    isClipped = true;
  }
  return isClipped;

}

bool ColorClass::setTo(const ColorClass &inColor)
{
  red = inColor.red;
  blue = inColor.blue;
  green = inColor.green;
  return false;
}

bool ColorClass::addColor(const ColorClass &rhs)
{
  bool isClipped = false;
  ColorClass tempColor;

  // calculate the result 
  if (tempColor.setTo(red + rhs.red, green + rhs.green, 
    blue + rhs.blue))
  {
    isClipped = true;
  }

  // set back the sum to current ColorClass object
  if (setTo(tempColor))
  {
    isClipped = true;
  }
  return isClipped;
}

bool ColorClass::subtractColor(const ColorClass &rhs)
{
  bool isClipped = false;
  ColorClass tempColor;

  // calculate the result 
  if (tempColor.setTo(red - rhs.red, green - rhs.green, 
    blue - rhs.blue))
  {
    isClipped = true;
  }

  // set back the sum to current ColorClass object
  if (setTo(tempColor))
  {
    isClipped = true;
  }
  return isClipped;
}

bool ColorClass::adjustBrightness(const double adjFactor)
{
  bool isClipped = false;
  ColorClass tempColor;

  // calculate the result 
  if (tempColor.setTo((int)(red * adjFactor), (int)(green * adjFactor),
    (int)(blue * adjFactor)))
  {
    isClipped = true;
  }

  // set back the sum to current ColorClass object
  if (setTo(tempColor))
  {
    isClipped = true;
  }

  return isClipped;
}

void ColorClass::printComponentValues() const
{
  std::cout << "R: " << red << " G: " << green << " B: " << blue;
}

RowColumnClass::RowColumnClass()
{
  col = DEFAULT_NUMBER;
  row = DEFAULT_NUMBER;
}
RowColumnClass::RowColumnClass(const int inRow, const int inCol)
{
  setRow(inRow);
  setCol(inCol);
}
void RowColumnClass::setRowCol(const int inRow, const int inCol)
{
  row = inRow;
  col = inCol; 
}
void RowColumnClass::setRow(const int inRow)
{
  row = inRow;
}
void RowColumnClass::setCol(const int inCol)
{
  col = inCol;
}

int RowColumnClass::getRow() const
{
  return row;
}
int RowColumnClass::getCol() const
{
  return col; 
}

void RowColumnClass::addRowColTo(const RowColumnClass &inRowCol)
{
  row += inRowCol.row;
  col += inRowCol.col;
}
void RowColumnClass::printRowCol() const
{
  cout << "[" << row << "," << col << "]";

}

ColorImageClass::ColorImageClass()
{
  numRow = ROW_OF_IMG;
  numCol = COL_OF_IMG;

  for (int i = 0; i < numRow; i++)
  {
    for (int j = 0; j < numCol; j++)
    {
      img[i][j].setToBlack();
    }
  }
}

void ColorImageClass::initializeTo(const ColorClass &inColor)
{
  for (int i = 0; i < numRow; i++)
  {
    for (int j = 0; j < numCol; j++)
    {
      img[i][j].setTo(inColor);
    }
  }
}

bool ColorImageClass::addImageTo(const ColorImageClass &rhsImg)
{
  bool isClipped = false;

  for (int i = 0; i < numRow; i++)
  {
    for (int j = 0; j < numCol; j++)
    {
      if(img[i][j].addColor(rhsImg.img[i][j]))
      {
        isClipped = true;
      }
    }
  }
  return isClipped;
}

bool ColorImageClass::addImages(
  const int numImgsToAdd, 
  const ColorImageClass imagesToAdd []
)
{
  ColorClass black;
  black.setToBlack();
  initializeTo(black);

  ColorImageClass tempImg;
  bool isClipped = false;

  for (int i = 0; i < numRow; i++)
  {
    for (int j = 0; j < numCol; j++)
    {
      for (int k = 0; k < numImgsToAdd; k++)
      {
        if(tempImg.img[i][j].addColor(imagesToAdd[k].img[i][j]))
        {
          isClipped = true;
        }
      }
    }
  }
  addImageTo(tempImg);

  return isClipped;
}

bool ColorImageClass::setColorAtLocation(
  const RowColumnClass &inRowCol,
  const ColorClass &inColor
)
{
  bool isModified = false;
  if (inRowCol.getRow() >= numRow || inRowCol.getRow() < 0 || 
    inRowCol.getCol() >= numCol || inRowCol.getCol() < 0)
  {
    return isModified;
  }
  else
  {
    img[inRowCol.getRow()][inRowCol.getCol()].setTo(inColor);
    isModified = true;
    return isModified;
  }
}

bool ColorImageClass::getColorAtLocation(
  const RowColumnClass &inRowCol, 
  ColorClass &outColor
) const
{
  bool isModified = false;
  if (inRowCol.getRow() >= numRow || inRowCol.getRow() < 0 || 
    inRowCol.getCol() >= numCol || inRowCol.getCol() < 0)
  {
    return isModified;
  }
  else
  {
    outColor.setTo(img[inRowCol.getRow()][inRowCol.getCol()]);
    isModified = true;
    return isModified;
  }
}

void ColorImageClass::printImage() const
{
  for (int idxRow = 0; idxRow < numRow; idxRow++)
  {
    for (int idxCol = 0; idxCol < numCol; idxCol++)
    {
      if (idxCol == 0)
      {
        img[idxRow][idxCol].printComponentValues();
      }
      else if (idxCol == numCol - 1)
      {
        cout << "--";
        img[idxRow][idxCol].printComponentValues();
        cout << endl;
      }
      else 
      {
        cout << "--";
        img[idxRow][idxCol].printComponentValues();

      }
      
    }
  }

}