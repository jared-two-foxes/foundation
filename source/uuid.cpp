
#include <foundation/uuid/uuid.hpp>

static int s_nextIdentifier = 0;

int getUuid() {
  return s_nextIdentifier++;
}
