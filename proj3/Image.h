/**
 * @file Image.h
 *
 * This header file defines the Image class, which provides functionality to 
 * load, save, and manipulate PPM images, as well as encode and decode hidden 
 * messages.
 *
 * @author Yiwei Gui
 * @date 3/21/2025
 */


#ifndef IMAGE_H
#define IMAGE_H

#include "Color.h"
#include "constants.h"
#include <string>
#include <fstream>
#include <iostream>
class Image {
private:
    int width, height;  // Image dimensions
    Color** pixels; // 2D array of Color objects representing image pixels

public:
    /**
     * Default constructor
     * Initializes an empty image with width=0, height=0, and pixels=NULL
     */
    Image();

    /**
     * Destructor
     * Releases dynamically allocated memory for the pixels array
     */
    ~Image();

    /**
     * Loads an image from a PPM file
     * @param filename Path to the PPM file to load
     * @return true if the image was loaded successfully, false otherwise
     * @note Supports only P3 (ASCII) PPM format
     */
    bool load(const std::string &filename);

    /**
     * Saves the image to a PPM file
     * @param filename Path where the image will be saved
     * @note Saves in P3 (ASCII) PPM format
     */
    void save(const std::string &filename) const;

    /**
     * Encodes a message into the image using steganography
     * @param messageFile Path to the file containing the message to encode
     * @param startX X-coordinate (column) where encoding should begin
     * @param startY Y-coordinate (row) where encoding should begin
     * @return true if a message is encoded into the image successfully, false
     * otherwise
     * @note The message is encoded by modifying the least significant bits of 
     * pixel colors
     */
    void encodeMessage(const std::string &messageFile, int startX, int startY);
    
    /**
     * Decodes a hidden message from the image
     * @note Transforms the image to visualize the hidden message by 
     *       setting each pixel to a specific color based on its encoded value
     */
    void decodeMessage();
};

#endif