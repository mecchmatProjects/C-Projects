#include "DPoly.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/* A function for assertions to request a pointer to a valid
 * dpoly structure.
 */
static inline int _dpoly_valid(const dpoly* poly) {
    return poly && (poly->size == 0 || (poly->size > 0 && poly->coefficients));
}

/* Error handler.
 * Terminates the program after printing a diagnostic
 */
static void _error(const char* message) {
    fprintf(stderr, "ERROR: %s\n", message);
    exit(1);
}

/*
 * Allocates the memory for the polynomial coefficients
 * _without_ initializing them.
 *
 * Should be used only when the coefficients will be initialized
 * immediately after the call
 */
static void _dpoly_allocate(dpoly* poly, int size) {
    assert(poly && size >= 0);

    if (size == 0) {
        poly->coefficients = NULL;
        poly->size = 0;
    } else {
        poly->coefficients = (dtype*)malloc(sizeof(dtype) * size);
        if (!poly->coefficients) {
            _error("Failed to allocate memory");
        }
        poly->size = size;
    }
}

/* Resizes the polynomial, adding zero zoefficients if the size is
 * larger than the current one, or removing larger coefficients, if
 * it is smaller.
 */
static void _dpoly_resize(dpoly* poly, int size) {
    assert(_dpoly_valid(poly) && size >= 0);

    if (size == 0) {
        /* Uses the fact that the `dpoly` structure is a valid
         * zero-sized polynomial after calling `dpoly_destroy` */
        dpoly_destroy(poly);
    } else {
        poly->coefficients = (dtype*)realloc(poly->coefficients, sizeof(dtype) * size);
        if (!poly->coefficients) {
            _error("Failed to allocate memory");
        }
        /* fill the new coefficients with zeroes */
        if (poly->size < size) {
            memset(poly->coefficients + poly->size, 0, sizeof(dtype) * (size - poly->size));
        }
        poly->size = size;
    }
}

/* Reduces the allocated space for the polynomial, removing highest
 * zero coefficients */
static void _dpoly_slim(dpoly* poly) {
    assert(_dpoly_valid(poly));

    while (poly->size > 1 && poly->coefficients[poly->size - 1] == 0.) {
        --poly->size;
    }
    poly->coefficients = (dtype*)realloc(poly->coefficients, sizeof(dtype) * poly->size);
    if (!poly->coefficients) {
        _error("Failed to allocate memory");
    }
}

void dpoly_zero(dpoly* poly, int size) {
    assert(poly && size >= 0);

    _dpoly_allocate(poly, size);

    /* fill the coefficient array with zeroes */
    memset(poly->coefficients, 0, size * sizeof(dtype));
}

void dpoly_generate(dpoly* poly, int size) {
    assert(poly && size >= 0);

    _dpoly_allocate(poly, size);

    for (int i = 0; i < size; ++i) {
        /* choses random coefficients from -1000 .. 1000 range */
        poly->coefficients[i] = 2000. * ((double)rand() / RAND_MAX) - 1000;
    }
}

void dpoly_destroy(dpoly* poly) {
    assert(_dpoly_valid(poly));

    free(poly->coefficients);
    poly->coefficients = NULL;
    poly->size = 0;
}

void dpoly_copy(const dpoly* poly, dpoly* dest) {
    assert(_dpoly_valid(poly) && dest);

    _dpoly_allocate(dest, poly->size);
    /* copy the coefficients array from `poly` to `dest` */
    memcpy(dest->coefficients, poly->coefficients, poly->size * sizeof(dtype));
}

/* adds a term "coef * x^order" to the polynomial, resizing it
 * if needed */
static void _dpoly_add_term(dpoly* poly, int order, dtype coef) {
    assert(_dpoly_valid(poly) && order >= 0);

    /* check if we need to resize the polynomial */
    if (order >= poly->size) {
        /* if we resize, increase the size at least by half of the
         * previous size to avoid quadratic time, when building
         * the polynomial from the lowest order */
        int ns = poly->size + (poly->size >> 1);
        if (order >= ns) {
            ns = order + 1;
        }
        _dpoly_resize(poly, ns);
    }
    poly->coefficients[order] += coef;
}

/* A string containing symbols considered to be whitespace */
static const char* wspace = " \f\n\r\t\v";

/* main part of the string input function*/
int _dpoly_sinput_sub(dpoly* poly, const char* s) {
    assert(poly && s);

    dpoly_zero(poly, 16);
    int ncoef = 0;
    for (const char* c = s; *c != 0; ) {
        /* skip leading whitespaces */
        c += strspn(c, wspace);
        int sign = 0;
        /* find the sign */
        if (*c == '+') {
            sign = 1;
            ++c;
            c += strspn(c, wspace);
        } else if (*c == '-') {
            sign = -1;
            ++c;
            c += strspn(c, wspace);
        }

        /* the only coefficient without sign can be the first one
         * for others we got an error */
        if (sign == 0 && ncoef > 0) {
            return ncoef;
        }

        /* read the coefficient */
        const char* end;
        /* Read the double coefficient from the string
         *
         * Yes, strtod _requires_ the second parameter to be modifiable
         * even when the first one is 'const char*'
         * This was done to preserve existing non-const correct code
         * Nothing we can do here, just bear it. */
        dtype coef = strtod(c, (char**)&end);

        /* skipped coefficient means 1 */
        int coef_skipped = 0;
        if (c == end) {
            coef = 1.0;
            coef_skipped = 1;
        }

        c = end;

        /* apply sign if needed */
        if (sign == -1) {
            coef = -coef;
        }

        /* skip whitespace after the coefficient */
        c += strspn(c, wspace);

        /* process the optional '*' sign between the coefficient and the order */
        int star_given = 0;
        if (*c == '*') {
            ++c;
            c += strspn(c, wspace);
            /* star can not follow a skipped coefficient */
            if (coef_skipped) {
                return ncoef;
            }
        }

        int x_skipped = 1;
        int order = 0;
        if (*c == 'x') {
            ++c;
            c += strspn(c, wspace);
            x_skipped = 0;
            /* no power means the same as 'x^1' */
            order = 1;
            if (*c == '^') {
                ++c;
                c += strspn(c, wspace);
                const char* end;
                /* Read an integer (base 10) order */
                order = strtol(c, (char**)&end, 10);
                /* order must be nonempty and nonnegatve */
                if (end == c || order < 0) {
                    return ncoef;
                }
                c = end;
            }
        }
        /* can not skip 'x' if we already have skipped the coefficient or have written a star */
        if (x_skipped && (coef_skipped || star_given)) {
            return ncoef;
        }

        _dpoly_add_term(poly, order, coef);
        ++ncoef;
    }
    return ncoef;
}

int dpoly_sinput(dpoly* poly, const char* s) {
    assert(poly && s);

    int n = _dpoly_sinput_sub(poly, s);
    _dpoly_slim(poly);
    return n;
}

/* Reads a line of arbitrary length from file
 * The line returned must be `free`d after use */
char* _readline(FILE* file) {
    assert(file);

    int size = 0;
    int len = 0;
    int last = 0;
    char* buf = NULL;


    do {
        /* Increase the buffer by either half its length, or BUFSIZ,
         * whatever is larger */
        int dsize = size >> 1;
        if (dsize < BUFSIZ) {
            dsize = BUFSIZ;
        }
        size += dsize;
        /* Increase the size of the string buffer
         * When buf == NULL 'realloc(NULL, size)' is the same as
         * 'malloc(size)'
         */
        buf = (char*)realloc(buf, size);
        if (!buf) {
            _error("Failed to allocate memory");
        }

        /* Reads the remaining part of the string
         *
         * Nonzero return may mean either reaching end of file,
         * which is ok,
         * or another error on which we call an error handler
         *
         * If the last symbol is '\n' we have finished reading the line
         * otherwise we need to increase our buffer and continue reading*/
        if (!fgets(buf + last, size - last, file)) {
            if (feof(file)) {
                break;
            } else {
                _error("Error reading file");
            }
        }
        len = last + strlen(buf + last);
        last = len - 1;
    } while(buf[last] != '\n');
    buf[len] = 0;
    return buf;
}

int dpoly_finput(dpoly* poly, FILE* file) {
    assert(poly && file);

    char* str = _readline(file);

    int ncoef = dpoly_sinput(poly, str);
    free(str);
    return ncoef;
}

int dpoly_input(dpoly* poly) {
    assert(poly);

    return dpoly_finput(poly, stdin);
}

/* main part of the string read function */
int _dpoly_sread_text_sub(dpoly* poly, const char* s) {
    assert(poly && s);

    dpoly_zero(poly, 16);
    int ncoef = 0;
    for (const char* c = s; *c != 0; ) {
        /* skip leading whitespaces */
        c += strspn(c, wspace);
        const char* end;

        /* read a double coefficient */
        dtype coef = strtod(c, (char**)&end);

        if (c == end) {
            return ncoef;
        }
        c = end;
        _dpoly_add_term(poly, ncoef, coef);
        ++ncoef;
    }
    return ncoef;
}

int dpoly_sread_text(dpoly* poly, const char* s) {
    assert(poly && s);

    int n = _dpoly_sread_text_sub(poly, s);
    _dpoly_slim(poly);
    return n;
}

int dpoly_fread_text(dpoly* poly, FILE* file) {
    assert(poly && file);

    char* str = _readline(file);
    int ncoef = dpoly_sread_text(poly, str);
    free(str);
    return ncoef;
}

int dpoly_read_text(dpoly* poly) {
    assert(poly);

    return dpoly_fread_text(poly, stdin);
}

int dpoly_fread_binary(dpoly* poly, FILE* file) {
    assert(poly && file);

    int size;
    int nsize = fread(&size, sizeof size, 1, file);
    if (nsize != 1) {
        _error("Binary file too short");
    }
    if (size < 0) {
        _error("Negative polynomial size");
    }
    _dpoly_allocate(poly, size);
    int ncoef = fread(poly->coefficients, sizeof(dtype), size, file);
    if (ncoef != size) {
        _error("Binary file too short");
    }
    return size;
}

/* reserves a string buffer for at least `nchars` extra characters */
static void _buf_reserve(char** buf, int* size, int* capacity, int nchars) {
    assert(buf && *size >= 0 && *capacity > *size);
    int newsize = *size + nchars;
    /* check if the buffer has enough capacity */
    if (newsize >= *capacity) {
        /* increase capacity by at least half of the old value */
        int newcap = *capacity + (*capacity >> 1);
        if (newsize >= newcap) {
            newcap = newsize + 1;
        }

        *buf = (char*)realloc(*buf, newcap);
        if (!*buf) {
            _error("Failed to allocate memory");
        }

        *capacity = newcap;
    }
}

/* append an integer 'n' to the buffer */
static inline void _buf_append_int(char** buf, int* size, int* capacity, int n) {
    assert(buf && *size >= 0 && *capacity >= *size);

    /* calling snprintf with NULL as destination buffer just returns
     * the number of characters to be printed */
    int nchars = snprintf(NULL, 0, "%d", n);
    /* snprintf returns negative values in case of an error */
    if (nchars < 0) {
        _error("printing failure");
    }
    _buf_reserve(buf, size, capacity, nchars);
    nchars = snprintf(*buf + *size, nchars + 1, "%d", n);
    *size += nchars;
}

/* append a string 's' to the buffer */
static inline void _buf_append_string(char** buf, int* size, int* capacity, const char* s) {
    assert(buf && *size >= 0 && *capacity >= *size);

    int nchars = strlen(s);
    _buf_reserve(buf, size, capacity, nchars);
    strcpy(*buf + *size, s);
    *size += nchars;
}

/* append a double 'n' to the buffer */
static inline void _buf_append_dtype(char** buf, int* size, int* capacity, dtype n) {
    assert(buf && *size >= 0 && *capacity >= *size);

    /* calling snprintf with NULL as destination buffer just returns
     * the number of characters to be printed */
    int nchars = snprintf(NULL, 0, "%g", n);
    /* snprintf returns negative values in case of an error */
    if (nchars < 0) {
        _error("printing failure");
    }
    _buf_reserve(buf, size, capacity, nchars);
    nchars = snprintf(*buf + *size, nchars + 1, "%g", n);
    *size += nchars;
}


char* dpoly_sprint(const dpoly* poly) {
    assert(_dpoly_valid(poly));

    int size = 0;
    int capacity = 1024;
    char* buf = (char*)malloc(capacity);
    if (!buf) {
        _error("Failed to allocate memory");
    }
    buf[0] = 0;

    int first = 1;
    for (int i = 0; i < poly->size; ++i) {
        dtype coef = poly->coefficients[i];
        if (coef != 0.) {
            if (coef > 0) {
                if (first) {
                    first = 0;
                    if (coef != 1. || i == 0) {
                        _buf_append_dtype(&buf, &size, &capacity, coef);
                        if (i >= 1) {
                            _buf_append_string(&buf, &size, &capacity, " ");
                        }
                    }
                    if (i == 1) {
                        _buf_append_string(&buf, &size, &capacity, "x");
                    } else if (i > 1) {
                        _buf_append_string(&buf, &size, &capacity, "x^");
                        _buf_append_int(&buf, &size, &capacity, i);
                    }
                } else {
                    if (coef != 1. || i == 0) {
                        _buf_append_string(&buf, &size, &capacity, " + ");
                    } else {
                        _buf_append_string(&buf, &size, &capacity, " +");
                    }
                    if (coef != 1. || i == 0) {
                        _buf_append_dtype(&buf, &size, &capacity, coef);
                    }
                    if (i == 1) {
                        _buf_append_string(&buf, &size, &capacity, " x");
                    } else if (i > 1) {
                        _buf_append_string(&buf, &size, &capacity, " x^");
                        _buf_append_int(&buf, &size, &capacity, i);
                    }
                }
            } else {
                if (first) {
                    _buf_append_string(&buf, &size, &capacity, "-");
                    first = 0;
                    if (coef != -1. || i == 0) {
                        _buf_append_dtype(&buf, &size, &capacity, -coef);
                        if (i >= 1) {
                            _buf_append_string(&buf, &size, &capacity, " ");
                        }
                    }
                    if (i == 1) {
                        _buf_append_string(&buf, &size, &capacity, "x");
                    } else if (i > 1) {
                        _buf_append_string(&buf, &size, &capacity, "x^");
                        _buf_append_int(&buf, &size, &capacity, i);
                    }
                } else {
                    if (coef != -1. || i == 0) {
                        _buf_append_string(&buf, &size, &capacity, " - ");
                    } else {
                        _buf_append_string(&buf, &size, &capacity, " -");
                    }
                    if (coef != -1. || i == 0) {
                        _buf_append_dtype(&buf, &size, &capacity, -coef);
                    }
                    if (i == 1) {
                        _buf_append_string(&buf, &size, &capacity, " x");
                    } else if (i > 1) {
                        _buf_append_string(&buf, &size, &capacity, " x^");
                        _buf_append_int(&buf, &size, &capacity, i);
                    }
                }
            }
        }
    }
    if (first) {
        _buf_append_string(&buf, &size, &capacity, "0");
    }
    return buf;
}

void dpoly_fprint(const dpoly* poly, FILE* f) {
    assert(_dpoly_valid(poly) && f);

    int first = 1;
    for (int i = 0; i < poly->size; ++i) {
        dtype coef = poly->coefficients[i];
        if (coef != 0.) {
            if (coef > 0) {
                if (first) {
                    first = 0;
                    if (coef != 1. || i == 0) {
                        fprintf(f, "%g", coef);
                        if (i >= 1) {
                            fprintf(f, " ");
                        }
                    }
                    if (i == 1) {
                        fprintf(f, "x");
                    } else if (i > 1) {
                        fprintf(f, "x^%d", i);
                    }
                } else {
                    if (coef != 1. || i == 0) {
                        fprintf(f, " + ");
                    } else {
                        fprintf(f, " +");
                    }
                    if (coef != 1. || i == 0) {
                        fprintf(f, "%g", coef);
                    }
                    if (i == 1) {
                        fprintf(f, " x");
                    } else if (i > 1) {
                        fprintf(f, " x^%d", i);
                    }
                }
            } else {
                if (first) {
                    fprintf(f, "-");
                    first = 0;
                    if (coef != -1. || i == 0) {
                        fprintf(f, "%g", -coef);
                        if (i >= 1) {
                            fprintf(f, " ");
                        }
                    }
                    if (i == 1) {
                        fprintf(f, "x");
                    } else if (i > 1) {
                        fprintf(f, "x^%d", i);
                    }
                } else {
                    if (coef != -1. || i == 0) {
                        fprintf(f, " - ");
                    } else {
                        fprintf(f, " -");
                    }
                    if (coef != -1. || i == 0) {
                        fprintf(f, "%g", -coef);
                    }
                    if (i == 1) {
                        fprintf(f, " x");
                    } else if (i > 1) {
                        fprintf(f, " x^%d", i);
                    }
                }
            }
        }
    }
    if (first) {
        fprintf(f, "0");
    }
    fprintf(f, "\n");
}

void dpoly_print(const dpoly* poly) {
    assert(_dpoly_valid(poly));

    dpoly_fprint(poly, stdout);
}


char* dpoly_swrite_text(const dpoly* poly) {
    assert(_dpoly_valid(poly));

    int size = 0;
    int capacity = 1024;
    char* buf = (char*)malloc(capacity);
    if (!buf) {
        _error("Failed to allocate memory");
    }
    buf[0] = 0;

    if (poly->size > 0) {
        _buf_append_dtype(&buf, &size, &capacity, poly->coefficients[0]);
    }

    for (int i = 1; i < poly->size; ++i) {
        _buf_append_string(&buf, &size, &capacity, " ");
        _buf_append_dtype(&buf, &size, &capacity, poly->coefficients[i]);
    }
    return buf;
}

void dpoly_fwrite_text(const dpoly* poly, FILE* file) {
    assert(_dpoly_valid(poly) && file);

    if (poly->size > 0) {
        fprintf(file, "%g", poly->coefficients[0]);
    }

    for (int i = 1; i < poly->size; ++i) {
        fprintf(file, " %g", poly->coefficients[i]);
    }
    fprintf(file, "\n");
}

void dpoly_write_text(const dpoly* poly) {
    assert(_dpoly_valid(poly));

    dpoly_fwrite_text(poly, stdout);
}

void dpoly_fwrite_binary(const dpoly* poly, FILE* file) {
    assert(_dpoly_valid(poly) && file);

    if (fwrite(&poly->size, sizeof poly->size, 1, file) != 1) {
        _error("Writing to the binary file failed");
    }

    if ((int)fwrite(poly->coefficients, sizeof(dtype), poly->size, file) != poly->size) {
        _error("Writing to the binary file failed");
    }
}

dtype dpoly_value_at(const dpoly* poly, dtype x) {
    assert(_dpoly_valid(poly));

    dtype res = 0.;
    /* calculate the polynomial at x using Horner's method */
    for (int i = poly->size - 1; i >= 0; --i) {
        res = res * x + poly->coefficients[i];
    }
    return res;
}

void dpoly_add_assign(dpoly* lhs, const dpoly* rhs) {
    assert(_dpoly_valid(lhs) && _dpoly_valid(rhs));

    if (rhs->size > lhs->size) {
        _dpoly_resize(lhs, rhs->size);
    }

    for (int i = 0; i < rhs->size; ++i) {
        lhs->coefficients[i] += rhs->coefficients[i];
    }

    _dpoly_slim(lhs);
}

void dpoly_add(const dpoly* lhs, const dpoly* rhs, dpoly* res) {
    assert(_dpoly_valid(lhs) && _dpoly_valid(rhs) && res);

    dpoly_copy(lhs, res);
    dpoly_add_assign(res, rhs);
}

void dpoly_mul(const dpoly* lhs, const dpoly* rhs, dpoly* res) {
    assert(_dpoly_valid(lhs) && _dpoly_valid(rhs) && res);

    dpoly_zero(res, lhs->size + rhs->size - 1);

    for (int i = 0; i < lhs->size; ++i) {
        for (int j = 0; j < rhs->size; ++j) {
            res->coefficients[i + j] += lhs->coefficients[i] * rhs->coefficients[j];
        }
    }

    _dpoly_slim(res);
}


void dpoly_mul_assign(dpoly* lhs, const dpoly* rhs) {
    assert(_dpoly_valid(lhs) && _dpoly_valid(rhs));

    dpoly res;
    dpoly_mul(lhs, rhs, &res);

    /* destroy old_value of lhs
     * and move res to lhs
     * Since we do not need res anymore we can just use structure assignment.
     * of course in this case res should not be destoyed */
    dpoly_destroy(lhs);
    *lhs = res;
}

/* A helper function to implement div and mod functions:
 * Calculates lhs / rhs into div (if div is not a NULL pointer),
 * and reassigns lhs to lhs % rhs
 */
static void _dpoly_divmod_helper(dpoly* lhs, const dpoly* rhs, dpoly* div) {
    assert(_dpoly_valid(lhs) && _dpoly_valid(rhs));

    /* highest order of a nonzero coefficient in rhs */
    int rhead = rhs->size - 1;
    while (rhead >= 0 && rhs->coefficients[rhead] == 0.) {
        --rhead;
    }
    if (rhead < 0) {
        _error("Division by zero");
    }

    dtype rhead_inverse = 1. / rhs->coefficients[rhead];

    /* highest order of a nonzero coefficient in lhs */
    int lhead = lhs->size - 1;
    while (lhead >= 0 && lhs->coefficients[lhead] == 0.) {
        --lhead;
    }
    /* if order of lhs is less than the order of rhs than div is 0, mod is lhs */
    if (lhead < rhead) {
        if (div) {
            dpoly_zero(div, 1);
        }
        return;
    }

    if (div) {
        _dpoly_allocate(div, lhead - rhead + 1);
    }

    for (; lhead >= rhead; --lhead) {
        if (lhs->coefficients[lhead] != 0.) {
            dtype r = lhs->coefficients[lhead] * rhead_inverse;
            if (div) {
                div->coefficients[lhead - rhead] = r;
            }
            for (int i = 0; i < rhead; ++i) {
                lhs->coefficients[lhead - rhead + i] -= rhs->coefficients[i] * r;
            }
            lhs->coefficients[lhead] = 0.;
        } else if (div) {
            div->coefficients[lhead - rhead] = 0.;
        }
    }

    if (div) {
        _dpoly_slim(div);
    }

    _dpoly_slim(lhs);
}

void dpoly_divmod(const dpoly* lhs, const dpoly* rhs, dpoly* div, dpoly* mod) {
    assert(_dpoly_valid(lhs) && _dpoly_valid(rhs) && div && mod);

    dpoly_copy(lhs, mod);
    _dpoly_divmod_helper(mod, rhs, div);
}

void dpoly_div(const dpoly* lhs, const dpoly* rhs, dpoly* res) {
    assert(_dpoly_valid(lhs) && _dpoly_valid(rhs) && res);

    dpoly mod;
    dpoly_copy(lhs, &mod);
    _dpoly_divmod_helper(&mod, rhs, res);
    dpoly_destroy(&mod);
}


void dpoly_mod(const dpoly* lhs, const dpoly* rhs, dpoly* res) {
    assert(_dpoly_valid(lhs) && _dpoly_valid(rhs) && res);

    dpoly_copy(lhs, res);
    _dpoly_divmod_helper(res, rhs, NULL);
}





void dpoly_div_assign(dpoly* lhs, const dpoly* rhs) {
    assert(_dpoly_valid(lhs) && _dpoly_valid(rhs));

    dpoly res;
    dpoly_div(lhs, rhs, &res);

    /* destroy old_value of lhs and move res to lhs
     * Since we do not need res anymore we can just use structure assignment.
     * of course in this case res should not be destoyed */
    dpoly_destroy(lhs);
    *lhs = res;
}


void dpoly_mod_assign(dpoly* lhs, const dpoly* rhs) {
    assert(_dpoly_valid(lhs) && _dpoly_valid(rhs));

    _dpoly_divmod_helper(lhs, rhs, NULL);
}


void dpoly_modulo_add(const dpoly* lhs, const dpoly* rhs, const dpoly* modulo, dpoly* res) {
    assert(_dpoly_valid(lhs) && _dpoly_valid(rhs) && _dpoly_valid(modulo) && res);

    dpoly_add(lhs, rhs, res);
    dpoly_mod_assign(res, modulo);
}

void dpoly_modulo_add_assign(dpoly* lhs, const dpoly* rhs, const dpoly* modulo) {
    assert(_dpoly_valid(lhs) && _dpoly_valid(rhs) && _dpoly_valid(modulo));

    dpoly_add_assign(lhs, rhs);
    dpoly_mod_assign(lhs, modulo);
}

void dpoly_modulo_mul(const dpoly* lhs, const dpoly* rhs, const dpoly* modulo, dpoly* res) {
    assert(_dpoly_valid(lhs) && _dpoly_valid(rhs) && _dpoly_valid(modulo) && res);

    dpoly_mul(lhs, rhs, res);
    dpoly_mod_assign(res, modulo);
}

void dpoly_modulo_mul_assign(dpoly* lhs, const dpoly* rhs, const dpoly* modulo) {
    assert(_dpoly_valid(lhs) && _dpoly_valid(rhs) && _dpoly_valid(modulo));

    dpoly_mul_assign(lhs, rhs);
    dpoly_mod_assign(lhs, modulo);
}

void dpoly_derivative(const dpoly* poly, dpoly* res) {
    assert(_dpoly_valid(poly) && res);

    _dpoly_allocate(res, poly->size - 1);
    for (int i = 1; i < poly->size; ++i) {
        res->coefficients[i - 1] = i * poly->coefficients[i];
    }

    _dpoly_slim(res);
}

dtype dpoly_derivative_at(const dpoly* poly, dtype x0) {
    assert(_dpoly_valid(poly));

    dtype res = 0.;
    for (int i = poly->size - 1; i >= 1; --i) {
        res = res * x0 + i * poly->coefficients[i];
    }
    return res;
}

void dpoly_indefinite_integral(const dpoly* poly, dpoly* res) {
    assert(_dpoly_valid(poly) && res);

    _dpoly_allocate(res, poly->size + 1);
    /* the constant term can be anything just set it to 0 */
    res->coefficients[0] = 0.;
    for (int i = 0; i < poly->size; ++i) {
        res->coefficients[i + 1] = poly->coefficients[i] / (i + 1);
    }

    _dpoly_slim(res);
}

dtype dpoly_definite_integral(const dpoly* poly, dtype low_bound, dtype high_bound) {
    assert(_dpoly_valid(poly));

    dtype res_low = 0.;
    dtype res_high = 0.;
    for (int i = poly->size - 1; i >= 0; --i) {
        dtype coef = poly->coefficients[i] / (i + 1);
        res_low = res_low * low_bound + coef;
        res_high = res_high * high_bound + coef;
    }
    /* take in accout an extra power of x due to integration */
    res_low *= low_bound;
    res_high *= high_bound;
    return res_high - res_low;
}
