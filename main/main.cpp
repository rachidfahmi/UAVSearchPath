#include <cadmium/modeling/celldevs/grid/coupled.hpp>
#include <cadmium/simulation/logger/csv.hpp>
#include <cadmium/simulation/root_coordinator.hpp>
#include <fstream>
#include <string>
#include "prob_cell.hpp"

using namespace cadmium::celldevs;

std::shared_ptr<GridCell<ProbState, double>> addProbCell(
    const std::vector<int>& cellId,
    const std::shared_ptr<const GridCellConfig<ProbState, double>>& cellConfig) {

    auto cellModel = cellConfig->cellModel;
    if (cellModel == "default" || cellModel == "prob") {
        return std::make_shared<ProbCell>(cellId, cellConfig);
    }
    throw std::bad_typeid();
}

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cout << "Usage: " << argv[0]
                  << " SCENARIO_CONFIG.json [SIM_TIME (default: 50)]" << std::endl;
        return -1;
    }
    std::string configFilePath = argv[1];
    double simTime = (argc > 2) ? std::stod(argv[2]) : 50;

    auto model = std::make_shared<GridCellDEVSCoupled<ProbState, double>>(
        "prob_grid", addProbCell, configFilePath);
    model->buildModel();

    auto rootCoordinator = cadmium::RootCoordinator(model);
    rootCoordinator.setLogger<cadmium::CSVLogger>("output/prob_log.csv", ";");
    rootCoordinator.start();
    rootCoordinator.simulate(simTime);
    rootCoordinator.stop();

    std::cout << "Simulation complete. Output: output/prob_log.csv" << std::endl;
    return 0;
}
