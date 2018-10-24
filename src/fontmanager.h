#ifndef FONTMANAGER_H
#define FONTMANAGER_H
#include <memory>
#include "ofMain.h"
#include <map>
class FontManager
{
public:
    static std::shared_ptr<FontManager> get_instance();

    std::shared_ptr<ofTrueTypeFont> getFont(std::string name, int size);

private:
    std::map<std::string, std::shared_ptr<ofTrueTypeFont>> fonts;
    static std::shared_ptr<FontManager> instance;
    FontManager() = default;
};



#endif // FONTMANAGER_H
