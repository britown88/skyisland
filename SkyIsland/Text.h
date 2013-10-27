#pragma once

#include "ft2build.h"
#include FT_FREETYPE_H
#include FT_GLYPH_H 

#include "Vector.h"
#include <memory>
#include <string>
#include <unordered_map>
#include "Color.h"

struct TexturePattern
{
   Float2 offset;
   Float2 size;
};


struct TextFont
{
   TextFont() {}
   TextFont(std::string fontFile_in, int height_in)
      : fontFile(std::move(fontFile_in)), height(height_in)
   {

   }
   bool operator==(TextFont const& rhs) const
   {
      if (rhs.fontFile != fontFile) return false;
      if (rhs.height   != height)   return false;
      return true;
   }
   std::string fontFile;
   int height;
};

struct TextString
{
   TextString() {}
   TextString(Float2 const& pos_in, std::string text_in, Colorf const& color_in, std::shared_ptr<TextFont> font_in)
      : pos(pos_in), text(std::move(text_in)), color(color_in), font(font_in)
   {

   }
   Float2 pos;
   std::string text;
   Colorf color;
   std::shared_ptr<TextFont> font;
};

class FontHasher
{
public:
   size_t operator()(TextFont const& font) const
   {
      size_t hashVal = std::hash<std::string>()(font.fontFile);
      hashVal = (hashVal << 5) + hashVal + std::hash<int>()(font.height);
      return hashVal;
   }
};

class FontEngine;

class Font
{
   unsigned int m_textures[128];
   TextFont m_font;
   FontEngine* m_fontEngine;
   unsigned int m_displayList;
   float m_widths[128];
public:
   Font(TextFont font, FontEngine* fontEngine);
   void buildFont();
   unsigned int getDisplayList() const;
   float getCharWidth(char ch) const;
};

class FontEngine
{
   //Create and initilize a freetype font library.
   FT_Library m_library;
   std::unordered_map<TextFont, std::unique_ptr<Font>, FontHasher> m_fontMap;
public:
   static const int ID = 1719627241;
   FontEngine();
   ~FontEngine();
   Font& getFont(TextFont const& font);
   FT_Library GetLibrary();
};