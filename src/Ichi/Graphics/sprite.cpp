#include "Ichi/Graphics/sprite.h"

namespace ichi::graphics
{
    void Sprite::draw()
    {
        SDL_RenderCopy(core::Engine::getInstance()->getRenderer(), textureManager::getTextureFor(*this), NULL, hitbox.toSdlRect());
    }

    Sprite::Sprite(core::Hitbox h, Layer l, std::string path) : hitbox(h), layer(l)
    {
        if (path != "")
            textureManager::addTextureFor(*this, path);
    }

    bool Sprite::operator==(const Sprite &other) const
    {
        return layer == other.layer && hitbox == other.hitbox;
    }
}

namespace std
{

    size_t hash<ichi::graphics::Sprite>::operator()(const ichi::graphics::Sprite &sprite) const
    {
        size_t layerHash = hash<int>()(static_cast<int>(sprite.getLayer()));
        size_t hitboxHash = hash<ichi::core::Hitbox>()(sprite.getHitbox());

        // Combine hashes (XOR + shift method)
        return layerHash ^ (hitboxHash << 1);
    }

} // namespace std