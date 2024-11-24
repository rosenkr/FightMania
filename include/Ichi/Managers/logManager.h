#ifndef LOGMANAGER_H
#define LOGMANAGER_H

namespace Ichi::Managers
{
    class LogManager
    {
    public:
        void init();
        void shutdown();

        LogManager() = default;
        ~LogManager() = default;
    };
} // namespace Ichi::Managers

#endif