#include "Ichi/UIComponents/progressBar.h"
#include "Ichi/Core/engine.h"
#include "Ichi/Graphics/textureManager.h"
#include "SDL2/SDL_image.h"

#include <algorithm>

namespace ichi::uicomponents
{

    ProgressBar::ProgressBar(datatypes::Hitbox hb, graphics::Sprite s, graphics::Sprite c, bool mirror = false) : UIComponent(hb), bar(s), color(c), isMirrored(mirror)
    {
    }

    void ProgressBar::draw() const
    {
        auto hb = datatypes::Hitbox(datatypes::Point(hitbox.getX(), hitbox.getY()), hitbox.getWidth() * procentageFilled, hitbox.getHeight(), false);
        if (isMirrored)
            hb.setX(hitbox.getX() + (hitbox.getWidth() - hb.getWidth()));
        auto texture = graphics::TextureManager::getTextureFor(color.getPath());
        SDL_RenderCopy(core::Engine::getInstance()->getRenderer(), texture, NULL, hb.getSDLRect());

        bar.draw();
    }

    void ProgressBar::setProcentageFilled(float f)
    {
        procentageFilled = std::clamp(f, 0.f, 1.f);
    }

} // namespace ichi::uicomponents
