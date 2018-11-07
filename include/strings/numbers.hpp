// Maintainer: mec@google.com (Michael Chastain)
//
// Convert strings to numbers or numbers to strings.

#ifndef FOUNDATION_STRINGS_NUMBERS_H_
#define FOUNDATION_STRINGS_NUMBERS_H_

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <functional>
using std::binary_function;
using std::less;
#include <limits>
#include <string>
using std::string;

#include <foundation/base/macros.hpp>
#include <foundation/strings/ascii_ctype.hpp>
#include <foundation/strings/stringpiece.hpp>

namespace foundation {


// ----------------------------------------------------------------------
// FastIntToBuffer()
// FastHexToBuffer()
// FastHex64ToBuffer()
// FastHex32ToBuffer()
// FastTimeToBuffer()
//    These are intended for speed.  FastHexToBuffer() puts output in
//    hex rather than decimal.  FastTimeToBuffer() puts the output
//    into RFC822 format.
//
//    FastHex64ToBuffer() puts a 64-bit unsigned value in hex-format,
//    padded to exactly 16 bytes (plus one byte for '\0')
//
//    FastHex32ToBuffer() puts a 32-bit unsigned value in hex-format,
//    padded to exactly 8 bytes (plus one byte for '\0')
//
//    All functions take the output buffer as an arg.  FastInt() uses
//    at most 22 bytes, FastTime() uses exactly 30 bytes.  They all
//    return a pointer to the beginning of the output, which for
//    FastHex() may not be the beginning of the input buffer.  (For
//    all others, we guarantee that it is.)
//
//    NOTE: In 64-bit land, sizeof(time_t) is 8, so it is possible
//    to pass to FastTimeToBuffer() a time whose year cannot be
//    represented in 4 digits. In this case, the output buffer
//    will contain the string "Invalid:<value>"
// ----------------------------------------------------------------------

// Previously documented minimums -- the buffers provided must be at least this
// long, though these numbers are subject to change:
//     Int32, UInt32:                   12 bytes
//     Int64, UInt64, Hex, Int, Uint:   22 bytes
//     Time:                            30 bytes
//     Hex32:                            9 bytes
//     Hex64:                           17 bytes
// Use kFastToBufferSize rather than hardcoding constants.
static const int kFastToBufferSize = 32;

char* FastUInt32ToBuffer(uint32_t i, char* buffer);
char* FastUInt64ToBuffer(uint64_t i, char* buffer);
char* FastHexToBuffer(int i, char* buffer);
char* FastTimeToBuffer(time_t t, char* buffer);
char* FastHex64ToBuffer(uint64_t i, char* buffer);
char* FastHex32ToBuffer(uint32_t i, char* buffer);

// ----------------------------------------------------------------------
// FastInt32ToBufferLeft()
// FastUInt32ToBufferLeft()
// FastInt64ToBufferLeft()
// FastUInt64ToBufferLeft()
//
// Like the Fast*ToBuffer() functions above, these are intended for speed.
// Unlike the Fast*ToBuffer() functions, however, these functions write
// their output to the beginning of the buffer (hence the name, as the
// output is left-aligned).  The caller is responsible for ensuring that
// the buffer has enough space to hold the output.
//
// Returns a pointer to the end of the string (i.e. the null character
// terminating the string).
// ----------------------------------------------------------------------

char* FastInt32ToBufferLeft(int32_t i, char* buffer);    // at least 12 bytes
char* FastUInt32ToBufferLeft(uint32_t i, char* buffer);    // at least 12 bytes
char* FastInt64ToBufferLeft(int64_t i, char* buffer);    // at least 22 bytes
char* FastUInt64ToBufferLeft(uint64_t i, char* buffer);    // at least 22 bytes

// Just define these in terms of the above.

inline char* FastInt32ToBuffer(int32_t i, char* buffer) {
  FastInt32ToBufferLeft(i, buffer);
  return buffer;
}
inline char* FastUInt32ToBuffer(uint32_t i, char* buffer) {
  FastUInt32ToBufferLeft(i, buffer);
  return buffer;
}
inline char* FastInt64ToBuffer(int64_t i, char* buffer) {
  FastInt64ToBufferLeft(i, buffer);
  return buffer;
}
inline char* FastUInt64ToBuffer(uint64_t i, char* buffer) {
  FastUInt64ToBufferLeft(i, buffer);
  return buffer;
}
inline char* FastIntToBuffer(int i, char* buffer) {
  return (sizeof(i) == 4 ?
          FastInt32ToBuffer(i, buffer) : FastInt64ToBuffer(i, buffer));
}
inline char* FastUIntToBuffer(unsigned int i, char* buffer) {
  return (sizeof(i) == 4 ?
          FastUInt32ToBuffer(i, buffer) : FastUInt64ToBuffer(i, buffer));
}

// ----------------------------------------------------------------------
// HexDigitsPrefix()
//  returns 1 if buf is prefixed by "num_digits" of hex digits
//  returns 0 otherwise.
//  The function checks for '\0' for string termination.
// ----------------------------------------------------------------------
int HexDigitsPrefix(const char* buf, int num_digits);

// ----------------------------------------------------------------------
// ConsumeStrayLeadingZeroes
//    Eliminates all leading zeroes (unless the string itself is composed
//    of nothing but zeroes, in which case one is kept: 0...0 becomes 0).
void ConsumeStrayLeadingZeroes(string* str);

// ----------------------------------------------------------------------
// ParseLeadingInt32Value
//    A simple parser for int32_t values. Returns the parsed value
//    if a valid integer is found; else returns deflt. It does not
//    check if str is entirely consumed.
//    This cannot handle decimal numbers with leading 0s, since they will be
//    treated as octal.  If you know it's decimal, use ParseLeadingDec32Value.
// --------------------------------------------------------------------
int32_t ParseLeadingInt32Value(const char* str, int32_t deflt);
inline int32_t ParseLeadingInt32Value(const string& str, int32_t deflt) {
  return ParseLeadingInt32Value(str.c_str(), deflt);
}

// ParseLeadingUInt32Value
//    A simple parser for uint32_t values. Returns the parsed value
//    if a valid integer is found; else returns deflt. It does not
//    check if str is entirely consumed.
//    This cannot handle decimal numbers with leading 0s, since they will be
//    treated as octal.  If you know it's decimal, use ParseLeadingUDec32Value.
// --------------------------------------------------------------------
uint32_t ParseLeadingUInt32Value(const char* str, uint32_t deflt);
inline uint32_t ParseLeadingUInt32Value(const string& str, uint32_t deflt) {
  return ParseLeadingUInt32Value(str.c_str(), deflt);
}

// ----------------------------------------------------------------------
// ParseLeadingDec32Value
//    A simple parser for decimal int32_t values. Returns the parsed value
//    if a valid integer is found; else returns deflt. It does not
//    check if str is entirely consumed.
//    The string passed in is treated as *10 based*.
//    This can handle strings with leading 0s.
//    See also: ParseLeadingDec64Value
// --------------------------------------------------------------------
int32_t ParseLeadingDec32Value(const char* str, int32_t deflt);
inline int32_t ParseLeadingDec32Value(const string& str, int32_t deflt) {
  return ParseLeadingDec32Value(str.c_str(), deflt);
}

// ParseLeadingUDec32Value
//    A simple parser for decimal uint32_t values. Returns the parsed value
//    if a valid integer is found; else returns deflt. It does not
//    check if str is entirely consumed.
//    The string passed in is treated as *10 based*.
//    This can handle strings with leading 0s.
//    See also: ParseLeadingUDec64Value
// --------------------------------------------------------------------
uint32_t ParseLeadingUDec32Value(const char* str, uint32_t deflt);
inline uint32_t ParseLeadingUDec32Value(const string& str, uint32_t deflt) {
  return ParseLeadingUDec32Value(str.c_str(), deflt);
}

// ----------------------------------------------------------------------
// ParseLeadingUInt64Value
// ParseLeadingInt64Value
// ParseLeadingHex64Value
// ParseLeadingDec64Value
// ParseLeadingUDec64Value
//    A simple parser for long long values.
//    Returns the parsed value if a
//    valid integer is found; else returns deflt
// --------------------------------------------------------------------
uint64_t ParseLeadingUInt64Value(const char* str, uint64_t deflt);
inline uint64_t ParseLeadingUInt64Value(const string& str, uint64_t deflt) {
  return ParseLeadingUInt64Value(str.c_str(), deflt);
}
int64_t ParseLeadingInt64Value(const char* str, int64_t deflt);
inline int64_t ParseLeadingInt64Value(const string& str, int64_t deflt) {
  return ParseLeadingInt64Value(str.c_str(), deflt);
}
uint64_t ParseLeadingHex64Value(const char* str, uint64_t deflt);
inline uint64_t ParseLeadingHex64Value(const string& str, uint64_t deflt) {
  return ParseLeadingHex64Value(str.c_str(), deflt);
}
int64_t ParseLeadingDec64Value(const char* str, int64_t deflt);
inline int64_t ParseLeadingDec64Value(const string& str, int64_t deflt) {
  return ParseLeadingDec64Value(str.c_str(), deflt);
}
uint64_t ParseLeadingUDec64Value(const char* str, uint64_t deflt);
inline uint64_t ParseLeadingUDec64Value(const string& str, uint64_t deflt) {
  return ParseLeadingUDec64Value(str.c_str(), deflt);
}

// ----------------------------------------------------------------------
// ParseLeadingDoubleValue
//    A simple parser for double values. Returns the parsed value
//    if a valid double is found; else returns deflt. It does not
//    check if str is entirely consumed.
// --------------------------------------------------------------------
double ParseLeadingDoubleValue(const char* str, double deflt);
inline double ParseLeadingDoubleValue(const string& str, double deflt) {
  return ParseLeadingDoubleValue(str.c_str(), deflt);
}

// ----------------------------------------------------------------------
// ParseLeadingBoolValue()
//    A recognizer of boolean string values. Returns the parsed value
//    if a valid value is found; else returns deflt.  This skips leading
//    whitespace, is case insensitive, and recognizes these forms:
//    0/1, false/true, no/yes, n/y
// --------------------------------------------------------------------
bool ParseLeadingBoolValue(const char* str, bool deflt);
inline bool ParseLeadingBoolValue(const string& str, bool deflt) {
  return ParseLeadingBoolValue(str.c_str(), deflt);
}

// ----------------------------------------------------------------------
// SimpleItoa()
//    Description: converts an integer to a string.
//    Faster than printf("%d").
//
//    Return value: string
// ----------------------------------------------------------------------
inline string SimpleItoa(int32_t i) {
  char buf[16];  // Longest is -2147483648
  return string(buf, FastInt32ToBufferLeft(i, buf));
}

// We need this overload because otherwise SimpleItoa(5U) wouldn't compile.
inline string SimpleItoa(uint32_t i) {
  char buf[16];  // Longest is 4294967295
  return string(buf, FastUInt32ToBufferLeft(i, buf));
}

inline string SimpleItoa(int64_t i) {
  char buf[32];  // Longest is -9223372036854775808
  return string(buf, FastInt64ToBufferLeft(i, buf));
}

// We need this overload because otherwise SimpleItoa(5ULL) wouldn't compile.
inline string SimpleItoa(uint64_t i) {
  char buf[32];  // Longest is 18446744073709551615
  return string(buf, FastUInt64ToBufferLeft(i, buf));
}

/*
// SimpleAtoi converts a string to an integer.
// Uses safe_strto?() for actual parsing, so strict checking is
// applied, which is to say, the string must be a base-10 integer, optionally
// followed or preceded by whitespace, and value has to be in the range of
// the corresponding integer type.
//
// Returns true if parsing was successful.
template <typename int_type>
bool SimpleAtoi(const char* s, int_type* out) {
  // Must be of integer type (not pointer type), with more than 16-bitwidth.
  static_assert(sizeof(*out) == 4 || sizeof(*out) == 8,
                "SimpleAtoi only works with 32 or 64 bit Ints");
  if (std::numeric_limits<int_type>::is_signed) {  // Signed
    if (sizeof(*out) == 64 / 8) {  // 64-bit
      return safe_strto64(s, reinterpret_cast<int64*>(out));
    } else {  // 32-bit
      return safe_strto32(s, reinterpret_cast<int32*>(out));
    }
  } else {  // Unsigned
    if (sizeof(*out) == 64 / 8) {  // 64-bit
      return safe_strtou64(s, reinterpret_cast<uint64_t*>(out));
    } else {  // 32-bit
      return safe_strtou32(s, reinterpret_cast<uint32_t*>(out));
    }
  }
}

template <typename int_type>
bool SimpleAtoi(const string& s, int_type* out) {
  return SimpleAtoi(s.c_str(), out);
}
*/

// ----------------------------------------------------------------------
// SimpleDtoa()
// SimpleFtoa()
//    Description: converts a double or float to a string which, if passed to
//    strtod() or strtof() respectively, will produce the exact same original
//    double or float.  Exception: for NaN values, strtod(SimpleDtoa(NaN)) or
//    strtof(SimpleFtoa(NaN)) may produce any NaN value, not necessarily the
//    exact same original NaN value.
//
//    The output string is not guaranteed to be as short as possible.
//
//    The output string, including terminating NUL, will have length
//    less than or equal to kFastToBufferSize defined above.  Of course,
//    we would prefer that your code not depend on this property of
//    the output string.  This guarantee derives from a similar guarantee
//    from the previous generation of char-buffer-based functions.
//    We had to carry it forward to preserve compatibility.
// ----------------------------------------------------------------------
string SimpleDtoa(double value);
string SimpleFtoa(float value);

// Converts a boolean to a string. The returned string will be "true" if
// value == true, and "false" otherwise.
string SimpleBtoa(bool value);

// ----------------------------------------------------------------------
// ItoaKMGT()
//    Description: converts an integer to a string
//    Truncates values to K, G, M or T as appropriate
//    Opposite of atoi_kmgt()
//    e.g. 3000 -> 2K   57185920 -> 45M
//
//    Return value: string
// ----------------------------------------------------------------------
string ItoaKMGT(int64_t i);

// ----------------------------------------------------------------------
// ParseDoubleRange()
//    Parse an expression in 'text' of the form: <double><sep><double>
//    where <double> may be a double-precision number and <sep> is a
//    single char or "..", and must be one of the chars in parameter
//    'separators', which may contain '-' or '.' (which means "..") or
//    any chars not allowed in a double. If allow_unbounded_markers,
//    <double> may also be a '?' to indicate unboundedness (if on the
//    left of <sep>, means unbounded below; if on the right, means
//    unbounded above). Depending on num_required_bounds, which may be
//    0, 1, or 2, <double> may also be the empty string, indicating
//    unboundedness. If require_separator is false, then a single
//    <double> is acceptable and is parsed as a range bounded from
//    below. We also check that the character following the range must
//    be in acceptable_terminators. If null_terminator_ok, then it is
//    also OK if the range ends in \0 or after len chars. If
//    allow_currency is true, the first <double> may be optionally
//    preceded by a '$', in which case *is_currency will be true, and
//    the second <double> may similarly be preceded by a '$'. In these
//    cases, the '$' will be ignored (otherwise it's an error). If
//    allow_comparators is true, the expression in 'text' may also be
//    of the form <comparator><double>, where <comparator> is '<' or
//    '>' or '<=' or '>='. separators and require_separator are
//    ignored in this format, but all other parameters function as for
//    the first format. Return true if the expression parsed
//    successfully; false otherwise. If successful, output params are:
//    'end', which points to the char just beyond the expression;
//    'from' and 'to' are set to the values of the <double>s, and are
//    -inf and inf (or unchanged, depending on dont_modify_unbounded)
//    if unbounded. Output params are undefined if false is
//    returned. len is the input length, or -1 if text is
//    '\0'-terminated, which is more efficient.
// ----------------------------------------------------------------------
struct DoubleRangeOptions {
  const char* separators;
  bool require_separator;
  const char* acceptable_terminators;
  bool null_terminator_ok;
  bool allow_unbounded_markers;
  uint32_t num_required_bounds;
  bool dont_modify_unbounded;
  bool allow_currency;
  bool allow_comparators;
};

// NOTE: The instruction below creates a Module titled
// NumbersFunctions within the auto-generated Doxygen documentation.
// This instruction is needed to expose global functions that are not
// within a namespace.
//
bool ParseDoubleRange(const char* text, int len, const char** end,
                      double* from, double* to, bool* is_currency,
                      const DoubleRangeOptions& opts);


}  // namespace googleapis
#endif  // GOOGLEAPIS_STRINGS_NUMBERS_H_
