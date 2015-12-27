#pragma once

#include <memory>
#include <vector>

#include <GLES2/gl2.h>

#include <projection/drawing.hpp>
#include <projection/program_helper.hpp>

#include <scratch/article.hpp>


namespace scratch {
  class scratch : public projection::drawing {
    bool variable_lifespan = false;
    GLuint program;
    GLuint vbo[2];
    std::unique_ptr<projection::program_helper> program_helper;
    std::vector<article> articles; // x coords of texture articles
    void update();
    void spawn();
  public:
    void setup();
    void draw();
    explicit scratch(){};
  };
}
