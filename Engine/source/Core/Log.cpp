#include "Core/Log.h"

#include <stdio.h>
#include <stdarg.h>

namespace Engine
{
    void Log(LogLevel level, const char* format, ...)
    {
        va_list args;

        switch (level)
        {
            case LogLevel::Trace:
            {
                va_start(args, format);
                printf("[Trace] ");
                vprintf(format, args);
                printf("\n");
                va_end(args);
                break;
            }

            case LogLevel::Info:
            {
                va_start(args, format);
                printf("[Info] ");
                vprintf(format, args);
                printf("\n");
                va_end(args);
                break;
            }

            case LogLevel::Warn:
            {
                va_start(args, format);
                printf("[Warn] ");
                vprintf(format, args);
                printf("\n");
                va_end(args);
                break;
            }

            case LogLevel::Error:
            {
                va_start(args, format);
                printf("[Error] ");
                vprintf(format, args);
                printf("\n");
                va_end(args);
                break;
            }

            case LogLevel::Fatal:
            {
                va_start(args, format);
                printf("[Fatal] ");
                vprintf(format, args);
                printf("\n");
                va_end(args);
                break;
            }

            default:
                break;
        }
    }
}
