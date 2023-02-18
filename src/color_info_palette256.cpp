#include <cstdlib>
#include <ftxui/dom/elements.hpp>
#include <ftxui/dom/node.hpp>
#include <ftxui/screen/color.hpp>
#include <ftxui/screen/color_info.hpp>
#include <ftxui/screen/screen.hpp>
#include <vector>

// don't see the point of using '.ipp' file extension here
#include "./inc/color_info_sorted_2d.ipp"

using namespace ftxui;

int main(void) {
	std::vector<std::vector<ftxui::ColorInfo>> info_columns = ColorInfoSorted2D();

	// draw every columns
	Elements columns_elements;
	for (auto& column: info_columns) {
		Elements column_elements;
		for (auto& it: column) {
			column_elements.push_back(hbox({
						text("    ") | bgcolor(Color(Color::Palette256(it.index_256))),
						separator(),
						text(it.name),
						}));
		}
		columns_elements.push_back(vbox(std::move(column_elements)));
	}
	auto document = hbox(std::move(columns_elements));

	auto screen = Screen::Create(Dimension::Full(), Dimension::Fit(document));
	Render(screen, document);

	screen.Print();

	return EXIT_SUCCESS;
}
