#ifndef LOG_H

#include "spdlog/spdlog.h"

#define ICHI_DEFAULT_LOGGER_NAME "IchiLogger"

#ifdef NDEBUG

#define ICHI_TRACE(...) (void)0
#define ICHI_DEBUG(...) (void)0
#define ICHI_INFO(...) (void)0
#define ICHI_WARNING(...) (void)0
#define ICHI_ERROR(...) (void)0
#define ICHI_FATAL(...) (void)0

#else

#define ICHI_TRACE(...)                                            \
    if (spdlog::get(ICHI_DEFAULT_LOGGER_NAME) != nullptr)          \
    {                                                              \
        spdlog::get(ICHI_DEFAULT_LOGGER_NAME)->trace(__VA_ARGS__); \
    }
#define ICHI_DEBUG(...)                                            \
    if (spdlog::get(ICHI_DEFAULT_LOGGER_NAME) != nullptr)          \
    {                                                              \
        spdlog::get(ICHI_DEFAULT_LOGGER_NAME)->debug(__VA_ARGS__); \
    }
#define ICHI_INFO(...)                                            \
    if (spdlog::get(ICHI_DEFAULT_LOGGER_NAME) != nullptr)         \
    {                                                             \
        spdlog::get(ICHI_DEFAULT_LOGGER_NAME)->info(__VA_ARGS__); \
    }
#define ICHI_WARNING(...)                                         \
    if (spdlog::get(ICHI_DEFAULT_LOGGER_NAME) != nullptr)         \
    {                                                             \
        spdlog::get(ICHI_DEFAULT_LOGGER_NAME)->warn(__VA_ARGS__); \
    }
#define ICHI_ERROR(...)                                            \
    if (spdlog::get(ICHI_DEFAULT_LOGGER_NAME) != nullptr)          \
    {                                                              \
        spdlog::get(ICHI_DEFAULT_LOGGER_NAME)->error(__VA_ARGS__); \
    }
#define ICHI_FATAL(...)                                               \
    if (spdlog::get(ICHI_DEFAULT_LOGGER_NAME) != nullptr)             \
    {                                                                 \
        spdlog::get(ICHI_DEFAULT_LOGGER_NAME)->critical(__VA_ARGS__); \
    }

#endif

#endif