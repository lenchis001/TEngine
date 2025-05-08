#ifndef TENGINE_GL_WRAPPER_H
#define TENGINE_GL_WRAPPER_H

#if defined(_WIN32)
    #include <GL/gl.h>
    #include <GL/glext.h>

    // Declare the function pointer for glBindBuffer
    typedef void (APIENTRY *PFNGLBINDBUFFERPROC)(GLenum target, GLuint buffer);
    extern PFNGLBINDBUFFERPROC glBindBuffer;

    // Declare the function pointer for glActiveTexture
    typedef void (APIENTRY *PFNGLACTIVETEXTUREPROC)(GLenum texture);
    extern PFNGLACTIVETEXTUREPROC glActiveTexture;

    // Declare the function pointer for glBindVertexArray
    typedef void (APIENTRY *PFNGLBINDVERTEXARRAYPROC)(GLuint array);
    extern PFNGLBINDVERTEXARRAYPROC glBindVertexArray;

    // Declare the function pointer for glGenVertexArrays
    typedef void (APIENTRY *PFNGLGENVERTEXARRAYSPROC)(GLsizei n, GLuint *arrays);
    extern PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;

    // Declare the function pointer for glUseProgram
    typedef void (APIENTRY *PFNGLUSEPROGRAMPROC)(GLuint program);
    extern PFNGLUSEPROGRAMPROC glUseProgram;

    // Declare the function pointer for glUniformMatrix4fv
    typedef void (APIENTRY *PFNGLUNIFORMMATRIX4FVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
    extern PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv;

    // Declare the function pointer for glUniform1i
    typedef void (APIENTRY *PFNGLUNIFORM1IPROC)(GLint location, GLint v0);
    extern PFNGLUNIFORM1IPROC glUniform1i;

    // Declare the function pointer for glBufferData
    typedef void (APIENTRY *PFNGLBUFFERDATAPROC)(GLenum target, GLsizeiptr size, const void *data, GLenum usage);
    extern PFNGLBUFFERDATAPROC glBufferData;

    // Declare the function pointer for glVertexAttribPointer
    typedef void (APIENTRY *PFNGLVERTEXATTRIBPOINTERPROC)(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer);
    extern PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;

    // Declare the function pointer for glEnableVertexAttribArray
    typedef void (APIENTRY *PFNGLENABLEVERTEXATTRIBARRAYPROC)(GLuint index);
    extern PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;

    // Declare the function pointer for glGetUniformLocation
    typedef GLint (APIENTRY *PFNGLGETUNIFORMLOCATIONPROC)(GLuint program, const GLchar *name);
    extern PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;

    // Declare the function pointer for glBindBufferBase
    typedef void (APIENTRY *PFNGLBINDBUFFERBASEPROC)(GLenum target, GLuint index, GLuint buffer);
    extern PFNGLBINDBUFFERBASEPROC glBindBufferBase;

    // Declare the function pointer for glUniform3fv
    typedef void (APIENTRY *PFNGLUNIFORM3FVPROC)(GLint location, GLsizei count, const GLfloat *value);
    extern PFNGLUNIFORM3FVPROC glUniform3fv;

    // Declare the function pointer for glGenBuffers
    typedef void (APIENTRY *PFNGLGENBUFFERSPROC)(GLsizei n, GLuint *buffers);
    extern PFNGLGENBUFFERSPROC glGenBuffers;

    // Declare the function pointer for glDeleteBuffers
    typedef void (APIENTRY *PFNGLDELETEBUFFERSPROC)(GLsizei n, const GLuint *buffers);
    extern PFNGLDELETEBUFFERSPROC glDeleteBuffers;

    // Declare the function pointer for glDeleteVertexArrays
    typedef void (APIENTRY *PFNGLDELETEVERTEXARRAYSPROC)(GLsizei n, const GLuint *arrays);
    extern PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays;

    // Declare the function pointer for glCreateProgram
    typedef GLuint (APIENTRY *PFNGLCREATEPROGRAMPROC)(void);
    extern PFNGLCREATEPROGRAMPROC glCreateProgram;

    // Declare the function pointer for glCreateShader
    typedef GLuint (APIENTRY *PFNGLCREATESHADERPROC)(GLenum type);
    extern PFNGLCREATESHADERPROC glCreateShader;

    // Declare the function pointer for glShaderSource
    typedef void (APIENTRY *PFNGLSHADERSOURCEPROC)(GLuint shader, GLsizei count, const GLchar *const*string, const GLint *length);
    extern PFNGLSHADERSOURCEPROC glShaderSource;

    // Declare the function pointer for glCompileShader
    typedef void (APIENTRY *PFNGLCOMPILESHADERPROC)(GLuint shader);
    extern PFNGLCOMPILESHADERPROC glCompileShader;

    // Declare the function pointer for glGetShaderiv
    typedef void (APIENTRY *PFNGLGETSHADERIVPROC)(GLuint shader, GLenum pname, GLint *params);
    extern PFNGLGETSHADERIVPROC glGetShaderiv;

    // Declare the function pointer for glGetShaderInfoLog
    typedef void (APIENTRY *PFNGLGETSHADERINFOLOGPROC)(GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
    extern PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;

    // Declare the function pointer for glDeleteShader
    typedef void (APIENTRY *PFNGLDELETESHADERPROC)(GLuint shader);
    extern PFNGLDELETESHADERPROC glDeleteShader;

    // Declare the function pointer for glAttachShader
    typedef void (APIENTRY *PFNGLATTACHSHADERPROC)(GLuint program, GLuint shader);
    extern PFNGLATTACHSHADERPROC glAttachShader;

    // Declare the function pointer for glLinkProgram
    typedef void (APIENTRY *PFNGLLINKPROGRAMPROC)(GLuint program);
    extern PFNGLLINKPROGRAMPROC glLinkProgram;

    // Declare the function pointer for glGetProgramiv
    typedef void (APIENTRY *PFNGLGETPROGRAMIVPROC)(GLuint program, GLenum pname, GLint *params);
    extern PFNGLGETPROGRAMIVPROC glGetProgramiv;

    // Declare the function pointer for glGetProgramInfoLog
    typedef void (APIENTRY *PFNGLGETPROGRAMINFOLOGPROC)(GLuint program, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
    extern PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;

    // Declare the function pointer for glDeleteProgram
    typedef void (APIENTRY *PFNGLDELETEPROGRAMPROC)(GLuint program);
    extern PFNGLDELETEPROGRAMPROC glDeleteProgram;

    extern "C" {
        void InitializeOpenGLFunctionPointers();
    }

#elif defined(__APPLE__)
    #include <OpenGL/gl3.h>
#elif defined(__ANDROID__)
    #include <EGL/egl.h>
    #include <GLES3/gl3.h>
#elif defined(__linux__)
    #include <GL/gl.h>
    #include <GL/glx.h>

    // Declare the function pointer for glBindBuffer
    typedef void (*PFNGLBINDBUFFERPROC)(GLenum target, GLuint buffer);
    extern PFNGLBINDBUFFERPROC glBindBuffer;

    // Declare the function pointer for glBindVertexArray
    typedef void (*PFNGLBINDVERTEXARRAYPROC)(GLuint array);
    extern PFNGLBINDVERTEXARRAYPROC glBindVertexArray;

    // Declare the function pointer for glGenVertexArrays
    typedef void (*PFNGLGENVERTEXARRAYSPROC)(GLsizei n, GLuint *arrays);
    extern PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;

    // Declare the function pointer for glUseProgram
    typedef void (*PFNGLUSEPROGRAMPROC)(GLuint program);
    extern PFNGLUSEPROGRAMPROC glUseProgram;

    // Declare the function pointer for glUniformMatrix4fv
    typedef void (*PFNGLUNIFORMMATRIX4FVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
    extern PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv;

    // Declare the function pointer for glUniform1i
    typedef void (*PFNGLUNIFORM1IPROC)(GLint location, GLint v0);
    extern PFNGLUNIFORM1IPROC glUniform1i;

    // Declare the function pointer for glBufferData
    typedef void (*PFNGLBUFFERDATAPROC)(GLenum target, GLsizeiptr size, const void *data, GLenum usage);
    extern PFNGLBUFFERDATAPROC glBufferData;

    // Declare the function pointer for glVertexAttribPointer
    typedef void (*PFNGLVERTEXATTRIBPOINTERPROC)(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer);
    extern PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;

    // Declare the function pointer for glEnableVertexAttribArray
    typedef void (*PFNGLENABLEVERTEXATTRIBARRAYPROC)(GLuint index);
    extern PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;

    // Declare the function pointer for glGetUniformLocation
    typedef GLint (*PFNGLGETUNIFORMLOCATIONPROC)(GLuint program, const GLchar *name);
    extern PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;

    // Declare the function pointer for glBindBufferBase
    typedef void (*PFNGLBINDBUFFERBASEPROC)(GLenum target, GLuint index, GLuint buffer);
    extern PFNGLBINDBUFFERBASEPROC glBindBufferBase;

    // Declare the function pointer for glUniform3fv
    typedef void (*PFNGLUNIFORM3FVPROC)(GLint location, GLsizei count, const GLfloat *value);
    extern PFNGLUNIFORM3FVPROC glUniform3fv;

    // Declare the function pointer for glGenBuffers
    typedef void (*PFNGLGENBUFFERSPROC)(GLsizei n, GLuint *buffers);
    extern PFNGLGENBUFFERSPROC glGenBuffers;

    // Declare the function pointer for glDeleteBuffers
    typedef void (*PFNGLDELETEBUFFERSPROC)(GLsizei n, const GLuint *buffers);
    extern PFNGLDELETEBUFFERSPROC glDeleteBuffers;

    // Declare the function pointer for glDeleteVertexArrays
    typedef void (*PFNGLDELETEVERTEXARRAYSPROC)(GLsizei n, const GLuint *arrays);
    extern PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays;

    // Declare the function pointer for glCreateProgram
    typedef GLuint (*PFNGLCREATEPROGRAMPROC)(void);
    extern PFNGLCREATEPROGRAMPROC glCreateProgram;

    // Declare the function pointer for glCreateShader
    typedef GLuint (*PFNGLCREATESHADERPROC)(GLenum type);
    extern PFNGLCREATESHADERPROC glCreateShader;

    // Declare the function pointer for glShaderSource
    typedef void (*PFNGLSHADERSOURCEPROC)(GLuint shader, GLsizei count, const GLchar *const*string, const GLint *length);
    extern PFNGLSHADERSOURCEPROC glShaderSource;

    // Declare the function pointer for glCompileShader
    typedef void (*PFNGLCOMPILESHADERPROC)(GLuint shader);
    extern PFNGLCOMPILESHADERPROC glCompileShader;

    // Declare the function pointer for glGetShaderiv
    typedef void (*PFNGLGETSHADERIVPROC)(GLuint shader, GLenum pname, GLint *params);
    extern PFNGLGETSHADERIVPROC glGetShaderiv;

    // Declare the function pointer for glGetShaderInfoLog
    typedef void (*PFNGLGETSHADERINFOLOGPROC)(GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
    extern PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;

    // Declare the function pointer for glDeleteShader
    typedef void (*PFNGLDELETESHADERPROC)(GLuint shader);
    extern PFNGLDELETESHADERPROC glDeleteShader;

    // Declare the function pointer for glAttachShader
    typedef void (*PFNGLATTACHSHADERPROC)(GLuint program, GLuint shader);
    extern PFNGLATTACHSHADERPROC glAttachShader;

    // Declare the function pointer for glLinkProgram
    typedef void (*PFNGLLINKPROGRAMPROC)(GLuint program);
    extern PFNGLLINKPROGRAMPROC glLinkProgram;

    // Declare the function pointer for glGetProgramiv
    typedef void (*PFNGLGETPROGRAMIVPROC)(GLuint program, GLenum pname, GLint *params);
    extern PFNGLGETPROGRAMIVPROC glGetProgramiv;

    // Declare the function pointer for glGetProgramInfoLog
    typedef void (*PFNGLGETPROGRAMINFOLOGPROC)(GLuint program, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
    extern PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;

    // Declare the function pointer for glDeleteProgram
    typedef void (*PFNGLDELETEPROGRAMPROC)(GLuint program);
    extern PFNGLDELETEPROGRAMPROC glDeleteProgram;

    extern "C" {
        void InitializeOpenGLFunctionPointers();
    }
#else
    #error "Platform not supported"
#endif

#endif // TENGINE_GL_WRAPPER_H