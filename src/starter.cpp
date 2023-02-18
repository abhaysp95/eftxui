#include <cstdlib>
#include <ftxui/dom/node.hpp>
#include <iostream>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>

using namespace std;

int main(void) {
	using namespace ftxui;

	// Define the docuent
	Element document = hbox({
				text("left") | border,
				text("middle") | border | flex,
				text("right") | border,
			});

	auto screen = Screen::Create(
				Dimension::Full(),  // width
				Dimension::Fit(document)  // Height
			);
	Render(screen, document);
	screen.Print();

	return EXIT_SUCCESS;
}
