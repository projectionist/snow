#pragma once

#include <GLES2/gl2.h>

namespace scratch {
  class article {
    GLfloat lifespan;
    GLfloat spawned;
  public:
    GLfloat x;
    GLfloat y;
    GLfloat r;
    GLfloat g;
    GLfloat b;
    bool dead;
    explicit article(GLfloat spawned, GLfloat  lifespan);
    void update(GLfloat elapsed_seconds);
  };
}
