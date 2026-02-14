//
// Created by lampr on 13/02/2026.
//
#include "TodoList.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>

void TodoList::addActivity(const std::string& description) {
    activities.emplace_back(nextId++, description);
}

bool TodoList::completeActivity(int id) {
    for (auto& activity : activities) {
        if (activity.getId() == id) {
            activity.setCompleted(true);
            return true;
        }
    }
    return false;
}

void TodoList::showActivities() const {
    if (activities.empty()) {
        std::cout << "Nessuna attivita' presente." << std::endl;
        return;
    }

    for (const auto& activity : activities) {
        activity.print();
    }
}

const std::vector<Activity>& TodoList::getActivities() const {
    return activities;
}

void TodoList::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return; // Se il file non esiste partiamo con lista vuota
    }

    activities.clear();
    std::string line;
    int maxId = 0;

    while (std::getline(file, line)) {
        if (line.length() < 6) continue; // Riga non valida

        try {
            // Stato completamento: [X] oppure [ ]
            bool completed = (line.substr(1, 1) == "X");

            // Trova il punto dopo l'ID
            size_t posDot = line.find(". ");
            if (posDot == std::string::npos) continue;

            // Estrai ID
            std::string idStr = line.substr(4, posDot - 4);
            int id = std::stoi(idStr);

            // Estrai descrizione
            std::string description = line.substr(posDot + 2);

            // Ricrea l'oggetto Activity
            Activity loadedActivity(id, description);
            loadedActivity.setCompleted(completed);
            activities.push_back(loadedActivity);

            if (id > maxId) {
                maxId = id;
            }

        } catch (...) {
            std::cerr << "Attenzione: riga ignorata (formato non valido): "
                      << line << std::endl;
        }
    }

    nextId = maxId + 1;
}

void TodoList::saveToFile(const std::string& filename) const {
    // Assicura che la directory esista
    try {
        std::filesystem::path filePath(filename);
        std::filesystem::path dirPath = filePath.parent_path();

        if (!dirPath.empty() && !std::filesystem::exists(dirPath)) {
            std::filesystem::create_directories(dirPath);
        }
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Errore nella creazione della directory: "
                  << e.what() << std::endl;
        return;
    }

    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Errore: impossibile salvare il file " << filename << std::endl;
        return;
    }

    for (const auto& activity : activities) {
        file << (activity.isCompleted() ? "[X] " : "[ ] ")
             << activity.getId() << ". "
             << activity.getDescription() << "\n";
    }
}
