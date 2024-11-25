#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H
namespace ichi::core {
    class AnimatedSprite{
        public: 
        // Define operator< for Sprite comparison, usage in textureManager std::map
        bool operator<(const AnimatedSprite& other) const {
            return id < other.id;
        }

        private:
        int id; // Temporary
    };
}
#endif