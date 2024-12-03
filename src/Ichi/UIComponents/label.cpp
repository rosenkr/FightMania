#include "Ichi/UIComponents/label.h"
#include "Ichi/Core/engine.h"
#include "Ichi/log.h"

namespace ichi::uicomponents
{

    Label::Label(datatypes::Hitbox h, const std::string &s, TTF_Font *f, SDL_Color c) : UIComponent(h)
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

        this->texture = texture;
    }

    void Label::draw() const
    {
        SDL_RenderCopy(core::Engine::getInstance()->getRenderer(), texture, NULL, hitbox.toSdlRect());
    }

} // namespace ichi::uicomponents
