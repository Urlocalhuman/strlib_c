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

