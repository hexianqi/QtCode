#ifndef HDESIGNPATTERN_H
#define HDESIGNPATTERN_H

#ifndef SAFE_DELETE
    #define SAFE_DELETE(p) { if (p) { delete(p); (p) = nullptr; } }
#endif

#ifndef GET_ARRAY_LEN
    #define GET_ARRAY_LEN(array, len) { len = (sizeof(array) / sizeof(array[0])); }
#endif

#endif // HDESIGNPATTERN_H
