#include <cstdlib>
#include <ftxui/dom/elements.hpp>
#include <ftxui/dom/node.hpp>
#include <ftxui/screen/screen.hpp>

int main(void) {
  using namespace ftxui;

  int saturation = 255;
  Elements red_line;
  Elements green_line;
  Elements blue_line;
  Elements cyan_line;
  Elements magenta_line;
  Elements yellow_line;

  for (size_t value = 0; value < 255; value += 3) {
    int v = value * value / 255;
    red_line.push_back(text(" ") | bgcolor(Color::RGB(v, 0, 0)));
    green_line.push_back(text(" ") | bgcolor(Color::RGB(0, v, 0)));
    blue_line.push_back(text(" ") | bgcolor(Color::RGB(0, 0, v)));
    cyan_line.push_back(text(" ") | bgcolor(Color::RGB(0, v, v)));
    magenta_line.push_back(text(" ") | bgcolor(Color::RGB(v, 0, v)));
    yellow_line.push_back(text(" ") | bgcolor(Color::RGB(v, v, 0)));
  }

  auto document = vbox({
      window(
          text("Primary colors"),
          vbox({
              hbox({text("Red red_line     :"), hbox(std::move(red_line))}),
              hbox({text("Green red_line   :"), hbox(std::move(green_line))}),
              hbox({text("Blue red_line	   :"), hbox(std::move(blue_line))}),
          })),
      window(
          text("Secondary colors"),
          vbox({
              hbox({text("cyan line       :"), hbox(std::move(cyan_line))}),
              hbox({text("magenta line    :"), hbox(std::move(magenta_line))}),
              hbox({text("yellow line     :"), hbox(std::move(yellow_line))}),
          })),
  });

  auto screen = Screen::Create(Dimension::Full(), Dimension::Fit(document));
  Render(screen, document);

  screen.Print();

  return EXIT_SUCCESS;
}
