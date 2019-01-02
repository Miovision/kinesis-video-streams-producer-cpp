#pragma once

/*
#include <log4cplus/configurator.h>
#include <log4cplus/loggingmacros.h>
#include <log4cplus/logger.h>
#include <log4cplus/consoleappender.h>
#include <log4cplus/layout.h>
*/
#include <sstream>
#include <stdexcept>
#include <iostream>
namespace com { namespace amazonaws { namespace kinesis { namespace video {

// configure the logger by loading configuration from specific properties file.
// generally, it should be called only once in your main() function.
#define LOG_CONFIGURE(filename)

#define _LOG_CONFIGURE_CONSOLE(level, logToStdErr)

#define LOG_CONFIGURE_STDOUT(level) _LOG_CONFIGURE_CONSOLE(level, false)

#define LOG_CONFIGURE_STDERR(level) _LOG_CONFIGURE_CONSOLE(level, true)

// runtime queries for enabled log level. useful if message construction is expensive.
#define LOG_IS_TRACE_ENABLED
#define LOG_IS_DEBUG_ENABLED
#define LOG_IS_INFO_ENABLED
#define LOG_IS_WARN_ENABLED
#define LOG_IS_ERROR_ENABLED
#define LOG_IS_FATAL_ENABLED

// logging macros - any usage must be preceded by a LOGGER_TAG definition visible at the current scope.
// failure to use the LOGGER_TAG macro will result in "error: 'KinesisVideoLogger' has not been declared"
#define LOG_TRACE(msg) std::cout << msg << std::endl;
#define LOG_DEBUG(msg) std::cout << msg << std::endl;
#define LOG_INFO(msg) std::cout << msg << std::endl;
#define LOG_WARN(msg) std::cout << msg << std::endl;
#define LOG_ERROR(msg) std::cout << msg << std::endl;
#define LOG_FATAL(msg) std::cout << msg << std::endl;

#define LOG_AND_THROW(msg) \
  do { \
    std::ostringstream __oss; \
    __oss << msg; \
	  std::cerr << __oss.str() << std::endl;\
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
} // namespace video
} // namespace kinesis
} // namespace amazonaws
} // namespace com
