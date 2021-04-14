//
// Created by captain on 3/29/21.
//

#ifndef CG_ASSIGNMENT_FONT_H
#define CG_ASSIGNMENT_FONT_H

#include <ft2build.h>
#include FT_FREETYPE_H
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <map>

struct Character {
    unsigned int textureId;  // ID handle of the glyph texture
    glm::ivec2 size;       // Size of glyph
    glm::ivec2 bearing;    // Offset from baseline to left/top of glyph
    unsigned int advance;    // Offset to advance to next glyph
};

void initFreetype();

void RenderText(GLuint &s, std::string text, float x, float y, float scale, glm::vec3 color);

#endif //CG_ASSIGNMENT_FONT_H
