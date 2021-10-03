#pragma once
#include "Texture.h"
#include "Buffer/VertexArray.h"
#include "Buffer/IndexBuffer.h"
#include "Shader/Shader.h"
#include "BatchRenderer/BatchRenderer2D.h"
#include "Vector.h"
#include <iostream>
#include <unordered_map>
#include <vector>
#include <ft2build.h>
#include FT_FREETYPE_H  

struct Glyph {
    Vec2u size;
    Vec2i bearing;
    Vec2f texPos;
    Vec2f texDim;
    uint32_t advance = 0;
};

class Font
{
private:
    static FT_Library* s_pLibrary;

    FT_Face m_Face;
    Vec2f m_HeightRange;
    std::unordered_map<uint32_t, std::unordered_map<char, Glyph>> m_Glyphs;
    std::unordered_map<uint32_t, Texture> m_Textures;
public:
    Font(const std::string& filepath);
    ~Font();

    void GenFontTexture(uint32_t fontHeight);

    Glyph GetGlyph(char ch, uint32_t fontHeight) { return m_Glyphs[fontHeight][ch]; }
    const Texture& GetTexture(uint32_t fontHeight) { return m_Textures[fontHeight]; }

    Vec2f GetHeightRange() const { return m_HeightRange; }
};

enum class Anchor : uint8_t
{
    LEFT = 0, MIDDLE, RIGHT
};
class Text
{
private:
    std::string m_Text;
    Vec3u m_Pos;
    uint32_t m_TextWidth;
    Font& m_Font;
    uint32_t m_FontHeight;
    Vec4f m_Color;
    Anchor m_Anchor;
    std::vector<TexturedQuad> m_Quads;
public:
    Text(const std::string& text, Vec3u pos, Font& font, uint32_t fontHeight, Vec4f color, Anchor = Anchor::LEFT);

    const std::string& GetText() const { return m_Text; }
    void SetText(const std::string& text);
    void SetPosition(Vec3u pos);
    void SetColor(Vec4f color);
    void SetFontHeight(uint32_t fontHeight);

    void PushToBatch();
};