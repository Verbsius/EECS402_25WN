/**
 * @file Color.h
 *
 * This header file defines the Color class, which provides methods for handling 
 * RGB color components, encoding and decoding hidden data, and file I/O 
 * operations.
 *
 * @author Yiwei Gui
 * @date 3/21/2025
 */

#ifndef COLOR_H
#define COLOR_H

#include <fstream>
#include <string>
#include <iostream>
#include "constants.h"


class Color {
private:
    int r, g, b;  // Red, green, and blue color components (0-255)
public:
    /**
     * Constructor for Color
     * @param r Red component value (0-255), defaults to 0
     * @param g Green component value (0-255), defaults to 0
     * @param b Blue component value (0-255), defaults to 0
     */
    Color(int r = 0, int g = 0, int b = 0);

    /**
     * Encodes a 3-bit value into the color by modifying the least significant 
     * bits of RGB
     * @param value The value to encode (0-7)
     * @note Bit 0 goes to R, bit 1 to G, and bit 2 to B component
     */
    void encode(int value);

    /**
     * Decodes the 3-bit value hidden in the RGB components
     * @return The decoded value (0-7) from the least significant bits of RGB
     */
    int decode() const;

    /**
     * Reads RGB values from input file stream
     * @param inFile Reference to the input file stream
     * @return true if read successfully, false on error or invalid values
     */
    bool readFromFile(std::ifstream &inFile);

    /**
     * Writes RGB values to output file stream
     * @param outFile Reference to the output file stream
     */
    void writeToFile(std::ofstream &outFile) const;

    /**
     * Sets the RGB components to new values
     * @param red New value for red component
     * @param green New value for green component
     * @param blue New value for blue component
     */
    void setRGB(int red, int green, int blue);

};

#endif