#ifndef _BITMAP_FONT_HPP_
#define _BITMAP_FONT_HPP_

#include <memory>
#include <map>
#include <string>

#include "bitmap.hpp"
#include "texture.hpp"
#include "sprite_batcher.hpp"

struct GlyphData{
	float x, y, w, h;
};

class BitmapFont{
public:
	typedef char Character;
	typedef std::map<Character, GlyphData> CharacterSet;

	BitmapFont(std::shared_ptr<Texture> texture, const CharacterSet& charset);
	std::shared_ptr<Texture> getTexture()const { return texture; }

	bool getGlyph(Character c, GlyphData& glyph);

private:
	std::shared_ptr<Texture> texture;
	std::map<Character, GlyphData> charset;
};

class Text {
public:
	Text(std::shared_ptr<BitmapFont> font);
	
	void setText(const std::string& text);
	const std::string& getText() const { return text; }

	const std::vector<SpriteBatcher::VertexData> getVertices()const { return vertices; }
	const std::vector<unsigned int> getIndices()const { return indices; }

	std::shared_ptr<BitmapFont> getFont() const { return font; }

private:
	void glyphVertices(float x, float y, const GlyphData& glyph);

	std::shared_ptr<BitmapFont> font;
	std::string text;
	std::vector<SpriteBatcher::VertexData> vertices;
	std::vector<unsigned int> indices;
};

#endif