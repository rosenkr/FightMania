#ifndef POP_UP_MENU_H
#define POP_UP_MENU_H

#include "Ichi/UIComponents/uicomponent.h"
#include "Ichi/Graphics/sprite.h"

#include <vector>

namespace ichi::scene
{
    class PopUpMenu
    {
    public:
        PopUpMenu(std::vector<uicomponents::UIComponent *>, graphics::Sprite, graphics::Sprite);

        void update();
        void draw() const;

        ~PopUpMenu()
        {
            for (auto p : uicomponents)
                delete p;
            uicomponents.clear();
        };

    private:
        std::vector<uicomponents::UIComponent *> uicomponents;
        graphics::Sprite background;
        graphics::Sprite window;
    };
} // namespace ichi::scene

#endif