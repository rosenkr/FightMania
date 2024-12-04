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
        /* data */
        Button(datatypes::Hitbox hb, std::string path, TTF_Font *f, SDL_Color c, graphics::Sprite s, graphics::Sprite fs, void (*ptr)());
        ~Button() { SDL_DestroyTexture(text); }

        void draw() const;
        void update();

    private:
        SDL_Texture *text;
        graphics::Sprite sprite;
        graphics::Sprite focusedSprite;
        void (*funcPtr)();
    };

} // namespace ichi::uicomponents

#endif