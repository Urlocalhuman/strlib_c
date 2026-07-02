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
    // non constant vals
    string* inp = str_init("");
    string* cmp = str_init("");
    string* formatted = NULL; // format out
    // constants**
    string* prompt1 = str_init("Input string (quit to quit)> ");
    string* prompt2 = str_init("Compare to > ");
    string* format = str_init(
        "String: '{}':\nStartswith {}: {!i}\nEndswith {}: {!i}\n");
    // you can put information into the braces, since the formatter
    // will ignore the contents inside (except for formatting strings)

    while (running) { // main loop
        input(prompt1, inp); // get inp from user
        if (_strcmp_s(inp, "quit", _strlen("quit"))) {
            running = false; break; // quit
        } // looking back on this why tf did i use
          // the _ version instead of the normal
          // may correct that in fut

        input(prompt2, cmp); // comparison string
        formatted = format->format(format,
            inp,
            cmp,
            inp->startswith(inp, cmp),
            cmp,
            inp->endswith(inp, cmp)); // returns a formatted string
                                      // (puts values into the format string's braces)

        formatted->print(formatted); // out
        formatted->del(formatted);
        // cleans up the string, the allocator will reuse the free slot instead of
         //creating a new string, will maybe save like 100 ish bytes (not that much lol)
         //every little helps ig
         //would have been cleaned up in strlib_uninit but good practice
    }
    // **not really
}

void test2(void) {
    // calc
    bool running = 1;
    // will be modified
    string* op = str_init("");
    string* n1 = str_init("");
    string* n2 = str_init("");
    int in1 = 0;
    int in2 = 0;
    float result = 0.0f;
    string* formatted = NULL; // format out

    // constants
    string* prompt1 = str_init("Operator (quit to quit)> ");
    string* prompt2 = str_init("Num1 > ");
    string* prompt3 = str_init("Num2 > ");
    string* fmt     = str_init("{!i} {operator} {!i} = {!f12}\n");
    string* bad_inp = str_init("Num1 and Num2 should be numerical integers!\n");
    string* bad_inp2= str_init("Operator should be + - / or *!\n");

    while (running) {
        input(prompt1, op); // operator
        if (_strcmp_s(op, "quit", _strlen("quit"))) {
            running = false; break;
        }
        input(prompt2, n1); // number 1
        input(prompt3, n2); // number 2
        if (!n1->isdigit(n1) || !n2->isdigit(n2)) {
            bad_inp->print(bad_inp); // looks like they arent numbers
            continue;
        }
        if (op->len != 1) {
            bad_inp2->print(bad_inp2); // invalid operator (more than one character given)
        }
        in1 = atoi_s(n1); // number 1 -> int
        in2 = atoi_s(n2); // same as number 2

        if (_strcmp_s(op, "+", 1)) { // calculation block
            result = (float)(in1 + in2); // add
        } else if (_strcmp_s(op, "-", 1)) {
            result = (float)(in1 - in2); // sub
        } else if (_strcmp_s(op, "*", 1)) {
            result = (float)(in1 * in2); // mul
        } else if (_strcmp_s(op, "/", 1)) {
            result = (float)in1 / (float)in2; // div
        } else {
            bad_inp2->print(bad_inp2); // not an operator
            continue;
        }
        formatted = fmt->format(fmt,
            in1, op, in2, result); // format
        formatted->print(formatted); // print format
        
    }
}

void test3(void) { // i think this one's been written a bit differently
    // todo: will document in future
    // todo: this function sucks, but oh well
    // todo: rewrite/refactor
    bool running = 1;
    string* ln = str_init("");
    int lni = 0;
    string* out = str_init("");
    string* tmp = str_init("");

    string* prompt = str_init("\nPyramid layers: ");
    string* bad = str_init("Give an integer value!");
    while (running) {
        input(prompt, ln);
        if (strcmp_s(ln, str_init("quit"))) {
            running = 0;
            return;
        }
        if (!ln->isdigit) {
            strprint_s(bad);
            continue;
        }
        lni = atoi_s(ln);
        for (int i = 1; i < lni*2; i++, i++) {
            for (int ix = 0; ix < i; ix++) {
                _appendc(tmp, '*'); _appendc(tmp, ' ');
            } // can just use concat if more than one char, but idfc
            tmp = _centre_s(tmp, lni*4, ' ');
            concat_s(out, tmp);
            _appendc(out, '\n');
            _strcpy_s(tmp, "");
        }
        strprint_s(out);
        _strcpy_s(out, ""); // clear
        // in an ideal world i would have been
        // able to overrdide "" -> string* instead of "" -> char*
        // but that would make this less fun; at that point js use python
        // work around probvlems
    }
}

int main(void) {
    string* sel = input(str_init("test/calc/pyramid > "), NULL);

    if (strcmp_s(sel, str_init("test"))) test1();
    if (strcmp_s(sel, str_init("calc"))) test2();
    if (strcmp_s(sel, str_init("pyramid"))) test3();

    strlib_uninit();
    return 0;
}
