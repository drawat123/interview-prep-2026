#include <chrono>
#include <iostream>
#include <vector>

const int ROWS = 10000;
const int COLS = 10000;

int main() {
  // 1. Allocate a massive 2D array (10000 x 10000)
  // Systems Note: We use a flat 1D vector mapped to 2D to guarantee
  // contiguous memory allocation. A std::vector<std::vector<int>> does NOT
  // guarantee contiguous memory between rows!
  std::cout << "Allocating memory...\n";
  std::vector<int> matrix(ROWS * COLS, 1);

  // ==========================================
  // ROW-BY-ROW TRAVERSAL
  // ==========================================
  std::cout << "Starting Row-by-Row Traversal...\n";
  auto start_row = std::chrono::high_resolution_clock::now();

  long long sum_row = 0;
  // TODO: Write a nested loop that iterates through the matrix ROW by ROW.
  // The outer loop should be 'r' (0 to ROWS) and inner should be 'c' (0 to
  // COLS). Access element at index: matrix[r * COLS + c]
  for (int r = 0; r < ROWS; r++) {
    for (int c = 0; c < COLS; c++) {
      sum_row += matrix[r * COLS + c];
    }
  }

  auto end_row = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> row_duration = end_row - start_row;
  std::cout << "Row-by-Row Sum: " << sum_row << "\n";
  std::cout << "Row-by-Row Time: " << row_duration.count() << " ms\n\n";

  // ==========================================
  // COLUMN-BY-COLUMN TRAVERSAL
  // ==========================================
  std::cout << "Starting Col-by-Col Traversal...\n";
  auto start_col = std::chrono::high_resolution_clock::now();

  long long sum_col = 0;
  // TODO: Write a nested loop that iterates through the matrix COLUMN by
  // COLUMN. The outer loop should be 'c' (0 to COLS) and inner should be 'r' (0
  // to ROWS). Access element at index: matrix[r * COLS + c]
  for (int c = 0; c < COLS; c++) {
    for (int r = 0; r < ROWS; r++) {
      sum_col += matrix[r * COLS + c];
    }
  }

  auto end_col = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> col_duration = end_col - start_col;
  std::cout << "Col-by-Col Sum: " << sum_col << "\n";
  std::cout << "Col-by-Col Time: " << col_duration.count() << " ms\n\n";

  return 0;
}
