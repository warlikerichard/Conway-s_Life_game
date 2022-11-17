//! This class implements a life board in the Conway's Game of Life.
/*!
 * @file life.h
 *
 * @details Class Life, to simulate the Conway's Game of Life.
 *
 * @author	Selan R dos Santos, <selan.rds@gmail.com>
 * @date	2015, updated 2015-04-03
 * @update 2019, April 2nd.
 * @version     v1.1
 */

#ifndef _LIFE_H_
#define _LIFE_H_

#include <cassert>
#include <cstring>  // std::memcpy().
#include <iostream>
#include <set>
#include <sstream>  // std::ostringstream
#include <stdexcept>
#include <string>
#include <vector>
#include <fstream> // To generate images.

using std::cerr;
using std::cout;
using std::endl;
using std::set;
using std::string;
using std::vector;

#include "../lib/canvas.h"

namespace life {
struct Cell{
    int row;
    int col;
    Cell(int r, int c) : row(r), col(c) {};
    // bool operator==(Cell& other){
    //     return (row == other.row) && (col == other.col);
    // }
};

/// A life configuration.
class LifeCfg {

   public:
    LifeCfg(const vector<Cell>& input_cell, size_t rows, size_t cols);  // lines, columns
    ~LifeCfg(){ /* empty */ };

    /// Returns a unique key for the current alive cells.
    std::string get_key(void) const;
    /// Returns a map for the cells and how many neighbours it has.
    std::unordered_map<std::string, unsigned> get_neighbours(void) const;
    /// Returns a vector with the cells of the next generation.
    std::vector<Cell> get_next_gen(void);
    /// Returns true if the given cell is alive.
    bool is_alive(const Cell& cell);
    /// Returns the alive cells.
    std::vector<Cell> get_alive_cells(void) const;
    /// Prints the current life table.
    void print_life(char alive_char);
    /// Returns true if there are no more alive cells.
    bool is_empty(void);
    /// Sets a canvas with a given block size and current alive cells.
    void set_life_canvas(short block_size, Color bg_color, Color alive);
    /// Saves image of current life_canvas.
    bool save_img(std::string path, std::string file_name);
    /* void set_alive(const std::vector<Location2>&);
    void update(void);
    std::string to_string(void) const;
    bool operator==(const LifeCfg&) const;
    LifeCfg& operator=(const LifeCfg& _rhs);
    bool extinct(void) const;
    size_type rows(void) const;
    size_type cols(void) const; */

    /*============= OPERATORS =============*/

    /// Changes the current alive cells and updates the neighbours of each cell.
    void operator=(std::vector<Cell> new_cells){
        alive_cells = new_cells;
    }

    private:
    std::vector<Cell> alive_cells; // List of cells that are alive.
    std::unordered_map<std::string, unsigned> neighbours; // Maps how many neighbours a cell has.

    size_t r_rows, r_cols;

    Canvas life_table;
};

class SimDatabase{
    private:
     std::unordered_map<std::string, unsigned long> generations;
     
    public:
     SimDatabase(); // Constructor
     bool find(const std::string& key) const; // Returns true if key exists.
     void insert(const std::string& key, unsigned long value); // Inserts key into database (generations).
     unsigned long get(const std::string& key) const; // Returns the generation number of given key.
};

}  // namespace life

#endif
