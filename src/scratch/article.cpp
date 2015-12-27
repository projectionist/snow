#include <cstdio>
#include <cstdlib>
#include <math.h>
#include <scratch/article.hpp>


namespace scratch {
  article::article(GLfloat _spawned, GLfloat _lifespan) {
    x = (float) rand();
    x /= (float) RAND_MAX;
    x = (x * 2) - 1;
    y = 1.0f;

    r = 0.5 + (0.5 * ((float) rand() / (float) RAND_MAX));
    g = 0.5 + (0.5 * ((float) rand() / (float) RAND_MAX));
    b = 0.5 + (0.5 * ((float) rand() / (float) RAND_MAX));
    lifespan = _lifespan;
    spawned  = _spawned;
    dead = false;
  }

  void article::update(GLfloat elapsed_seconds)
  {
    GLfloat age = elapsed_seconds - spawned;

    // normalize age
    GLfloat normalized_age = age / lifespan;

    if (normalized_age >= 1.0f) {
      dead = true;
      return;
    }

    y = 1.0f - (normalized_age * 2.0);
  }
}
