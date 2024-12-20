#include "Ichi/UIComponents/textbox.h"
#include "Ichi/Core/engine.h"
#include "Ichi/Input/keyboard.h"
#include "Ichi/Input/mouse.h"
#include "Ichi/log.h"

using namespace ichi::input;

namespace ichi::uicomponents
{

    Textbox::Textbox(datatypes::Hitbox hb, TTF_Font *f, SDL_Color c, graphics::Sprite s, graphics::Sprite fs, int cap) : UIComponent(hb), font(f), color(c), sprite(s), focusedSprite(fs), maxLetterCap(cap) {}

    void Textbox::draw() const
    {
        if (focused)
            focusedSprite.draw();
        else
            sprite.draw();

        if (texture == nullptr)
            return;

        int textWidth, textHeight;
        SDL_QueryTexture(texture, nullptr, nullptr, &textWidth, &textHeight);

        auto rect = SDL_Rect{hitbox.getX(), hitbox.getY(), textWidth, textHeight};

        if (texture != nullptr)
            SDL_RenderCopy(core::Engine::getInstance()->getRenderer(), texture, NULL, &rect);
    }

    void Textbox::update()
    {
        if (Mouse::DX() != 0 || Mouse::DY() != 0)
            focused = hitbox.pointIsInRect(datatypes::Point(Mouse::getX(), Mouse::getY()));

        if (!focused)
            return;

        bool wasChanged = false;

        if (Keyboard::keyIsPressed(Keyboard::Key::ICHIKEY_LEFT))
            cursor--;

        if (Keyboard::keyIsPressed(Keyboard::Key::ICHIKEY_RIGHT))
            cursor++;

        if (cursor > (int)text.size())
            cursor = text.size();

        if (cursor < 0)
            cursor = 0;

        for (int i = static_cast<int>(Keyboard::Key::ICHIKEY_FIRST); i <= static_cast<int>(Keyboard::Key::LAST_INPUT_KEY); i++)
        {
            Keyboard::Key key = static_cast<Keyboard::Key>(i);

            if (!Keyboard::keyIsPressed(key))
                continue;

            if (key == Keyboard::Key::ICHIKEY_BACKSPACE && cursor != 0)
            {
                text.erase(text.begin() + cursor - 1);
                cursor--;
                wasChanged = true;
                continue;
            }

            if (maxLetterCap != -1 && cursor >= maxLetterCap)
                continue;

            bool shiftState = Keyboard::keyIsDown(Keyboard::Key::ICHIKEY_LSHIFT) || Keyboard::keyIsDown(Keyboard::Key::ICHIKEY_RSHIFT);
            std::string keyString = Keyboard::stringRepresentation(key, shiftState);

            text.insert(text.begin() + cursor, keyString.begin(), keyString.end());

            cursor += keyString.size();
            wasChanged = true;
        }

        if (wasChanged)
            updateTextTexture();
    }

    void Textbox::clear()
    {
        text = "";
        updateTextTexture();
    }

    void Textbox::updateTextTexture()
    {
        if (texture)
        {
            SDL_DestroyTexture(texture);
            texture = nullptr;
        }

        if (text.size() == 0)
            return;

        SDL_Surface *surf = TTF_RenderText_Blended(font, text.c_str(), color);

        if (surf == nullptr)
        {
            ICHI_ERROR("Could not create surface for label: {}", SDL_GetError());
            return;
        }

        texture = SDL_CreateTextureFromSurface(core::Engine::getInstance()->getRenderer(), surf);

        SDL_FreeSurface(surf);

        if (texture == nullptr)
        {
            ICHI_ERROR("Could not create texture for label");
            return;
        }
    }

} // namespace ichi::uicomponents
