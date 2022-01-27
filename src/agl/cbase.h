#ifndef CBase_H
#define CBase_H

#include <memory>

#include "basicdefs.h"
#include "classutils.h"
#include "cobserver.hpp"

namespace agl {

class CWndManager;
class CRenderer;
class CLogger;
class CShader;
class CCamera;
class CTransform;

class CBase {

    public:

        enum eBASEEVENT {
            eGeometryPass,
            eStartGuiPass,
            eGuiPass,
            eResolutionChange
        };

        CBase();
        ~CBase();

        void Init();
        void Update();

        static  SPtr<CBase>                     GetBase();
                SPtr<CWndManager>               GetWndManager();
                SPtr<CCamera>                   GetCamera();
                SPtr<CRenderer>                 GetRenderer();
                SPtr<CShader>                   GetShader();
                SPtr<CLogger>                   GetLogger();
                SPtr<CTransform>                GetTransform();
                SPtr<bu::CObserver<eBASEEVENT>>  GetObserver();

    private:

        NO_COPY_CLASS(CBase)

        bool readConfigure();

    private:

        static  SPtr<CBase>                 m_ptrBase;
                SPtr<CWndManager>           m_ptrWndManager;
                SPtr<CCamera>               m_ptrCamera;
                SPtr<CRenderer>             m_ptrRenderer;
                SPtr<CShader>               m_ptrShader;
                SPtr<CTransform>            m_ptrTransforms;
                SPtr<CLogger>               m_ptrLogger;

                SPtr<bu::CObserver<eBASEEVENT>>  m_ptrObserver;
    };
}

#endif
