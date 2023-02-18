#include <cstdlib>
#include <ftxui/screen/color.hpp>
#include <ftxui/screen/screen.hpp>
#include <iostream>

using namespace std;

int main(void) {
using namespace ftxui;
	auto screen = Screen::Create(Dimension::Fixed(32), Dimension::Fixed(10));

	auto& pixel = screen.PixelAt(9, 9);
	pixel.character = U'A';
	pixel.bold = true;
	pixel.foreground_color = Color::Blue;

	cout << screen.ToString() << endl;

	return EXIT_SUCCESS;
}
