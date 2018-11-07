
#ifndef BASE_MACROS_H_
#define BASE_MACROS_H_

#include <stddef.h>         // For size_t

namespace foundation {

// A macro to disallow the copy constructor and operator= functions
// This must be placed in the private: declarations for a class.
//
// For disallowing only assign or copy, delete the relevant operator or
// constructor, for example:
// void operator=(const TypeName&) = delete;
// Note, that most uses of DISALLOW_ASSIGN and DISALLOW_COPY are broken
// semantically, one should either use disallow both or neither. Try to
// avoid these in new code.
//
// When building with C++11 toolchains, users should instead prefer the
// language supported "= delete" syntax and place those lines in the
// public: declaration of the class.
#if LANG_CXX11
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&) = delete;      \
  void operator=(const TypeName&) = delete
#else
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&);               \
  void operator=(const TypeName&)
#endif

// A macro to disallow all the implicit constructors, namely the
// default constructor, copy constructor and operator= functions.
//
// This should be used in the private: declarations for a class
// that wants to prevent anyone from instantiating it. This is
// especially useful for classes containing only static methods.
#define DISALLOW_IMPLICIT_CONSTRUCTORS(TypeName) \
  TypeName();                                    \
  DISALLOW_COPY_AND_ASSIGN(TypeName)


// A macro to turn a symbol into a string
#define AS_STRING(x)   AS_STRING_INTERNAL(x)
#define AS_STRING_INTERNAL(x)   #x

}  // namespace foundation

#endif  // BASE_MACROS_H_
