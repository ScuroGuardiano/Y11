#include "keyframe.hpp"

namespace y11::animations {

Keyframe::Keyframe(unsigned short duration, float strength, Color target){
    this->duration = duration;
    this->strength = strength;
    this->target = target;
}

Keyframe::~Keyframe(){}

}
