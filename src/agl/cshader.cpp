#ifdef _WEB
#include <GLES3/gl3.h>
#endif

#include <stdlib.h>
#include <fstream>

#include <GL/glew.h>

#include "cbase.h"
#include "clogger.h"
#include "cshader.h"

using namespace agl;

//---------------------------------------------------------------
CShader::CShader() {

    m_uniformTypeConvertion["e1f"] = e1f;
    m_uniformTypeConvertion["e2f"] = e2f;
    m_uniformTypeConvertion["e3f"] = e3f;
    m_uniformTypeConvertion["e1i"] = e1i;
    m_uniformTypeConvertion["e2i"] = e2i;
    m_uniformTypeConvertion["e3i"] = e3i;
    m_uniformTypeConvertion["e4fv"] = e4fv;

    m_propNameConvertion["Kd"] = eDiffuse;
    m_propNameConvertion["Ka"] = eAmbient;
    m_propNameConvertion["Ks"] = eSpecular;

    m_propNameConvertion["Shininess"]       = eShininess;
    m_propNameConvertion["ProjectionMatr"]  = eProjectionMatr;
    m_propNameConvertion["ModelViewMatr"]   = eModelViewMatr;
    m_propNameConvertion["ModNormalMatr"]   = eModNormalMatr;

    loadLibrary();
    }

//---------------------------------------------------------------
CShader::~CShader() {

}

//---------------------------------------------------------------
bool CShader::loadShader(const std::string& shaderFile_, uint type_, uint &shaderID_) {

    SPtr<CLogger> ptrLog = CBase::GetBase()->GetLogger();

    std::string     ShaderCode = "";
    std::ifstream   ShaderStream(shaderFile_.c_str(), std::ios::in);
    if(ShaderStream.is_open()) {
        std::string Line = "";
        while(getline(ShaderStream, Line))
            ShaderCode += "\n" + Line;
        ShaderStream.close();
        }
    else
        ptrLog->Write("Failed to open " + shaderFile_);

    shaderID_ = glCreateShader(type_);
    if (!shaderID_) {
        ptrLog->Write("Could not create shader:");
        ptrLog->Write(shaderFile_);
        return false;
        }

    const char* source = ShaderCode.c_str();

    glShaderSource(shaderID_, 1, &source, NULL);
    glCompileShader(shaderID_);
    char msg[1024];
    glGetShaderInfoLog(shaderID_, sizeof msg, NULL, msg);

    if (std::string(msg) != "") {
        ptrLog->Write("Shader info: " + shaderFile_);
        if (type_ == GL_VERTEX_SHADER)
            ptrLog->Write("Vertex shader");
        if (type_ == GL_FRAGMENT_SHADER)
            ptrLog->Write("Fragment shader");
        ptrLog->Write(msg);
    }

    return true;
    }

//---------------------------------------------------------------
void CShader::loadLibrary() {

    TShaderName name;
    std::string frName;
    std::string vrName;
    std::vector<std::string> sprops;

    //----------------------------------------------

    name   = "textureOutput";
    frName = "./filesystem/shaders/fTextureOutput.glsl";
    vrName = "./filesystem/shaders/vTextureOutput.glsl";
    sprops.clear();
    sprops.push_back("ProjectionMatr");
    sprops.push_back("e4fv");

    buildShader(name, frName, vrName, sprops);

    //----------------------------------------------

    name   = "phongFlat";
    frName = "./filesystem/shaders/fPhongFlat.glsl";
    vrName = "./filesystem/shaders/vVertexFlat.glsl";
    sprops.clear();
    sprops.push_back("Kd");
    sprops.push_back("e3f");
    sprops.push_back("Ks");
    sprops.push_back("e3f");
    sprops.push_back("Ka");
    sprops.push_back("e3f");
    sprops.push_back("Shininess");
    sprops.push_back("e1f");
    sprops.push_back("ProjectionMatr");
    sprops.push_back("e4fv");
    sprops.push_back("ModelViewMatr");
    sprops.push_back("e4fv");
    sprops.push_back("ModNormalMatr");
    sprops.push_back("e4fv");

    buildShader(name, frName, vrName, sprops);

    //----------------------------------------------

    name   = "phong";
    frName = "./filesystem/shaders/fPhong.glsl";
    vrName = "./filesystem/shaders/vVertex.glsl";
    sprops.clear();
    sprops.push_back("Kd");
    sprops.push_back("e3f");
    sprops.push_back("Ks");
    sprops.push_back("e3f");
    sprops.push_back("Ka");
    sprops.push_back("e3f");
    sprops.push_back("Shininess");
    sprops.push_back("e1f");
    sprops.push_back("ProjectionMatr");
    sprops.push_back("e4fv");
    sprops.push_back("ModelViewMatr");
    sprops.push_back("e4fv");
    sprops.push_back("ModNormalMatr");
    sprops.push_back("e4fv");

    buildShader(name, frName, vrName, sprops);

    //----------------------------------------------

    name   = "wireframe";
    frName = "./filesystem/shaders/fWireframe.glsl";
    vrName = "./filesystem/shaders/vWireframe.glsl";
    sprops.clear();
    sprops.push_back("Kd");
    sprops.push_back("e3f");
    sprops.push_back("ProjectionMatr");
    sprops.push_back("e4fv");
    sprops.push_back("ModelViewMatr");
    sprops.push_back("e4fv");

    buildShader(name, frName, vrName, sprops);

    //----------------------------------------------

    name   = "diffuse";
    frName = "./filesystem/shaders/fDiffuse.glsl";
    vrName = "./filesystem/shaders/vVertex.glsl";
    sprops.clear();
    sprops.push_back("Kd");
    sprops.push_back("e3f");
    sprops.push_back("ProjectionMatr");
    sprops.push_back("e4fv");
    sprops.push_back("ModelViewMatr");
    sprops.push_back("e4fv");
    sprops.push_back("ModNormalMatr");
    sprops.push_back("e4fv");

    buildShader(name, frName, vrName, sprops);

    //----------------------------------------------

    name   = "primitive";
    frName = "./filesystem/shaders/fDiffuse.glsl";
    vrName = "./filesystem/shaders/vPrimitive.glsl";
    sprops.clear();
    sprops.push_back("Kd");
    sprops.push_back("e3f");
    sprops.push_back("ProjectionMatr");
    sprops.push_back("e4fv");
    sprops.push_back("ModelViewMatr");
    sprops.push_back("e4fv");

    buildShader(name, frName, vrName, sprops);

    //----------------------------------------------

    name   = "interface";
    frName = "./filesystem/shaders/fInterface.glsl";
    vrName = "./filesystem/shaders/vInterface.glsl";
    sprops.clear();
    sprops.push_back("ProjectionMatr");
    sprops.push_back("e4fv");

    buildShader(name, frName, vrName, sprops);
    }

//---------------------------------------------------------------
const TShaderMap& CShader::GetLibrary() const {
    return m_shaders;
}

//---------------------------------------------------------------
const TShaderPropsLocation &CShader::GetProperties(const TShaderName& name_) {

    auto it = m_shaders.find(name_);

    assert(it != m_shaders.end());

    return m_shadersData[it->second];
}

//---------------------------------------------------------------
const TShaderPropsLocation& CShader::GetProperties(TShaderProgram program_) {
    return m_shadersData[program_];
}

//---------------------------------------------------------------
TShaderProgram CShader::GetProgram(const TShaderName& name_) {
    assert(m_shaders.count(name_));
    return m_shaders[name_];
}

//---------------------------------------------------------------
void CShader::buildShader(  const TShaderName& name_,
                            const std::string& fragmentFileName_,
                            const std::string& vertexFileName_,
                            const std::vector<std::string>& properties_) {

    GLuint vertexShader, fragmentShader;
    SPtr<CLogger> ptrLog = CBase::GetBase()->GetLogger();
    if (!loadShader(vertexFileName_, GL_VERTEX_SHADER, vertexShader)) {
        ptrLog->Write("Failed to load vertex shader");
        return;
        }

    if (!loadShader(fragmentFileName_, GL_FRAGMENT_SHADER, fragmentShader)) {
        ptrLog->Write("Failed to load fragment shader");
        return;
        }

    TShaderProgram crtShader = glCreateProgram();
    if(!crtShader) {
        ptrLog->Write("Couldn't create shader program");
        return;
        }

    glAttachShader(crtShader, vertexShader);
    glAttachShader(crtShader, fragmentShader);

    glBindAttribLocation(crtShader, eVertCoord,      "VertexPosition"   );
    glBindAttribLocation(crtShader, eVertNorm,       "VertexNorm"       );
    glBindAttribLocation(crtShader, eVertTexCoord,   "VertTexCoord"     );
    glBindAttribLocation(crtShader, eVertBaryCoord,  "VertBaryCoord"    );
    glBindAttribLocation(crtShader, eVertColor,      "VertColor"        );

    glLinkProgram(crtShader);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    GLint linked;
    glGetProgramiv(crtShader, GL_LINK_STATUS, &linked);

    if(!linked) {
        ptrLog->Write("Couldn't link shader program ");
        GLint logLen;
        glGetProgramiv(crtShader, GL_INFO_LOG_LENGTH, &logLen);

        if( logLen > 0 ) {
            char * programlog = (char *)malloc(logLen);
            GLsizei written;
            glGetProgramInfoLog(crtShader, logLen, &written, programlog);
            ptrLog->Write(programlog);
            free(programlog);
            }
        return;
        }

    TShaderPropsLocation props;
    for (int i = 0; i < properties_.size(); i += 2) {

        TShaderPropName     propName    = properties_[i + 0];
        eUNIFORM_TYPE       type        = m_uniformTypeConvertion[properties_[i + 1]];

        SUniformsLocation unifData;
        unifData.type       = type;
        unifData.location   = glGetUniformLocation(crtShader, propName.c_str());

        TShaderPropId id = m_propNameConvertion[propName];

        props[id] = unifData;
    }

    m_shaders[name_] = crtShader;
    m_shadersData[crtShader] = props;

    }
