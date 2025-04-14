#ifndef TENGINE_GL_WRAPPER_H
#define TENGINE_GL_WRAPPER_H

#if defined(_WIN32)
    #include <Windows.h>
    #include <GL/gl.h>
#elif defined(__APPLE__)
    #include <OpenGL/gl3.h>
#elif defined(__linux__)
    #include <GL/gl.h>
    #include <GL/glx.h>
#elif defined(__ANDROID__)
    #include <EGL/egl.h>
    #include <GLES3/gl3.h>
#else
    #error "Platform not supported"
#endif

inline void BindVertexArray(GLuint array) {
#if defined(__ANDROID__)
    glBindVertexArrayOES(array);
#else
    glBindVertexArray(array);
#endif
}


#endif // TENGINE_GL_WRAPPER_H