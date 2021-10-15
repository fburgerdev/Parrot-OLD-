#include "Font.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

FT_Library* Font::s_pLibrary = nullptr;
static uint32_t fontCount = 0;

Font::Font(const std::string& filepath)
{
    fontCount++;
    if (s_pLibrary == nullptr)
    {
        s_pLibrary = new FT_Library;
        if (FT_Init_FreeType(s_pLibrary))
            std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
    }
    
    if (FT_New_Face(*s_pLibrary, filepath.c_str(), 0, &m_Face))
        std::cout << "[ERROR] Freetype Failed to load font!" << std::endl;

    m_HeightRange = Vec2f(INFINITY, -INFINITY);
}

Font::~Font()
{
    fontCount--;
    FT_Done_Face(m_Face);
    if (fontCount == 0)
    {
        FT_Done_FreeType(*s_pLibrary);
        s_pLibrary = nullptr;
    }
}

void Font::GenFontTexture(uint32_t fontHeight)
{
    if (!m_Glyphs[fontHeight].empty())
        return;
    
    Vec2u atlasDim(std::max((uint32_t)1024, fontHeight));
    uint8_t* bitmap = new uint8_t[atlasDim.x * atlasDim.y];
    memset(bitmap, 0, atlasDim.x * atlasDim.y);
    
    Vec2u atlasCoords(0, 0);
    FT_Set_Pixel_Sizes(m_Face, 0, fontHeight);
    for (char ch = ' '; ch <= '~'; ch++)
    {
        if (FT_Load_Char(m_Face, ch, FT_LOAD_RENDER))
        {
            std::cout << "[ERROR] Freetype Failed to load Glyph!" << std::endl;
            return;
        }
        
        if (atlasCoords.x + m_Face->glyph->bitmap.width > atlasDim.x)
        {
            atlasCoords.x = 0;
            atlasCoords.y += fontHeight;
        }
        if (atlasCoords.y + fontHeight >= atlasDim.y)
        {
            atlasDim.y += fontHeight;
            bitmap = (uint8_t*)realloc(bitmap, atlasDim.x * atlasDim.y);
            if (bitmap == nullptr)
                return;
            memset(bitmap + atlasDim.x * (atlasDim.y - fontHeight), 0, fontHeight * atlasDim.x);
        }

        Glyph glyph;
        glyph.size = Vec2u(m_Face->glyph->bitmap.width, m_Face->glyph->bitmap.rows);
        glyph.bearing = Vec2i(m_Face->glyph->bitmap_left, m_Face->glyph->bitmap_top);
        glyph.advance = m_Face->glyph->advance.x;
        glyph.texPos = (Vec2f)atlasCoords;

        for (uint32_t y = 0; y < m_Face->glyph->bitmap.rows; y++)
            for (uint32_t x = 0; x < m_Face->glyph->bitmap.width; x++)
                bitmap[atlasCoords.x + x + (atlasCoords.y + y) * atlasDim.x] = (uint8_t)(m_Face->glyph->bitmap.buffer[x + y * m_Face->glyph->bitmap.width]);
        m_Glyphs[fontHeight][ch] = glyph;
        atlasCoords.x += glyph.size.x;

        if (m_Textures.empty())
        {
            if (m_HeightRange.a > glyph.bearing.y)
                m_HeightRange.a = glyph.bearing.y;
            if (m_HeightRange.b < glyph.bearing.y)
                m_HeightRange.b = glyph.bearing.y;
        }
    }
    for (char ch = ' '; ch <= '~'; ch++)
    {
        m_Glyphs[fontHeight][ch].texPos.x /= atlasDim.x;
        m_Glyphs[fontHeight][ch].texPos.y /= atlasDim.y;
        m_Glyphs[fontHeight][ch].texDim.x = (float)m_Glyphs[fontHeight][ch].size.x / atlasDim.x;
        m_Glyphs[fontHeight][ch].texDim.y = (float)m_Glyphs[fontHeight][ch].size.y / atlasDim.y;
    }

    TextureConfig config;
    config.internalFormat = GL_RED;
    config.format = GL_RED;
    config.magFilter = GL_NEAREST;
    config.minFilter = GL_NEAREST;
    m_Textures[fontHeight].LoadTexture(bitmap, atlasDim.x, atlasDim.y, config);
    delete[] bitmap;
}

Text::Text(const std::string& text, Vec3u pos, Font& font, uint32_t fontHeight, Vec4f color, Anchor anchor)
    : m_Pos(pos), m_TextWidth(0), m_Font(font), m_FontHeight(fontHeight), m_Color(color), m_Anchor(anchor)
{
    font.GenFontTexture(fontHeight);
    SetText(text);
}

void Text::SetText(const std::string& text)
{
    m_Text = text;
    m_Quads.resize(text.length());
    int32_t TexID = m_Font.GetTexture(m_FontHeight).GetID();

    Vec3u pos = m_Pos;
    m_TextWidth = 0;
    for (uint32_t i = 0; i < text.length(); i++)
        m_TextWidth += m_Font.GetGlyph(text[i], m_FontHeight).advance >> 6;
    if (m_Anchor == Anchor::MIDDLE)
        pos.x -= m_TextWidth >> 1;
    else if (m_Anchor == Anchor::RIGHT)
        pos.x -= m_TextWidth;

    for (uint32_t i = 0; i < text.length(); i++)
    {
        Glyph glyph = m_Font.GetGlyph(text[i], m_FontHeight);

        m_Quads[i].pos = Vec3i(pos.x + glyph.bearing.x, pos.y - glyph.bearing.y, pos.z);
        m_Quads[i].dim = glyph.size;
        m_Quads[i].texID = TexID;
        m_Quads[i].texPos = glyph.texPos;
        m_Quads[i].texDim = glyph.texDim;
        m_Quads[i].tint = m_Color;
        pos.x += glyph.advance >> 6;
    }
}

void Text::SetPosition(Vec3u pos)
{
    if (pos == m_Pos)
        return;
    Vec3u posDiff = pos - m_Pos;
    m_Pos = pos;
    for (uint32_t i = 0; i < m_Quads.size(); i++)
        m_Quads[i].pos += posDiff;
}

void Text::SetColor(Vec4f color)
{
    if (color == m_Color)
        return;
    m_Color = color;
    for (uint32_t i = 0; i < m_Quads.size(); i++)
        m_Quads[i].tint = color;
}

void Text::SetFontHeight(uint32_t fontHeight)
{
    if (m_FontHeight == fontHeight)
        return;
    m_Font.GenFontTexture(fontHeight);
    m_FontHeight = fontHeight;
    SetText(m_Text);
}

void Text::PushToBatch()
{
    for (uint32_t i = 0; i < m_Quads.size(); i++)
        BatchRenderer2D::PushQuad(m_Quads[i]);
}
