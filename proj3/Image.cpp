/**
 * @file Image.cpp
 *
 * This file provides functions to load, save, encode, and decode PPM images.
 * It ensures proper file handling and memory management.
 *
 * @author Yiwei Gui
 * @date 3/21/2025
 */

#include "Image.h"

Image::Image() : width(0), height(0), pixels(NULL) {}

Image::~Image() {
    if (pixels != NULL) {
        for (int i = 0; i < height; ++i) {
            delete[] pixels[i];
        }
        delete[] pixels;
    }
}

bool Image::load(const std::string &filename) {
    std::ifstream inFile;
    inFile.open(filename.c_str());

    // Error checking: whether valid file
    if (inFile.fail()) {
        
        std::cout << "Error: Cannot open the file" << std::endl;
        return false;
    }

    std::string magic;
    inFile >> magic;

    // Error checking: valid magic number
    if (inFile.fail()) {
        std::cout << "Error: Cannot read magic number or file is incomplete" 
          << std::endl;
        return false;
    }
    if (magic != "P3") {
        std::cout << "Error: Invalid PPM format" << std::endl;
        return false;
    }


    int newWidth;
    inFile >> newWidth;
    // Error checking: valid width
    if (inFile.fail()) {
        std::cout << "Error: Cannot read width or file is incomplete" 
          << std::endl;
        return false;
    }

    int newHeight;
    inFile >> newHeight;
    // Error checking: valid height
    if (inFile.fail()) {
        std::cout << "Error: Cannot read height or file is incomplete" 
          << std::endl;
        return false;
    }


    // Error checking: image dimensions
    if (newWidth < MIN_IMAGE_SIZE || newWidth > MAX_IMAGE_SIZE || 
        newHeight < MIN_IMAGE_SIZE || newHeight > MAX_IMAGE_SIZE) {
        std::cout << "Error: Image dimensions must be between " 
          << MIN_IMAGE_SIZE << " and " << MAX_IMAGE_SIZE << std::endl;
        return false;
    }
    
    int maxVal;
    inFile >> maxVal;

    // Error checking: valid maxVal
    if (inFile.fail()) {
        std::cout << "Error: Cannot read max color value or file is incomplete" 
          << std::endl;
        return false;
    }
    if (maxVal != MAX_COLOR_VALUE) {
        std::cout << "Error: Max color value must be " << MAX_COLOR_VALUE 
          << std::endl;
        return false;
    }
    
    // Clean up existing pixels if there are any
    if (pixels != NULL) {
        for (int i = 0; i < height; ++i) {
            delete[] pixels[i];
        }
        delete[] pixels;
    }
    
    // Update dimensions
    width = newWidth;
    height = newHeight;
    
    // Allocate memory for pixels
    pixels = new Color*[height];
    for (int i = 0; i < height; ++i) {
        pixels[i] = new Color[width];
    }
    
    // Read pixel data
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (!pixels[i][j].readFromFile(inFile)) {
                std::cout << "Error: Reading color from file" 
                  << std::endl; 
                std::cout << "Error: Reading image pixel at row: " << i 
                  << " col: " << j << std::endl;
                
                // Free memory
                for (int k = 0; k < height; ++k) {
                    delete[] pixels[k];
                }
                delete[] pixels;

                return false;
            }
        }
    }
    
    // Error Checking: if there is something left in the file, it means 
    // this file is invalid formatted.
    std::string leftover;
    inFile >> leftover;
    if (!inFile.fail()) {
        std::cout << "Error: Extra data found in file (expected " 
                  << width * height * 3 << " values, but found more)" 
                  << std::endl;
        // Free memory
        for (int i = 0; i < height; ++i) {
            delete[] pixels[i];
        }
        
        delete[] pixels;

        return false;
    }

    std::cout << "Image read successful: Yes" << std::endl;
    inFile.close();
    return true;
}

void Image::save(const std::string &filename) const {
    std::ofstream file(filename.c_str());
    if (!file) {
        std::cout << "Error: Cannot write to file " << filename 
          << std::endl;
        return;
    }
    
    file << "P3" << std::endl << width << " " << height << std::endl 
      << MAX_COLOR_VALUE << std::endl;
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            pixels[i][j].writeToFile(file);
        }
        file << std::endl;
    }
    
    std::cout << "Image write successful: Yes" << std::endl;
}


void Image::encodeMessage(const std::string &messageFile, int startX, 
      int startY) {
    std::ifstream file(messageFile.c_str());

    if (file.fail()) {
        std::cout << "Error: Cannot open message file " << messageFile 
          << std::endl;
        std::cout << "Message encode successful: No" << std::endl;
        return;

    }
    
    int msgWidth, msgHeight;
    file >> msgWidth >> msgHeight;
    
    if (file.fail()) {
        std::cout << "Error: Invalid message file format" << std::endl;
        std::cout << "Message encode successful: No" << std::endl;
        return;
    }
    
    // Allocate memory for the message
    int** message = new int*[msgHeight];
    for (int i = 0; i < msgHeight; ++i) {
        message[i] = new int[msgWidth];
    }
    
    // Read message data
    for (int i = 0; i < msgHeight; ++i) {
        for (int j = 0; j < msgWidth; ++j) {

            file >> message[i][j];
            // Error checking: double or float is invalid
            if (message[i][j] < MIN_ENCODING_VALUE || 
                   message[i][j] > MAX_ENCODING_VALUE || file.fail() || 
                   file.peek() == '.') {
                std::cout << "Error: Reading message value at row/col: "
                  << i << " "<< j << std::endl;
                std::cout << "Message encode successful: No" << std::endl;

                // Clean up allocated memory
                for (int k = 0; k <= i; ++k) {
                    delete[] message[k];
                }
                delete[] message;
                
                return;
            }
        }
    }
    // Error checking: if there is something left in message file. it means this
    // file is invalid formatted.
    std::string leftover;
    file >> leftover;
    if (!file.fail()) {
        // Free memory
        for (int i = 0; i < msgHeight; ++i) {
            delete[] message[i];
        }
        delete[] message;
    
        std::cout << "Error: Extra data found in file (expected " 
                  << msgHeight * msgWidth << " values, but found more)" 
                  << std::endl;
        std::cout << "Message encode successful: No" << std::endl;
        return;
    }
    
    // Encode the message into the image
    bool isOutOfBounds = false;

    for (int i = 0; i < msgHeight; ++i) {
        for (int j = 0; j < msgWidth; ++j) {
            int row = startY + i;
            int col = startX + j;
            
            // Skip pixels outside the image bounds
            if (row >= 0 && row < height && col >= 0 && col < width) {
                pixels[row][col].encode(message[i][j]);
            } else {
                isOutOfBounds = true;
            }
        }
    }
    
    // Clean up
    for (int i = 0; i < msgHeight; ++i) {
        delete[] message[i];
    }
    delete[] message;
    
    std::cout << "Message encode successful: Yes" << std::endl;
    if (isOutOfBounds) {
        std::cout << "Warning: Part of the message was out of image " 
          << "bounds and was not encoded." << std::endl;
    }
}

void Image::decodeMessage() {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            int colorCode = pixels[i][j].decode();
            
            // Set pixel to full color based on decoded value
            switch (colorCode) {
                case BLACK: // Black (Even, Even, Even)
                    pixels[i][j].setRGB(MIN_COLOR_VALUE, 
                          MIN_COLOR_VALUE, MIN_COLOR_VALUE);
                    break;
                case RED: // Red (Odd, Even, Even)
                    pixels[i][j].setRGB(MAX_COLOR_VALUE, 
                          MIN_COLOR_VALUE, MIN_COLOR_VALUE);
                    break;
                case GREEN: // Green (Even, Odd, Even)
                    pixels[i][j].setRGB(MIN_COLOR_VALUE, 
                          MAX_COLOR_VALUE, MIN_COLOR_VALUE);
                    break;
                case BLUE: // Blue (Even, Even, Odd)
                    pixels[i][j].setRGB(MIN_COLOR_VALUE, 
                          MIN_COLOR_VALUE, MAX_COLOR_VALUE);
                    break;
                case WHITE: // White (Odd, Odd, Odd)
                    pixels[i][j].setRGB(MAX_COLOR_VALUE, 
                          MAX_COLOR_VALUE, MAX_COLOR_VALUE);
                    break;
                case YELLOW: // Yellow (Odd, Odd, Even)
                    pixels[i][j].setRGB(MAX_COLOR_VALUE, 
                          MAX_COLOR_VALUE, MIN_COLOR_VALUE);
                    break;
                case MAGENTA: // Magenta (Odd, Even, Odd)
                    pixels[i][j].setRGB(MAX_COLOR_VALUE, 
                          MIN_COLOR_VALUE, MAX_COLOR_VALUE);
                    break;
                case CYAN: // Cyan (Even, Odd, Odd)
                    pixels[i][j].setRGB(MIN_COLOR_VALUE, 
                          MAX_COLOR_VALUE, MAX_COLOR_VALUE);
                    break;
            }
        }
    }
    
    std::cout << "Image modified to decoded image contents" << std::endl;
}