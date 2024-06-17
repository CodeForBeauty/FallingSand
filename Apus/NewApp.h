#pragma once
#include <App.h>
#include <Sprite.h>

#include <cmath>


class NewApp : public ApusCore::App {
public:
	ApusCore::ScreenOverlay canvas = ApusCore::ScreenOverlay(&window);

	GLFWwindow* win;

	bool* sand;
	int drawRadius = 10;

	void Start() override {
		auto test = [](lm::vec2 pos, lm::vec2 uv) {
			ApusCore::Color output = { 0, 0, 0, 1 };
			return output;
		};


		AddObject(&canvas);

		window.ResizeViewport(150, 150);
		std::cout << window.viewportWidth;
		sand = new bool[window.viewportWidth * window.viewportHeight];
		for (int x = 0; x < window.viewportWidth; x++) {
			for (int y = 0; y < window.viewportHeight; y++) {
				sand[x + window.viewportWidth * y] = false;
			}
		}
		canvas.GenerateTexture(test, false);
		win = window.GetWindow();
	}

	void GenerateSand(int x, int y) {
		for (int i = -drawRadius; i < drawRadius; i++) {
			for (int j = -drawRadius; j < drawRadius; j++) {
				int xpos = x + i;
				int ypos = y + j;
				if ((i * i + j * j) >= drawRadius)
					continue;
				if (xpos >= 0 && ypos >= 0 && xpos < window.viewportWidth && ypos < window.viewportHeight)
					sand[xpos + window.viewportWidth * ypos] = true;
			}
		}
	}

	void Tick() override {
		if (glfwGetMouseButton(win, GLFW_MOUSE_BUTTON_LEFT)) {
			double xpos, ypos;
			glfwGetCursorPos(win, &xpos, &ypos);
			ypos = window.height - ypos;

			xpos = (xpos / window.width) * window.viewportWidth;
			ypos = (ypos / window.height) * window.viewportHeight;

			GenerateSand(xpos, ypos);
		}

		for (int x = 0; x < window.viewportWidth; x++) {
			for (int y = 0; y < window.viewportHeight; y++) {
				if (y == 0 || !sand[x + window.viewportWidth * y])
					continue;
				if (!sand[x + window.viewportWidth * (y - 1)]) {
					sand[x + window.viewportWidth * y] = false;
					sand[x + window.viewportWidth * (y - 1)] = true;
				}
				else if (x > 0 && !sand[(x - 1) + window.viewportWidth * (y - 1)]) {
					sand[x + window.viewportWidth * y] = false;
					sand[(x - 1) + window.viewportWidth * (y - 1)] = true;
				}
				else if (x < window.viewportWidth - 1 && !sand[(x + 1) + window.viewportWidth * (y - 1)]) {
					sand[x + window.viewportWidth * y] = false;
					sand[(x + 1) + window.viewportWidth * (y - 1)] = true;
				}
			}
		}

		auto generator = [this](lm::vec2 pos, lm::vec2 uv, ApusCore::Color previous) {
			ApusCore::Color output;
			if (sand[(int)(pos.x + window.viewportWidth * pos.y)]) {
				output = { 1, 1, 1, 1 };
			}
			else {
				output = { 0, 0, 0, 1 };
			}
			return output;
		};
		canvas.RegenerateTexture(generator);

		App::Tick();
	}

	void LateTick() override {
	}

	void End() override {
		App::End();
	}
};