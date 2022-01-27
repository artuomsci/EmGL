#ifndef CTRANSFORM_H
#define CTRANSFORM_H

#include "basicdefs.h"

/**< Max number of transformation states to store */
#define MATRIXSTACKSIZE 100

namespace agl {

class CTransform {

    public:

        CTransform();
        ~CTransform();

        void Translate(double x_, double y_, double z_);
        void Translate(const aVec3& vec_);
        void Rotate(double ane_, double x_, double y_, double z_);
        void Rotate(const aQuat& orientation_);
        void SetNodeTransform(const aVec3 &pos_, const aVec3 &rot_, bool ismovable_);
        void SetNodeTransform(const aVec3 &pos_, const aQuat& quat_, bool ismovable_);
        void Scale(double x_, double y_, double z_);
        void LoadIdentity();
        void PushMatrix();
        void PopMatrix();
        int  GetMatInd() const;
        void LookAt(aVec3 eyePos_, aVec3 viewPoint_, aVec3 up_);
        void Perspective( double fov_, double WndRatio_, double nearplane_, double farplane_);
        void Ortho( double left_, double right_,
                    double bottom_, double top_,
                    double nearplane_, double farplane_);
        void IntoScreenCoord(const aVec3 &worldVec_, aVec2 &scrVec_);

        aMat4 &GetModelViewMat();
        aMat4 &GetProjectionMat();
        aMat4 &GetModNormalMat();

    private:

        int m_matIndex;
        /**< Major projection matrix */
        aMat4 m_ProjectionMat;
        /**< Local transformations matrix */
        aMat4 m_NodeMat;
        /**< Global transformations matrices stack */
        aMat4 m_ModelViewMat[MATRIXSTACKSIZE];
        /**< Temporary storages for return references */
        aMat4 m_ModelViewMatTemp, m_ModNormalMatTemp;
    };
}

#endif
