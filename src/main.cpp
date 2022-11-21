/**
 * @file life_game.cpp
 *
 * @description
 * This program simulates the Conway's Game of Life.
 * It reads a initial game configuration from a input file and
 * keeps updating it, if the user so whishes.
 *
 * @author	Selan R dos Santos, <selan.rds@gmail.com>
 * @date	2015, updated 2015-04-03
 *
 * @remark On 2015-09-19 changed the way stability is verified.
 * In the previous version we just looked back one configuration and compare it
 * with the current configuration.
 * Now, the stability may span more than one configuration. Because of that we
 * need to keep track of all configurations and check whether the current configuration
 * has already been generated. If this is the case, the game has reached stability and
 * must stop.
 */

#include <cstdlib>  // EXIT_SUCCESS
#include <iostream>
#include <iomanip>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <thread>

#include "../lib/tip.h"
#include "life.h"

int main(int argc, char* argv[])
{
    int rows, columns;
    char alive_char;
    std::string config_path = argc == 1 ? ".config/glife.ini" : argv[1];

    TIP reader{ config_path };
 
    // Check for any parser error.
    if (not reader.parsing_ok()) {
        std::cerr << ">> Sorry, parser failed with message: " << reader.parser_error_msg() << "\n";
        return EXIT_FAILURE;
    }

    auto fps = reader.get_int("text", "fps"); // Tries to get info of how much fps the app will run.
    auto max_gen = reader.get_int("ROOT", "max_gen"); // Tries to get max generations number from config file.
    auto input_cfg = reader.get_str("ROOT", "input_cfg"); // Tries to get info of where the data is stored.
    auto create_img = reader.get_bool("image", "generate_image"); // Tries to get whether images should or not be generated.
    auto bk_color = reader.get_str("image", "bkg"); // Tries to get the background color.
    auto alive_color = reader.get_str("image", "alive"); // Tries to get color of alive cell.
    auto block_size = reader.get_int("image", "block_size"); // Tries to get the block size.
    auto path = reader.get_str("image", "path"); // Tries to get the path in which the image will be saved.
    bool unstoppable = max_gen == 0; // Verifies if a max_gen exists.

    std::transform(bk_color.begin(), bk_color.end(), bk_color.begin(), ::tolower);
    std::transform(alive_color.begin(), alive_color.end(), alive_color.begin(), ::tolower);

    // Verifies if there's a risk of overcharging disk.
    if(create_img and unstoppable) {
        std::cout << "\033[1;31mWARNING: \033[0m Risk of generating too many images and overchargin hard disk.\n"
        << "Do you want to continue? [S/n]: \n";
        char answer;
        std::cin >> answer;

        if(answer == 'n' or answer == 'N'){
            std::cout << "Process finished\n";
            return EXIT_SUCCESS;
        } 
        else if(answer != 's' and answer != 'S'){
            std::cout << "\033[1;31mError: \033[0mInvalid input.\n";
            return EXIT_FAILURE;
        }
    }

    // Here we are reading the file representing the table's configuration, and saving
    // it's dimensions and values where the living cells are located.
    std::ifstream input{input_cfg};
    if(not input.is_open()){
        std::cout << "Cannot open file in " << input_cfg << '\n';
    }
    else{
        std::string line;

        // Getting rows and columns
        std::getline(input, line);
        size_t space_idx = line.find(" ");
        rows = std::stoi(line.substr(0, space_idx));
        columns = std::stoi(line.substr(space_idx+1, line.length()));

        // Getting character that represents alive cell.
        std::getline(input, line);
        alive_char = line[0];

        // Getting positions of living cells.
        int current_row = 0;
        std::vector<life::Cell> alive_cells;
        while(std::getline(input, line)){
            for(int column{0u}; column < columns; column++){
                if(line[column] == alive_char){
                    alive_cells.push_back({current_row, column});
                }
            }

            current_row++;
        }

        life::LifeCfg current_table(alive_cells, rows, columns);
        life::SimDatabase database;
        database.insert(current_table.get_key(), 1);

        // Here starts the repetitions.
        int gen{1u};
        if(unstoppable) max_gen = gen+1;
        if(create_img) std::cout << "Generating images...\n";
        while(not current_table.is_empty() and gen < max_gen+1){
            if(unstoppable) max_gen++;
            if(not create_img){
                std::cout << "Generation: " << gen << "\n";
                current_table.print_life(alive_char);
                std:cout << "\n\n";
            }
            else{
                // Generating images.
                std::string file_name = "gen " + std::to_string(gen);
                current_table.set_life_canvas(block_size, life::color_pallet[bk_color], life::color_pallet[alive_color]);
                current_table.save_img(path, file_name);
            }   
                current_table = current_table.get_next_gen();
        
                if(database.find(current_table.get_key()) and gen != max_gen){
                    std::cout << "Generation " << gen+1 << " found match with generation " << database.get(current_table.get_key()) << "\n";
                    return EXIT_SUCCESS;
                }

                gen++;
                database.insert(current_table.get_key(), gen);          

                // Delay based on given fps parameter.
                if(not create_img) std::this_thread::sleep_for(std::chrono::milliseconds(1000/fps));
        }
        if(gen == max_gen+1){
            std::cout << "Reached limit of generations\n";
            return EXIT_SUCCESS;
        }
        std::cout << "The population has been extinguished\n";
    }

    return EXIT_SUCCESS;
}
