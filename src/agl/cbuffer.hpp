#ifndef CBUFFER_H
#define CBUFFER_H

#include <vector>

#include <GL/glew.h>

#ifdef _WEB
#include <GLES3/gl3.h>
#endif

namespace agl {

enum eBufferType { eStatic, eDynamic };

//---------------------------------------------------------------
template <class T>
class CBuffer {

    public:

        CBuffer();
        ~CBuffer();

        bool            PushData(GLenum target_, eBufferType type_ = eStatic);
        void            AddElement(const T& data_);
        void            SetData(const std::vector<T>& data_);
        void            ResizeBuffer(const int size_);
        std::vector<T>& GetDataRef();
        void            SetElement(uint ind_, const T& data_);
        bool            GetElement(uint ind_, T& data_) const;
        const T*        GetElementPtr(uint ind_) const;
        eBufferType     GetBufferType() const;
        void            SetBufferType(eBufferType type_);
        GLenum          GetTarget() const;
        GLuint          GetId() const;
        uint            GetNumElements() const;
        void            Clear();

    private:

        std::vector<T>  m_data;
        GLuint          m_id;
        GLenum          m_target;
        eBufferType     m_bufferType;
    };

//---------------------------------------------------------------
template <class T>
CBuffer<T>::CBuffer() :
    m_id    (0)
  , m_target(0) {
    }

//---------------------------------------------------------------
template <class T>
CBuffer<T>::~CBuffer() {
    glDeleteBuffers(1, &m_id);
    }

//---------------------------------------------------------------
template <class T>
void CBuffer<T>::AddElement(const T& data_) {
    m_data.push_back(data_);
    }

//---------------------------------------------------------------
template <class T>
void CBuffer<T>::SetData(const std::vector<T>& data_) {
    m_data.clear();
    m_data = data_;
    }

//---------------------------------------------------------------
template <class T>
void CBuffer<T>::ResizeBuffer(const int size_) {
    m_data.resize(size_);
    }

//---------------------------------------------------------------
template <class T>
uint CBuffer<T>::GetNumElements() const {
    return m_data.size();
    }

//---------------------------------------------------------------
template <class T>
bool CBuffer<T>::PushData(GLenum target_, eBufferType type_) {
    m_bufferType = type_;
    m_target = target_;

    if (m_id == 0)
        glGenBuffers(1, &m_id);

    if (m_id == GL_INVALID_VALUE)
        return false;

    glBindBuffer(m_target, m_id);
    switch (type_) {
        case eStatic: {
            glBufferData(m_target, sizeof(T) * m_data.size(), &m_data[0], GL_STATIC_DRAW);
    }
        break;
        case eDynamic: {
            glBufferData(m_target, sizeof(T) * m_data.size(), &m_data[0], GL_DYNAMIC_DRAW);
    }
    break;
    }

    glBindBuffer(m_target, 0);

    return (m_data.size() == 0) ? false : true;
    }

//---------------------------------------------------------------
template <class T>
std::vector<T> &CBuffer<T>::GetDataRef() {
    return m_data;
    }

//---------------------------------------------------------------
template <class T>
void CBuffer<T>::SetElement(uint ind_, const T& data_) {
    if (ind_ >= 0 && ind_ < m_data.size()) {
        if (m_data[ind_] != data_) {
            m_data[ind_] = data_;
            PushData(m_target, m_bufferType);
            }
        }
    }

//---------------------------------------------------------------
template <class T>
bool CBuffer<T>::GetElement(uint ind_, T& data_) const {
    if (ind_ >= 0 && ind_ < m_data.size()) {
        data_ = m_data[ind_];
        return true;
        }
    else
        return false;
    }

//---------------------------------------------------------------
template <class T>
const T *CBuffer<T>::GetElementPtr(uint ind_) const {
    if (ind_ >= 0 && ind_ < m_data.size())
        return &m_data[ind_];
    else
        return 0;
    }

//---------------------------------------------------------------
template <class T>
eBufferType CBuffer<T>::GetBufferType() const {
    return m_bufferType;
    }

//---------------------------------------------------------------
template <class T>
void CBuffer<T>::SetBufferType(eBufferType type_) {
    m_bufferType = type_;
    PushData(m_target, type_);
    }

//---------------------------------------------------------------
template <class T>
GLenum CBuffer<T>::GetTarget() const {
    return m_target;
    }

//---------------------------------------------------------------
template <class T>
GLuint CBuffer<T>::GetId() const {
    return m_id;
    }

//---------------------------------------------------------------
template <class T>
void CBuffer<T>::Clear() {
    m_data.clear();
    }
}

#endif
