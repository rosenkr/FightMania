#include "Ichi/Graphics/sprite.h"

// temp
#include "Ichi/Core/engine.h"
#include "Ichi/log.h"

namespace ichi::graphics
{

    Sprite::Sprite(core::Hitbox hb, Layer l, std::string s) : hitbox(hb), layer(l), path(s)
    {
    }

    void Sprite::draw()
    {
        if (texture == nullptr)
        {
            SDL_Surface *surf = IMG_Load(path.c_str());

            if (surf == nullptr)
            {

                ICHI_ERROR("Could not open image: {}", path);
                return;
            }

            SDL_Texture *texture = SDL_CreateTextureFromSurface(core::Engine::getInstance()->getRenderer(), surf);

            SDL_FreeSurface(surf);

            if (texture == nullptr)
            {
                ICHI_ERROR("Could not create texture for sprite: {}", SDL_GetError());
                return;
            }

            this->texture = texture;
        }

        SDL_RenderCopy(core::Engine::getInstance()->getRenderer(), texture, NULL, hitbox.toSdlRect());
    }

    bool Sprite::operator<(const Sprite &other) const
    {
        return layer < other.layer;
    }

} // namespace ichi::graphics
