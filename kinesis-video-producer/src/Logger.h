#pragma once

#include <sstream>
#include <stdexcept>
#include <iostream>

// This is a Mio-reimplementation of Amazon's generic log4cpp wrapper class.
// Log-level is configurable at runtime, 

#define KINESIS_LOG_LEVEL_TRACE 1
#define KINESIS_LOG_LEVEL_DEBUG 2
#define KINESIS_LOG_LEVEL_INFO 3
#define KINESIS_LOG_LEVEL_WARN 4 
#define KINESIS_LOG_LEVEL_ERROR 5
#define KINESIS_LOG_LEVEL_FATAL 6

// configure the logger by loading configuration from specific properties file.
// generally, it should be called only once in your main() function.
#define LOG_CONFIGURE(filename)

#define _LOG_CONFIGURE_CONSOLE(level, logToStdErr) KINESIS_LOG_LEVEL = level

#define LOG_CONFIGURE_STDOUT(level) _LOG_CONFIGURE_CONSOLE(level, false)

#define LOG_CONFIGURE_STDERR(level) _LOG_CONFIGURE_CONSOLE(level, true)

// runtime queries for enabled log level. useful if message construction is expensive.
#define LOG_IS_TRACE_ENABLED (com::amazonaws::kinesis::video::KINESIS_LOG_LEVEL <= KINESIS_LOG_LEVEL_TRACE)
#define LOG_IS_DEBUG_ENABLED (com::amazonaws::kinesis::video::KINESIS_LOG_LEVEL <= KINESIS_LOG_LEVEL_DEBUG)
#define LOG_IS_INFO_ENABLED (com::amazonaws::kinesis::video::KINESIS_LOG_LEVEL <= KINESIS_LOG_LEVEL_INFO)
#define LOG_IS_WARN_ENABLED (com::amazonaws::kinesis::video::KINESIS_LOG_LEVEL <= KINESIS_LOG_LEVEL_WARN)
#define LOG_IS_ERROR_ENABLED (com::amazonaws::kinesis::video::KINESIS_LOG_LEVEL <= KINESIS_LOG_LEVEL_ERROR)
#define LOG_IS_FATAL_ENABLED  (com::amazonaws::kinesis::video::KINESIS_LOG_LEVEL <= KINESIS_LOG_LEVEL_FATAL)

// logging macros - any usage must be preceded by a LOGGER_TAG definition visible at the current scope.
// failure to use the LOGGER_TAG macro will result in "error: 'KinesisVideoLogger' has not been declared"
#define LOG_TRACE(msg) if(LOG_IS_TRACE_ENABLED) {std::cerr << msg << std::endl;}
#define LOG_DEBUG(msg) if(LOG_IS_DEBUG_ENABLED) {std::cerr << msg << std::endl;}
#define LOG_INFO(msg) if(LOG_IS_INFO_ENABLED) {std::cerr << msg << std::endl;}
#define LOG_WARN(msg) if(LOG_IS_WARN_ENABLED) {std::cerr << msg << std::endl;}
#define LOG_ERROR(msg) if(LOG_IS_ERROR_ENABLED) {std::cerr << msg << std::endl;}
#define LOG_FATAL(msg) if(LOG_IS_FATAL_ENABLED) {std::cerr << msg << std::endl;}

#define LOG_AND_THROW(msg) \
  do { \
    std::ostringstream __oss; \
    __oss << msg; \
          LOG_ERROR(__oss.str()) \
    throw std::runtime_error(__oss.str()); \
  } while (0)

#define LOG_AND_THROW_IF(cond, msg) \
  if (cond) { \
    LOG_AND_THROW(msg); \
  }

#define ASSERT_MSG(cond, msg) \
  LOG_AND_THROW_IF(!(cond), \
      __FILE__ << ":" << __LINE__ << ": " << msg << ": " << #cond)

#define ASSERT(cond) \
  ASSERT_MSG(cond, "Assertion failed");


// defines a class which contains a logger instance with the given tag
#define LOGGER_TAG(tag)

namespace com { namespace amazonaws { namespace kinesis { namespace video {
// Set in Logger.cpp. Defaults to 3, so INFO and up will be printed.
extern int KINESIS_LOG_LEVEL;
} // namespace video
} // namespace kinesis
} // namespace amazonaws
} // namespace com
