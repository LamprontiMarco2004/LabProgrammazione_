#include <iostream>
#include "TodoList.h"
#include <fstream>
// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
int main()
{
    // reset della lista (cancella il contenuto del file)
    std::ofstream("data/activities.txt", std::ios::trunc);
    TodoList myList;
    myList.loadFromFile("data/activities.txt");


    // Caricamento da file (se esiste)
    myList.loadFromFile("data/activities.txt");

    std::cout << "Attivita' iniziali: " << std::endl;
    myList.showActivities();

    // Aggiunta di nuove attività
    std::cout << " Aggiungo alcune attivita'" << std::endl;
    myList.addActivity("Studiare C++");
    myList.addActivity("Fare esercizi");
    myList.addActivity("Allenamento");

    std::cout << " Dopo l'aggiunta: " << std::endl;
    myList.showActivities();

    // Completa un'attività (esempio ID = 2)
    int idToComplete = 2;
    std::cout << " Segno come completata l'attivita' con ID "
              << idToComplete << "..." << std::endl;

    if (myList.completeActivity(idToComplete)) {
        std::cout << "Attivita' completata con successo!" << std::endl;
    } else {
        std::cout << "ID non trovato." << std::endl;
    }

    std::cout << " Stato aggiornato " << std::endl;
    myList.showActivities();

    // Salvataggio su file
    myList.saveToFile("data/activities.txt");
    std::cout << " Dati salvati su file." << std::endl;

    return 0;
    }


