#include "lodepng.h"

#include "cimage.h"
#include "cbase.h"
#include "clogger.h"

using namespace agl;

//---------------------------------------------------------------
CImage::CImage() :
        m_imgRef    (0)
      , m_width     (0)
      , m_height    (0) {
    }

//---------------------------------------------------------------
void CImage::MakeTexture(const std::string &filename_, const GLint &filter_type_) {
    std::string newfilename;
    newfilename.append("files/textures/");
    newfilename += filename_;
    unsigned error = lodepng::decode(m_imgDat, m_width, m_height, newfilename.c_str());

    if(error) {
        SPtr<CLogger> ptrLog = CBase::GetBase()->GetLogger();
        ptrLog->Write("Error loading texture");
        ptrLog->Write(lodepng_error_text(error));
        }

    glGenTextures(1, &m_imgRef);
    glBindTexture(GL_TEXTURE_2D, m_imgRef);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter_type_);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter_type_);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &m_imgDat[0]);
    }
