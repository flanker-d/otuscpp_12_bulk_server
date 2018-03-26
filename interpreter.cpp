#include <interpreter.h>

namespace async
{
  using namespace std::chrono_literals;

  interpreter::interpreter(mt::command_processor::ref commands_processor)
    : m_commands_processor(commands_processor)
  {
  }

  void interpreter::process_cmd(const std::string &cmd)
  {
    if (cmd == "{")
    {
      process_open_bracket();
    }
    else if (cmd == "}")
    {
      process_close_bracket();
    }
    else
    {
      process_simple_cmd(cmd);
    }
  }

  void interpreter::forced_dump()
  {
    m_commands_processor->forced_dump();
  }

  void interpreter::process_open_bracket()
  {
    m_open_brackets_count++;
    if (m_open_brackets_count == 1)
    {
      m_commands_storage.init_time();
    }
  }

  void interpreter::process_close_bracket()
  {
    m_open_brackets_count--;
    if (m_open_brackets_count == 0)
    {
      m_commands_processor->process_cmd_pipeline(m_commands_storage);
      m_commands_storage.clear();
    }
  }

  void interpreter::process_simple_cmd(const std::string &cmd)
  {
    if(!m_commands_storage.is_empty())
      m_commands_storage.append(cmd);
    else
      m_commands_processor->process_cmd(cmd);
  }
}
