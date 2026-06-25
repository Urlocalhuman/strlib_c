/*
    STRLIB EXAMPLE FILE
    
    note that: 
        - This program heavily uses the string* class for
          constant values, take into mind the library is made
          for more dynamic purposes, like gamedev or smt
        
        - My code SUCKS
        - This program is inefficient
        - It also lacks functionality/examples

    so for anyone reading this, this program is more for demonstrational purposes
    the docs will have more info (wip)
    
    ALSO

    it may be better to use the raw functions instead of through the string type
    so instead of str->method(str) you can just do method_s(str)
*/

#include "strlib_c.h"
#include <stdio.h>

#define bool char
#define true 1
#define false 0

void test1(void) {
    // first program
    bool running = true;
    string* inp = str_init("");
    string* cmp = str_init("");

    string* prompt1 = str_init("Input string (quit to quit)> ");
    string* prompt2 = str_init("Compare to > ");
    string* format = str_init(
        "String: '{}':\nStartswith {}: {!i}\nEndswith {}: {!i}\n");
    // you can put information into the braces, since the formatter
    // will ignore the contents inside (except for formatting strings)
    string* formatted = NULL;

    while (running) {
        input(prompt1, inp);
        if (_strcmp_s(inp, "quit", _strlen("quit"))) {
            running = false; break;
        }
        input(prompt2, cmp);
        formatted = format->format(format,
            inp,
            cmp,
            inp->startswith(inp, cmp),
            cmp,
            inp->endswith(inp, cmp));
        formatted->print(formatted);
        formatted->del(formatted); 
        // would have been cleaned up in strlib_uninit but good practice
    }
}

void test2(void) {
    // calc
    bool running = 1;
    string* op = str_init("");
    string* n1 = str_init("");
    string* n2 = str_init("");
    int in1 = 0;
    int in2 = 0;
    float result = 0.0f;

    string* prompt1 = str_init("Operator (quit to quit)> ");
    string* prompt2 = str_init("Num1 > ");
    string* prompt3 = str_init("Num2 > ");
    string* fmt     = str_init("{!i} {operator} {!i} = {!f12}\n");
    string* bad_inp = str_init("Num1 and Num2 should be numerical integers!\n");
    string* bad_inp2= str_init("Operator should be + - / or *!\n");
    string* formatted = NULL;
    while (running) {
        input(prompt1, op);
        if (_strcmp_s(op, "quit", _strlen("quit"))) {
            running = false; break;
        }
        input(prompt2, n1);
        input(prompt3, n2);
        if (!n1->isdigit(n1) || !n2->isdigit(n2)) {
            bad_inp->print(bad_inp);
            continue;
        }
        if (op->len != 1) {
            bad_inp2->print(bad_inp2);
        }
        in1 = atoi_s(n1);
        in2 = atoi_s(n2);
        if (_strcmp_s(op, "+", 1)) {
            result = (float)(in1 + in2);
        } else if (_strcmp_s(op, "-", 1)) {
            result = (float)(in1 - in2);
        } else if (_strcmp_s(op, "*", 1)) {
            result = (float)(in1 * in2);
        } else if (_strcmp_s(op, "/", 1)) {
            result = (float)in1 / (float)in2;
        }
        formatted = fmt->format(fmt,
            in1, op, in2, result);
        formatted->print(formatted);
        
    }
}

int main(void) {
    string* sel = input(str_init("test or calc > "), NULL);
    
    if (strcmp_s(sel, str_init("test"))) test1();
    if (strcmp_s(sel, str_init("calc"))) test2();

    strlib_uninit();
    return 0;
}
