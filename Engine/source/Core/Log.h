#pragma once

#define LOG_TRACE(...) Engine::Log(Engine::LogLevel::Trace, __VA_ARGS__)
#define LOG_INFO(...) Engine::Log(Engine::LogLevel::Info, __VA_ARGS__)
#define LOG_WARN(...) Engine::Log(Engine::LogLevel::Warn, __VA_ARGS__)
#define LOG_ERROR(...) Engine::Log(Engine::LogLevel::Error, __VA_ARGS__)
#define LOG_FATAL(...) Engine::Log(Engine::LogLevel::Fatal, __VA_ARGS__)

namespace Engine
{
    enum class LogLevel
    {
        Trace = 0,
        Info,
        Warn,
        Error,
        Fatal
    };

    void Log(LogLevel level, const char* format, ...);
}
