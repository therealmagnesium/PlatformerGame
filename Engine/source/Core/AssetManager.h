#pragma once
#include "Core/Base.h"

#include <SFML/Graphics/Texture.hpp>
#include <string>
#include <unordered_map>

namespace Engine
{
    class AssetManager
    {
    public:
        AssetManager();

        static inline AssetManager* Get() { return s_instance; }
        inline u64 GetTextureCount() { return m_textures.size(); }
        inline sf::Texture& GetTexture(const std::string& name) { return m_textures[name]; }

        void AddTexture(const std::string& name, const std::string& path);
        void Clean();

    private:
        std::unordered_map<std::string, sf::Texture> m_textures;

    private:
        static AssetManager* s_instance;
    };
}
