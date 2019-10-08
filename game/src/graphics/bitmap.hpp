#ifndef _BITMAP_HPP_
#define _BITMAP_HPP_

#include <vector>
#include <string>
#include <memory>

struct Pixel{
	unsigned char r, g, b, a;
};

class Bitmap{
public:
	static std::unique_ptr<Bitmap> createFromFile(const std::string& file);

	void setPixel(unsigned int x, unsigned int y, const Pixel& pixel);
	Pixel getPixel(unsigned int x, unsigned int y) const;

	const unsigned char* getData() const { return pixels.data(); }
	unsigned int getWidth() const { return width; }
	unsigned int getHeight() const { return height; }
private:
	Bitmap(){}
	std::vector<unsigned char> pixels;
	unsigned int width, height;
};

#endif