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
        double used_pct = ctx.at("used_percentage").get<double>();
        int input_tokens = ctx.at("total_input_tokens").get<int>();
        int output_tokens = ctx.at("total_output_tokens").get<int>();
        int window_size = ctx.at("context_window_size").get<int>();

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

        int total_tokens = input_tokens + output_tokens;
        std::string used_str = format_tokens(total_tokens);
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
