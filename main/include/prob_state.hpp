#ifndef UAV_PROB_STATE_HPP
#define UAV_PROB_STATE_HPP

#include <iostream>
#include <cmath>
#include <nlohmann/json.hpp>

struct ProbState {
    double prob;   // target probability value [0.0, 1.0]

    ProbState() : prob(0.0) {}
};

inline bool operator!=(const ProbState& x, const ProbState& y) {
    return std::abs(x.prob - y.prob) > 1e-9;
}

inline std::ostream& operator<<(std::ostream& os, const ProbState& s) {
    os << s.prob;
    return os;
}

[[maybe_unused]] void from_json(const nlohmann::json& j, ProbState& s) {
    j.at("prob").get_to(s.prob);
}

#endif
