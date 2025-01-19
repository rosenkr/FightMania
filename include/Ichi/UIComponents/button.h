#ifndef BUTTON_H
#define BUTTON_H

#include "Ichi/Graphics/sprite.h"
#include "Ichi/UIComponents/uicomponent.h"

#include "SDL2/SDL_ttf.h"

namespace ichi::uicomponents
{

    class Button : public UIComponent
    {
    public:
        Button(datatypes::Hitbox hb, std::string btnLabel, TTF_Font *f, SDL_Color c, graphics::Sprite s, graphics::Sprite fs, std::function<void()> ptr);
        ~Button(){}

        void draw() const;
        void update();

    private:
        std::string t;
        TTF_Font* f;
        SDL_Color c;
        graphics::Sprite sprite;
        graphics::Sprite focusedSprite;
        std::function<void()> funcPtr;
    };

} // namespace ichi::uicomponents

#endif