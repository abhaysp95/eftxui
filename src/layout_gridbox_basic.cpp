#include <cstdlib>
#include <ftxui/dom/elements.hpp>
#include <ftxui/dom/node.hpp>
#include <ftxui/screen/screen.hpp>

using namespace std;

int main(void) {
  using namespace ftxui;

  auto cell = [](const char *t) { return text(t) | border; };
  auto cell_center = [](const char *t) { return center(text(t)) | border; };

  auto document = gridbox({
      {
          // these cell go horizontally
          cell("north-west"),
          cell_center("north"),
          cell("north-east"),
      }, // one row completed for grid
      {
          cell_center("center-west"),
          gridbox({{
                       cell("center-north-west"),
                       cell("center-north-east"),
                   },
                   {
                       cell("center-south-west"),
                       cell("center-south-east"),
                   }}),
          cell_center("center-east"), // this sets text vertically center too
      },
      {
          cell("south-west"),
          cell_center("south"),
          cell("south-east"),
      },
  });

  auto screen = Screen::Create(Dimension::Fit(document));
  Render(screen, document);
  screen.Print();

  return EXIT_SUCCESS;
}
