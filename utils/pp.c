#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pp.h"

typedef void (*pretty_printer_t)(FILE *, void *);

void ppf(const char *format, ...) {
    va_list args;
    va_start(args, format);

    // Call fppf with stdout as the target file
    fppf(stdout, format, args);

    va_end(args);
}
void fppf(FILE *file, const char *format, ...) {
    va_list args;
    va_start(args, format);

    const char *p = format;

    while (*p) {
        if (*p == '%' && *(p + 1) == 'a') {
            // Handle `%a`
            p += 2; // Skip "%a"

            // Get the pretty printer function and the associated argument
            pretty_printer_t pp = va_arg(args, pretty_printer_t);
            void *data = va_arg(args, void *);

            // Call the pretty-printer
            if (pp) {
                pp(file, data);
            }
        } else {
            // Find the next '%' or end of the format string
            const char *next_percent = strchr(p, '%');
            if (!next_percent) {
                // No more '%' found, print the remaining string
                fputs(p, file);
                break;
            }

            // Print everything up to the next '%'
            fwrite(p, 1, next_percent - p, file);

            // Process the '%' and forward to vfprintf
            p = next_percent;

            if (*(p + 1) == 'a') {
                // `%a` is handled separately (skip it here)
                continue;
            } else {
                // Handle standard printf format specifiers
                const char *spec_start = p++;
                while (*p && strchr("dioxXucsfeEgGp%", *p) == NULL) {
                    ++p; // Advance to find the format specifier
                }
                if (*p)
                    ++p; // Include the specifier

                // Create a temporary format string for this specifier
                size_t len = p - spec_start + 1;
                char *temp_fmt = (char *)malloc(len + 1);
                strncpy(temp_fmt, spec_start, len);
                temp_fmt[len] = '\0';

                // Print the formatted output using vfprintf
                vfprintf(file, temp_fmt, args);
                free(temp_fmt);
            }
        }
    }

    va_end(args);
}
