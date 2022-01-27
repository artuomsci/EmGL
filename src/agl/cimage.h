#ifndef CIMAGE_H
#define CIMAGE_H

#include <vector>
#include <string>

#include <GL/glew.h>

#ifdef _WEB
#include <GLES3/gl3.h>
#endif

namespace agl{

class CBase;

class CImage{
    public:
    GLuint  m_imgRef;

    CImage();
    void MakeTexture(const std::string &filename_, const GLint &filter_type_);

    private:
    unsigned m_width, m_height;
    std::vector<unsigned char> m_imgDat;
};

};

#endif
