#include <interpreter.h>

namespace async
{
  using namespace std::chrono_literals;

  interpreter::interpreter(mt::command_processor::ref a_commands_processor)
    : m_commands_processor(a_commands_processor)
  {
  }

  void interpreter::process_cmd(const std::string &a_cmd)
  {
    if (a_cmd == "{")
    {
      process_open_bracket();
    }
    else if (a_cmd == "}")
    {
      process_close_bracket();
    }
    else
    {
      process_simple_cmd(a_cmd);
    }
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

  void interpreter::process_simple_cmd(const std::string &a_cmd)
  {
    if(m_open_brackets_count > 0)
      m_commands_storage.append(a_cmd);
    else
      m_commands_processor->process_cmd(a_cmd);
  }
}
