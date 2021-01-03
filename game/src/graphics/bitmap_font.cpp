#include "bitmap_font.hpp"

BitmapFont::BitmapFont(std::shared_ptr<Texture> texture, const CharacterSet& charset):
	texture(texture),
	charset(charset){}

bool BitmapFont::getGlyph(Character c, GlyphData& glyph) {
	auto it = charset.find(c);

	if (it != charset.end()) {
		glyph = it->second;
		return true;
	}

	return false;
}

Text::Text(std::shared_ptr<BitmapFont> font):
	font(font){}

void Text::setText(const std::string& text){
	float x = 0.0f;
	float y = 0.0f;
	GlyphData glyph;

	this->text = text;

	vertices.clear();
	indices.clear();

	for (const BitmapFont::Character& c : text) {
		if (font->getGlyph(c, glyph)) {
			glyphVertices(x, y, glyph);
			x += glyph.w;
		}
	}
}

void Text::glyphVertices(float x, float y, const GlyphData& glyph) {
	size_t startIdx = vertices.size();

	std::shared_ptr<Texture> texture = font->getTexture();

	float u0 = glyph.x / texture->getWidth();
	float v0 = glyph.y / texture->getHeight();
	float u1 = (glyph.x + glyph.w) / texture->getWidth();
	float v1 = (glyph.y + glyph.h) / texture->getHeight();

	vertices.push_back({x, y, 0, u0, v0});
	vertices.push_back({ x + glyph.w, y, 0, u1, v0});
	vertices.push_back({ x + glyph.w, y + glyph.h, 0, u1, v1 });
	vertices.push_back({ x, y + glyph.h, 0, u0, v1});

	indices.push_back(startIdx);
	indices.push_back(startIdx + 1);
	indices.push_back(startIdx + 2);
	indices.push_back(startIdx + 2);
	indices.push_back(startIdx + 3);
	indices.push_back(startIdx);
}