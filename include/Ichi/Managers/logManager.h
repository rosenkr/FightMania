#ifndef LOGMANAGER_H
#define LOGMANAGER_H

namespace Ichi::Managers
{
    class logManager
    {
    public:
        void init();
        void shutdown();

        logManager() = default;
        ~logManager() = default;
    };
} // namespace Ichi::Managers

#endif