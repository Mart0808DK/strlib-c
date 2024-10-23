#ifndef STRLIB_H
#define STRLIB_H

#include <stdbool.h>
#include <stdlib.h>

typedef struct {
    char* data;           // Pointer to UTF-8 string
    size_t byte_length;   // Length in bytes
    size_t char_length;   // Length in codepoints
    bool owns_data;       // Flag indicating if we should free data in destructor
} String;

// Constructor and destructor
String str_construct(const char* str);
void str_destruct(String str);
char* str_valueOf(String str);

// String prototypes
String str_at(String str, int index);
String str_charAt(String str, int index);
String str_concat(String str1, String str2);
bool str_endsWith(String str, String searchStr);
bool str_includes(String str, String searchStr);
int str_indexOf(String str, String searchStr);
int str_lastIndexOf(String str, String searchStr);
String str_padEnd(String str, size_t targetLength, String padStr);
String str_padStart(String str, size_t targetLength, String padStr);
String str_repeat(String str, size_t count);
String str_slice(String str, int start, int end);
bool str_startsWith(String str, String searchStr, size_t position);
String str_substring(String str, int start, int end);
String str_toLowerCase(String str);
String str_toUpperCase(String str);
String str_trim(String str);
String str_trimEnd(String str);
String str_trimStart(String str);

#endif