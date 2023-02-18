#include <algorithm>
#include <cstddef>
#include <ftxui/screen/color.hpp>
#include <ftxui/screen/color_info.hpp>
#include <vector>

using namespace ftxui;

using namespace std;

vector<vector<ColorInfo>> ColorInfoSorted2D() {

	// acquire the color information for the pallete256
	vector<ColorInfo> info_gray;
	vector<ColorInfo> info_color;

	for (size_t i = 16; i < 256; ++i) {
		ColorInfo info = GetColorInfo(Color::Palette256(i));
		if (0 == info.saturation) {
			info_gray.push_back(info);
		}
		else {
			info_color.push_back(info);
		}
	}

	// sort info_color by hue
	sort(info_color.begin(), info_color.end(),
			[](const ColorInfo& a, const ColorInfo& b) {
				return a.hue < b.hue;
			});

	// make 8 columns, one gray and seven colored
	vector<vector<ColorInfo>> info_columns(8);  // outer vector of size 8
	info_columns[0] = info_gray;
	for (size_t i = 0; i < info_color.size(); ++i) {
		info_columns[1 + 7 * i / info_color.size()].push_back(info_color[i]);
	}

	// minimize discontinuties for every columns
	for (auto& column: info_columns) {
		std::sort(column.begin(), column.end(),
				[](const ColorInfo& a, const ColorInfo& b) {
					return a.value < b.value;
				});

		for (int i = 0; i < int(column.size()) - 1; ++i) {
			int best_index = i + 1;
			int best_distance = 255 * 255 * 3;
			for (int j = i + 1; j < column.size(); ++j) {
				int dx = column[i].red - column[j].red;
				int dy = column[i].green - column[j].green;
				int dz = column[i].blue - column[j].blue;
				int distance = dx * dx + dy * dy + dz * dz;
				if (best_distance > distance) {
					best_distance = distance;
					best_index = j;
				}
			}
			std::swap(column[i + 1], column[best_index]);
		}
	}

	return std::move(info_columns);
}
