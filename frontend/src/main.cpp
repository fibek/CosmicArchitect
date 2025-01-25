#include "webui.hpp"
#include <string>
#include <nlohmann/json.hpp>
#include <vector>
#include <iostream>
#include "SimulatedUniverse.hpp"
#include "Timeline.hpp"
#include "UniverseParameters.hpp"
#include "UniverseDB.hpp"
#include "UniverseValidator.hpp"

using json = nlohmann::json;

// Convert milestone type to string
std::string getMilestoneTypeString(int type) {
    switch (type) {
        case 0: return "BIG_BANG";
        case 1: return "INFLATION";
        case 2: return "PARTICLE_ERA";
        case 3: return "NUCLEOSYNTHESIS";
        case 4: return "RECOMBINATION";
        case 5: return "DARK_AGES";
        case 6: return "FIRST_STARS";
        case 7: return "GALAXY_FORMATION";
        case 8: return "ACCELERATED_EXPANSION";
        case 9: return "BIG_RIP";
        case 10: return "HEAT_DEATH";
        case 11: return "BIG_CRUNCH";
        default: return "UNKNOWN";
    }
}

// Convert SimulatedUniverse to JSON
json universe_to_json(SimulatedUniverse& universe, int id) {
    json j;
    j["id"] = id;
    j["name"] = universe.getName();
    
    // Create JSON directly from universe parameters
    j["matterDensity"] = universe.getMatterDensity();
    j["darkEnergyDensity"] = universe.getDarkEnergyDensity();
    j["hubbleConstant"] = universe.getHubbleConstant();
    j["matterAntimatterRatio"] = universe.getMatterAntimatterRatio();
    j["darkEnergyW"] = universe.getDarkEnergyW();
    
    // Generate timeline and log details
    std::cout << "Generating timeline for universe " << id << " (" << universe.getName() << ")" << std::endl;
    auto timeline = universe.generateTimeline();
    auto timelineJson = timeline->toJson();
    std::cout << "Timeline generated with " << timelineJson["milestones"].size() 
              << " milestones" << std::endl;
    
    // Convert milestone types to strings
    json milestones = json::array();
    for (const auto& milestone : timelineJson["milestones"]) {
        json m = milestone;
        m["type"] = getMilestoneTypeString(milestone["type"].get<int>());
        milestones.push_back(m);
        
        // Print for verification
        if (milestones.size() <= 3) {
            std::cout << "Milestone " << (milestones.size() - 1) << ": " 
                      << m["type"].get<std::string>() << " at t=" 
                      << m["timestamp"].get<double>() << std::endl;
        }
    }
    j["milestones"] = milestones;
    
    return j;
}

// Callback to create a new universe
void create_universe(webui::window::event* e) {
    try {
        auto data = json::parse(e->get_string());
        
        // Extract parameters from JSON
        std::string name = data["name"].get<std::string>();
        double matterDensity = data["matterDensity"].get<double>();
        double darkEnergyDensity = data["darkEnergyDensity"].get<double>();
        double hubbleConstant = data["hubbleConstant"].get<double>();
        double matterAntimatterRatio = data["matterAntimatterRatio"].get<double>();
        double darkEnergyW = data["darkEnergyW"].get<double>();
        
        // Create new universe with parameters
        auto universe = std::make_unique<SimulatedUniverse>(
            name, matterDensity, darkEnergyDensity, hubbleConstant,
            matterAntimatterRatio, darkEnergyW
        );
        
        // Generate timeline
        auto timeline = universe->generateTimeline();
        
        // Store universe and get its ID
        size_t id = UniverseDB::instance().getAllUniverses().size();
        UniverseDB::instance().addUniverse(std::move(universe));
        
        // Get reference to the stored universe
        auto& stored_universe = UniverseDB::instance().getAllUniverses()[id].get();
        
        // Create the response JSON
        json response;
        response["status"] = "success";
        response["message"] = "Universe created successfully";
        response["universe"] = universe_to_json(stored_universe, id);
        
        e->return_string(response.dump());
        
    } catch (const std::exception& ex) {
        json error = {
            {"status", "error"},
            {"message", std::string("Error creating universe: ") + ex.what()}
        };
        e->return_string(error.dump());
    }
}

// Callback to delete a universe
void delete_universe(webui::window::event* e) {
    try {
        json params = json::parse(e->get_string());
        int id = params["id"].get<int>();
        
        std::cout << "Deleting universe " << id << std::endl;
        
        if (UniverseDB::instance().removeUniverse(id)) {
            json response;
            response["status"] = "success";
            response["message"] = "Universe deleted successfully";
            e->return_string(response.dump());
        } else {
            throw std::runtime_error("Universe not found");
        }
    } catch (const std::exception& ex) {
        std::cout << "Error deleting universe: " << ex.what() << std::endl;
        json error;
        error["status"] = "error";
        error["message"] = ex.what();
        e->return_string(error.dump());
    }
}

// Callback to get list of universes
void get_universes(webui::window::event* e) {
    try {
        json response;
        response["status"] = "success";
        
        // Get all universes from the database
        auto universes = UniverseDB::instance().getAllUniverses();
        
        // Convert all universes to JSON
        json universe_list = json::array();
        int id = 0;
        for (auto& universe : universes) {
            universe_list.push_back(universe_to_json(universe.get(), id++));
        }
        response["universes"] = universe_list;
        
        e->return_string(response.dump());
    } catch (const std::exception& ex) {
        json error;
        error["status"] = "error";
        error["message"] = ex.what();
        e->return_string(error.dump());
    }
}

// Add new export handlers
void export_universe(webui::window::event* e) {
    try {
        auto data = json::parse(e->get_string());
        int id = data["id"].get<int>();
        std::string format = data["format"].get<std::string>();
        
        std::optional<std::string> exportData;
        if (format == "json") {
            exportData = UniverseDB::instance().exportToJSON(id);
        } else if (format == "csv") {
            exportData = UniverseDB::instance().exportToCSV(id);
        }
        
        if (exportData) {
            json response = {
                {"status", "success"},
                {"data", *exportData}
            };
            e->return_string(response.dump());
        } else {
            throw std::runtime_error("Universe not found");
        }
    } catch (const std::exception& ex) {
        json error = {
            {"status", "error"},
            {"message", std::string("Export failed: ") + ex.what()}
        };
        e->return_string(error.dump());
    }
}

// Add handler for exporting all universes
void export_all_universes(webui::window::event* e) {
    try {
        auto data = json::parse(e->get_string());
        std::string format = data["format"].get<std::string>();
        
        auto universes = UniverseDB::instance().getAllUniverses();
        
        if (format == "json") {
            // Create a JSON array of all universes
            json allUniverses = json::array();
            for (const auto& universe : universes) {
                std::string exportData = universe.get().toJSON();
                allUniverses.push_back(json::parse(exportData));
            }
            json response = {
                {"status", "success"},
                {"data", allUniverses.dump(4)}
            };
            e->return_string(response.dump());
        } else if (format == "csv") {
            // Combine all universes into one CSV
            std::stringstream combined;
            bool first = true;
            for (const auto& universe : universes) {
                if (!first) {
                    combined << "\n\n"; // Add separation between universes
                }
                combined << universe.get().toCSV();
                first = false;
            }
            json response = {
                {"status", "success"},
                {"data", combined.str()}
            };
            e->return_string(response.dump());
        }
    } catch (const std::exception& ex) {
        json error = {
            {"status", "error"},
            {"message", std::string("Export failed: ") + ex.what()}
        };
        e->return_string(error.dump());
    }
}

int main() {
    webui::window win;
    
    // Set the base directory for UI files
    win.set_root_folder("../frontend/ui");
    
    // Bind backend functions
    win.bind("createUniverse", create_universe);
    win.bind("getUniverses", get_universes);
    win.bind("deleteUniverse", delete_universe);
    win.bind("exportUniverse", export_universe);
    win.bind("exportAllUniverses", export_all_universes);  // Add new binding
    
    // Show the UI starting with index.html
    win.show("index.html");
    
    // Wait for the window
    webui::wait();
    return 0;
} 