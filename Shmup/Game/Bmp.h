#pragma once

#include <stdio.h>
#include <vector>

class Bmp
{
public:
	bool LoadFromFile(const char* file)
	{
		// set bmp format constants
		const int headerSize = 54;
		const int pixelSize = 4;

		// open file and read header
		FILE* f = fopen(file, "rb");
		if (f == NULL)
		{
			printf("Failed to open bmp file");
			return false;
		}

		unsigned char info[headerSize];
		fread(info, sizeof(unsigned char), headerSize, f);

		// extract width and height of bmp
		int width = *(int*)&info[18];
		int height = *(int*)&info[22];

		// read the pixels and store them in data
		int size = pixelSize * width * height;
		unsigned char* data = new unsigned char[size];
		fread(data, sizeof(unsigned char), size, f);
		fclose(f);

		// pack rgba values into an int and store into pixels vector
		// convert bgra to rgba
		// covert bottom-top row order to top-bottom row order
		const int numPixels = width * height;
		m_pixels.reserve(numPixels);

		int rowStart;
		for (int i = 0; i < height; ++i)
		{
			// starts at the first of the last row, ends at the front of the first row
			rowStart = size - (i+1) * width * pixelSize;
			for (int j = 0; j < width * pixelSize; j += pixelSize)
			{
				// get the index for each element of the pixel
				unsigned int r, g, b, a;
				b = rowStart + j;
				g = rowStart + j + 1;
				r = rowStart + j + 2;
				a = rowStart + j + 3;
				
				// pack chars into int
				unsigned int packed = data[r] << 24 | data[g] << 16 | data[b] << 8 | data[a];

				// add to pixel vector
				m_pixels.push_back(packed);
			}
		}
		
		// assign width and height
		m_width = width;
		m_height = height;

		// free data
		delete[] data;

		return true;
	}

	void ToRgba(unsigned int packed, unsigned char& r, unsigned char& g, unsigned char& b, unsigned char& a)
	{
		r = (packed & rmask) >> 24;
		g = (packed & gmask) >> 16;
		b = (packed & bmask) >> 8;
		a = packed & amask;
	}

	unsigned int& operator[] (int x)
	{
		return m_pixels[x];
	}

	int Width() const
	{
		return m_width;
	}

	int Height() const
	{
		return m_height;
	}

protected:
	const unsigned int rmask = 0xFF000000;
	const unsigned int gmask = 0x00FF0000;
	const unsigned int bmask = 0x0000FF00;
	const unsigned int amask = 0x000000FF;

protected:
	std::vector<unsigned int> m_pixels;
	int m_width, m_height;
};