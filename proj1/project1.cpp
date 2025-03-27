// Name: Yiwei Gui
// Purpose: To approximate the area between a curve and the X-axis by fitting a
// number of rectangles
// Date: Jan 22rd, 2025

#include <iostream>
using namespace std;

// Define magic numbers
const int APPROXIMATE_INTEGRAL_OPTION = 1;
const int EXPERIMENT_PRECISION_OPTION = 2;
const int EXIT_OPTION= 3;
const int MAX_ITERATION_NUM = 100;

// This function prints out the possible choices the user has in a menu format
void printMenu();

// This function raises "val" to the power "power" and returns the result.
double toThePower(const double val, const int power);

// This function evaluates the cubic formula specified as:
// y = aCoeff * xValue^3 + bCoeff * xValue^2 + cCoeff * xValue + dCoeff
// at the x value specified as “xValue”. The resulting y value is output back 
// to the calling function as the reference parameter “resultVal”. 
// The function will return false if the resulting y value is a negative value, 
// or true if the resulting value is greater or equal to zero.
bool evaluateCubicFormula(
        const double aCoeff, 
        const double bCoeff, 
        const double cCoeff, 
        const double dCoeff, 
        const double xValue, 
        double &resultVal);

// This function will approximate the area between the X-axis and the curve 
// defined by the formula:y = aCoeff * x^3 + bCoeff * x^2 + cCoeff * x + dCoeff
// Rectangles are used to approximate the area. The rectangle's width will be 
// determined by considering the interval of interest and number of rectangles 
// that are to be used. The rectangle's height is determined by evaluating the 
// function at the rectangle's midpoint along x (width). The area of interest’s 
// interval is from "startX" to "endX", and "numRects" rectangles should be 
// used to do the approximation.
double approximateAreaWithRectangles(
        const double aCoeff, 
        const double bCoeff, 
        const double cCoeff, 
        const double dCoeff, 
        const double startX, 
        const double endX, 
        const int numRects);

#ifdef ANDREW_TEST
#include "andrewTest.h"
#else

int main()
{

    int choice = 0;
    while(choice != EXIT_OPTION)
    {
        printMenu();
        cout << "YOUR CHOICE: ";
        cin >> choice;

        if (choice == APPROXIMATE_INTEGRAL_OPTION)
        {
            double aCoeff, bCoeff, cCoeff, dCoeff, startX, endX, result;
            int numRects;
            cout << "Enter (a b c d) for function "
                "y = a*x^3 + b*x^2 + c*x + d: ";
            cin >> aCoeff >> bCoeff >> cCoeff >> dCoeff;
            cout << "Now enter x start and end values: ";
            cin >> startX >> endX;

            // Check whether range of x is valid
            // endX should always greater than startX
            while(startX >= endX)
            {
                cout << "Invalid range entered" << endl;
                cout << "Now enter x start and end values: ";
                cin >> startX >> endX;
            }

            cout << "Enter the number of rectangles to use: ";
            cin >> numRects;

            // Check whether number of rectangles is valid
            // The number of rectangles should always greater than zero
            while(numRects <= 0)
            {
                cout << "Invalid number of rectangles entered" << endl;
                cout << "Enter the number of rectangles to use: ";
                cin >> numRects;
            }

            result = approximateAreaWithRectangles(aCoeff, bCoeff, cCoeff,
                    dCoeff, startX, endX, numRects);
            cout << "Rectangle result is: " << result << endl;

        }
        else if (choice == EXPERIMENT_PRECISION_OPTION)
        {
            double aCoeff, bCoeff, cCoeff, dCoeff, startX, endX,
                   correctAns, precision;
            
            cout << "Enter (a b c d) for function"
                " y = a*x^3 + b*x^2 + c*x + d: ";
            cin >> aCoeff >> bCoeff >> cCoeff >> dCoeff;
            cout << "Now enter x start and end values: ";
            cin >> startX >> endX;
            
            // Check whether range of x is valid
            while(startX >= endX)
            {
                cout << "Invalid range entered" << endl;
                cout << "Now enter x start and end values: ";
                cin >> startX >> endX;
            }


            cout << "Enter correct answer: ";
            cin >> correctAns;
            // Check whether correctAns is valid
            // exact integral should be greater than and equal to zero  
            while (correctAns < 0)
            {
                cout << "Invalid correct answer entered" << endl;
                cout << "Enter correct answer: ";
                cin >> correctAns;
            }

            cout << "Enter precision to reach: ";
            cin >> precision;
            // Check whether precision is valid
            // Precision should always be greater than and equal to zero
            while(precision < 0)
            {
                cout << "Invalid precision entered" << endl;
                cout << "Enter precision to reach: ";
                cin >> precision;
            }

            // Find the minimum number of rectangles that reach the precision 
            // using loop. The condition should be the program
            // satisify result > precision + correctAns or result < correctAns
            // - precision. At the same time, numRectsNeeded should be less than 
            // and equal MAX_ITERATION_NUM

            int numRectsNeeded = 1;
            double result = approximateAreaWithRectangles(aCoeff,
                        bCoeff, cCoeff, dCoeff, startX, endX, numRectsNeeded);
            
            while ((result > correctAns + precision || result < correctAns
                    - precision) && numRectsNeeded <= MAX_ITERATION_NUM)
            {
                numRectsNeeded++;
                result = approximateAreaWithRectangles(aCoeff,
                        bCoeff, cCoeff, dCoeff, startX, endX, numRectsNeeded);
  
            }
            if (numRectsNeeded > MAX_ITERATION_NUM)
            {
                cout << "Tried " << MAX_ITERATION_NUM << " without reaching precision" 
                    << endl;
            }
            else 
            {
                cout << "Rectangles needed to reach precision: " 
                    << numRectsNeeded << endl;
            }
            

        }
        else if (choice == EXIT_OPTION)
        {
            cout << "Thanks for using this program" << endl;
        }
        else 
        {
            cout << "Invalid menu choice entered" << endl;
        }
    }   

    return 0;
}
#endif

void printMenu()
{
    cout << APPROXIMATE_INTEGRAL_OPTION << " Approximate Integral Using Rectangles" << endl;
    cout << EXPERIMENT_PRECISION_OPTION << " Experiment With Rectangle Precision" << endl;
    cout << EXIT_OPTION << " Quit The Program" << endl;
}

double toThePower(const double val, const int power)
{
    double curNum = 1.0;
    for (int i = 0; i < power; i++)
    {
        curNum *= val;
    }

    return curNum;
}
bool evaluateCubicFormula(
        const double aCoeff, 
        const double bCoeff,
        const double cCoeff, 
        const double dCoeff, 
        const double xValue,
        double &resultVal)
{
    resultVal = aCoeff * toThePower(xValue, 3) + bCoeff * toThePower(xValue, 2)
        + cCoeff * xValue + dCoeff;
    if (resultVal >= 0)
    {
        return true;
    }
    else
    {
        return false;
    }

}
double approximateAreaWithRectangles(
        const double aCoeff, 
        const double bCoeff, 
        const double cCoeff, 
        const double dCoeff, 
        const double startX, 
        const double endX, 
        const int numRects)
{
    double widthRects = (endX - startX) / numRects;
    double curApproximateArea = 0;
    for (int i = 0; i < numRects; i++)
    {
        double curMidX = (startX + i * widthRects + 
                startX + (i + 1) * widthRects) / 2;
        double curRectangleHeight;
        double curRectangleArea;
        bool isPositive;

        isPositive = evaluateCubicFormula(aCoeff, bCoeff, cCoeff, dCoeff,
                curMidX, curRectangleHeight);
        if (isPositive)
        {
            curRectangleArea = widthRects * curRectangleHeight;
        
        }
        else 
        {
            curRectangleArea = -widthRects * curRectangleHeight;
        }

        curApproximateArea += curRectangleArea;

   
    }
    return curApproximateArea;
}
