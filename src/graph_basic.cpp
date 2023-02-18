#include <ftxui/dom/elements.hpp>
#include <ftxui/dom/node.hpp>
#include <ftxui/screen/screen.hpp>
#include <functional>
#include <iostream>
#include <math.h>
#include <thread>
#include <vector>
#include <chrono>

class Graph {
	private:
		int shift{};
	public:
		std::vector<int> operator()(int width, int height) const {
			std::vector<int> output(width);
			for (int i = 0; i < width; ++i) {
				float v = 0;
				v += 0.1f * sin((i + this->shift) * 0.1f);
				v += 0.2f * sin((i + this->shift + 10) * 0.15f);
				v += 0.1f + sin((i + this->shift) * 0.03f);
				v *= height;
				v += 0.5f * height;
				output[i] = static_cast<int>(v);
			}
			return output;
		}
		void operator++(int) {
			this->shift++;
		}
};

std::vector<int> triangle(int width, int height) {
	std::vector<int> output(width);
	for (size_t i = 0; i < width; ++i) {
		output[i] = i % (height - 4) + 2;
	}

	return output;
}

int main(void) {
	using namespace ftxui;
	using namespace std::chrono_literals;

	Graph my_graph;

	std::string reset_position{};
	for (size_t i = 0; ; ++i) {
		auto document = hbox({
				vbox({
						graph(std::ref(my_graph)),
						separator(),
						graph(triangle) | inverted | bgcolor(Color::CadetBlue),
						// graph(triangle) | bgcolor(Color::CadetBlue),
				}) | flex,
				separator(),
				vbox({
						graph(std::ref(my_graph)) | color(Color::BlueLight),
						separator(),
						graph(std::ref(my_graph)) | color(Color::RedLight),
						separator(),
						graph(std::ref(my_graph)) | color(Color::YellowLight),
					}) | flex,
				});

		document |= border;

		const int min_width = 40;
		document |= size(HEIGHT, GREATER_THAN, min_width);

		auto screen = Screen::Create(Dimension::Full(), Dimension::Fit(document));
		Render(screen, document);
		std::cout << reset_position;
		screen.Print();
		reset_position = screen.ResetPosition();

		const auto sleep_time = 0.03s;
		std::this_thread::sleep_for(sleep_time);
		my_graph++;
		// my_graph.shift++;
	}

	return 0;
}
