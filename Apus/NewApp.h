#pragma once
#include <App.h>
#include <Sprite.h>

#include <cmath>


bool operator> (ApusCore::Color a, float b) {
	return a.r > b && a.g > b && a.b > b && a.a > b;
}
bool operator< (ApusCore::Color a, float b) {
	return a.r < b && a.g < b && a.b < b && a.a < b;
}
bool operator== (ApusCore::Color a, float b) {
	return a.r == b && a.g == b && a.b == b && a.a == b;
}

bool operator> (ApusCore::Color a, int b) {
	return a.r > b && a.g > b && a.b > b && a.a > b;
}
bool operator< (ApusCore::Color a, int b) {
	return a.r < b && a.g < b && a.b < b && a.a < b;
}
bool operator== (ApusCore::Color a, int b) {
	return a.r == b && a.g == b && a.b == b && a.a == b;
}

class NewApp : public ApusCore::App {
public:
	ApusCore::ScreenOverlay canvas = ApusCore::ScreenOverlay(&window);

	GLFWwindow* win;

	ApusCore::Color* sand;
	int drawRadius = 50;

	ApusCore::Color currentColor = { 1, 1, 1, 1 };
	bool colorSet = false;

	void Start() override {
		auto test = [](lm::vec2 pos, lm::vec2 uv) {
			ApusCore::Color output = { 0, 0, 0, 0 };
			return output;
		};


		AddObject(&canvas);

		int width = 0, height = 0;

		while (width == 0 || height == 0) {
			std::cout << "Enter canvas width: ";
			std::cin >> width;
			std::cout << "Enter canvas height: ";
			std::cin >> height;
		}

		window.ResizeViewport(width, height);
		sand = new ApusCore::Color[window.viewportWidth * window.viewportHeight];
		for (int x = 0; x < window.viewportWidth; x++) {
			for (int y = 0; y < window.viewportHeight; y++) {
				sand[x + window.viewportWidth * y] = { 0, 0, 0, 0};
			}
		}
		canvas.GenerateTexture(test, true);
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
					sand[xpos + window.viewportWidth * ypos] = currentColor;
			}
		}
	}

	float RandomNumber() {
		return rand();
	}

	void Tick() override {
		if (glfwGetMouseButton(win, GLFW_MOUSE_BUTTON_LEFT)) {
			double xpos, ypos;
			glfwGetCursorPos(win, &xpos, &ypos);
			ypos = window.height - ypos;

			xpos = (xpos / window.width) * window.viewportWidth;
			ypos = (ypos / window.height) * window.viewportHeight;

			if (!colorSet) {
				currentColor = { RandomNumber(), RandomNumber(), RandomNumber(), 1 };
				colorSet = true;
			}
			GenerateSand(xpos, ypos);
		}
		else {
			colorSet = false;
		}
		if (glfwGetKey(win, GLFW_KEY_EQUAL)) {
			drawRadius++;
		}
		if (glfwGetKey(win, GLFW_KEY_MINUS)) {
			drawRadius--;
		}
#pragma omp parallel for
		for (int x = 0; x < window.viewportWidth; x++) {
			for (int y = 0; y < window.viewportHeight; y++) {
				if (y == 0 || sand[x + window.viewportWidth * y] == 0)
					continue;
				if (sand[x + window.viewportWidth * (y - 1)] == 0 ) {
					sand[x + window.viewportWidth * (y - 1)] = sand[x + window.viewportWidth * y];
					sand[x + window.viewportWidth * y] = {};
				}
				else if (x > 0 && sand[(x - 1) + window.viewportWidth * (y - 1)] == 0) {
					sand[(x - 1) + window.viewportWidth * (y - 1)] = sand[x + window.viewportWidth * y];
					sand[x + window.viewportWidth * y] = {};
				}
				else if (x < window.viewportWidth - 1 && 
					sand[(x + 1) + window.viewportWidth * (y - 1)] == 0) {
					sand[(x + 1) + window.viewportWidth * (y - 1)] = sand[x + window.viewportWidth * y];
					sand[x + window.viewportWidth * y] = {};
				}
			}
		}

		auto generator = [this](lm::vec2 pos, lm::vec2 uv, ApusCore::Color previous) {
			return sand[(int)(pos.x + window.viewportWidth * pos.y)];
		};
		canvas.RegenerateTexture(generator);

		App::Tick();
	}

	void LateTick() override {
		if (glfwGetKey(win, GLFW_KEY_R)) {
			renderer.SaveRender("testing/Render.png", ApusCore::jpeg);
		}
	}

	void End() override {
		delete[] sand;
		App::End();
	}
};