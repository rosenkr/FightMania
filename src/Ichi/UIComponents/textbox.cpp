#include "Ichi/UIComponents/textbox.h"
#include "Ichi/Core/engine.h"
#include "Ichi/Input/keyboard.h"
#include "Ichi/Input/mouse.h"
#include "Ichi/log.h"
#include "Ichi/Graphics/textureManager.h"

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

        auto texture = graphics::TextureManager::getTextTextureFor(text,font,color);
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

        if ((wasFocused && !focused) || (!wasFocused && focused)) // updates texture on mouse enter and when mouse leaves
            updateTextTexture();

        wasFocused = focused;

        if (!focused)
            return;

        bool wasChanged = false;

        if (Keyboard::keyIsPressed(Keyboard::Key::ICHIKEY_LEFT))
        {
            cursor--;
            wasChanged = true;
        }

        if (Keyboard::keyIsPressed(Keyboard::Key::ICHIKEY_RIGHT))
        {
            cursor++;
            wasChanged = true;
        }

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
        ichi::graphics::TextureManager::dropTextTextureFor(text);
        text = "";
        cursor = 0;
        updateTextTexture();
    }

    bool Textbox::canMoveCursorLeft() { return cursor != 0; } // the only cursor position a cursor cant move left is if the cursor is on the first pos

    bool Textbox::canMoveCursorRight() { return cursor != (int)text.size(); } // the only cursor position a cursor cant move right is if the cursor is on the last pos

    void Textbox::updateTextTexture()
    {
        if (text.empty())
            return;
        std::string temp = text;
        if (focused)
            temp.insert(temp.begin() + cursor, '|');

        ichi::graphics::TextureManager::addTextTextureFor(text, font, color);

    }

} // namespace ichi::uicomponents
