#ifndef POP_UP_MENU_H
#define POP_UP_MENU_H

#include "Ichi/UIComponents/uicomponent.h"
#include "Ichi/Graphics/sprite.h"

#include <memory>
#include <vector>

namespace ichi::scene
{
    class PopUpMenu
    {
    public:
        PopUpMenu(std::vector<std::shared_ptr<uicomponents::UIComponent>>, graphics::Sprite, graphics::Sprite);

        void update();
        void draw() const;

    private:
        std::vector<std::shared_ptr<uicomponents::UIComponent>> uicomponents;
        graphics::Sprite background;
        graphics::Sprite window;
    };
} // namespace ichi::scene

#endif