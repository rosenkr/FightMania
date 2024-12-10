#include "Ichi/UIComponents/textbox.h"
#include "Ichi/Core/engine.h"
#include "Ichi/Input/keyboard.h"
#include "Ichi/Input/mouse.h"
#include "Ichi/log.h"

using namespace ichi::input;

namespace ichi::uicomponents
{

    Textbox::Textbox(datatypes::Hitbox hb, TTF_Font *f, SDL_Color c, graphics::Sprite s, graphics::Sprite fs) : UIComponent(hb), font(f), color(c), sprite(s), focusedSprite(fs) {}

    void Textbox::draw() const
    {
        if (focused)
            focusedSprite.draw();
        else
            sprite.draw();

        if (texture != nullptr)
            SDL_RenderCopy(core::Engine::getInstance()->getRenderer(), texture, NULL, hitbox.getSDLRect());
    }

    void Textbox::update()
    {
        if (Mouse::DX() != 0 || Mouse::DY() != 0)
            focused = hitbox.pointIsInRect(datatypes::Point(Mouse::getX(), Mouse::getY()));

        if (!focused)
            return;

        bool wasChanged = false;

        if (Keyboard::keyIsPressed(Keyboard::Key::ICHIKEY_LEFT) && --cursor < 0)
            cursor = 0;

        if (Keyboard::keyIsPressed(Keyboard::Key::ICHIKEY_RIGHT) && ++cursor > (int)text.size())
            cursor = text.size();

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

            bool shiftState = Keyboard::keyIsDown(Keyboard::Key::ICHIKEY_LSHIFT) || Keyboard::keyIsDown(Keyboard::Key::ICHIKEY_RSHIFT);
            std::string keyString = Keyboard::stringRepresentation(key, shiftState);

            text.insert(text.begin() + cursor, keyString.begin(), keyString.end());

            cursor += keyString.size();
            wasChanged = true;
        }

        if (wasChanged)
        {
            if (texture)
                SDL_DestroyTexture(texture);

            if (text.size() == 0)
                return;

            SDL_Surface *surf = TTF_RenderText_Solid(font, text.c_str(), color);

            if (surf == nullptr)
            {
                ICHI_ERROR("Could not create surface for label: {}", SDL_GetError());
                return;
            }

            SDL_Texture *texture = SDL_CreateTextureFromSurface(core::Engine::getInstance()->getRenderer(), surf);
            SDL_FreeSurface(surf);

            if (texture == nullptr)
            {
                ICHI_ERROR("Could not create texture for label");
                return;
            }

            this->texture = texture;
        }
    }

} // namespace ichi::uicomponents
