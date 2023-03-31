#ifndef __ERROR_H__
#define __ERROR_H__

// Errors enum for the library
typedef enum {
    OK = 0,
    ERR_NOT_IMPLEMENTED = -1,
    ERR_INVALID = -2,
    ERR_MEMORY_ERROR = -3,
    ERR_NOT_FOUND = -4,
    ERR_DUPLICATED = -5,
    ERR_INVALID_INDEX = -6,
    ERR_EMPTY = -7,
    ERR_EMPTY_LIST = -8,
	ERR_INVALID_COUNTRY= -9,
	ERR_INVALID_VACCINE= -10
} tError;

#endif // __ERROR_H__
