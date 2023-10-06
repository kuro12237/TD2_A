#pragma once
#include"MatrixTransform.h"

class IMapWall
{
public:

    virtual Vector3 GetWorldPosition() = 0;


    virtual void OnLeftWall() = 0;
    virtual void OnRightWall() = 0;

    virtual void OnTopWall() = 0;
    virtual void OnBottomWall() = 0;


    float GetSize() { return size_; }
    Vector3 GetVelocity() { return Velocity_; }

    void SetVelosity(Vector3 v) { Velocity_ = v; }
    void SetSize(float size) { size_ = size; }


private:

    float size_ = 0.5f;
    Vector3 Velocity_ = {};
};

