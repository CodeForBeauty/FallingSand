#include "Renderer.h"
#include "stb/stb_image_write.h"


#include<iostream>

void ApusCore::Renderer::Destroy() {
	for (int i = 0; i < sprites.size(); i++) {
		sprites[i]->Destroy();
	}
}

void ApusCore::Renderer::Render(lm::mat4 proj, lm::mat4 cam) {
	glClearColor(background.x, background.y, background.z, background.w);
	glClear(GL_COLOR_BUFFER_BIT);

	for (int i = 0; i < sprites.size(); i++) {
		sprites[i]->Draw(proj, cam);
	}
}

void ApusCore::Renderer::SetBackground(float x, float y, float z, float w) {
	background = { x, y, z, w };
}

void ApusCore::Renderer::SaveRender(const char* outputPath, ApusCore::ImageType imgType) {
	int stride = window->width * 3;
	int width = (stride % 4) ? window->width + (4 - stride % 4) : window->width;
	stride += (stride % 4) ? (4 - stride % 4) : 0;

	unsigned char* data = new unsigned char[width * window->height * 3];
	glReadPixels(0, 0, width, window->height, GL_RGB, GL_UNSIGNED_BYTE, data);

	switch (imgType)
	{
	case ApusCore::png:
		stbi_write_png(outputPath, width, window->height, 3, data, stride);
		break;
	case ApusCore::jpeg:
		stbi_write_jpg(outputPath, width, window->height, 3, data, 100);
		break;
	case ApusCore::bmp:
		stbi_write_bmp(outputPath, width, window->height, 3, data);
		break;
	case ApusCore::tga:
		stbi_write_tga(outputPath, width, window->height, 3, data);
		break;
	}

	delete[] data;
}
