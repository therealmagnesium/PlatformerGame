#include "Graphics/Camera.h"
#include "Core/Base.h"
#include "Core/Log.h"
#include "Core/Math.h"
#include "Graphics/Window.h"
#include "Core/Application.h"
#include "Core/Input.h"
#include "Scene/Tile.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <assert.h>

namespace Engine
{
    static Application* app = NULL;

    Camera::Camera()
    {
        m_panSpeed = 8.f;
        m_type = CameraType::Static;
        m_zone = CameraZone(-250.f, 250.f);
        m_zoneBox = CameraBox(-200.f, 200.f, -150.f, 150.f);
        m_target = sf::Vector2f(0.f, 0.f);
        m_clearColor = sf::Color::White;

        m_view.setCenter(m_target);
        m_view.setSize(1280.f, 720.f);
        m_view.setRotation(0.f);
    }

    void Camera::Update()
    {
        app = Application::Get();
        assert(app);

        if (!app->DebugEnabled())
        {
            switch (m_type)
            {
                case CameraType::Static:
                {
                    static sf::Vector2f startPosition = m_target;
                    m_view.setCenter(startPosition);

                    break;
                }

                case CameraType::PositionLock:
                {
                    sf::Vector2f newTarget = m_target;
                    newTarget.x += TILE_SIZE / 2.f;
                    newTarget.y += TILE_SIZE / 2.f;

                    m_view.setCenter(newTarget);
                    break;
                };

                case CameraType::HorizontalScroll:
                {
                    static float startY = m_target.y;

                    sf::Vector2f newTarget = m_target;
                    newTarget.x += TILE_SIZE / 2.f;
                    newTarget.y += TILE_SIZE / 2.f;

                    m_view.setCenter(sf::Vector2f(newTarget.x, startY));
                    break;
                };

                case CameraType::ZoneWalls:
                {
                    static sf::Vector2f position = m_target;

                    if (m_target.x < m_view.getCenter().x + m_zone.checkpointA)
                        position.x -= m_panSpeed * Time::deltaTime;

                    if (m_target.x > m_view.getCenter().x + m_zone.checkpointB)
                        position.x += m_panSpeed * Time::deltaTime;

                    m_view.setCenter(position);

                    break;
                }

                case CameraType::ZoneBox:
                {
                    static sf::Vector2f position = m_target;

                    if (m_target.x < m_view.getCenter().x + m_zoneBox.xAxisZone.checkpointA)
                        position.x -= m_panSpeed * Time::deltaTime;

                    if (m_target.x > m_view.getCenter().x + m_zoneBox.xAxisZone.checkpointB)
                        position.x += m_panSpeed * Time::deltaTime;

                    if (m_target.y < m_view.getCenter().y + m_zoneBox.yAxisZone.checkpointA)
                        position.y -= m_panSpeed * Time::deltaTime;

                    if (m_target.y > m_view.getCenter().y + m_zoneBox.yAxisZone.checkpointB)
                        position.y += m_panSpeed * Time::deltaTime;

                    m_view.setCenter(position);
                    break;
                }

                default:
                    break;
            }
        }
        else
        {
            this->DebugControls();
        }
    }

    void Camera::BeginScope()
    {
        assert(app);
        sf::RenderWindow* nativeWindow = app->GetWindow()->GetHandle();
        nativeWindow->clear(m_clearColor);
        nativeWindow->setView(m_view);
    }

    void Camera::EndScope()
    {
        assert(app);
        sf::RenderWindow* nativeWindow = app->GetWindow()->GetHandle();

        nativeWindow->setView(nativeWindow->getDefaultView());
    }

    void Camera::DebugControls()
    {
        sf::Vector2f inputAxis;
        inputAxis.x = Input::GetAxis("Horizontal", true);
        inputAxis.y = Input::GetAxis("Vertical", true);
        Normalize(inputAxis);

        m_view.move(m_panSpeed * inputAxis * Time::deltaTime);
    }
}
