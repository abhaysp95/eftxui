#include <cstdio>
#include <cstdlib>
#include <ftxui/dom/elements.hpp>
#include <ftxui/dom/node.hpp>
#include <ftxui/screen/screen.hpp>

int main(void) {
	using namespace ftxui;

	auto document = vbox({
			hbox({
					text("north-west"),
					filler(),
					text("north-east"),
					}),
			filler(),
			hbox({
					filler(),
					text("center"),
					filler(),
					}),
			filler(),
			hbox({
					text("south-west"),
					filler(),
					text("south-east"),
					}),
			});

	auto screen = Screen::Create(Dimension::Full());
	Render(screen, document);
	screen.Print();

	getchar();

	return EXIT_SUCCESS;
}
