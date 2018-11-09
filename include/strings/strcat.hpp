
#ifndef FOUNDATION_STRINGS_STRCAT_H_
#define FOUNDATION_STRINGS_STRCAT_H_

#include <foundation/base/macros.hpp>
#include <foundation/strings/numbers.hpp>
#include <foundation/strings/stringpiece.hpp>

#include <string>
using std::string;


namespace foundation {

// The AlphaNum type was designed to be used as the parameter type for StrCat().
// Any routine accepting either a string or a number may accept it.
// The basic idea is that by accepting a "const AlphaNum &" as an argument
// to your function, your callers will automagically convert bools, integers,
// and floating point values to strings for you.
//
// NOTE: Use of AlphaNum outside of the //strings package is unsupported except
// for the specific case of function parameters of type "AlphaNum" or "const
// AlphaNum &". In particular, instantiating AlphaNum directly as a stack
// variable is not supported.
//
// Conversion from 8-bit values is not accepted because if it were, then an
// attempt to pass ':' instead of ":" might result in a 58 ending up in your
// result.
//
// Bools convert to "0" or "1".
//
// Floating point values are converted to a string which, if passed to strtod(),
// would produce the exact same original double (except in case of NaN; all NaNs
// are considered the same value). We try to keep the string short but it's not
// guaranteed to be as short as possible.
//
// This class has implicit constructors.
// Style guide exception granted:
// http://goto/style-guide-exception-20978288
//
struct AlphaNum {
  StringPiece piece;
  char digits[kFastToBufferSize];

  // No bool ctor -- bools convert to an integral type.
  // A bool ctor would also convert incoming pointers (bletch).

  AlphaNum(int32_t i32)
      : piece(digits, FastInt32ToBufferLeft(i32, digits) - &digits[0]) {}
  AlphaNum(uint32_t u32)
      : piece(digits, FastUInt32ToBufferLeft(u32, digits) - &digits[0]) {}
  AlphaNum(int64_t i64)
      : piece(digits, FastInt64ToBufferLeft(i64, digits) - &digits[0]) {}
  AlphaNum(uint64_t u64)
      : piece(digits, FastUInt64ToBufferLeft(u64, digits) - &digits[0]) {}

  // AlphaNum(float f)  // NOLINT(runtime/explicit)
  //   : piece(digits, FloatToBuffer(f, digits))) {}
  // AlphaNum(double f)  // NOLINT(runtime/explicit)
  //   : piece(digits, strlen(DoubleToBuffer(f, digits))) {}

  AlphaNum(const char *c_str) : piece(c_str) {}
  AlphaNum(const StringPiece &pc) : piece(pc) {}

  template <class Allocator>
  AlphaNum(const std::basic_string<char, std::char_traits<char>, Allocator> &str)
      : piece(str) {}


  StringPiece::size_type size() const { return piece.size(); }
  const char *data() const { return piece.data(); }

 private:
  // Use ":" not ':'
  AlphaNum(char c);

  DISALLOW_COPY_AND_ASSIGN(AlphaNum);
};

// ----------------------------------------------------------------------
// StrCat()
//    This merges the given strings or numbers, with no delimiter.  This
//    is designed to be the fastest possible way to construct a string out
//    of a mix of raw C strings, StringPieces, strings, bool values,
//    and numeric values.
// ----------------------------------------------------------------------

template <typename T >
string StrCat(const T u) {
  AlphaNum a(u);
  return string(a.data(), a.size());
}

template <typename T, typename... Args >
string StrCat(const T u, Args... args) {
  return StrCat(u) + StrCat(args...);
}

// ----------------------------------------------------------------------
// StrAppend()
//    Same as above, but adds the output to the given string.
//    WARNING: For speed, StrAppend does not try to check each of its input
//    arguments to be sure that they are not a subset of the string being
//    appended to.  That is, while this will work:
//
//    string s = "foo";
//    s += s;
//
//    This will not (necessarily) work:
//
//    string s = "foo";
//    StrAppend(&s, s);
//
//    Note: while StrCat supports appending up to 12 arguments, StrAppend
//    is currently limited to 9.  That's rarely an issue except when
//    automatically transforming StrCat to StrAppend, and can easily be
//    worked around as consecutive calls to StrAppend are quite efficient.
// ----------------------------------------------------------------------

void StrAppend(string *dest,      const AlphaNum &a);
void StrAppend(string *dest,      const AlphaNum &a, const AlphaNum &b);
void StrAppend(string *dest,      const AlphaNum &a, const AlphaNum &b,
               const AlphaNum &c);
void StrAppend(string *dest,      const AlphaNum &a, const AlphaNum &b,
               const AlphaNum &c, const AlphaNum &d);
void StrAppend(string *dest,      const AlphaNum &a, const AlphaNum &b,
               const AlphaNum &c, const AlphaNum &d, const AlphaNum &e);

}  // namespace googleapis
#endif  // GOOGLEAPIS_STRINGS_STRCAT_H_
