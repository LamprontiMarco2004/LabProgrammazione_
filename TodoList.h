//
// Created by lampr on 13/02/2026.
//

#ifndef LABPROGRAMMAZIONEC___TODOLIST_H
#define LABPROGRAMMAZIONEC___TODOLIST_H
#include "Activity.h"
#include <vector>
#include <string>

class TodoList {
public:

    void addActivity(const std::string& description);
    bool completeActivity(int id);
    void showActivities() const;

    // Restituisce la lista (utile per test o altre elaborazioni)
    const std::vector<Activity>& getActivities() const;

    // Caricamento e salvataggio su file
    void loadFromFile(const std::string& filename);
    void saveToFile(const std::string& filename) const;

private:
    std::vector<Activity> activities; // Contenitore delle attività
    int nextId = 1; // Generatore di ID univoci
};

#endif //LABPROGRAMMAZIONEC___TODOLIST_H