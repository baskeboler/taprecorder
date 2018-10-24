#include "tapdisplay.h"


glm::vec2 TapDisplay::getSize() const
{
    return size;
}

void TapDisplay::setSize(const glm::vec2 &value)
{
    size = value;
}

glm::vec2 TapDisplay::getPosition() const
{
    return position;
}

void TapDisplay::setPosition(const glm::vec2 &value)
{
    position = value;
}
