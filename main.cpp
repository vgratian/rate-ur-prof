#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "professor.cpp"
#include "student.cpp"
#include "course.cpp"
#include "rating.cpp"
#include "session.cpp"

extern "C" {
  Session* Session_new() {
    return new Session();
  }
}

/* Compile this as a shared library:
g++ -c -fPIC main.cpp -o main.o
g++ -shared -Wl,-soname,libfoo.so -o libfoo.so  main.o
*/

int main() {

  Session hello;

  return 0;
}
