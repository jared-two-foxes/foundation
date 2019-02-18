#ifndef FOUNDATION_LOGGER_HPP__
#define FOUNDATION_LOGGER_HPP__

#include <string>
#include <ostream>


class Logger
{
public:
  virtual ~Logger() {}
  virtual void write( std::string const& line ) = 0;
};

class BasicLogger : public Logger
{
private:
  std::ostream& stream;
public:
  BasicLogger(std::ostream& os);
  void write( std::string const& line );
};


void ClearLoggers();
void RegisterLogger( Logger* logger, int threshold );
void SendToLogger( int level, std::string const& line );


template <typename... Args >
inline void Log( int level, char const * line, Args... args ) {
  char buffer[256];
  snprintf( buffer, 255, line, args... );
  SendToLogger( level, buffer );
}

inline void Log( int level, char const * line ) {
  char buffer[256];
  snprintf( buffer, 255, "%s", line );
  SendToLogger( level, buffer );
}

template <typename... Args >
inline void ConditionalLog( bool conditional, int level, char const * line, Args... args ) {
  if (conditional) {
    Log( level, line, args... );
  }
}

#endif // FOUNDATION_LOGGER_HPP__
