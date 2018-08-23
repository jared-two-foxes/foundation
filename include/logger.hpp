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

void Log( int level, std::string const& line );


#endif // FOUNDATION_LOGGER_HPP__
