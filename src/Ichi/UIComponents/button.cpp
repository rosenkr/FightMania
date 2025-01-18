#include "Ichi/UIComponents/button.h"
#include "Ichi/Core/engine.h"
#include "Ichi/log.h"
#include "Ichi/Input/keyboard.h"
#include "Ichi/Input/mouse.h"
#include "Ichi/Input/controllerHandler.h"
#include "Ichi/Graphics/textureManager.h"

using namespace ichi::input;

namespace ichi::uicomponents
{
    Button::Button(datatypes::Hitbox hb, std::string btnLabel, TTF_Font *f, SDL_Color c, graphics::Sprite s, graphics::Sprite fs, std::function<void()> ptr) : UIComponent(hb), t(btnLabel), f(f), c(c), sprite(s), focusedSprite(fs), funcPtr(ptr)
    {
        ichi::graphics::TextureManager::addTextTextureFor(t, f, c);
    }

    void Button::draw() const
    {
        auto text = graphics::TextureManager::getTextTextureFor(t, f, c);
        if (focused)
            focusedSprite.draw();
        else
            sprite.draw();

        if (!text)
            return;

        int textWidth, textHeight;
        SDL_QueryTexture(text, nullptr, nullptr, &textWidth, &textHeight);

        int xDiff = (hitbox.getWidth() - textWidth) / 2;
        int yDiff = (hitbox.getHeight() - textHeight) / 2;

        auto rect = SDL_Rect{hitbox.getX() + xDiff, hitbox.getY() + yDiff, textWidth, textHeight};

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
