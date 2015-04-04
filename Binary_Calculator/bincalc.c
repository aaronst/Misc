// Aaron Stephens
// Binary Calculator

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// This function scans in a binary
// number and converts it to a double.
double bin2double() {
    char c;           // Current character
    int frac = 0;     // Fraction flag
    int done = 0;     // Done flag
    double po2 = .5;  // Power of 2
    double d = 0.0;   // Converted double

    // Scan in first non-whitespace
    // character.
    scanf(" %c", &c);

    // Continue until break.
    while(1) {

        // Calculating double before
        // the decimal.
        if (!frac) {
            switch (c) {
                case 'Q':
                    exit(0);
                case '1':
                    d *= 2;
                    d += 1;
                    break;
                case '0':
                    d *= 2;
                    break;
                case '.':
                    frac = 1;
                    break;
                default:
                    done = 1;
            }

        // Calculating double after
        // the decimal.
        } else {
            switch (c) {
                case '1':
                    d += po2;
                    po2 /= 2;
                    break;
                case '0':
                    po2 /= 2;
                    break;
                default:
                    done = 1;
            }
        }

        // Finish
        if (done) break;

        // Scan in next character.
        scanf("%c", &c);
    }

    return d;
}

// This function is the opposite of the
// bin2double fun.  It takes a double
// and outputs a binary number to console.
void double2bin(double d) {
    // Handles negative doubles.
    if (d < 0) {
        printf("-");
        d *= -1;
    }

    // Calculating correct power of 2.
    double po2 = 1.0;
    while (po2 <= d) po2 *= 2;
    po2 /= 2;

    // Calculating binary number before
    // the decimal.
    int before = 0;
    while (po2 >= 1) {
        if (d >= po2) {
            d -= po2;
            printf("1");
        } else {
            printf("0");
        }
        po2 /= 2;
        before++;
    }

    // Formatting to make sure at least
    // one 0 before decimal.
    if (before == 0) {
        printf("0.");
    } else {
        printf(".");
    }

    // Calculating binary number after
    // the decimal.
    if (d == 0) {
        printf("0");
    } else {
        int after = 0;
        while (d != 0 && after < 20) {
            if (d >= po2) {
                d -= po2;
                printf("1");
            } else {
                printf("0");
            }
            po2 /= 2;
            after++;
        }
    }

    printf("\n");
}

int main(void) {
    double a = 0;      // First operand
    double b = 0;      // Second operand
    double result;     // Result of operation
    char o;            // Operator
    int badop = 0;     // Bad operator flag
    
    // Run forever.
    while (1) {

        // Convert first operand into double.
        a = bin2double();

        // Scan in operator.
        scanf(" %c", &o);

        // Convert second operand into double.
        b = bin2double();

        // Perform operation.
        switch (o) {
            case '+':
                result = a + b;
                break;
            case '-':
                result = a - b;
                break;
            case '*':
                result = a * b;
                break;
            case '/':
                result = a / b;
                break;
            default:
                badop = 1;
        }

        // Don't attempt to print out a result
        // if bad operator was scanned in.
        if (badop == 1) {
            badop = 0;
            continue;
        }

        // Convert result back into binary
        // and print to console.
        double2bin(result);
    }

    return 0;
}
