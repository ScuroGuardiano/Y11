#include "animation.hpp"
#include "src/animations/keyframe.hpp"
#include "src/widgets/widget.hpp"
#include <memory>

namespace y11::animations {

Animation::Animation(){}
Animation::~Animation(){}

std::shared_ptr<Keyframe> Animation::addKeyframe(std::shared_ptr<Keyframe> keyframe){
    this->keyframes.push_back(keyframe);
    return keyframe;
}

Animation* Animation::advance(){
    if ( this->timer >= this->keyframes[this->index]->duration ) { this->index += 1; this->timer = 0; }
    if ( this->index >= this->keyframes.size() ) { this->index = 0; }
    this->timer += 1;

    return this;
}

Animation* Animation::evaluate(std::shared_ptr<widgets::Widget> widget){
    Color color = widget->getColor();
    color.r = (unsigned char)(
        (
            (float)color.r +
            (float)this->keyframes[this->index]->target.r * this->keyframes[this->index]->strength
        )
        / (1.0 + this->keyframes[this->index]->strength)
    );
    color.g = (unsigned char)(
        (
            (float)color.g +
            (float)this->keyframes[this->index]->target.g * this->keyframes[this->index]->strength
        )
        / (1.0 + this->keyframes[this->index]->strength)
    );
    color.b = (unsigned char)(
        (
            (float)color.b +
            (float)this->keyframes[this->index]->target.b * this->keyframes[this->index]->strength
        )
        / (1.0 + this->keyframes[this->index]->strength)
    );
    color.a = (unsigned char)(
        (
            (float)color.a +
            (float)this->keyframes[this->index]->target.a * this->keyframes[this->index]->strength
        )
        / (1.0 + this->keyframes[this->index]->strength)
    );
    widget->setColor(color);

    return this;
}


}
