#include <cmath>
#include <cstdlib>
#include <ftxui/dom/canvas.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/dom/node.hpp>
#include <ftxui/screen/screen.hpp>
#include <vector>

using namespace std;

int main(void) {
  using namespace ftxui;

  auto c = Canvas(100, 100);

  c.DrawText(0, 0, "This is a canvas", [](Pixel &p) {
    p.foreground_color = Color::Red;
    p.underlined = true;
  });

  // triangle
  c.DrawPointLine(10, 10, 80, 10, Color::Red);
  c.DrawPointLine(80, 10, 80, 40, Color::Blue);
  c.DrawPointLine(80, 40, 10, 10, Color::Green);

  // circle, not filled and filled
  c.DrawPointCircle(30, 50, 20);
  c.DrawPointCircleFilled(40, 40, 10);

  // plot a function
  std::vector<int> ys(1000);
  for (int x = 0; x < 100; x++) {
    ys[x] = int(80 + 20 * cos(x * 0.2));
  }
  for (int x = 0; x < 99; x++) {
    c.DrawPointLine(x, ys[x], x + 1, ys[x + 1], Color::Red);
  }

  auto document = canvas(&c) | border;

  auto screen = Screen::Create(Dimension::Fit(document));
  Render(screen, document);

  screen.Print();
  getchar();

  return EXIT_SUCCESS;
}
