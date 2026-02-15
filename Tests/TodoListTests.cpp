#include "gtest/gtest.h"
#include "../TodoList.h" // <<< MODIFICA: Includiamo TodoList.h
#include <fstream>
#include <cstdio>

// TEST DELLA LOGICA DI BASE


// La macro TEST definisce un caso di test.
// Argomento 1: "TestSuite Name" -> Raggruppa test correlati. Ho scelto "TodoListLogicTest".
// Argomento 2: "TestCase Name" -> Descrive cosa fa questo specifico test.

TEST(TodoListLogicTest, AddActivityIncreasesSizeAndAssignsCorrectDescription) {
    TodoList list;
    list.addActivity("Fare la spesa");

    const auto& activities = list.getActivities();
    ASSERT_EQ(activities.size(), 1);
    EXPECT_EQ(activities.front().getDescription(), "Fare la spesa");
}

TEST(TodoListLogicTest, NewActivityIsInitiallyNotCompleted) {
    TodoList list;
    list.addActivity("Studiare C++");

    ASSERT_FALSE(list.getActivities().front().isCompleted());
}

TEST(TodoListLogicTest, CompleteActivityCorrectlyChangesState) {
    TodoList list;
    list.addActivity("Scrivere i test");
    int activityId = list.getActivities().front().getId();

    list.completeActivity(activityId);

    ASSERT_TRUE(list.getActivities().front().isCompleted());
}

TEST(TodoListLogicTest, CompletingNonExistentActivityReturnsFalse) {
    TodoList list;
    ASSERT_FALSE(list.completeActivity(999));
}


// TEST DELLA PERSISTENZA SU FILE

// Uso una "Test Fixture" per gestire risorse esterne (in questo caso, un file temporaneo).
// Una Fixture è una classe che permette di condividere la logica di setup e cleanup tra più test.

class PersistenceTest : public ::testing::Test {
protected:
    std::string test_filename;

    void SetUp() override {
        test_filename = "test_activities_temp.txt";
    }

    void TearDown() override {
        remove(test_filename.c_str()); // Il metodo .c_str() converte la std::string in una stringa C (const char*), che è il formato richiesto da remove.
    }
};

// Uso TEST_F (F per Fixture) per indicare che questo test fa parte della suite "PersistenceTest"
// e quindi deve eseguire SetUp() prima e TearDown() dopo.

TEST_F(PersistenceTest, SaveAndLoadCycleIsConsistent) {
    // ARRANGE
    TodoList list_to_save;
    list_to_save.addActivity("Prima attivita'");
    list_to_save.addActivity("Seconda attivita', con virgole");
    list_to_save.completeActivity(2);

    // ACT
    list_to_save.saveToFile(test_filename);

    TodoList list_to_load;
    list_to_load.loadFromFile(test_filename);

    // ASSERT
    const auto& loaded_activities = list_to_load.getActivities();
    ASSERT_EQ(loaded_activities.size(), 2);

    EXPECT_EQ(loaded_activities[0].getId(), 1);
    EXPECT_EQ(loaded_activities[0].getDescription(), "Prima attivita'");
    EXPECT_FALSE(loaded_activities[0].isCompleted());

    EXPECT_EQ(loaded_activities[1].getId(), 2);
    EXPECT_EQ(loaded_activities[1].getDescription(), "Seconda attivita', con virgole");
    EXPECT_TRUE(loaded_activities[1].isCompleted());
}

TEST_F(PersistenceTest, LoadFromFileCorrectlySetsNextId) {
    // ARRANGE
    std::ofstream test_file(test_filename);
    test_file << "[ ] 5. Attivita' con ID alto\n";
    test_file << "[X] 12. Altra attivita' con ID alto\n";
    test_file.close();

    TodoList list;

    // ACT
    list.loadFromFile(test_filename);
    list.addActivity("Nuova attivita' aggiunta dopo il caricamento");

    // ASSERT
    const auto& activities = list.getActivities();
    ASSERT_EQ(activities.size(), 3);
    EXPECT_EQ(activities.back().getId(), 13);
}
