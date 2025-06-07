#pragma once

#include "src/animations/keyframe.hpp"
#include "src/widgets/widget.hpp"
#include <memory>
#include <vector>
namespace y11::animations {

class Animation{
public:
    Animation();
    ~Animation();
    std::shared_ptr<Keyframe> addKeyframe(std::shared_ptr<Keyframe>);
    Animation* evaluate(std::shared_ptr<y11::widgets::Widget>);
    Animation* advance();

private:
    std::vector<std::shared_ptr<Keyframe>> keyframes;
    unsigned short index{};
    unsigned short timer{};
};

}
