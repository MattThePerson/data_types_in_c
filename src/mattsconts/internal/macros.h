// NOTE: Currently unused!

#ifndef MATTSCONTS_MACROS_H
#define MATTSCONTS_MACROS_H

#define COLOR_RED "\x1b[31m"
#define COLOR_RESET "\x1b[0m"

// for making sure your library internally functions as expected, like
// additional tests. E.G. throw if a pointer is not null
#define INTERNAL_ERR(...)                                                      \
    do {                                                                       \
        fprintf(stderr,                                                        \
                COLOR_RED "[INTERNAL_ERROR] " COLOR_RESET __VA_ARGS__);        \
        exit(1);                                                               \
    } while (0)

#endif // MATTSCONTS_MACROS_H
