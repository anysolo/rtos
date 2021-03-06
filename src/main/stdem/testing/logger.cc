#include <stdem/testing/logger.h>
#include <stdem/cstr.h>


extern "C" int _write(int file, char *ptr, int len);


namespace StdEm {
namespace Testing {


Logger& Logger::operator<< (int n)
{
  char buf[21];
  print(Cstr::integerToCstr(n, buf, sizeof(buf)));

  return *this;
}

void Logger::print(const char* str)
  { _write(0, (char*)str, Cstr::strLen(str)); }

}} // Testing, StdEm
