#pragma once
#include "Core/Base.h"
#include "Core/Log.h"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Vector2.hpp>

namespace Engine
{
    enum class CameraType
    {
        Static = 0,
        PositionLock = 1,
        HorizontalScroll = 2,
        ZoneWalls = 3,
        ZoneBox = 4,
    };

    struct CameraZone
    {
        float checkpointA;
        float checkpointB;

        CameraZone() = default;
        CameraZone(float a, float b) : checkpointA(a), checkpointB(b) {}
    };

    struct CameraBox
    {
        CameraZone xAxisZone;
        CameraZone yAxisZone;

        CameraBox() = default;
        CameraBox(CameraZone& a, CameraZone& b) : xAxisZone(a), yAxisZone(b) {}
        CameraBox(float a, float b, float c, float d) : xAxisZone(a, b), yAxisZone(c, d) {}
    };

    class Camera
    {
    public:
        Camera();

        inline sf::View& GetView() { return m_view; }

        inline void SetType(CameraType type) { m_type = type; }
        inline void SetPanSpeed(float speed) { m_panSpeed = speed; }
        inline void SetZoneWalls(float a, float b) { m_zone = CameraZone(a, b); }
        inline void SetZoneBox(float a, float b, float c, float d) { m_zoneBox = CameraBox(a, b, c, d); }
        inline void SetTarget(const sf::Vector2f& target) { m_target = target; }
        inline void SetClearColor(const sf::Color& color) { m_clearColor = color; }
        inline void LogPosition() { LOG_INFO(V2_FMT, V2_OPEN(m_view.getCenter())); }

        void Update();
        void BeginScope();
        void EndScope();

    private:
        void DebugControls();

    private:
        float m_panSpeed;
        CameraType m_type;
        CameraZone m_zone;
        CameraBox m_zoneBox;

        sf::Vector2f m_target;
        sf::Color m_clearColor;
        sf::View m_view;
    };
}
