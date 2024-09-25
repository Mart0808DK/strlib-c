#include <stdio.h>
#include <stdbool.h>
#include <string.h>

void str_cpy(char *to, char *from);
int str_len(char *s);
char str_at(char *str, int index);
char str_char_at(char *str, int index);
void str_concat(char *str1, char *str2, char *output);
void str_ends_with( char *word, char *end, bool *output);

int main()
{
    // char myString[] = "HelloWorld";
    // int index = -4;
    // char result = str_at(myString, index);
    // printf("Character at index %d: %c", index, result);

    char str1[] = "Hello";
    char str2[] = "World";
    char output[100];

    str_concat(str1, str2, output);
    printf("concat('%s', '%s'): %s\n", str1, str2, output);

    char str3[] = "Hejsa Kaj";
    char str4[] = "Ka";
    bool bool_output;
    str_ends_with("Hejsa Kaj", "Kaj", &bool_output);

    return 0;
}

void str_cpy(char *to, char *from)
{
    while ((*to++ = *from++))
        ;
}

int str_len(char *s)
{
    int lenght = 0;
    while (s[lenght] != '\0')
    {
        lenght++;
    }

    return lenght;
}

// String.prototype.at()
char str_at(char *str, int index)
{
    int length = str_len(str);
    if (index < 0)
    {
        index = length + index;
    }

    if (index < 0)
    {
        return '\0';
    }
    else if (index >= length)
    {
        return '\0';
    }
    else
    {
        return str[index];
    }
}

// String.prototype.charAt()
char str_char_at(char *str, int index)
{
    int length = str_len(str);
    if (index < 0)
    {
        index = length + index;
    }

    if (index < 0)
    {
        return '\0';
    }
    else if (index >= length)
    {
        return '\0';
    }
    else
    {
        return str[index];
    }
}

// String.prototype.concat()
void str_concat(char *str1, char *str2, char *output)
{
    int i = 0;
    while (*str1)
    {
        output[i++] = *str1++;
    }
    while (*str2)
    {
        output[i++] = *str2++;
    }

    output[i] = '\0';
}

// String.prototype.endsWith()
void str_ends_with(char *word, char *end, bool *output)
{
    int word_len = str_len(word);
    int end_len = str_len(end);

    if (end_len > word_len)
    {
        *output = false;
    }
    else
    {
        char *difference = word + word_len - end_len;
        *output = true;
        while (*end)
        {
            if (*difference++ != *end++)
            {
                *output = false;
                break;
            }
        }
    }
}

// String.prototype.includes()
void str_includes(char* sentence, char* word, bool *output){

}

// String.prototype.indexOf()
void str_indexOf(char* sentence, char* word, int* count) {
    int len_sentence = str_len(sentence);
    int len_word = str_len(sentence);
    for (int i = 0; i <= len_sentence - len_word; i++)
    {
        int j = 0;
        while (j < len_word)
        {
            if (word[i + j] != sentence)
            {
                break;
            }
            
        }
        
    }
    
}

// String.prototype.lastIndexOf()

// String.prototype.localeCompare()

// String.prototype.padEnd()

// String.prototype.padStart()

// String.prototype.repeat()

// String.prototype.slice()

// String.prototype.startsWith()

// String.prototype.substring()

// String.prototype[Symbol.iterator]()

// String.prototype.toLocaleLowerCase()

// String.prototype.toLocaleUpperCase()

// String.prototype.toLowerCase()

// String.prototype.toString()

// String.prototype.toUpperCase()

// String.prototype.trim()

// String.prototype.trimEnd()

// String.prototype.trimStart()

// String.prototype.valueOf()