#include <iostream>
#include <string>
#include "TodoList.h"

void printMenu() {
    std::cout << "\n--- To-Do List ---" << std::endl;
    std::cout << "1. Visualizza attivita'" << std::endl;
    std::cout << "2. Aggiungi attivita'" << std::endl;
    std::cout << "3. Segna attivita' come completata" << std::endl;
    std::cout << "4. Esci" << std::endl;
    std::cout << "Scegli un'opzione: ";
}

int main() {
    const std::string filename = "data/activities.txt";
    TodoList list;

    // Caricamento dati all'avvio
    list.loadFromFile(filename);

    std::string inputLine;
    int choice = 0;

    do {
        printMenu();

        std::getline(std::cin, inputLine);

        try {
            choice = std::stoi(inputLine);
        } catch (const std::exception&) {
            choice = -1; // Scelta non valida per default
        }

        switch (choice) {
            case 1:
                std::cout << "\n";
                list.showActivities();
                break;

            case 2: {
                std::cout << "Inserisci la descrizione della nuova attivita': ";
                std::string description;
                std::getline(std::cin, description);

                if (!description.empty()) {
                    list.addActivity(description);
                } else {
                    std::cout << "La descrizione non puo' essere vuota." << std::endl;
                }
                break;
            }

            case 3: {
                std::cout << "Inserisci l'ID dell'attivita' da completare: ";
                std::getline(std::cin, inputLine);

                try {
                    int id = std::stoi(inputLine);
                    if (list.completeActivity(id)) {
                        std::cout << "Attivita' segnata come completata." << std::endl;
                    } else {
                        std::cout << "ID non trovato." << std::endl;
                    }
                } catch (const std::exception&) {
                    std::cout << "Input non valido. Inserisci un ID numerico." << std::endl;
                }
                break;
            }

            case 4:
                std::cout << "Salvataggio e chiusura in corso..." << std::endl;
                break;

            default:
                std::cout << "Scelta non valida. Riprova." << std::endl;
        }

    } while (choice != 4);

    // Salvataggio dati alla chiusura
    list.saveToFile(filename);

    std::cout << "Arrivederci!" << std::endl;
    return 0;
}
