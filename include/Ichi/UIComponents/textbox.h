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
        Textbox(datatypes::Hitbox, TTF_Font *, SDL_Color, graphics::Sprite, graphics::Sprite, int = -1);

        void draw() const;
        void update();
        std::string getText() const { return text; }
        void setText(const std::string &newText)
        {
            text = newText;
            cursor = text.size();
            updateTextTexture();
        }
        void clear();

        bool canMoveCursorLeft();
        bool canMoveCursorRight();

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

        bool wasFocused = false;
    };

} // namespace ichi::uicomponents

#endif