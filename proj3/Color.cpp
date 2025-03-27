/**
 * @file Color.cpp
 * 
 * This file provides the implementation of the Color class, including methods 
 * for encoding and decoding data using least significant bits, reading from 
 * and writing to files, and modifying RGB values.
 *
 * @author Yiwei Gui
 * @date 3/21/2025
 */

#include "Color.h"

Color::Color(int r, int g, int b) : r(r), g(g), b(b) {}


void Color::encode(int value) {
    bool isROdd = false;
    bool isGOod = false;
    bool isBOod = false;
    
    isROdd = (value == RED || value == WHITE || value == YELLOW || 
        value == MAGENTA); 

    isGOod = (value == GREEN || value == WHITE || value == YELLOW || 
        value == CYAN); 

    isBOod = (value == BLUE || value == WHITE || value == MAGENTA || 
        value == CYAN); 

    // Encode first bit (least significant) in red
    if ((r % 2 == 1) != isROdd) {
        r += (r % 2 == 0) ? 1 : -1;
    }
    
    // Encode second bit in green
    if ((g % 2 == 1) != isGOod) {
        g += (g % 2 == 0) ? 1 : -1;
    }
    
    // Encode third bit in blue
    if ((b % 2) != isBOod) {
        b += (b % 2 == 0) ? 1 : -1;
    }
}

int Color::decode() const {
    int colorCode = (r % 2 << 2) | ((g % 2) << 1) | ((b % 2));
    switch (colorCode) {
        case BLACK_BIN: // Black (Even, Even, Even)
            return BLACK;

        case RED_BIN: // Red (Odd, Even, Even)
            return RED;

        case GREEN_BIN: // Green (Even, Odd, Even)
            return GREEN;

        case BLUE_BIN: // Blue (Even, Even, Odd)
            return BLUE;

        case WHITE_BIN: // White (Odd, Odd, Odd)
            return WHITE;

        case YELLOW_BIN: // Yellow (Odd, Odd, Even)
            return YELLOW;

        case MAGENTA_BIN: // Magenta (Odd, Even, Odd)
            return MAGENTA;

        case CYAN_BIN: // Cyan (Even, Odd, Odd)
            return CYAN;
    }
    return DECODE_DEFAULT_RETURN_VALUE;
}

bool Color::readFromFile(std::ifstream &inFile) {

    if (!(inFile >> r)) {
        std::cout<< "Error: Unexpected end of file while reading R value." 
          << std::endl;
        return false;
    }
    if (!(inFile >> g)) {
        std::cout << "Error: Unexpected end of file while reading G value." 
          << std::endl;
        return false;
    }
    if (!(inFile >> b)) {
        std::cout << "Error: Unexpected end of file while reading B value." 
          << std::endl;
        return false;
    }
    
    // Check that RGB values are within valid range
    if (r < MIN_COLOR_VALUE || r > MAX_COLOR_VALUE || 
          g < MIN_COLOR_VALUE || g > MAX_COLOR_VALUE || 
          b < MIN_COLOR_VALUE || b > MAX_COLOR_VALUE) {
        return false;
    }
    
    return true;
}

void Color::writeToFile(std::ofstream &outFile) const {
    outFile << r << " " << g << " " << b << " ";
}

void Color::setRGB(int red, int green, int blue) {
    r = red;
    g = green;
    b = blue;
}

