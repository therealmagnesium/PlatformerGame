#include "Core/AssetManager.h"
#include "Core/Log.h"
#include <SFML/Graphics/Texture.hpp>

namespace Engine
{
    AssetManager* AssetManager::s_instance;

    AssetManager::AssetManager() { s_instance = this; }

    void AssetManager::AddTexture(const std::string& name, const std::string& path)
    {
        sf::Texture texture;
        if (!texture.loadFromFile(path))
        {
            LOG_WARN("Failed to load %s", path.c_str());
            return;
        }

        m_textures[name] = texture;
    }

    void AssetManager::Clean() { m_textures.clear(); }
}
