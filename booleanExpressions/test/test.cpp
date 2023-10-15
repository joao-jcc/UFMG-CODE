#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.hpp"
#include "stack.hpp"
#include "utils.hpp"

#include <string>


TEST_CASE("Infix to Posfix Expression") {
    std::string formula = "0 & (1 | 2)";
    std::string valuation = "101";

    CHECK_EQ("101|&", to_posfix(formula, valuation));

}

TEST_CASE("Boolean Evaluation") {
    std::string formula = "(0 | 1) & ~2";
    std::string valuation = "010";

    CHECK_EQ(true, evaluate_expression(formula, valuation));
}