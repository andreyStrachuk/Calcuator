#ifndef CALCULATOR_H
#define CALCULATOR_H

#define ASSERT_OK(smth, doSmth)         do { if (smth) { doSmth;}} while (0)

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#define STR_EQ(str1, str2)             (strncmp (str1, str2, strlen (str1)) == 0)

enum FUNCTION_TYPES {
    NOTFOUND,
    COS,
    SIN,
    LN
};

int GetFileSize (FILE *txtFile);

double GetN (char **exp);

double GetG (char **exp);

double GetE (char **exp);

double GetT (char **exp);

double GetP (char **exp);

double GetF (char **exp);

void Require (char **exp, char symbol);

int CheckFunction (char *func);

int GetString (char *str, char **exp);

double DoMathFunction (char *funcName, double val);

void SyntaxError ();

#endif