#ifndef CSHADER_H
#define CSHADER_H

#include <string>
#include <vector>
#include <unordered_map>

#include "basicdefs.h"

namespace agl {

enum eVERTATTRIB { eVertCoord, eVertNorm, eVertTexCoord, eVertBaryCoord, eVertColor };

enum eUNIFORM_TYPE { e1f, e2f, e3f, e1i, e2i, e3i, e4fv };

enum eUNIFORM_PARAMETER {
    eSpecular,
    eDiffuse,
    eAmbient,
    eShininess,
    eProjectionMatr,
    eModelViewMatr,
    eModNormalMatr
};

typedef std::string  TShaderName;
typedef std::string  TShaderPropName;
typedef uint         TShaderPropId;
typedef uint         TShaderProgram;
typedef uint         TUniformLocation;

struct SUniformsLocation {
    eUNIFORM_TYPE       type;
    TUniformLocation    location;

    SUniformsLocation() : location(0) {}
    };

struct SUniformsData {
    int    i1;
    float  f1;
    double d1;
    aVec4  v4;
    aVec3  v3;
    aVec2  v2;
    aMat4  mat4;
    aMat3  mat3;
    };

typedef std::unordered_map<TShaderPropId,   SUniformsData>          TShaderPropsData;
typedef std::unordered_map<TShaderPropId,   SUniformsLocation>      TShaderPropsLocation;
typedef std::unordered_map<TShaderProgram,  TShaderPropsLocation>   TShaderDataMap;
typedef std::unordered_map<TShaderName,     TShaderProgram>         TShaderMap;

class CShader {

    public:

                CShader();
                ~CShader();
        const   TShaderPropsLocation& GetProperties(const TShaderName& name_);
        const   TShaderPropsLocation& GetProperties(TShaderProgram program_);
        TShaderProgram GetProgram(const TShaderName& name_);

        const TShaderMap& GetLibrary() const;

    private:

        void    loadLibrary();
        bool    loadShader(const std::string& shaderFile_, uint type_, uint& shaderID_);
        void    buildShader(const TShaderName& name_,
                            const std::string& fragmentFileName_,
                            const std::string& vertexFileName_,
                            const std::vector<std::string>& properties_);

        std::unordered_map<std::string, eUNIFORM_TYPE>      m_uniformTypeConvertion;
        std::unordered_map<TShaderPropName, TShaderPropId>  m_propNameConvertion;

        TShaderMap      m_shaders;
        TShaderDataMap  m_shadersData;
    };
}

#endif
