
#include <foundation/logger.hpp>

#include <iostream>
#include <vector>

//Mutex mutex;
std::vector<std::pair<Logger*, int> > loggers;


BasicLogger::BasicLogger(std::ostream& os) :
  stream(os)
{}

void BasicLogger::write( std::string const& line )
{
  stream << line;
  stream.flush();
}

void ClearLoggers()
{
  // We do not delete these here, since we didnt create them.
  loggers.clear();
}

void RegisterLogger( Logger* logger, int threshold )
{
  loggers.push_back( std::make_pair(logger, threshold) );
}

void Log( int level, std::string const& line )
{
  //Locker lock(muxtex);

  for ( auto i : loggers )
  {
    if ( level >= i.second )
    {
      i.first->write( line );
    }
  }
}
