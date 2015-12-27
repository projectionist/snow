#include <cassert>
#include <ctime>
#include <cstdio>
#include <algorithm>

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include <scratch/scratch.hpp>

using namespace std;

namespace scratch {

  void scratch::setup()
  {
    program_helper = make_unique<projection::program_helper>("./src/scratch/vert.glsl", "./src/scratch/frag.glsl");
    program = program_helper->program();
    /*
      if you bind attribute names to locations, do it before linking
    */
    program_helper->link();
    /*
      if you get attribute/uniform locations, do it after linking
    */

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_STENCIL_TEST);
    // enable alpha blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glUseProgram(program);

    glGenBuffers(2, vbo);
  }

  void scratch::spawn()
  {
    static float last_spawn = elapsed();

    if ((elapsed() - last_spawn) < 0.001) return;

    for (int i = 0; i < 600; i++) {
      auto lifespan = 9.0;

      if (variable_lifespan) {
        lifespan += (-2.0 + (4.0 * ((float) rand() / (float) RAND_MAX)));
      }

      article a(elapsed(), lifespan);
      articles.push_back(a);
    }

    last_spawn = elapsed();
  }

  void scratch::update()
  {
    spawn();
    for (auto &article:articles) article.update(elapsed());

    auto remove = remove_if(articles.begin(), articles.end(), [](const article &a) {
      return a.dead;
    });

    articles.erase(remove, articles.end());
  }

  void scratch::draw()
  {
    update();

    glViewport(0, 0, width(), height());
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    // Clear the color buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    vector<GLfloat> coord_buffer;
    vector<GLfloat> colour_buffer;
    for(auto &article:articles) {
      coord_buffer.push_back(article.x);
      coord_buffer.push_back(article.y);
      colour_buffer.push_back(article.r);
      colour_buffer.push_back(article.g);
      colour_buffer.push_back(article.b);
    }

    GLfloat *vertices = (GLfloat *) &coord_buffer[0];
    GLfloat *colours = (GLfloat *) &colour_buffer[0];

    auto a_coord_location = glGetAttribLocation(program, "a_coord");
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, coord_buffer.size() * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(a_coord_location, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(a_coord_location);


    auto a_colour_location = glGetAttribLocation(program, "a_colour");
    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glBufferData(GL_ARRAY_BUFFER, colour_buffer.size() * sizeof(GLfloat), colours, GL_STATIC_DRAW);
    glVertexAttribPointer(a_colour_location, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(a_colour_location);

    glDrawArrays(GL_POINTS, 0, articles.size());
  }
}
