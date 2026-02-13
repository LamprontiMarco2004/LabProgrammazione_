//
// Created by lampr on 13/02/2026.
//
#include "Activity.h"
#include <iostream>
#include <utility>

Activity::Activity(int id, std::string description)
    : id(id), description(std::move(description)), completed(false) {}

int Activity::getId() const {
    return id;
}

const std::string& Activity::getDescription() const {
    return description;
}

bool Activity::isCompleted() const {
    return completed;
}

void Activity::setCompleted(bool completed) {
    this->completed = completed;
}

void Activity::print() const {
    std::cout << id << ") "
              << (completed ? "[DONE] " : "[TODO] ")
              << description << std::endl;
}
