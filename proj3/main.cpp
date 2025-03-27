/**
 * @file main.cpp
 *
 * This program loads a PPM image file, provides a menu-driven interface 
 * for encoding a message into the image, decoding a hidden message, and 
 * saving the modified image. It ensures proper error checking for user 
 * input and file handling.
 *
 * @author Yiwei GUi
 * @date 3/21/2025
 */

#include "Image.h"
#include <iostream>
#include <cstdlib>

int main(int argc, char *argv[]) {

    // Error checking: there should be 2 inputs. If not, exit the 
    // program with the value of 2
    if (argc != MAIN_ARGC_VALUE) {
        std::cout << "Usage: " << argv[0] << " <startPPM.ppm>";
        exit(EXIT_CODE_INVALID_ARGUMENTS);
    }
    
    Image img;
    std::string filename = argv[1];
    std::cout << "Reading initial image from: " << filename << std::endl;

    // Error checking: the filename should contain a properly formatted 
    // PPM image. If not, exit the program with the value of 3
    if (!img.load(filename)) {
        std::cout << "Image read successful: No" << std::endl;
        std::cout << "Error: While reading the image, an error was" 
          << " encountered. Exiting the program!";
        exit(EXIT_CODE_INVALID_FORMATTED_FILE);
    }
    
    int choice;
    while (true) {
        // Print the Menu
        std::cout << ENCODE_MESSAGE_OPTION << ". Encode a message from file" 
          << std::endl << PERFORM_DECODE_OPTION <<". Perform decode" 
          << std::endl << WRITE_TO_FILE_OPTION 
          << ". Write current image to file" << std::endl 
          << EXIT_OPTION << ". Exit the program" << std::endl << 
          "Enter your choice: ";
        std::cin >> choice;
        
        // Error checking: the "choice" must be an integer. If not, 
        // request input again
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(MAX_IGNORE_CHARS, '\n'); 
            std::cout << "Error: Invalid input. Please enter a number."
              << std::endl;
            continue;
        }
        
        
        if (choice == ENCODE_MESSAGE_OPTION) {
            std::string messageFile;
            std::cout << "Enter name of file containing message: ";
            std::cin >> messageFile;

            int startX, startY;
            std::cout << "Enter row and column for message placement: ";
            std::cin >> startY >> startX;
            
            // Error checking: "startX" and "startY" must be integers. If
            // not, request input again
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(MAX_IGNORE_CHARS, '\n');
                std::cout << "Error: Invalid input for row and column."
                  << std::endl;
                continue;
            }   
            
            img.encodeMessage(messageFile, startX, startY);
        }
        else if (choice == PERFORM_DECODE_OPTION) {
            img.decodeMessage();
        }
        else if (choice == WRITE_TO_FILE_OPTION) {
            std::string outFilename;
            std::cout << "Enter name of file to write image to: ";
            std::cin >> outFilename;
            img.save(outFilename);
        }
        else if (choice == EXIT_OPTION) {
            std::cout << "Thanks for using this program!";
            return MAIN_DEFAULT_RETURN_VALUE;
        }
        else {
            // Error checking: "choice" must be a number between 1 and 4,
            // inclusive. If not, request again.
            std::cout << "Error: Invalid choice. Please enter a number " << 
              "between " << ENCODE_MESSAGE_OPTION << " and " << EXIT_OPTION <<
              "." << std::endl;
        }
    }
    return MAIN_DEFAULT_RETURN_VALUE;
}