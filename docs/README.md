## Documentation (wip)

### List of all (accessible) functions/methods:

- `str_init( char* inits ) -> string*`
  >*Returns a pointer to a new string. Uses **inits** as the contents for the string*
- `strcpy_s( string* a, string* b ) -> void`
  >*Copies the contents of **a** into **b***
- `strprint_s( string* self ) -> void`
  >*Prints string*
- `strdel_s( string* self ) -> void`
  >*Deletes string (free's memory)*
- `startswith_s( string* self, string* str ) -> int`
  >*Checks if **self** starts with **str**. Returns **1** on success*
- `endswith_s( string* self, string* str ) -> int`
  >*Checks if **self** ends with **str**. Returns **1** on success*
- `concat_s ( string* self, string* str ) -> void`
  >*Concatenates **str** onto **self***
- `strcmp_s ( string* a, string* b) -> void`
  >*Checks if **a** and **b** are identical strings. Returns **1** on success*
- `format_s ( string* self, [ANY]... ) -> string*`
  >*Formats **self**. **READ DOCUMENTATION***
- `itoa_s ( int n ) -> string*`
  >*Returns a pointer to a new string containing **n** in text form*
- `atoi_s ( string* num ) -> int`
  >*Does the opposite of itoa_s, taking in **num** and returning it in integer form*
- `isdigit_s (string* self ) -> int`
  >*Returns **1** if self is a string made up of only digits 0-9*
- `input ( string* prompt, string* out ) ->`
  >*Gets keyboard input. **out** is OPTIONAL, give **NULL** if not used*
- `print_s ( int count, string* sep, string* end, [string*]... ) ->`
  >*Prints multiple strings. **sep** and **end** are optional. **READ DOCUMENTATION***
- `check_freed_strings ( void ) -> void`
  >*Prints out a list of all allocated strings. Immensely useful for debugging, and seeing how the library works*
- `free_all_strings ( void ) -> void`
  >*Calls strdel_s on all strings, highly reccomended at end of program execution*
- `strlib_uninit ( void ) -> void`
  >*Free's the string pool along with all strings. Better to use this instead of the above.*

### How to use
**It is highly reccomended *NOT* to just create a string\* object**

To create a new string call str_init(starting content)
```
string* hw = str_init("Hello, World!\n");
strprint_s(hw);
hw->print(hw); // same effect
```
From there you can do as you want just rember
- free unused strings (strdel_s and strlib_uninit)
- dont use a string after you've free'd it
  ```
  string* abc = str_init("something");
  abc->del(abc); // or strdel_s(abc);
  strprint_s(abc); // !!!
  ```
- strings don't actually take up much memory, so freeing them is more best practice
- free'd strings will be reused by the allocator to save memory
## String struct/type
The string 'class' is defined in strlib_c.h as
```
typedef struct string {
  ...
  'methods' (functions)
  uint32_t len;
  ...
}
```
The 'methods' included in the struct are as given:
- `str->print ( self )` *strprint_s*
- `str->del ( self )` *strdel_s*
- `str->concat ( self )` *concat_s*
- `str->startswith ( self, str )` *startswith_s*
- `str->endswith ( self, str )` *endswith_s*
- `str->isdigit ( self )` *isdigit_s*
- `str->upper ( self ) -> string*` *Returns a fully uppercase copy of the string*
- `str->lower ( self ) -> string*` *Returns a fully lowercase copy of the string*
- `str->format (self, ...)` *format_s*
- **str->len** *An integer containing the length of the string*

## All functions and what they do
-  wip will be done when i have time
