#pragma once
#include "GameObject.h"

class UpdatableObject : virtual public GameObject {
public:
    virtual void update() = 0;
};