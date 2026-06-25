#include "strlib_c.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <stdarg.h>

#define NOT_IN_USE_MSG "Use of free'd string"

static void raise(char* msg) {
    perror(msg);
    exit(1);
}

// Source - https://stackoverflow.com/q/14476627
// Posted by Hommer Smith, modified by community. See post 'Timeline' for change history
// Retrieved 2026-04-22, License - CC BY-SA 3.0

static void _strcpy(char dest[], const char source[]) {
    int i = 0;
    while (1) {
        dest[i] = source[i];

        if (dest[i] == '\0') {
            break;
        }

        i++;
    } 
}

// Source - https://stackoverflow.com/a/1068937
// Posted by paxdiablo, modified by community. See post 'Timeline' for change history
// Retrieved 2026-04-26, License - CC BY-SA 4.0

int _numPlaces(int n) {
    if (n < 0) return _numPlaces((n == INT_MIN) ? INT_MAX : -n);
    if (n < 10) return 1;
    return 1 + _numPlaces(n / 10);
}


int _strlen(const char *s) {
    int count = 0;
    while(*s!='\0'){
        count++;
        s++;
    }
    return count;
}

string** pool;
int32_t pool_size = 0;
int32_t pool_used = 0;

unsigned char init_called;

static void init() {
    if (!init_called) {
        pool = malloc(sizeof(string*));
        pool_size = 1;
    }
    init_called = 1;
}

static void pool_ensure_capacity(int needed) {
    if (pool_size >= needed) return;
    
    void* ptr = 0;

    while (pool_size < needed) {
        pool_size *= 2;
    }
    ptr = realloc(pool, pool_size * sizeof(string*));
    if (ptr == NULL) {
        raise("Realloc returned NULL");
    }
    pool = ptr;
}

static void string_ensure_capacity(string* s, uint32_t needed) {
    if (s->_m_capacity >= needed) return;
    if (s->_m_capacity == 0) s->_m_capacity = 1;

    void* ptr = 0;

    while (s->_m_capacity < needed) {
        s->_m_capacity *= 2;
    }
    ptr = realloc(s->data, s->_m_capacity);
    if (ptr == NULL) {
        raise("Realloc returned NULL");
    }
    s->data = ptr;
}

static void _strcpy_s(string* a, char* b) {
    int len = _strlen(b);
    string_ensure_capacity(a, len+1);
    _strcpy(a->data, b);
    a->len = len;
}

static void _concat_s(string* a, char* b) {
    int len = _strlen(b);

    string_ensure_capacity(a, a->len + len + 1);
    int ix = 0;
    int i;
    for (i = a->len; i < a->len + len; i++) {
        a->data[i] = b[ix];
        ix++;
    }
    a->len = a->len + len;
    a->data[i] = '\0';
}

void strcpy_s(string* a, string* b) {
    if (!a->_in_use || !b->_in_use) raise(NOT_IN_USE_MSG);
    string_ensure_capacity(a, b->len+1);
    _strcpy(a->data, b->data);
    a->len = b->len;
    return;
}

void strprint_s(string* self) {
    if (!self->_in_use) raise(NOT_IN_USE_MSG);
    printf("%s", self->data);
}

void strdel_s(string* self) {
    if (self->_in_use == 0 || self->data == NULL) return;
    self->_in_use = 0;
    free(self->data);
    self->data = NULL;
    //self->data = realloc(self->data, 1);
    self->_m_capacity = 0;
    self->len = 0;
}

int startswith_s(string* self, string* str) {
    if (!self->_in_use || !str->_in_use) raise(NOT_IN_USE_MSG);
    if (self->len < str->len) return 0;
    for (int i = 0; i < str->len; i++) {
        if (self->data[i] != str->data[i]) return 0;
    }
    return 1;
}

int endswith_s(string* self, string* str) {
    if (!self->_in_use || !str->_in_use) raise(NOT_IN_USE_MSG);
    if (self->len < str->len) return 0;
    int ix = 0;
    for (int i = self->len - str->len; i < self->len; i++) {
        if (self->data[i] != str->data[ix]) return 0;
        ix++;
    }
    return 1;
}

void concat_s(string* self, string* str) {
    if (!self->_in_use || !str->_in_use) raise(NOT_IN_USE_MSG);
    string_ensure_capacity(self, self->len + str->len + 1);
    int ix = 0;
    int i;
    for (i = self->len; i < self->len + str->len; i++) {
        self->data[i] = str->data[ix];
        ix++;
    }
    self->len = self->len + str->len;
    self->data[i] = '\0';
}

int _strcmp_s(string* a, char* b, int b_len) {
    if (!a->_in_use) raise(NOT_IN_USE_MSG);
    if (a->len != b_len) return 0;
    for (uint32_t i = 0; i < a->len; i++) {
        if (a->data[i] - b[i] != 0) return 0;
    }
    return 1;
}

int strcmp_s(string* a, string* b) {
    if (!a->_in_use || !b->_in_use) raise(NOT_IN_USE_MSG);
    if (a->len != b->len) return 0;
    for (uint32_t i = 0; i < a->len; i++) {
        if (a->data[i] - b->data[i] != 0) return 0;
    }
    return 1;
}

char upper(char c) {
    if (c >= 'a' && c <= 'z') {
        return c - ('a' - 'A');
    }
    return c;
}

char lower(char c) {
    if (c >= 'A' && c <= 'Z') {
        return c + ('a' - 'A');
    }
    return c;
}

string* lower_s(string* self) {
    if (!self->_in_use) raise(NOT_IN_USE_MSG);
    string* out = str_init(self->data);
    for (int i = 0; i < self->len; i++) {
        out->data[i] = lower(self->data[i]);
    }
    out->data[self->len] = '\0';
    return out;
}

string* upper_s(string* self) {
    if (!self->_in_use) raise(NOT_IN_USE_MSG);
    string* out = str_init(self->data);
    for (int i = 0; i < self->len; i++) {
        out->data[i] = upper(self->data[i]);
    }
    out->data[self->len] = '\0';
    return out;
}

static int _precision(const char x[3]) { 
    // AI WARNING: THIS FUNCTION WAS GENERATED W/ CGPT FOR CONVENIENCE PURPOSES
    int p = 0;
    if (x[0] == '\0') return -1;
    for (int i = 0; i < 2 && x[i] != '\0'; i++) {
        if (x[i] < '0' || x[i] > '9') return -1;

        p = p * 10 + (x[i] - '0');
    }
    return p;
}

string* format_s(string* self, ...) {
    if (!self->_in_use) raise(NOT_IN_USE_MSG);
    string* out = str_init("");
    va_list args;
    va_start(args, self);

    int found = 0;
    char extra[3] = { '\0', '\0', '\0' };

    int num = 0;
    float flt = 0.0f;
    double dbl = 0.0;
    char tmp[64] = "";
    int prec = 0;

    for (int i = 0; i < self->len; i++) {
        if (!found) {
            if (self->data[i] == '{') {
                if (i + 2 < self->len && self->data[i + 1] == '!') {
                    found = (int)self->data[i + 2];
                    extra[1] = '\0';
                    extra[2] = '\0';
                    if (i + 3 < self->len && self->data[i + 3] != '}') {
                        extra[0] = self->data[i + 3]; // precision
                        if (i + 4 < self->len && self->data[i + 4] != '}') {
                            extra[1] = self->data[i + 4]; // for up to like 16 digits of precision
                        }
                    }
                } else found = 1;
            }
            else {
                string_ensure_capacity(out, out->len + 2);
                out->data[out->len++] = self->data[i];
                out->data[out->len] = '\0';
            }
        } else if (self->data[i] == '}') {
            string* arg = NULL;
            switch (found) {
            case 's':
                arg = str_init(va_arg(args, char*));
                break;
            case 'i':
                num = va_arg(args, int);
                arg = itoa_s(num);
                break;
            case 'f':
                flt = (float)va_arg(args, double);
                prec = _precision(extra);
                if (prec >= 0) snprintf(tmp, sizeof(tmp), "%.*f", prec, flt);
                else snprintf(tmp, sizeof(tmp), "%f", flt);
                arg = str_init(tmp);
                break;
            case 'd':
                dbl = va_arg(args, double);
                prec = _precision(extra);
                if (prec >= 0) snprintf(tmp, sizeof(tmp), "%.*f", prec, dbl);
                else snprintf(tmp, sizeof(tmp), "%f", dbl);
                arg = str_init(tmp);
                break;
            default:
                arg = va_arg(args, string*);
                if (!arg->_in_use) raise(NOT_IN_USE_MSG);
                break;
            }
            out->concat(out, arg);
            found = 0;
        }
    }
    va_end(args);
    if (found) {
        perror("String format unfinished");
        exit(1);
    }
    return out;
}

int isdigit_s(string* self) {
    if (!self->_in_use) raise(NOT_IN_USE_MSG);
    for (int i = 0; i < self->len; i++) {
        if (self->data[i] < '0' || self->data[i] > '9') return 0;
    }
    return 1;
}

// 0 string methods
// ------------------------------------------------------------
// 0 individual functions

// cock and ball

string* str_init(char* inits) {
    init();

    string* str = NULL;
    for (int i = 0; i < pool_used; i++) {
        if (pool[i] && pool[i]->_in_use == 0) {
            str = pool[i];
            break;
        }
    }
    if (str == NULL) {
        pool_ensure_capacity(pool_used + 1);
        str = malloc(sizeof(string));
        if (str == NULL) {
            perror("Malloc returned NULL");
            exit(1);
        }
        pool[pool_used++] = str;

        str->print      = strprint_s;
        str->del        = strdel_s;
        str->startswith = startswith_s;
        str->endswith   = endswith_s;
        str->concat     = concat_s;
        str->upper      = upper_s;
        str->lower      = lower_s;
        str->format     = format_s;
        str->isdigit    = isdigit_s;
        str->_id = pool_used;
        str->_type = STRING_TYPE_N;
    }
    
    str->len = 0;
    str->_m_capacity = 1;
    str->data = malloc(1);
    if (str->data == NULL) {
        perror("Malloc returned NULL");
        exit(1);
    }
    str->data[0] = '\0';
    str->_in_use = 1;

    _strcpy_s(str, inits);


    return str;
}

string* itoa_s(int n) {
    char c[12];
    _itoa_s(n, c, 10, 10);
    string* s = str_init(c);
    return s;
}

int atoi_s(string* num) { // easier
    return atoi(num->data);
}

string* input(string* prompt, string* out) {
    if (!prompt->_in_use) raise(NOT_IN_USE_MSG);
    int ch;
    if (out == NULL) {
        out = str_init("");
    }
    else _strcpy_s(out, "");
    prompt->print(prompt);

    while (1) {
        ch = _getch();
        if (ch != '\r' && ch != EOF) {
            if (ch == '\b') {
                if (out->len > 0) {
                    out->data[--out->len] = '\0';
                    printf("\b \b");
                }
            } else {
                printf("%c", ch);
                string_ensure_capacity(out, out->len + 2);
                out->data[out->len++] = ch;
                out->data[out->len] = '\0';
            }
        } else {
            printf("\n"); 
            return out;
        }
    }
}

void print_s(int count, string* sep, string* end, ...) {
    va_list args;
    va_start(args, end);
    
    uint8_t localv[2] = { 0, 0 };
    if (sep == NULL) {
        localv[0] = 1;
        sep = str_init(" ");
    }
    if (end == NULL) {
        localv[1] = 1;
        end = str_init("\n");
    }

    string* cs = NULL;

    for (int i = 0; i < count; i++) {
        cs = va_arg(args, string*);
        strprint_s(cs);
        if (i != count - 1) {
            strprint_s(sep);
        }
    }
    strprint_s(end);

    if (localv[0]) sep->del(sep);
    if (localv[1]) end->del(end);
    va_end(args);
}

// DEBUGGING / MEM
void check_freed_strings(void) {
    printf("\nString pool\n");
    char s = 'N';
    for (int i = 0; i < pool_used; i++) {
        printf("--String #%d:\n", pool[i]->_id);
        if (pool[i]->_in_use) s = 'N';
        else s = 'Y';

        printf("Freed: %c\n", s);
        if (pool[i]->_in_use) {
            printf("Data:\n\"%s\"\n", pool[i]->data);
        }
    }
}

void free_all_strings(void) {
    for (int i = 0; i < pool_used; i++) {
        strdel_s(pool[i]);
    }
}

void strlib_uninit(void) {
    free_all_strings();
    init_called = 0;
    for (int i = 0; i < pool_used; i++) {
        free(pool[i]);
    }
    free(pool);
    pool_size = 0;
    pool_used = 0;
}

// bugfix checklist:
// done -
//  - strcpy_s() uses len instead of len +1
//  - pool is never freed
//  - pool changed from array of strings to array of pointers to strings
// todo -
//  - malloc faliure checks
// potential improvements -
//  - itoa could directly return s
//  - remove input() 'out' entirely
//
