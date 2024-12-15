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
        Textbox(datatypes::Hitbox, TTF_Font *, SDL_Color, graphics::Sprite, graphics::Sprite, int = -1);

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

        int maxLetterCap;
        int cursor = 0;

        SDL_Texture *texture = nullptr;

        void updateTextTexture();
    };

} // namespace ichi::uicomponents

#endif