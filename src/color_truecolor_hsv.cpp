#include <algorithm>
#include <cstdlib>
#include <ftxui/dom/elements.hpp>
#include <ftxui/dom/node.hpp>
#include <ftxui/screen/screen.hpp>

int main(void) {

	using namespace ftxui;

	int saturation = 255;
	Elements array;
	for (size_t value = 0; value < 255; value += 20) {
		Elements line;
		for (int hue = 0; hue < 255; hue +=2 ) {
			line.push_back(text("▀")
					| color(Color::HSV(hue, saturation, value))
					| bgcolor(Color::HSV(hue, saturation, value + 10)));
		}
		array.push_back(hbox(std::move(line)));
	}

	auto document = vbox(std::move(array));

	auto screen = Screen::Create(Dimension::Full(),
			Dimension::Fit(document));
	Render(screen, document);
	screen.Print();

	return EXIT_SUCCESS;
}
