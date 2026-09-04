/**
 * ============================================================================
 *  AKP ENGINE - MODERN C++17 / C++20 RAII & STL WRAPPER (akp.hpp)
 *  Author: Akshar Miyani | AKP Studio
 * ============================================================================
 */

#ifndef AKP_HPP
#define AKP_HPP

#include "akp.h"
#include <iostream>
#include <string>
#include <vector>
#include <initializer_list>
#include <chrono>

namespace akp {

    /* Stream Color Modifiers */
    inline std::ostream& reset(std::ostream& os)       { return os << AKP_RESET; }
    inline std::ostream& bold(std::ostream& os)        { return os << AKP_BOLD; }
    inline std::ostream& dim(std::ostream& os)         { return os << AKP_DIM; }
    inline std::ostream& neon_cyan(std::ostream& os)   { return os << AKP_NEON_CYAN; }
    inline std::ostream& neon_pink(std::ostream& os)   { return os << AKP_NEON_PINK; }
    inline std::ostream& neon_purple(std::ostream& os) { return os << AKP_NEON_PURPLE; }
    inline std::ostream& neon_green(std::ostream& os)  { return os << AKP_NEON_GREEN; }
    inline std::ostream& neon_yellow(std::ostream& os) { return os << AKP_NEON_YELLOW; }
    inline std::ostream& gold(std::ostream& os)        { return os << AKP_GOLD; }
    inline std::ostream& fire_orange(std::ostream& os) { return os << AKP_FIRE_ORANGE; }

    /* RAII Benchmark Timer */
    class ScopedTimer {
    private:
        std::string name_;
        std::chrono::high_resolution_clock::time_point start_;
    public:
        explicit ScopedTimer(std::string name)
            : name_(std::move(name)), start_(std::chrono::high_resolution_clock::now()) {}

        ~ScopedTimer() {
            auto end = std::chrono::high_resolution_clock::now();
            double ms = std::chrono::duration<double, std::milli>(end - start_).count();
            akp_log_info("Benchmark [" AKP_BOLD AKP_NEON_YELLOW "%s" AKP_RESET "] elapsed: " AKP_BOLD AKP_NEON_GREEN "%.4f ms" AKP_RESET,
                         name_.c_str(), ms);
        }
    };

    /* Modern C++ Table Builder */
    class Table {
    private:
        akp_table_t* table_;
    public:
        Table(const std::string& title, std::initializer_list<std::string> headers) {
            table_ = akp_table_create((int)headers.size(), title.c_str());
            int col = 0;
            for (const auto& h : headers) {
                if (col < table_->cols) {
                    strncpy(table_->headers[col], h.c_str(), AKP_TABLE_MAX_CELL - 1);
                    int len = (int)h.length();
                    if (len > table_->col_widths[col]) table_->col_widths[col] = len;
                    col++;
                }
            }
        }

        ~Table() {
            if (table_) akp_table_free(table_);
        }

        void addRow(std::initializer_list<std::string> row) {
            if (!table_ || table_->rows >= AKP_TABLE_MAX_ROWS) return;
            int col = 0;
            for (const auto& cell : row) {
                if (col < table_->cols) {
                    strncpy(table_->cells[table_->rows][col], cell.c_str(), AKP_TABLE_MAX_CELL - 1);
                    int len = (int)cell.length();
                    if (len > table_->col_widths[col]) table_->col_widths[col] = len;
                    col++;
                }
            }
            table_->rows++;
        }

        void render() const {
            if (table_) akp_table_render(table_);
        }
    };

    /* Modern C++ Sparkline Helper */
    inline void sparkline(const std::vector<double>& values, const std::string& label) {
        if (!values.empty()) {
            akp_sparkline(values.data(), (int)values.size(), label.c_str());
        }
    }

    /* Modern C++ 2D Canvas RAII Guard */
    class Canvas {
    private:
        akp_canvas_t* canvas_;
    public:
        Canvas(int width, int height) {
            canvas_ = akp_canvas_create(width, height);
        }
        ~Canvas() {
            if (canvas_) akp_canvas_free(canvas_);
        }
        void drawLine(int x0, int y0, int x1, int y1, char ch, akp_rgb_t color) {
            akp_canvas_draw_line(canvas_, x0, y0, x1, y1, ch, color);
        }
        void drawRect(int x, int y, int w, int h, char ch, akp_rgb_t color) {
            akp_canvas_draw_rect(canvas_, x, y, w, h, ch, color);
        }
        void drawCircle(int xc, int yc, int r, char ch, akp_rgb_t color) {
            akp_canvas_draw_circle(canvas_, xc, yc, r, ch, color);
        }
        void drawText(int x, int y, const std::string& text, akp_rgb_t color) {
            akp_canvas_draw_text(canvas_, x, y, text.c_str(), color);
        }
        void render(const std::string& title) const {
            akp_canvas_render(canvas_, title.c_str());
        }
    };

} // namespace akp

#endif /* AKP_HPP */
