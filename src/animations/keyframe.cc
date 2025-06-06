#include "keyframe.hpp"

namespace y11::animations {

Keyframe::Keyframe(unsigned short duration, float strength, Color target, float mulX, float mulY){
    this->duration = duration;
    this->strength = strength;
    this->target = target;
    this->mulX = mulX;
    this->mulY = mulY;
}

Keyframe::~Keyframe(){}

}
