#pragma once

#include <common/interface.h>
#include <mt/file_logger.h>
#include <mt/console_logger.h>
#include <mt/commands_storage.h>
#include <mt/metricks.h>

namespace mt
{
  class command_processor : public common::interface<command_processor>
  {
    public:
      command_processor(const int block_size, const int file_loggers_count);
      virtual ~command_processor();
      void process_cmd(const std::string& cmd);
      void process_cmd_pipeline(commands_storage_t& cmd_pipeline);
      void forced_dump();
      void run_observers();
      void stop_observers();

    private:
      void subscribe(std::shared_ptr<observer>&& obs);
      void notify(commands_storage_t& commands_storage);

    private:
      std::vector<std::shared_ptr<observer>> m_subs;
      commands_storage_t m_commands_storage;
      int m_block_size;
      std::string m_thread_name = "main";
  };
}

