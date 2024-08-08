#ifndef TENGINEEXPORT_H
#define TENGINEEXPORT_H

#ifdef _WIN32
#ifdef TENGINE_EXPORTS
#define TENGINE_API __declspec(dllexport)
#else
#define TENGINE_API __declspec(dllimport)
#endif
#else
#define TENGINE_API
#endif

#endif // TENGINEEXPORT_H