#include "Calculator.h"

int main () {
    FILE *exp = fopen ("example.txt", "r");
    ASSERT_OK (exp == nullptr, return 0);

    int fileSize = GetFileSize (exp);

    char *expression = (char *)calloc (fileSize + 1, sizeof (char));
    ASSERT_OK (expression == nullptr, return 0);

    fileSize = fread (expression, sizeof (char), fileSize, exp);

    double val = GetG (&expression);

    printf ("val = %lg\n", val);

    return 0;
}