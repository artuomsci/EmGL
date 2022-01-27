#ifndef JSUTILS_H
#define JSUTILS_H

#include <string>

//================================================
// These functions are for calling external
// javascript
//================================================

namespace tinyxml2 { class XMLDocument; }

namespace jsutils {

        class CJutils {

        public:

        static void CallJava(const std::string &funcName_);
        static void CallJava1f(const std::string &funcName_, float val0_);
        static void CallJava2f(const std::string &funcName_, float val0_, float val1_);
        static void CallJava3f(const std::string &funcName_, float val0_, float val1_, float val2_);

        static void SaveData(const char* pData_, const std::string& fileName_);
        static void SaveXml(const tinyxml2::XMLDocument* pXml_, const std::string& fileName_);
        };
}

#endif
