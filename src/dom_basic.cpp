#include <cstdlib>
#include <ftxui/dom/elements.hpp>
#include <ftxui/dom/node.hpp>
#include <ftxui/screen/screen.hpp>

using namespace std;

int main(void) {
	using namespace ftxui;

	Element document =
		vbox({
				text("The window") | bold | color(Color::Blue),
				gauge(0.5) | border,
				text("The footer")
			});

	// add a border, by calling the `ftxui::border` decorator function
	document = border(document);

	// add another border, using the pipe operator
	document = document | border;

	// add another border, using the |= operator
	document |= border;

	auto screen = Screen::Create(
			Dimension::Full(),
			Dimension::Fit(document));

	Render(screen, document);
	screen.Print();

	return EXIT_SUCCESS;
}
