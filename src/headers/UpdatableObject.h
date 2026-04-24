#pragma once
#include "GameObject.h"


/**
* @brief Klasa abstrakcyjna definiująca metodę do aktualizacji obiektu
**/
class UpdatableObject : virtual public GameObject {
public:
    /**
    * @brief Metoda do aktualizacji obiektu
    **/
    virtual void update() = 0;
};