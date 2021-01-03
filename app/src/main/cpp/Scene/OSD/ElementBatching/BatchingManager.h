//
// Created by Constantin on 8/23/2018.
//

#ifndef FPV_VR_DYNAMICBACKGROUNDMANAGER_H
#define FPV_VR_DYNAMICBACKGROUNDMANAGER_H


#include <General/IUpdateable.hpp>
#include <General/IDrawable.hpp>
#include <GLES2/gl2.h>
#include <array>
#include <BasicGLPrograms.hpp>
#include "GLHelper.hpp"

#include "CpuGpuBuff.h"

/**
 * Batching many elements of the same kind into one draw call gives a big performance improvement
 * To use the batching manager, use "allocateXXX" to get a buffer and use modify() to write into this buffer
 * Each time per frame, the batching manager checks if these buffer(s) have been modified and uploads the new content to the GPU if needed
 */
class BatchingManager : public IUpdateable, public IDrawable {
public:
    explicit BatchingManager(const BasicGLPrograms& basicGLPrograms);
    ModifiableArray<ColoredVertex>* allocateVCTriangles(int nVertices);
    ModifiableArray<ColoredVertex>* allocateVCLines(int nVertices);
    ModifiableArray<GLProgramText::Character>* allocateText(int nRectangles);
    void initGL();
    void updateGL()override;
    void drawGL(const glm::mat4& ViewM,const glm::mat4& ProjM)override;
    void setTextColor(TrueColor textOutlineColor,float textOutlineStrength);
private:
    const BasicGLPrograms& mBasicGLPrograms;
    TrueColor mTextOutlineColor;
    float mTextOutlineStrength;
    CpuGpuBuff<ColoredVertex> mTriangleBuffer;
    CpuGpuBuff<ColoredVertex> mOutlineB;
    CpuGpuBuff<GLProgramText::Character> mTextB;
};


#endif //FPV_VR_DYNAMICBACKGROUNDMANAGER_H
