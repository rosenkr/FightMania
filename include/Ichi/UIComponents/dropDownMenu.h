#ifndef DROP_DOWN_MENU_H
#define DROP_DOWN_MENU_H

#include "Ichi/UIComponents/uicomponent.h"
#include "Ichi/Graphics/sprite.h"

#include "SDL2/SDL_ttf.h"

#include <string>
#include <map>

namespace ichi::uicomponents
{
    class DropDownMenu : public UIComponent
    {

    public:
        DropDownMenu(datatypes::Hitbox, std::vector<std::string>, TTF_Font *, SDL_Color, graphics::Sprite, graphics::Sprite, graphics::Sprite);

        void update();
        void draw() const;

        std::string getSelected() const { return selected; }
        void updateItems(std::vector<std::string> items);

    private:
        const std::string NONE_SELECTED = "NONE SELECTED";
        std::string selected = NONE_SELECTED;
        bool isExpanded = false;

        std::vector<std::string> items;
        TTF_Font *font;
        SDL_Color textColor;
        graphics::Sprite menu;
        graphics::Sprite focusedMenu;
        graphics::Sprite itemSprite;
    };
} // namespace ichi::uicomponents

#endif