#include <SDL.h>
#include <vector>
#include <iostream>
int cnt;
bool live;
// level data (if a cell is turned on at the beginning)
const int lvldata[10] = {
	1,1,
	1,2,
	1,3,
	1,4,
	1,5
};
// neighbour data to check for existing cells nearby.
const int chkneighbour[16] = {
	-1,-1,
	-1, 0,
	-1, 1,
	 0,-1,
	 0, 1,
	 1,-1,
	 1, 0,
	 1, 1
};
// main loop
int main(int argc, char* argv[]) {
	// initializing
	std::vector<std::vector<int>> data;
	std::vector<std::vector<int>> datachange;
	for (int i = 0; i < sizeof(lvldata) / 4; i += 2) {
		data.push_back({lvldata[i],lvldata[i + 1]});
	}
	SDL_INIT_EVERYTHING;
	SDL_Window* window;
	SDL_Renderer* render;
	window = SDL_CreateWindow("game of life", 500, 500, 500, 500, NULL);
	render = SDL_CreateRenderer(window, 0, NULL);
	SDL_Rect rect;
	rect.h = 10;
	rect.w = 10;
	while (true) {
		// draw cells on the screen
		SDL_SetRenderDrawColor(render, 255, 0, 0, 255);
		SDL_Event event;
		for (int i = 0; i < data.size(); i++) {
			rect.x = data[i][0] * 10;
			rect.y = data[i][1] * 10;
			SDL_RenderDrawRect(render, &rect);
		}
		// algorythm to check if a cell dies or reproduce
		for (int i = 0; i < 2500; i++) {
			cnt = 0;
			live = 0;
			for (int i2 = 0; i2 < data.size(); i2++) {
				for (int i3 = 0; i3 < sizeof(chkneighbour) / 4; i3 += 2) {
					if (i / 50 == data[i2][0] + chkneighbour[i3] && i % 50 == data[i2][1] + chkneighbour[i3 + 1]) {
						cnt += 1;
					}
				}
				if (i / 50 == data[i2][0] && i % 50 == data[i2][1]) {
					live = 1;
				}
			}
			if (cnt != 0) {
				datachange.push_back({ i / 50,i % 50,cnt ,live });
			}
		}
		//random stuff
		SDL_PollEvent(&event);
		SDL_RenderPresent(render);
		data.clear();
		//refresh cell data
		for (int i = 0; i < datachange.size(); i++) {
			if (datachange[i][2] > 1 && datachange[i][2] < 4 && datachange[i][3] == 1) {
				data.push_back({ datachange[i][0],datachange[i][1] });
			}
			else if (datachange[i][2] == 3 && datachange[i][3] == 0) {
				data.push_back({ datachange[i][0],datachange[i][1] });
			}
		}
		datachange.clear();
		SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
		SDL_RenderClear(render);
	}
	return 0;
}
