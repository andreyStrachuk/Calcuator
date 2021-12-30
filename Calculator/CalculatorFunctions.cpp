#include "Calculator.h"

static const char strLN[] = "ln";
static const char strSIN[] = "sin";
static const char strCOS[] = "cos";
static const double POISON = 1488228;

double GetG (char **exp) {
    assert (exp);

    double val1 = GetE (exp);

    double val2 = GetN (exp);

    if (**exp == '\n') {
        return val1 + val2;
    }
    else {
        return 0;
    }
}

double GetE (char **exp) {
    assert (exp);

    double val1 = GetT (exp);

    while (**exp == '+' || **exp == '-') {
        char sign = **exp;
        (*exp)++;

        int val2 = GetT (exp);

        if (sign == '+') val1 += val2;
        else val1 -= val2; 
    }

    return val1;
}

double GetT (char **exp) {
    assert (exp);

    double val1 = GetP (exp);

    while (**exp == '*' || **exp == '/') {
        char symbol = **exp;

        (*exp)++;

        double val2 = GetP (exp);

        if (symbol == '*') val1 *= val2;
        else val1 /= val2;
    }

    return val1;
}

double GetP (char **exp) {
    assert (exp);

    if (**exp == '(') {
        (*exp)++;

        double val = GetE (exp);

        Require (exp, ')');

        return val;

    }
    else if (isalpha (**exp)) {
        char func[50] = {};

        GetString (func, exp);

        Require (exp, '(');

        double val = GetE(exp);

        Require (exp, ')');

        val = DoMathFunction (func, val);

        return val;
    }
    else {
        return GetN (exp);
    }
}

double GetN (char **exp) {
    assert (exp);

    double val = 0;
    int n = 0;

    sscanf (*exp, "%lg%n", &val, &n);

    (*exp) += n;

    return val;
}

int GetFileSize (FILE *txtFile) {
    assert (txtFile);

    int numberOfSymbols = 0;

    fseek (txtFile, 0, SEEK_END);

    numberOfSymbols = ftell (txtFile);

    fseek (txtFile, 0, SEEK_SET);

    return numberOfSymbols;
}

void Require (char **exp, char symbol) {
    assert (exp);

    if (**exp != symbol) {
        printf ("Syntax error!\n");
        abort ();
    }

    (*exp)++;
}

int GetString (char *str, char **exp) {
    assert (str);
    assert (exp);

    int length = 0;

    while (isalpha (**exp)) {
        str [length] = **exp;
        (*exp)++;
        length++;
    }

    str [length] = '\0';

    return length;
}

double DoMathFunction (char *funcName, double val) {
    assert (funcName);

    if (STR_EQ (strSIN, funcName)) {
        return sin (val);
    }
    else if (STR_EQ (strCOS, funcName)) {
        return cos (val);
    }
    else if (STR_EQ (strLN, funcName)) {
        return log (val);
    }
    else {
        SyntaxError ();
    }

    return POISON;
}

void SyntaxError () {
    printf ("Syntax error!\n");

    exit (1);
}