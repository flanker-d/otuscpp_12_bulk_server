#include <mt/command_processor.h>

namespace mt
{
  command_processor::command_processor(const int block_size, const int file_loggers_count) : m_block_size(block_size)
  {
    metricks::instance().register_thread(m_thread_name);

    subscribe(std::make_shared<console_logger>());
    subscribe(std::make_shared<file_logger>(file_loggers_count));

    run_observers();
  }

  command_processor::~command_processor()
  {
    stop_observers();
  }

  void command_processor::process_cmd(const std::string &cmd)
  {
    mt::metricks::instance().lines_incr(m_thread_name);
    if (m_commands_storage.commands_count() == 0)
    {
      m_commands_storage.init_time();
    }

    m_commands_storage.append(cmd);
    if (m_commands_storage.commands_count() == m_block_size)
    {
      notify(m_commands_storage);
    }
  }

  void command_processor::process_cmd_pipeline(commands_storage_t &cmd_pipeline)
  {
    mt::metricks::instance().lines_incr(m_thread_name);
    notify(cmd_pipeline);
  }

  void command_processor::forced_dump()
  {
    notify(m_commands_storage);
  }

  void command_processor::run_observers()
  {
    for(auto& obs : m_subs)
      obs->run();
  }

  void command_processor::stop_observers()
  {
    for(auto& obs : m_subs)
      obs->stop();
  }

  void command_processor::subscribe(std::shared_ptr<observer> &&obs)
  {
    m_subs.emplace_back(std::move(obs));
  }

  void command_processor::notify(commands_storage_t &commands_storage)
  {
    if (!commands_storage.is_empty())
    {
      cmd_block_t cmd = commands_storage.make_block(metricks::instance().get_blocks_count(m_thread_name));
      for (auto &s : m_subs)
      {
        s->update(cmd);
      }
      metricks::instance().blocks_incr(m_thread_name);
      metricks::instance().commands_incr(m_thread_name, cmd.count);
      commands_storage.clear();
    }
  }
}