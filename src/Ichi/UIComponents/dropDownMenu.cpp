#include "Ichi/UIComponents/dropDownMenu.h"
#include "Ichi/Core/engine.h"
#include "Ichi/Graphics/textureManager.h"
#include "Ichi/Input/keyboard.h"
#include "Ichi/Input/mouse.h"
#include "Ichi/Input/controllerHandler.h"
#include "Ichi/log.h"

#include "SDL2/SDL_image.h"

using namespace ichi::input;

namespace ichi::uicomponents
{

    DropDownMenu::DropDownMenu(datatypes::Hitbox hb, std::vector<std::string> items, TTF_Font *f, SDL_Color c, graphics::Sprite m, graphics::Sprite item)
        : UIComponent(hb), items(items), font(f), textColor(c), menu(m), itemSprite(item)
    {

        for (auto s : items)
        {
            SDL_Surface *surf = TTF_RenderText_Solid(f, s.c_str(), c);

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

            itemTextures[s] = texture;
        }
        SDL_Surface *surf = TTF_RenderText_Solid(f, NONE_SELECTED.c_str(), c);

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
        itemTextures[NONE_SELECTED] = texture;
    }

    void DropDownMenu::update()
    {
        if (Mouse::DX() != 0 || Mouse::DY() != 0)
            setFocus(hitbox.pointIsInRect(datatypes::Point(Mouse::getX(), Mouse::getY())));

        if (isExpanded)
        {
            datatypes::Hitbox hb(datatypes::Point(hitbox.getX(), hitbox.getY() + hitbox.getHeight()), itemSprite.getWidth(), itemSprite.getHeight(), false);
            for (auto s : items)
            {
                if (hb.pointIsInRect(datatypes::Point(Mouse::getX(), Mouse::getY())) && Mouse::buttonIsReleased(Mouse::MouseButton::LEFT))
                {
                    isExpanded = !isExpanded;
                    selected = s;
                }
                hb += datatypes::Point(0, itemSprite.getHeight());
            }
        }

        if (focused && (Keyboard::keyIsPressed(Keyboard::Key::ICHIKEY_RETURN) ||
                        Keyboard::keyIsPressed(Keyboard::Key::ICHIKEY_SPACE) ||
                        ControllerHandler::anyControllerIsPressing(ControllerHandler::ControllerButton::A)))
        {
            isExpanded = !isExpanded;
            return;
        }

        if (hitbox.pointIsInRect(datatypes::Point(Mouse::getX(), Mouse::getY())) && Mouse::buttonIsReleased(Mouse::MouseButton::LEFT))
        {
            isExpanded = !isExpanded;
        }
    }

    void DropDownMenu::draw() const
    {
        menu.draw();
        SDL_RenderCopy(core::Engine::getInstance()->getRenderer(), itemTextures.at(selected), NULL, hitbox.getSDLRect());

        if (!isExpanded)
            return;

        datatypes::Hitbox hb(datatypes::Point(hitbox.getX(), hitbox.getY() + hitbox.getHeight()), itemSprite.getWidth(), itemSprite.getHeight(), false);
        for (auto s : items)
        {
            SDL_RenderCopy(core::Engine::getInstance()->getRenderer(), graphics::TextureManager::getTextureFor(itemSprite), NULL, hb.getSDLRect());
            SDL_RenderCopy(core::Engine::getInstance()->getRenderer(), itemTextures.at(s), NULL, hb.getSDLRect());
            hb += datatypes::Point(0, itemSprite.getHeight());
        }
    }
} // namespace ichi::uicomponents