
#include <foundation/strings/strcat.hpp>
//#include <foundation/strings/ascii_ctype.hpp>

#include <stdint.h>
#include <stdio.h>
#include <string.h>

namespace foundation {

AlphaNum gEmptyAlphaNum("");

// Append is merely a version of memcpy that returns the address of the byte
// after the area just overwritten.  It comes in multiple flavors to minimize
// call overhead.
static char *Append1(char *out, const AlphaNum &x) {
  memcpy(out, x.data(), x.size());
  return out + x.size();
}

static char *Append2(char *out, const AlphaNum &x1, const AlphaNum &x2) {
  memcpy(out, x1.data(), x1.size());
  out += x1.size();

  memcpy(out, x2.data(), x2.size());
  return out + x2.size();
}

static char *Append4(char *out,
                     const AlphaNum &x1, const AlphaNum &x2,
                     const AlphaNum &x3, const AlphaNum &x4) {
  memcpy(out, x1.data(), x1.size());
  out += x1.size();

  memcpy(out, x2.data(), x2.size());
  out += x2.size();

  memcpy(out, x3.data(), x3.size());
  out += x3.size();

  memcpy(out, x4.data(), x4.size());
  return out + x4.size();
}

// string StrCat(const AlphaNum &a, const AlphaNum &b) {
//   string result;
//   result.resize(a.size() + b.size());
//   char *const begin = &*result.begin();
//   char *out = Append2(begin, a, b);
//   //DCHECK_EQ(out, begin + result.size());
//   return result;
// }
// 
// string StrCat(const AlphaNum &a, const AlphaNum &b, const AlphaNum &c) {
//   string result;
//   result.resize(a.size() + b.size() + c.size());
//   char *const begin = &*result.begin();
//   char *out = Append2(begin, a, b);
//   out = Append1(out, c);
//   //DCHECK_EQ(out, begin + result.size());
//   return result;
// }
//
// string StrCat(const AlphaNum &a, const AlphaNum &b, const AlphaNum &c,
//               const AlphaNum &d) {
//   string result;
//   result.resize(a.size() + b.size() + c.size() + d.size());
//   char *const begin = &*result.begin();
//   char *out = Append4(begin, a, b, c, d);
//   //DCHECK_EQ(out, begin + result.size());
//   return result;
// }

void StrAppend(string *result, const AlphaNum &a) {
  result->append(a.data(), a.size());
}

void StrAppend(string *result, const AlphaNum &a, const AlphaNum &b) {
  string::size_type old_size = result->size();
  result->resize(old_size + a.size() + b.size());
  char *const begin = &*result->begin();
  char *out = Append2(begin + old_size, a, b);
  //DCHECK_EQ(out, begin + result->size());
}

void StrAppend(string *result,
               const AlphaNum &a, const AlphaNum &b, const AlphaNum &c) {
  string::size_type old_size = result->size();
  result->resize(old_size + a.size() + b.size() + c.size());
  char *const begin = &*result->begin();
  char *out = Append2(begin + old_size, a, b);
  out = Append1(out, c);
  //DCHECK_EQ(out, begin + result->size());
}

void StrAppend(string *result,
               const AlphaNum &a, const AlphaNum &b,
               const AlphaNum &c, const AlphaNum &d) {
  string::size_type old_size = result->size();
  result->resize(old_size + a.size() + b.size() + c.size() + d.size());
  char *const begin = &*result->begin();
  char *out = Append4(begin + old_size, a, b, c, d);
  //DCHECK_EQ(out, begin + result->size());
}


}  // namespace foundation
