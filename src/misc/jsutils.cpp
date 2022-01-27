#include <stdio.h>

#include "tinyxml2.h"

#ifdef _WEB

#include <emscripten/emscripten.h>

#include "jsutils.h"

using namespace jsutils;
using namespace tinyxml2;

void CJutils::CallJava(const std::string &funcName_) {
    emscripten_run_script(funcName_.c_str());
}

void CJutils::CallJava1f(const std::string &funcName_, float val0_) {
    std::string funcName = funcName_ + "(%.4f)";
    char buffer[100];
    sprintf(buffer, funcName.c_str(), val0_);
    emscripten_run_script(buffer);
    }

void CJutils::CallJava2f(const std::string &funcName_, float val0_, float val1_) {
    std::string funcName = funcName_ + "(%%.4f, %%.4f)";
    char buffer[100];
    sprintf(buffer, funcName.c_str(), val0_, val1_);
    emscripten_run_script(buffer);
    }

void CJutils::CallJava3f(const std::string &funcName_, float val0_, float val1_, float val2_) {
    std::string funcName = funcName_ + "(%%.4f, %%.4f, %%.4f)";
    char buffer[100];
    sprintf(buffer, funcName.c_str(), val0_, val1_, val2_);
    emscripten_run_script(buffer);
    }

void CJutils::SaveData(const char* pData_, const std::string& fileName_) {

    if (pData_) {

        EM_ASM_({
          var blob = new Blob([Pointer_stringify($0)], { type: "" });
          saveAs(blob, Pointer_stringify($1));
        }, pData_, fileName_.c_str() );
    }

    }

void CJutils::SaveXml(const tinyxml2::XMLDocument* pXml_, const std::string& fileName_) {
    if (!pXml_) return;
    auto pPrinter(new XMLPrinter);
    if (pPrinter) {
        pXml_->Print(pPrinter);
        SaveData(pPrinter->CStr(), fileName_);
        delete pPrinter;
    }
}

#endif
