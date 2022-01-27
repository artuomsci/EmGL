#ifndef CLOGGER_H
#define CLOGGER_H

#include <string>

namespace agl {

class CLogger {
    public:

        CLogger();
        ~CLogger();

        void Write(const std::string &message_);
        const std::string &GetLog(void) const;

    private:
        bool instantOutput;
        std::string m_log;
    };
};

#endif
