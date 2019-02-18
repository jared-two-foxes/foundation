#ifndef __COMMAND_DISPATCHER_HPP__
#define __COMMAND_DISPATCHER_HPP__

#include <assert.h>
#include <functional>
#include <map>


namespace framework {

/*
 *
 *   auto fn = [](){ do_something_interesting };
 *   CommandDispatcher<std::string, void() >
 *       dispatcher {{
 *           {"init", fn}}};
 *
 *   std::string command = "init";
 *   dispatcher.process(command); //< calls fn?
 *
 */
template <typename Key, typename Fn >
struct CommandDispatcher {
    std::map<Key, std::function<Fn > > m_CommandMap;

    bool exists(Key const & command) {
      auto it = m_CommandMap.find(command);
      return (it != m_CommandMap.end());
    }

    template <typename ...Args>
    void process(Key const & command, Args&&... args) {
      if (exists(command)) {
        m_CommandMap[command](args...);
      }
    }
};

}

#endif // __COMMAND_DISPATCHER_HPP__
