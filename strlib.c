#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "strlib.h"

// Helper functions
static int utf8_char_size(const char *s)
{
    if ((*s & 0x80) == 0)
        return 1;
    else if ((*s & 0xE0) == 0xC0)
        return 2;
    else if ((*s & 0xF0) == 0xE0)
        return 3;
    else if ((*s & 0xF8) == 0xF0)
        return 4;
    else
        return -1;
}

static const char *utf8_advance(const char *s)
{
    int len = utf8_char_size(s);
    return (len > 0) ? s + len : s;
}

String str_create(const char *s)
{
    String res;
    if (s == NULL)
    {
        res.data = NULL;
        res.byte_length = 0;
        res.char_length = 0;
        res.owns_data = false;
        return res;
    }

    size_t byte_len = 0;
    size_t char_len = 0;
    const char *ptr = s;
    while (*ptr)
    {
        int size = utf8_char_size(ptr);
        byte_len += size;
        char_len++;
        ptr += size;
    }

    res.data = (char *)malloc(byte_len + 1);
    for (size_t i = 0; i <= byte_len; i++)
    {
        res.data[i] = s[i];
    }
    res.byte_length = byte_len;
    res.char_length = char_len;
    res.owns_data = true;

    return res;
}

void str_destroy(String s)
{
    if (s.owns_data && s.data != NULL)
    {
        free(s.data);
    }
}

char *str_to_cstr(String s)
{
    char *res = (char *)malloc(s.byte_length + 1);
    for (size_t i = 0; i <= s.byte_length; i++)
    {
        res[i] = s.data[i];
    }
    return res;
}

// String.prototype.at()
String str_at(String s, int idx)
{
    if (idx < 0)
    {
        idx = s.char_length + idx;
    }

    if (idx < 0 || idx >= s.char_length)
    {
        return str_create("");
    }

    const char *cur = s.data;
    for (int i = 0; i < idx; i++)
    {
        cur = utf8_advance(cur);
    }

    int len = utf8_char_size(cur);
    char temp[5] = {0};
    for (int i = 0; i < len; i++)
    {
        temp[i] = cur[i];
    }

    return str_create(temp);
}

// String.prototype.charAt()
String str_charAt(String s, int idx)
{
    return str_at(s, idx);
}

// String.prototype.concat()
String str_concat(String s1, String s2)
{
    String res;
    res.byte_length = s1.byte_length + s2.byte_length;
    res.char_length = s1.char_length + s2.char_length;
    res.data = (char *)malloc(res.byte_length + 1);
    res.owns_data = true;

    for (size_t i = 0; i < s1.byte_length; i++)
    {
        res.data[i] = s1.data[i];
    }

    for (size_t i = 0; i < s2.byte_length; i++)
    {
        res.data[s1.byte_length + i] = s2.data[i];
    }

    res.data[res.byte_length] = '\0';
    return res;
}

// String.prototype.endsWith()
bool str_endsWith(String s, String searchStr)
{
    if (searchStr.char_length > s.char_length)
    {
        return false;
    }

    const char *end_ptr = s.data + s.byte_length - searchStr.byte_length;
    return memcmp(end_ptr, searchStr.data, searchStr.byte_length) == 0;
}

// String.prototype.indexOf()
int str_indexOf(String s, String searchStr)
{
    if (searchStr.char_length > s.char_length)
    {
        return -1;
    }

    const char *haystack = s.data;
    size_t pos = 0;

    while (*haystack)
    {
        if (memcmp(haystack, searchStr.data, searchStr.byte_length) == 0)
        {
            return pos;
        }
        haystack = utf8_advance(haystack);
        pos++;
    }

    return -1;
}

// String.prototype.includes()
bool str_includes(String s, String searchStr)
{
    return str_indexOf(s, searchStr) != -1;
}

// String.prototype.lastIndexOf()
int str_lastIndexOf(String s, String searchStr)
{
    if (searchStr.char_length > s.char_length)
    {
        return -1;
    }

    int last_pos = -1;
    const char *haystack = s.data;
    size_t pos = 0;

    while (*haystack)
    {
        if (memcmp(haystack, searchStr.data, searchStr.byte_length) == 0)
        {
            last_pos = pos;
        }
        haystack = utf8_advance(haystack);
        pos++;
    }

    return last_pos;
}

// String.prototype.padEnd()
String str_padEnd(String s, size_t targetLen, String padStr)
{
    if (s.char_length >= targetLen)
    {
        return str_create(s.data);
    }

    size_t pad_needed = targetLen - s.char_length;
    String res;
    res.data = (char *)malloc(s.byte_length + (pad_needed * padStr.byte_length / padStr.char_length) + 1);
    res.owns_data = true;

    memcpy(res.data, s.data, s.byte_length);

    size_t cur_pos = s.byte_length;
    const char *pad_ptr = padStr.data;
    for (size_t i = 0; i < pad_needed; i++)
    {
        int len = utf8_char_size(pad_ptr);
        memcpy(res.data + cur_pos, pad_ptr, len);
        cur_pos += len;
        pad_ptr = utf8_advance(pad_ptr);
        if (*pad_ptr == '\0')
            pad_ptr = padStr.data;
    }

    res.data[cur_pos] = '\0';
    res.byte_length = cur_pos;
    res.char_length = targetLen;

    return res;
}

// String.prototype.padStart()
String str_padStart(String s, size_t targetLen, String padStr)
{
    if (s.char_length >= targetLen)
    {
        return str_create(s.data);
    }

    size_t pad_needed = targetLen - s.char_length;
    String res;
    res.data = (char *)malloc(s.byte_length + (pad_needed * padStr.byte_length / padStr.char_length) + 1);
    res.owns_data = true;

    size_t cur_pos = 0;
    const char *pad_ptr = padStr.data;
    for (size_t i = 0; i < pad_needed; i++)
    {
        int len = utf8_char_size(pad_ptr);
        memcpy(res.data + cur_pos, pad_ptr, len);
        cur_pos += len;
        pad_ptr = utf8_advance(pad_ptr);
        if (*pad_ptr == '\0')
            pad_ptr = padStr.data;
    }

    memcpy(res.data + cur_pos, s.data, s.byte_length);
    cur_pos += s.byte_length;

    res.data[cur_pos] = '\0';
    res.byte_length = cur_pos;
    res.char_length = targetLen;

    return res;
}

// String.prototype.repeat()
String str_repeat(String s, size_t count)
{
    if (count == 0)
    {
        return str_create("");
    }

    String res;
    res.byte_length = s.byte_length * count;
    res.char_length = s.char_length * count;
    res.data = (char *)malloc(res.byte_length + 1);
    res.owns_data = true;

    size_t cur_pos = 0;
    for (size_t i = 0; i < count; i++)
    {
        memcpy(res.data + cur_pos, s.data, s.byte_length);
        cur_pos += s.byte_length;
    }

    res.data[res.byte_length] = '\0';
    return res;
}

// String.prototype.slice()
String str_slice(String s, int start, int end)
{
    if (start < 0)
        start += s.char_length;
    if (end < 0)
        end += s.char_length;
    if (end > s.char_length)
        end = s.char_length;
    if (start > end)
        start = end;

    if (start < 0)
        start = 0;
    if (end < 0)
        end = 0;

    const char *start_ptr = s.data;
    for (int i = 0; i < start && *start_ptr; i++)
    {
        start_ptr = utf8_advance(start_ptr);
    }

    const char *end_ptr = start_ptr;
    for (int i = start; i < end && *end_ptr; i++)
    {
        end_ptr = utf8_advance(end_ptr);
    }

    size_t byte_len = end_ptr - start_ptr;
    String res;
    res.data = (char *)malloc(byte_len + 1);
    res.owns_data = true;
    memcpy(res.data, start_ptr, byte_len);
    res.data[byte_len] = '\0';
    res.byte_length = byte_len;
    res.char_length = end - start;

    return res;
}

// String.prototype.startsWith()
bool str_startsWith(String s, String searchStr, size_t pos)
{
    if (pos >= s.char_length)
    {
        return false;
    }

    const char *start_ptr = s.data;
    for (size_t i = 0; i < pos; i++)
    {
        start_ptr = utf8_advance(start_ptr);
    }

    return memcmp(start_ptr, searchStr.data, searchStr.byte_length) == 0;
}

// String.prototype.substring()
String str_substring(String s, int start, int end)
{
    if (start < 0)
        start = 0;
    if (end > s.char_length)
        end = s.char_length;
    if (start > end)
    {
        int temp = start;
        start = end;
        end = temp;
    }

    return str_slice(s, start, end);
}

// String.prototype.toLowerCase()
String str_toLowerCase(String s)
{
    String res;
    res.data = (char *)malloc(s.byte_length + 1);
    res.owns_data = true;
    res.byte_length = s.byte_length;
    res.char_length = s.char_length;

    for (size_t i = 0; i < s.byte_length; i++)
    {
        if (s.data[i] >= 'A' && s.data[i] <= 'Z')
        {
            res.data[i] = s.data[i] + 32;
        }
        else
        {
            res.data[i] = s.data[i];
        }
    }

    res.data[s.byte_length] = '\0';
    return res;
}

// String.prototype.toUpperCase()
String str_toUpperCase(String s)
{
    String res;
    res.data = (char *)malloc(s.byte_length + 1);
    res.owns_data = true;
    res.byte_length = s.byte_length;
    res.char_length = s.char_length;

    for (size_t i = 0; i < s.byte_length; i++)
    {
        if (s.data[i] >= 'a' && s.data[i] <= 'z')
        {
            res.data[i] = s.data[i] - 32;
        }
        else
        {
            res.data[i] = s.data[i];
        }
    }

    res.data[s.byte_length] = '\0';
    return res;
}

// String.prototype.trim()
String str_trim(String s)
{
    if (s.char_length == 0)
    {
        return str_create("");
    }

    const char *start = s.data;
    const char *end = s.data + s.byte_length - 1;

    while (*start && (*start == ' ' || *start == '\t' || *start == '\n'))
    {
        start = utf8_advance(start);
    }

    while (end > start && (*end == ' ' || *end == '\t' || *end == '\n' || *end == '\0'))
    {
        end--;
    }

    size_t new_byte_len = end - start + 1;

    String res;
    res.data = (char *)malloc(new_byte_len + 1);
    res.owns_data = true;

    memcpy(res.data, start, new_byte_len);
    res.data[new_byte_len] = '\0';
    res.byte_length = new_byte_len;

    res.char_length = 0;
    const char *p = res.data;
    while (*p)
    {
        p = utf8_advance(p);
        res.char_length++;
    }

    return res;
}

// String.prototype.trimEnd()
String str_trimEnd(String s)
{
    if (s.char_length == 0)
    {
        return str_create("");
    }

    const char *end = s.data + s.byte_length - 1;

    while (end > s.data && (*end == ' ' || *end == '\t' || *end == '\n' || *end == '\0'))
    {
        end--;
    }

    size_t new_byte_len = end - s.data + 1;

    String res;
    res.data = (char *)malloc(new_byte_len + 1);
    res.owns_data = true;

    memcpy(res.data, s.data, new_byte_len);
    res.data[new_byte_len] = '\0';
    res.byte_length = new_byte_len;

    res.char_length = 0;
    const char *p = res.data;
    while (*p)
    {
        p = utf8_advance(p);
        res.char_length++;
    }

    return res;
}

// String.prototype.trimStart()
String str_trimStart(String s)
{
    if (s.char_length == 0)
    {
        return str_create("");
    }

    const char *start = s.data;

    while (*start && (*start == ' ' || *start == '\t' || *start == '\n'))
    {
        start = utf8_advance(start);
    }

    size_t new_byte_len = (s.data + s.byte_length) - start;

    String res;
    res.data = (char *)malloc(new_byte_len + 1);
    res.owns_data = true;

    memcpy(res.data, start, new_byte_len);
    res.data[new_byte_len] = '\0';
    res.byte_length = new_byte_len;

    res.char_length = 0;
    const char *p = res.data;
    while (*p)
    {
        p = utf8_advance(p);
        res.char_length++;
    }

    return res;
}