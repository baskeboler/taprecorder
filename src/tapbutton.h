#ifndef TAPBUTTON_H
#define TAPBUTTON_H

#include "sceneelement.h"
#include "state.h"
#include "label.h"

class TapButton: public SceneElement, public std::enable_shared_from_this<TapButton>
{
public:
    TapButton(ScenePtr scene);
    void initState();
    virtual ~TapButton();
    // SceneElement interface
public:
    virtual void update();
    virtual void draw();

    bool hitTest(int x, int y) const;
    bool hitTest(const glm::vec2 &pos) const;

    ofColor buttonColor, primaryColor, activeColor, borderColor;
    float buttonRadius, buttonInitRadius;
    std::shared_ptr<Label> label;
//    ofTrueTypeFont font;
    std::shared_ptr<State<TapButton>> state;
 };

#endif // TAPBUTTON_H
