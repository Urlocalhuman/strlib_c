# cstring
## library to make string management easier
cstring is a library designed to be *similar* to python's str class

it is massively a WIP, most methods havent been implemented
>it does work tho
---
### To use: 
just #include strlib_c.h and make sure it's compiled with your project

- most methods begin with str<xxx>_s ( args )
- methods that mix both char (\*) and string\* begin with '_'
- this is intended to be used more like how python's strings are, don't worrry about
  memory leaks or pointer loss, the allocator will be able to deal with these

*note: the allocator currently cannot detect loss of string pointers, but calling strlib_uninit() will do*

### misc
Documentation is available in ./docs, currently the **README** works as the documentation page

More is planned in future, like other libraries for the dict/list 'classes'

*end of readme*\
\
\
\
\
\
\
\
\
\
\
\
\
\
\
\
\
\
\
\
\
\
\
\
\
\
\
\
\
\
\
\
\
\
Yes i know this is supposed to be c
