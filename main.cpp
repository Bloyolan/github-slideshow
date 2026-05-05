

//Using SDL, SDL_image, standard IO, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm> // for std::shuffle
#include <random>    // for std::default_random_engine
#include <chrono>    // for seed
#include<iostream>
#include<sdl_timer.h>


//Function to declare a set of vector so we can hold the a deck of cards
// Create the list of filenames
std::vector<std::string> createFileList()
{
	std::vector<std::string> files;
	files.reserve(52);
	for (int i = 1; i <= 52; ++i) {
		files.push_back("c:/cards2/" + std::to_string(i) + ".png");
	}
	return files;
}


// Function to shuffle the list
void shuffleFiles(std::vector<std::string>& files)
{
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::shuffle(files.begin(), files.end(), std::default_random_engine(seed));
}


/*When you need to get the filename :
std::string getFilename(int number) {
	return std::to_string(number) + ".png";
}*/

// Function to print the filenames
void printFileList(const std::vector<std::string>& files)
{
	for (const auto& filename : files) {
		std::cout << filename << std::endl;
	}
}





int main(int argc, char* args[])
{
	auto fileList = createFileList(); // Your function to create the list
	//shuffleFiles(fileList);           // Your function to shuffle the list

	printFileList(fileList);          // Call the print function

	SDL_Delay(10000);

	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);

	SDL_Window* window = SDL_CreateWindow("Image Sequence",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 900, 480, 0);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	
	int index = 0;
	while (index < fileList.size())
	{

		SDL_Surface* surface = IMG_Load(fileList[index].c_str());
		if (!surface) {
			std::cerr << "Failed to load " << fileList[index] << " Error: " << IMG_GetError() << std::endl;
			continue;
		}

		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface); // free surface after creating texture

		if (!texture) {
			std::cerr << "Failed to create texture from " << fileList[index] << " Error: " << SDL_GetError() << std::endl;
			continue;
		}

		// Clear renderer
		SDL_RenderClear(renderer);
		// Copy texture to renderer
		SDL_RenderCopy(renderer, texture, NULL, NULL);
		SDL_RenderPresent(renderer);

		SDL_Delay(1); // Wait 1 second before showing next image
		index++;
		SDL_DestroyTexture(texture);
	}


		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);

		IMG_Quit();
		SDL_Quit();

		


		return 0;
	}
