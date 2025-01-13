#include "Ichi/UIComponents/label.h"
#include "Ichi/Core/engine.h"
#include "Ichi/log.h"

namespace ichi::uicomponents
{

    Label::Label(datatypes::Point location, const std::string &s, TTF_Font *f, SDL_Color c) : UIComponent(datatypes::Hitbox(location, 0, 0, false)), font(f), color(c)
    {
        updateText(s);
    }

    void Label::draw() const
    {
        SDL_RenderCopy(core::Engine::getInstance()->getRenderer(), texture, NULL, hitbox.getSDLRect());
    }

    void Label::updateText(std::string text)
    {
        SDL_Surface *surf = TTF_RenderText_Blended(font, text.c_str(), color);

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

        int textWidth, textHeight;
        SDL_QueryTexture(texture, nullptr, nullptr, &textWidth, &textHeight);

        hitbox = datatypes::Hitbox(hitbox.getPos(), textWidth, textHeight, false);
    }

} // namespace ichi::uicomponents
