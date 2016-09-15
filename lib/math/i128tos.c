#include <stdlib.h>
#include <stdbool.h>

static char *table = "0123456789abcdefghijklnmopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

static int iter(__int128 n, char *out, int offset, int scale) {
    if (n == 0) {
        return offset;
    }
    int o = iter(n / scale, out, offset, scale);

    if (out)
        out[o++] = table[n % scale];

    return o;
}

/**
 * Convert an __int128 to decimal.
 * 
 * If the scale is invalid then returns 0
 * 
 * @param n __int128 to convert
 * @param out buffer of sufficient size, NULL to calculate length
 * @param scale scale. 2=binary, 10=decimal, 16=hexadecimal, min 2 max 62
 * @return length of the generated string
 */
int uint128_to_str(__int128 n, char*out, int scale) {
    if (scale < 2 || scale > 62) {
        if (out)
            out[0] = 0;
        return 0;
    }

    int o = 0;
    if (n < 0) {
        if (out)
            out[0] = '-';
        o = iter(-n, out, 1, scale);
    } else
        o = iter(n, out, 0, scale);

    if (out)
        out[o] = 0;

    return o;
}
