#pragma once
#include <stdint.h>
#define STRING_TYPE_N 1

typedef struct string {
    char* data;

    void (*print)          (struct string* self);
    void (*del)            (struct string* self);
    void (*concat)         (struct string* self, struct string* str);
    int (*startswith)      (struct string* self, struct string* str);
    int (*endswith)        (struct string* self, struct string* str);
    int (*isdigit)         (struct string* self);
    struct string*(*upper) (struct string* self);
    struct string*(*lower) (struct string* self);
    struct string*(*format)(struct string* self, ...);

    uint32_t len;
    uint32_t _m_capacity;
    uint32_t _id;
    uint16_t _in_use : 1;
    uint16_t _type  : 15;
    uint16_t _state;
    // _type and _in_use are flags, so use : to specify bits
    // _state is a placeholder, since my compiler throws a shit when theres any padding remaining


    // will be used in future projects
    // if i make libraries for other types
} string;

/**
 * Creates a new string and returns a pointer to it.
 * @param[in] char array to initialise the string to
 * @param[out] string* pointer to the new string
 */
string* str_init(char* inits);

void strcpy_s    (string* a, string* b); // copy a into b
void strprint_s  (string* self);
void strdel_s    (string* self);
int  startswith_s(string* self, string* str);
int  endswith_s  (string* self, string* str);
void concat_s    (string* self, string* str);
int  strcmp_s    (string* a, string* b);
int  isdigit_s   (string* self);

string* format_s(string* self, ...);
string* itoa_s(int n);
int atoi_s(string* num);
/**
 * Gets keyboard input.
 * @param[in] string* prompt to display
 * @param[in] string* (optional) string to output to (creates new if not given)
 * @param[out] string* pointer to the new string
 */
string* input(string* prompt, string* out);
void print_s(int count, string* sep, string* end, ...);

void check_freed_strings(void);
void free_all_strings(void);
void strlib_uninit(void); // WILL FREE STRING POOL

int _strlen(const char* s);
int _strcmp_s(string* a, char* b, int b_len);
