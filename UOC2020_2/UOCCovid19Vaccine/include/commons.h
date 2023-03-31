#ifndef __COMMONS_H__
#define __COMMONS_H__

#include <stdbool.h>

// Definition of a Date data type
typedef struct {
    int day;
    int month;
    int year;
} tDate;

bool date_equal(tDate date1, tDate date2);

#endif // __COMMONS_H__
