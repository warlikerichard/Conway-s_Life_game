/*!
 * Canvas class implementation.
 * @file canvas.cpp
 */

#include "canvas.h"

namespace life {

  // TODO: Adicione o resto da implementação dos métodos aqui.

  Canvas::Canvas(size_t w, size_t h, short bs){
    m_width = w;
    m_height = h;
    m_block_size = bs;

    m_pixels.resize(w*h*4);
  }

  //=== Members
  /// Clear the canvas with black color.
  void Canvas::clear(const Color& color){
    for(size_t i{0u}; i < m_pixels.size(); i+=4){
      m_pixels[i] = color.channels[Color::R];
      m_pixels[i+1] = color.channels[Color::G];
      m_pixels[i+2] = color.channels[Color::B];
      m_pixels[i+3] = 255;
    }
  }
  /// Set the color of a pixel on the canvas.
  void Canvas::pixel(coord_t x, coord_t y, const Color& color){

    long index = getIndexOfRow(y) + getIndexOfColumn(x);
    // index += a;
    // index += b;
    m_pixels[index] = color.channels[Color::R];
    m_pixels[index+1] = color.channels[Color::G];
    m_pixels[index+2] = color.channels[Color::B];
    m_pixels[index+3] = 255;
  }

  /// Get the pixel color from the canvas.
  Color Canvas::pixel(coord_t x, coord_t y){
    size_t row = getIndexOfRow(y);
    size_t column = getIndexOfColumn(x);

    return Color(m_pixels[row+column], m_pixels[row+column+1], m_pixels[row+column+2]);
  }

  /// @brief Get the index of m_pixels representing the starting position of a given row.
  /// @brief It is used alongside getIndexOfColumn, since getIndexOfRow(x) + getIndexOfColumn(y) returns the true position (x, y).
  /// @param row The position of the row you wanna get the index of. 
  /// @return The index of m_pixels's row.
  size_t Canvas::getIndexOfRow(size_t row){
    return m_width * 4 * row;
  }

  /// @brief Get the index of m_pixel representing the starting position of a given column.
  /// @brief It is used alongside getIndexOfRow, since getIndexOfRow(x) + getIndexOfColumn(y) returns the true position (x, y).
  /// @param column The position of the column you wanna get the index of. 
  /// @return The index of m_pixels's column.
  size_t Canvas::getIndexOfColumn(size_t column){
    return 4 * column;
  }

  /// @brief Scale the pixels from m_pixels into m_resized_pixels.
  void Canvas::resize_pixels(){
    m_resized_pixels.clear();
    // Explanation: For each row in m_pixels, add each pixel of the row m_block_size
    // times in m_resized_pixels. Then, repeat the process m_block_size times, then go to the next row. 
    for(size_t i{0}; i < m_height; i++){
      size_t row = getIndexOfRow(i);
      for(int j{0u}; j < m_block_size; j++){
        for(size_t k{0}; k < m_width; k++){
          size_t column = getIndexOfColumn(k);
          for(int l{0u}; l < m_block_size; l++){
            m_resized_pixels.push_back(m_pixels[row+column]);
            m_resized_pixels.push_back(m_pixels[row+column+1]);
            m_resized_pixels.push_back(m_pixels[row+column+2]);
            m_resized_pixels.push_back(m_pixels[row+column+3]);
          }
        }
      }
    }

    m_resized_pixels.shrink_to_fit();
  }

}
  // namespace life