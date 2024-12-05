#include "Ichi/UIComponents/button.h"
#include "Ichi/Core/engine.h"
#include "Ichi/log.h"
#include "Ichi/Input/keyboard.h"
#include "Ichi/Input/mouse.h"
#include "Ichi/Input/controllerHandler.h"

using namespace ichi::input;

namespace ichi::uicomponents
{
    Button::Button(datatypes::Hitbox hb, std::string btnLabel, TTF_Font *f, SDL_Color c, graphics::Sprite s, graphics::Sprite fs, void (*ptr)()) : UIComponent(hb), sprite(s), focusedSprite(fs), funcPtr(ptr)
    {
        SDL_Surface *surf = TTF_RenderText_Solid(f, btnLabel.c_str(), c);

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

        text = texture;
    }

    void Button::draw() const
    {
        if (focused)
            focusedSprite.draw();
        else
            sprite.draw();

        SDL_RenderCopy(core::Engine::getInstance()->getRenderer(), text, NULL, hitbox.getSDLRect());
    }

    void Button::update()
    {
        if (Mouse::buttonIsPressed(Mouse::MouseButton::LEFT))
            setFocus(hitbox.pointIsInRect(datatypes::Point(Mouse::getX(), Mouse::getY())));

        if (focused && (Keyboard::keyIsPressed(Keyboard::Key::ICHIKEY_KP_ENTER) || Keyboard::keyIsPressed(Keyboard::Key::ICHIKEY_SPACE) || (ControllerHandler::getFirstController() != -1 && ControllerHandler::buttonIsPressed(ControllerHandler::getFirstController(), ControllerHandler::ControllerButton::A))))
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
