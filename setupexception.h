#ifndef SETUPEXCEPTION_H
#define SETUPEXCEPTION_H

#include <stdexcept>

// Thrown when a setup function is called in non-setup mode,
// when a non-setup function is called in setup mode,
// setupMode is false in Board constructor while size is not 8 or
// cannot exit setup mode because invariants have not been satisfied yet
class SetupException : public std::runtime_error {
public:
  SetupException(const char* m) : std::runtime_error(m) { }
};

#endif
