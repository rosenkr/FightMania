#include "Ichi/UIComponents/button.h"
#include "Ichi/Core/engine.h"
#include "Ichi/log.h"
#include "Ichi/Input/keyboard.h"
#include "Ichi/Input/mouse.h"
#include "Ichi/Input/controllerHandler.h"

using namespace ichi::input;

namespace ichi::uicomponents
{
    Button::Button(datatypes::Hitbox hb, std::string btnLabel, TTF_Font *f, SDL_Color c, graphics::Sprite s, graphics::Sprite fs, std::function<void()> ptr) : UIComponent(hb), sprite(s), focusedSprite(fs), funcPtr(ptr)
    {
        if (btnLabel.empty())
        {
            text = nullptr;
            return;
        }

        SDL_Surface *surf = TTF_RenderText_Blended(f, btnLabel.c_str(), c);

        if (surf == nullptr)
        {
            ICHI_ERROR("Could not create surface for button label: {}", SDL_GetError());
            return;
        }

        SDL_Texture *texture = SDL_CreateTextureFromSurface(core::Engine::getInstance()->getRenderer(), surf);
        SDL_FreeSurface(surf);

        if (texture == nullptr)
        {
            ICHI_ERROR("Could not create texture for button label", SDL_GetError());
            return;
        }

        text = texture;
    }

    void Button::draw() const
    {
        if (focused)
            focusedSprite.draw();
        else
            sprite.draw();

        if (!text)
            return;

        int textWidth, textHeight;
        SDL_QueryTexture(text, nullptr, nullptr, &textWidth, &textHeight);

        int diff = (hitbox.getWidth() - textWidth) / 2;

        auto rect = SDL_Rect{hitbox.getX() + diff, hitbox.getY(), textWidth, textHeight};

        if (textWidth > hitbox.getWidth())
            rect = SDL_Rect{hitbox.getX(), hitbox.getY(), textWidth, hitbox.getHeight()};

        SDL_RenderCopy(core::Engine::getInstance()->getRenderer(), text, NULL, &rect);
    }

    void Button::update()
    {
        if (Mouse::DX() != 0 || Mouse::DY() != 0)
            setFocus(hitbox.pointIsInRect(datatypes::Point(Mouse::getX(), Mouse::getY())));

        if (focused && (Keyboard::keyIsPressed(Keyboard::Key::ICHIKEY_RETURN) ||
                        Keyboard::keyIsPressed(Keyboard::Key::ICHIKEY_SPACE) ||
                        ControllerHandler::anyControllerIsPressing(ControllerHandler::ControllerButton::A)))
        {
            funcPtr();
            return;
        }

        if (hitbox.pointIsInRect(datatypes::Point(Mouse::getX(), Mouse::getY())) && Mouse::buttonIsReleased(Mouse::MouseButton::LEFT))
        {
            funcPtr();
        }
    }
} // namespace ichi::uicomponents
