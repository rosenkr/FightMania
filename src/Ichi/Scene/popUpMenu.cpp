#include "Ichi/Scene/popUpMenu.h"

namespace ichi::scene
{

    PopUpMenu::PopUpMenu(std::vector<uicomponents::UIComponent *> c, graphics::Sprite b, graphics::Sprite w) : uicomponents(std::move(c)), background(b), window(w)
    {
    }

    void PopUpMenu::update()
    {
        for (auto c : uicomponents)
            c->update();
    }
    void PopUpMenu::draw() const
    {
        background.draw();
        window.draw();
        for (auto c : uicomponents)
            c->draw();
    }

} // namespace ichi::scene
