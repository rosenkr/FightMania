#ifndef LOGMANAGER_H
#define LOGMANAGER_H

namespace ichi::managers
{
    class LogManager
    {
    public:
        void init();
        void shutdown();

        LogManager() = default;
        ~LogManager() = default;
    };
} // namespace ichi::managers

#endif