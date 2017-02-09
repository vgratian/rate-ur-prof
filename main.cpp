/*
This is a simple class in C that will allow to use the code writtin in C++
as a C library. Isn't it amazing how a few hundreds of lines of code are
accesible with just one simple method? TBC: this isn't a rhetorical question,
I really if this creative solution will not cause problems in the future :)
*/

// C++ libraries
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

// C libraries
#include <stdio.h>
#include <string.h>

// Components of software
#include "student.cpp"
#include "professor.cpp"
#include "session.cpp"

class C_mediator {
private:
  Session* session;
public:
  C_mediator() {
    session = new Session;
  }
  const char* tunnel(const char* query) {
    const char* response;
    response = session->welcome(query);
    return response;
  }
};

extern "C" {
  C_mediator* tunnel_init() {
    return new C_mediator();
  }
  const char* tunnel_start(C_mediator* new_tunnel, const char* query) {
    const char* msg = new_tunnel->tunnel(query);
    return msg;
  }
}
