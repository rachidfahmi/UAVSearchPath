#ifndef UAV_PROB_CELL_HPP
#define UAV_PROB_CELL_HPP

#include <cmath>
#include <nlohmann/json.hpp>
#include <cadmium/modeling/celldevs/grid/cell.hpp>
#include <cadmium/modeling/celldevs/grid/config.hpp>
#include "prob_state.hpp"

using namespace cadmium::celldevs;

class ProbCell : public GridCell<ProbState, double> {
    double alpha;

public:
    ProbCell(const std::vector<int>& id,
             const std::shared_ptr<const GridCellConfig<ProbState, double>>& config)
        : GridCell<ProbState, double>(id, config), alpha(0.05) {
        if (config->rawCellConfig.contains("alpha")) {
            config->rawCellConfig.at("alpha").get_to(alpha);
        }
        if (alpha <= 0.0 || alpha >= 0.125) {
            alpha = 0.05;
        }
    }

    [[nodiscard]] ProbState localComputation(
        ProbState state,
        const std::unordered_map<std::vector<int>,
            NeighborData<ProbState, double>>& neighborhood) const override {

        double neighborSum = 0.0;
        for (const auto& [neighborId, neighborData] : neighborhood) {
            neighborSum += neighborData.state->prob;
        }

        // Diffusion: P_new = (1 - 8α)*P + α * sum(8 Moore neighbors)
        double newProb = (1.0 - 8.0 * alpha) * state.prob + alpha * neighborSum;
        state.prob = std::max(0.0, std::min(1.0, newProb));
        return state;
    }

    [[nodiscard]] double outputDelay(const ProbState& state) const override {
        return 1.0;
    }
};

#endif
