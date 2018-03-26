#pragma once

#include <vector>
#include <ctime>
#include <mt/observer.h>

namespace mt
{
  struct commands_storage_t
  {
    time_t time;
    std::vector<std::string> commands;

    bool is_empty();
    std::size_t commands_count();
    void clear();
    void init_time();
    void append(const std::string &cmd);
    cmd_block_t make_block(int seq_num);
  };
}
