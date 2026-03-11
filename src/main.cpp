#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

std::string format_tokens(int tokens) {
    if (tokens >= 1'000'000) {
        double val = tokens / 1'000'000.0;
        std::ostringstream oss;
        if (val >= 10.0)
            oss << std::fixed << std::setprecision(0) << val << "M";
        else
            oss << std::fixed << std::setprecision(1) << val << "M";
        return oss.str();
    }
    if (tokens >= 1'000) {
        double val = tokens / 1'000.0;
        std::ostringstream oss;
        if (val >= 100.0)
            oss << std::fixed << std::setprecision(0) << val << "K";
        else if (val >= 10.0)
            oss << std::fixed << std::setprecision(0) << val << "K";
        else
            oss << std::fixed << std::setprecision(1) << val << "K";
        return oss.str();
    }
    return std::to_string(tokens);
}

int main() {
    try {
        std::string input(std::istreambuf_iterator<char>(std::cin), {});
        auto data = json::parse(input);

        auto& ctx = data.at("context_window");
        int window_size = ctx.at("context_window_size").get<int>();

        // Use current_usage for accurate context state (survives compression/flush).
        // Cumulative totals (total_input_tokens, total_output_tokens) grow forever
        // and don't reflect actual context after compression.
        int used_tokens = 0;
        double used_pct = 0.0;

        if (ctx.contains("current_usage") && !ctx["current_usage"].is_null()) {
            auto& usage = ctx["current_usage"];
            int input = usage.value("input_tokens", 0);
            int cache_creation = usage.value("cache_creation_input_tokens", 0);
            int cache_read = usage.value("cache_read_input_tokens", 0);
            used_tokens = input + cache_creation + cache_read;
            used_pct = (static_cast<double>(used_tokens) / window_size) * 100.0;
        } else if (ctx.contains("used_percentage") && !ctx["used_percentage"].is_null()) {
            used_pct = ctx["used_percentage"].get<double>();
            used_tokens = static_cast<int>(used_pct / 100.0 * window_size);
        }

        std::string model_name = data.at("model").at("display_name").get<std::string>();

        // Select color based on usage
        const char* color;
        if (used_pct < 50.0)
            color = "\033[32m"; // green
        else if (used_pct < 75.0)
            color = "\033[33m"; // yellow
        else
            color = "\033[31m"; // red

        const char* reset = "\033[0m";

        std::string used_str = format_tokens(used_tokens);
        std::string total_str = format_tokens(window_size);

        std::ostringstream pct_ss;
        pct_ss << std::fixed << std::setprecision(1) << used_pct << "%";

        std::cout << model_name << " | Context: "
                  << color << pct_ss.str() << reset
                  << " (" << used_str << " / " << total_str << ")";

    } catch (...) {
        // Silent failure — output nothing to keep status line clean
    }
    return 0;
}
