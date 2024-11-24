#include "Ichi/Managers/logManager.h"

#include "Ichi/log.h"
#include "spdlog/sinks/stdout_color_sinks.h"

#include <memory>

namespace Ichi::Managers
{
    void LogManager::init()
    {
        auto consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        consoleSink->set_pattern("%^[%Y-%m-%d %H:%M:%S.%e] %v%$");

        std::vector<spdlog::sink_ptr> sinks{consoleSink};
        auto logger = std::make_shared<spdlog::logger>(ICHI_DEFAULT_LOGGER_NAME, sinks.begin(), sinks.end());
        logger->set_level(spdlog::level::trace);
        logger->flush_on(spdlog::level::trace);

        spdlog::register_logger(logger);
    }

    void LogManager::shutdown()
    {
        spdlog::shutdown();
    }

} // namespace Ichi::Managers
