#pragma once

#include <mt/commands_storage.h>
#include <mt/command_processor.h>
#include <common/interface.h>
#include <memory>
#include <vector>
#include <iostream>

namespace async
{
  class interpreter : public common::interface<interpreter>
  {
    public:
      interpreter(mt::command_processor::ref a_commands_processor);
      void process_cmd(const std::string &a_cmd);

    private:
      void process_open_bracket();
      void process_close_bracket();
      void process_simple_cmd(const std::string &a_cmd);

    private:
      int m_open_brackets_count = 0;
      mt::commands_storage_t m_commands_storage;
      mt::command_processor::ref m_commands_processor;
  };
}
