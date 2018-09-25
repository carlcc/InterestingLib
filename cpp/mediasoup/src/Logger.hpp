/**
 * Logger facility.
 *
 * This include file defines logging macros for source files (.cpp). Each
 * source file including Logger.hpp MUST define its own MS_CLASS macro. Include
 * files (.h) MUST NOT include Logger.hpp.
 *
 * All the logging macros use the same format as printf(). The XXX_STD version
 * of a macro logs to stdoud/stderr instead of using the Channel instance.
 *
 * If the macro MS_LOG_FILE_LINE is defied, all the logging macros print more
 * verbose information, including current file and line.
 *
 * MS_TRACE()
 *
 *   Logs the current method/function if MS_LOG_TRACE macro is defined and the
 *   current debug level is "debug".
 *
 * MS_HAS_DEBUG_TAG(tag)
 * MS_HAS_WARN_TAG(tag)
 *
 *   True if the current debug level is satisfied and the given tag is enabled
 *   (or if the current source file defines the MS_LOG_DEV macro).
 *
 * MS_DEBUG_TAG(tag, ...)
 * MS_WARN_TAG(tag, ...)
 *
 *   Logs if the current debug level is satisfied and the given tag is enabled
 *   (or if the current source file defines the MS_LOG_DEV macro).
 *   Example:
 *     MS_WARN_TAG(ice, "ICE failed");
 *
 * MS_DEBUG_2TAGS(tag1, tag2, ...)
 * MS_WARN_2TAGS(tag1, tag2, ...)
 *
 *   Logs if the current debug level is satisfied and any of the given two tags
 *   is enabled (or if the current source file defines the MS_LOG_DEV macro).
 *   Example:
 *     MS_DEBUG_2TAGS(ice, dtls, "media connection established");
 *
 * MS_DEBUG_DEV(...)
 * MS_WARN_DEV(...)
 *
 * 	 Logs if the current source file defines the MS_LOG_DEV macro.
 * 	 Example:
 * 	   MS_DEBUG_DEV("Producer closed [producerId:%" PRIu32 "]", producerId);
 *
 * MS_DUMP(...)
 *
 *   For Dump() methods.
 *
 * MS_ERROR(...)
 *
 *   Logs an error. Must just be used for internal errors that should not
 *   happen.
 *
 * MS_ABORT(...)
 *
 *   Logs the given error to stderr and aborts the process.
 *
 * MS_ASSERT(condition, ...)
 *
 *   If the condition is not satisfied, it calls MS_ABORT().
 */

#pragma once

#include "common.hpp"
#include "MediaSoupError.hpp"
#include <cstdio>  // std::snprintf(), std::fprintf(), stdout, stderr
#include <cstdlib> // std::abort()
#include <cstring>
#include <string>
#include <exception>

// clang-format off
#define MS_INFO(fmt, ...) printf((fmt), ##__VA_ARGS__)

#define MS_ASSERT(condition, fmt, ...) do { if (condition) break; MS_INFO(fmt, ##__VA_ARGS__); } while (false)
#define MS_ABORT(fmt, ...) do { printf(fmt, ##__VA_ARGS__); abort(); } while (false)

#define MS_TRACE() do { MS_INFO("%S:%d", __FILE__, __LINE__); abort(); } while (false)

#define MS_ERROR MS_INFO
#define MS_WARN_DEV MS_INFO
#define MS_DUMP MS_INFO
#define MS_DEBUG_DEV MS_INFO

#define MS_DEBUG_TAG(tag, fmt, ...) MS_INFO("[%s] " fmt, #tag, ##__VA_ARGS__);