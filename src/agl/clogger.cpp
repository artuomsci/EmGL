#include "clogger.h"
#include <iostream>

using namespace agl;

//---------------------------------------------------------------
CLogger::CLogger() :
        instantOutput   (true) {
    }

//---------------------------------------------------------------
CLogger::~CLogger() {
    }

//---------------------------------------------------------------
void CLogger::Write(const std::string &message_) {
    if (instantOutput) {
        std::cout<<message_<<std::endl;
    }

    m_log += message_;
    m_log += "\n";
    }

//---------------------------------------------------------------
const std::string &CLogger::GetLog(void) const {
    return m_log;
    }
