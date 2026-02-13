//
// Created by lampr on 13/02/2026.
//

#ifndef LABPROGRAMMAZIONEC___ACTIVITY_H
#define LABPROGRAMMAZIONEC___ACTIVITY_H
#include <string>

class Activity {
public:
    Activity(int id, std::string description);

    int getId() const;
    const std::string& getDescription() const;
    bool isCompleted() const;

    void setCompleted(bool completed);

    void print() const;

private:
    int id;
    std::string description;
    bool completed;
};



#endif //LABPROGRAMMAZIONEC___ACTIVITY_H