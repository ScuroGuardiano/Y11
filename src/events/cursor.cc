#include "cursor.hpp"
#include "src/events/event.hpp"

namespace y11 {

Cursor::Cursor(){}
Cursor::~Cursor(){}

void Cursor::evaluate(const std::unique_ptr<y11::Backend>& backend) {
    backend->renderRaw(posX, posY, 4);
    if (backend->getKeyState(y11::Key::Up)) {this->posY-=4;}
    if (backend->getKeyState(y11::Key::Down)) {this->posY+=4;}
    if (backend->getKeyState(y11::Key::Left)) {this->posX-=4;}
    if (backend->getKeyState(y11::Key::Right)) {this->posX+=4;}
}

short Cursor::getPosX(){ return this->posX; }
short Cursor::getPosY(){ return this->posY; }


}
