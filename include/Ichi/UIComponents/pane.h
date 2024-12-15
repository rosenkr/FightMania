#ifndef PANE_H
#define PANE_H

#include "Ichi/UIComponents/uicomponent.h"

#include <map>
#include <memory>

namespace ichi::uicomponents
{

    class Pane : public UIComponent
    {
    public:
        Pane(datatypes::Hitbox hb, std::vector<std::shared_ptr<UIComponent>> uic) : UIComponent(hb)
        {
            for (auto c : uic)
                uiComponents[c.get()->getHitbox().getPos()] = c;
        }
        void update();
        void draw() const;
        const std::map<datatypes::Point, std::shared_ptr<UIComponent>> &getUIComponents() const { return uiComponents; }

    private:
        datatypes::Point findClosestPoint(int deltaX, int deltaY);

        std::map<datatypes::Point, std::shared_ptr<UIComponent>> uiComponents;
        datatypes::Point focused{-1, -1};
        datatypes::Point lastFocused{-1, -1};
    };

} // namespace ichi::uicomponents

#endif