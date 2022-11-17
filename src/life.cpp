/**
 * LLSeq class implementation.
 *
 */

#include "life.h"

namespace life {
/*============================================= Lifecfg =============================================*/

/// Basic constructor that creates a life board with default dimensions.
LifeCfg::LifeCfg(const vector<Cell>& input_cell, size_t rows, size_t cols)
{
    alive_cells = input_cell;
    r_rows = rows;
    r_cols = cols;

    // Here, we calculate the neighbours.

    for(const auto& cell : alive_cells){
        std::string topLeft_key = cell.row > 0 and cell.col > 0 ? std::to_string(cell.row-1) + "-" + std::to_string(cell.col-1) : "";
        std::string top_key = cell.row > 0 ? std::to_string(cell.row-1) + "-" + std::to_string(cell.col) : "";
        std::string topRight_key = cell.row > 0 and cell.col < r_cols-1 ? std::to_string(cell.row-1) + "-" + std::to_string(cell.col+1) : "";
        std::string right_key = cell.col < r_cols-1 ? std::to_string(cell.row) + "-" + std::to_string(cell.col+1) : "";
        std::string botRight_key = cell.row < r_rows-1 and cell.col < r_cols-1 ? std::to_string(cell.row+1) + "-" + std::to_string(cell.col+1) : "";
        std::string bot_key = cell.row < r_rows-1 ? std::to_string(cell.row+1) + "-" + std::to_string(cell.col) : "";
        std::string botLeft_key = cell.row < r_rows-1 and cell.col > 0 ? std::to_string(cell.row+1) + "-" + std::to_string(cell.col-1) : "";
        std::string left_key = cell.col > 0 ? std::to_string(cell.row) + "-" + std::to_string(cell.col-1) : "";

        std::vector<std::string> keys{topLeft_key, top_key, topRight_key, right_key, botRight_key, bot_key, botLeft_key, left_key};

        // For each candidate neighbour (key), adds it to neighbours if is a true neighbour.
        for(const auto& key : keys){
            if(key != ""){ // If the top-left neighbour exists...
                if(neighbours.count(key) == 0){ // If the top-left neighbour wasn't added yet...
                    neighbours.insert({key, 1});
                }
                else{
                    neighbours[key] = neighbours.at(key) + 1;
                }
            }
        }

    }
};

/// Returns a unique key for the current alive cells.
std::string LifeCfg::get_key(void) const {
    std::ostringstream oss;
    for(const Cell& cell : alive_cells){
        oss << cell.row << "-" << cell.col << " ";
    }
    return oss.str();
}

/// Returns all the neighbours of the current alive cells.
std::unordered_map<std::string, unsigned> LifeCfg::get_neighbours() const {
    return neighbours;
}

/// Returns true if the cell is alive.
bool LifeCfg::is_alive(const Cell& cell){
    for(const auto& other : alive_cells){
        if(other.row == cell.row && other.col == cell.col){
            return true;
        }
    }
    return false;
};

/// A generalization of is_alive. Returns true if the cell is in the given vector.
bool isInVector(std::vector<life::Cell> next_gen, life::Cell cell){
    for(const auto& other : next_gen){
        if(other.row == cell.row && other.col == cell.col){
            return true;
        }
        return false;
    }
}

/// Sorts a vector<Cell>.
bool sort_cells(life::Cell first, life::Cell last){
    return first.row < last.row or (first.row == last.row and first.col <= last.col);
}

/// Returns the next generation as a vector of cells.
std::vector<Cell> LifeCfg::get_next_gen(){
    std::vector<Cell> next_gen;

    for(const auto& cell_inst : neighbours){
        int divisor = cell_inst.first.find("-");
        int quantity = cell_inst.second;
        int row = std::stoi(cell_inst.first.substr(0, divisor));
        int col = std::stoi(cell_inst.first.substr(divisor+1, cell_inst.first.length()));

        Cell cell(row, col);
        // /*======== FIRST RULE ========*/
        // if(is_alive(cell) and quantity <= 1){
        //     continue;
        // }

        // /*======== SECOND RULE ========*/
        // if(is_alive(cell) and quantity >= 4){
        //     continue;
        // }

        /*======== THIRD RULE ========*/
        if(is_alive(cell) and (quantity == 2 or quantity == 3) and !isInVector(next_gen, cell)){
            next_gen.push_back(cell);
        }

        /*======== FOURTH RULE ========*/
        if(!is_alive(cell) and quantity == 3 and !isInVector(next_gen, cell)){
            next_gen.push_back(cell);
        }

    }
    std::sort(next_gen.begin(), next_gen.end(), sort_cells);
    return next_gen;
}

std::vector<Cell> LifeCfg::get_alive_cells(void) const {
    return alive_cells;
}

/// Prints the current life table.
void LifeCfg::print_life(char alive_char){
    for(int i{0u}; i < r_rows; i++){
        for(int j{0u}; j < r_cols; j++){
            Cell current_cell(i, j);
            if(is_alive(current_cell)){
                std::cout << alive_char;
            }
            else{
                std::cout << ".";
            }
        }
        std::cout << '\n';
    }
}

bool LifeCfg::is_empty(){
    return alive_cells.size() == 0;
}

void LifeCfg::set_life_canvas(short block_size, Color bg_color, Color alive){
    life_table = Canvas(r_cols, r_rows, block_size);
    life_table.clear(bg_color);

    for(const auto& cell : alive_cells){
        life_table.pixel(cell.col, cell.row, alive);
    }
}

/// Splits the input string based on `delimiter` into a list of substrings.
std::vector<std::string> split(const std::string & input_str, char delimiter='.'){
    // Store the tokens.
    std::vector<std::string> tokens;
    // read tokens from a string buffer.
    std::istringstream iss;
    iss.str(input_str);
    // This will hold a single token temporarily.
    std::string token;
    while (std::getline(iss >> std::ws, token, delimiter))
        tokens.emplace_back(token);
    return tokens;
}

bool LifeCfg::save_img(std::string path, std::string file_name){
    // Adds / to the end of the path if there is none.
    if(path[path.length()-1] != '/') path += '/';

    // Makes sure the file_name ends with .ppm.
    auto components = split(file_name, '.');
    file_name = components[0] + ".ppm";

    std::ofstream ofs_file(path+file_name, std::ios::out);
    if (not ofs_file.is_open())
        return false;

    // Basic configurations of ppm file
    ofs_file << "P3" << '\n';
    ofs_file << std::to_string(life_table.width()) + " " + std::to_string(life_table.height()) << '\n';
    ofs_file << 255 << "\n\n";

    // Data of the canvas.
    auto data = life_table.pixels();

    // Writing canvas data into the ppm file
    for(long i{0u}; i < life_table.width()*life_table.height()*4; i += 4){
        ofs_file << (int)data[i] << " ";
        ofs_file << (int)data[i+1] << " ";
        ofs_file << (int)data[i+2] << "\n";
    }
    
    ofs_file.close();

    return true; 
}

/*============================================= SimDatabase =============================================*/

SimDatabase::SimDatabase(){/* empty */};

bool SimDatabase::find(const std::string& key) const {
    return generations.count(key) != 0;
}

void SimDatabase::insert(const std::string& key, unsigned long value){
    generations.insert({key, value});
}

unsigned long SimDatabase::get(const std::string& key) const {
    return generations.at(key);
}

}  // namespace life
