#include "fontmanager.h"


std::shared_ptr<FontManager> FontManager::instance;
std::shared_ptr<FontManager> FontManager::get_instance()
{
    if (!instance) {
        instance.reset(new FontManager);
    }
    return instance;
}

std::shared_ptr<ofTrueTypeFont> FontManager::getFont(string name, int size) {
    std::stringstream ss;
    ss << name << " " << size;
    if (!fonts[ss.str()]) {
        auto f = std::make_shared<ofTrueTypeFont>();
        f->load(name + ".ttf", size);
        fonts[ss.str()] = f;
        return f;
    }
    return fonts[ss.str()];
}
