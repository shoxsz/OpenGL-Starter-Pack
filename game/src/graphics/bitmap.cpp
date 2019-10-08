#include "bitmap.hpp"

#include <lodepng.h>

std::unique_ptr<Bitmap> Bitmap::createFromFile(const std::string& file){
	std::vector<unsigned char> imageBuffer;
	lodepng::State state;
	bool alpha = false;

	std::unique_ptr<Bitmap> bitmap(new Bitmap());

	if (lodepng::load_file(imageBuffer, file)) {
		return nullptr;
	}

	/*state.decoder.color_convert = 1;
	state.info_raw.colortype = LCT_RGBA;
	state.info_raw.bitdepth = 32;*/

	if (lodepng::decode(bitmap->pixels, bitmap->width, bitmap->height, state, imageBuffer)) {
		return nullptr;
	}

	return bitmap;
}

void Bitmap::setPixel(unsigned int x, unsigned int y, const Pixel& pixel){
	x *= 4;
	y *= 4;

	memcpy((pixels.data() + (y * width + x)), &pixel, sizeof(Pixel));
}

Pixel Bitmap::getPixel(unsigned int x, unsigned int y) const{
	x *= 4;
	y *= 4;

	return *((Pixel*)(pixels.data() + (y * width + x)));
}