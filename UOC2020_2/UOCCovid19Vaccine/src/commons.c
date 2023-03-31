#include "commons.h"

/*****************************************************************
 * You can add general functions here. For example: data compare *
 *****************************************************************/

// Compare two dates. Return true if they are equal.
bool date_equal(tDate date1, tDate date2) {
    return date1.day == date2.day && date1.month == date2.month && date1.year == date2.year;
}
