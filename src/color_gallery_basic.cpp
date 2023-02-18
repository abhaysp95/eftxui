#include <cstdlib>
#include <ftxui/dom/elements.hpp>
#include <ftxui/dom/node.hpp>
#include <ftxui/screen/color.hpp>
#include <ftxui/screen/color_info.hpp>
#include <ftxui/screen/screen.hpp>
#include <ftxui/screen/terminal.hpp>
#include <vector>

#include "./inc/color_info_sorted_2d.ipp"

using namespace std;

int main(void) {
  using namespace ftxui;

  auto basic_color_display =
      vbox(text("16 color pallete:"), separator(),
           hbox(vbox(color(Color::Default, text("Default")),
                     color(Color::Black, text("Black")),
                     color(Color::GrayDark, text("GrayDark")),
                     color(Color::GrayLight, text("GrayLight")),
                     color(Color::White, text("White")),
                     color(Color::Blue, text("Blue")),
                     color(Color::BlueLight, text("BlueLight")),
                     color(Color::Cyan, text("Cyan")),
                     color(Color::CyanLight, text("CyanLight")),
                     color(Color::Green, text("Green")),
                     color(Color::GreenLight, text("GreenLight")),
                     color(Color::Magenta, text("Magenta")),
                     color(Color::MagentaLight, text("MagentaLight")),
                     color(Color::Red, text("Red")),
                     color(Color::RedLight, text("RedLight")),
                     color(Color::Yellow, text("Yellow")),
                     color(Color::YellowLight, text("YellowLight"))),
                vbox(bgcolor(Color::Default, text("Default")),
                     bgcolor(Color::Black, text("Black")),
                     bgcolor(Color::GrayDark, text("GrayDark")),
                     bgcolor(Color::GrayLight, text("GrayLight")),
                     bgcolor(Color::White, text("White")),
                     bgcolor(Color::Blue, text("Blue")),
                     bgcolor(Color::BlueLight, text("BlueLight")),
                     bgcolor(Color::Cyan, text("Cyan")),
                     bgcolor(Color::CyanLight, text("CyanLight")),
                     bgcolor(Color::Green, text("Green")),
                     bgcolor(Color::GreenLight, text("GreenLight")),
                     bgcolor(Color::Magenta, text("Magenta")),
                     bgcolor(Color::MagentaLight, text("MagentaLight")),
                     bgcolor(Color::Red, text("Red")),
                     bgcolor(Color::RedLight, text("RedLight")),
                     bgcolor(Color::Yellow, text("Yellow")),
                     bgcolor(Color::YellowLight, text("YellowLight")))));

  auto palette_256_color_display = text("256 colors palette:");
  {
    vector<vector<ColorInfo>> info_columns = ColorInfoSorted2D();
    Elements columns;
    for (auto &column : info_columns) {
      Elements column_elements;
      for (auto &it : column) {
        column_elements.push_back(
            text("    ") | bgcolor(Color(Color::Palette256(it.index_256))));
      }
      columns.push_back(hbox(std::move(column_elements)));
    }
    palette_256_color_display = vbox(
        {palette_256_color_display, separator(), vbox(std::move(columns))});
  }

  // true color display
  auto true_color_display = text("TrueColors: 24bits");
  {
    const int max_value = 255;
    const int value_increment = 8;
    const int hue_increment = 6;
    int saturation = max_value;

    Elements array;
    for (size_t value = 0; value < max_value; value += 2 * value_increment) {
      Elements line;
      for (size_t hue = 0; hue < max_value; hue += hue_increment) {
        line.push_back(
            text("▀") | color(Color::HSV(hue, saturation, value)) |
            bgcolor(Color::HSV(hue, saturation, value + value_increment)));
      }
      array.push_back(hbox(std::move(line)));
    }
    true_color_display = vbox({
        true_color_display,
        separator(),
        vbox(std::move(array)),
    });
  }

  auto terminal_info =
      vbox({
          Terminal::ColorSupport() >= Terminal::Color::Palette16
              ? text(" 16 color palette support : Yes")
              : text(" 16 color palette support : NO"),
          Terminal::ColorSupport() >= Terminal::Color::Palette256
              ? text("256 color palette support : Yes")
              : text("256 color palette support : No"),
          Terminal::ColorSupport() >= Terminal::Color::TrueColor
              ? text("    True color support : Yes")
              : text("    True color support : No"),
      }) |
      border;

  auto document = vbox({hbox({
                            basic_color_display,
                            text(" "),
                            palette_256_color_display,
                            text(" "),
                            true_color_display,
                        }),
                        terminal_info});

  auto screen = Screen::Create(Dimension::Full(), Dimension::Fit(document));
  Render(screen, document);

  screen.Print();

  return EXIT_SUCCESS;
}
