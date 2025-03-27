/**
 * @file constants.h
 *
 * This header file defines constants used in the program, including 
 * image format specifications, menu options, color encoding values, 
 * and exit codes for error handling.
 *
 * @author Yiwei Gui
 * @date 3/21/2025
 */

#ifndef CONSTANTS_H
#define CONSTANTS_H

const std::string PPM_MAGIC_NUMBER = "P3";

const int MAX_COLOR_VALUE = 255;
const int MIN_COLOR_VALUE = 0;
const int MIN_IMAGE_SIZE = 1;
const int MAX_IMAGE_SIZE = 2000;


const int ENCODE_MESSAGE_OPTION = 1;
const int PERFORM_DECODE_OPTION = 2;
const int WRITE_TO_FILE_OPTION = 3;
const int EXIT_OPTION = 4;


const int BLACK = 0;
const int BLACK_BIN = 0b000;
const int RED = 1;
const int RED_BIN = 0b100;
const int GREEN = 2;
const int GREEN_BIN = 0b010;
const int BLUE = 3;
const int BLUE_BIN = 0b001;
const int WHITE = 4;
const int WHITE_BIN = 0b111;
const int YELLOW = 5;
const int YELLOW_BIN = 0b110;
const int MAGENTA = 6;
const int MAGENTA_BIN = 0b101;
const int CYAN = 7;
const int CYAN_BIN = 0b011;

const int MAX_IGNORE_CHARS = 10000;

const int EXIT_CODE_INVALID_ARGUMENTS = 2;
const int EXIT_CODE_INVALID_FORMATTED_FILE = 3;

const int MAX_ENCODING_VALUE = 7;
const int MIN_ENCODING_VALUE = 0;

const int DECODE_DEFAULT_RETURN_VALUE = -1;
const int MAIN_DEFAULT_RETURN_VALUE = 0;
const int MAIN_ARGC_VALUE = 2;
#endif