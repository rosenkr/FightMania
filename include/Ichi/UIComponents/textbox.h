#ifndef TEXTBOX_H
#define TEXTBOX_H

#include "Ichi/UIComponents/uicomponent.h"
#include "Ichi/Graphics/sprite.h"

#include "SDL2/SDL_ttf.h"

#include <string>

namespace ichi::uicomponents
{

    class Textbox : public UIComponent
    {
    public:
        /* data */
        Textbox(datatypes::Hitbox, TTF_Font *, SDL_Color, graphics::Sprite, graphics::Sprite);

        void draw() const;
        void update();
        std::string getText() { return text; }

        ~Textbox() = default;

    private:
        std::string text = "";
        TTF_Font *font;
        SDL_Color color;
        graphics::Sprite sprite;
        graphics::Sprite focusedSprite;

        int cursor = 0;

        SDL_Texture *texture = nullptr;
    };

} // namespace ichi::uicomponents

#endif