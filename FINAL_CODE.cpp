#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <windows.h>  // Include Windows API header for Sleep()
#include <vector>     // Include vector for storing history
#include"MMSystem.h"

using namespace std;
  // ANSI escape code for red color
    const char* redColor = "\033[31m";
    // ANSI escape code to reset color
    const char* resetColor = "\033[0m";

    // Text "SHADOWS" with stylized format using basic characters
    const char* shadowText =
        "\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t  _____ _    _          _____   ______          _______ \n"
        "\t\t\t\t\t / ____| |  | |   /\\   |  __ \\ / __ \\ \\        / / ____|\n"
        "\t\t\t\t\t| (___ | |__| |  /  \\  | |  | | |  | \\ \\  /\\  / / (___  \n"
        "\t\t\t\t\t \\___ \\|  __  | / /\\ \\ | |  | | |  | | \\ \\/  \\/ / \\___ \\ \n"
        "\t\t\t\t\t ____) | |  | |/ ____ \\| |__| | |__| |  \\  /\\  /  ____) |\n"
        "\t\t\t\t\t|_____/|_|  |_/_/    \\_\\_____/ \\____/    \\/  \\/  |_____/ \n";

    // Print the text with red color
//    cout << redColor << shadowText << resetColor << endl;
                                                         
                                                         

// Constants for maximum number of clues, rooms, and suspects
const int MAX_CLUES = 2;
const int MAX_ROOMS = 4;
const int MAX_SUSPECTS = 4;
const int MAX_ATTEMPTS = 20; // Maximum number of attempts

// Base class for clues
class Clue {
public:
    string description;
    string location;
    string analysis;
    string riddle;
    string answer;

    Clue(string d = "", string l = "", string a = "", string r = "", string ans = "")
        : description(d), location(l), analysis(a), riddle(r), answer(ans) {}
};

// Specific types of clues inheriting from Clue
class BloodyRiddle : public Clue {
public:
    BloodyRiddle() : Clue("Bloody riddle on the wall", "Tom Hargrove House", "Clue to the next murder.",
        "Stained with anger, it whispers secrets bold, Black as night, it tells tales of old. What am I?", "shadow") {}
};

class TinyKey : public Clue {
public:
    TinyKey() : Clue("Tiny, elaborate key", "Tom Hargrove House", "Opens a box in Robert's study.") {}
};

class PuzzlePiece : public Clue {
public:
    PuzzlePiece() : Clue("Puzzle piece with a riddle", "Robert's Study", "Part of a bigger puzzle.",
        "In the shadows of revenge, it ticks away, counting past hideous actions, I will slip away. What am I?", "time") {}
};

class BoxNote : public Clue {
public:
    BoxNote() : Clue("Box with a note", "Robert's Study", "Refers to a scandal involving town officials.") {}
};

class FinancialRecords : public Clue {
public:
    FinancialRecords() : Clue("Document with financial records", "Town Hall", "Hidden financial dealings of the mayor.") {}
};

class MarkedMap : public Clue {
public:
    MarkedMap() : Clue("Map with locations marked", "Town Hall", "Points to possible murder sites.") {}
};

class EeriePainting : public Clue {
public:
    EeriePainting() : Clue("Eerie painting", "Elena's Studio", "Predicts the next murder.",
        "Stained with red, it paints the scene. Whose hands wield this brush so keen? In shades of red, a tale unfolds, of secrets kept and truths untold. What am I?","blood"){}
};

class BloodPaintbrush : public Clue {
public:
    BloodPaintbrush() : Clue("Paintbrush with blood", "Elena's Studio", "Blood matches the victim's.") {}
};

class JackSparrowHouseClue : public Clue {
public:
    JackSparrowHouseClue() : Clue("Mysterious knife found", "Jack Sparrow's House", "Belonged to the victim, possibly used in the crime.") {}
};

class JackSparrowHouseSecret : public Clue {
public:
    JackSparrowHouseSecret() : Clue("Hidden key under the victim's body", "Jack Sparrow's House", "Opens a hidden door revealing a dark secret.") {}
};

// Base class for suspects
class Suspect {
public:
    string name;
    string alibi;
    string motive;
    bool isMurderer;
    bool isLying;

    Suspect(string n = "", string a = "", string m = "", bool im = false, bool il = false)
        : name(n), alibi(a), motive(m), isMurderer(im), isLying(il) {}
};

// Specific suspects inheriting from Suspect
class TomHargrove : public Suspect {
public:
    TomHargrove(bool il) : Suspect("Tom Hargrove", "Was in a meeting at the town hall", "Hidden financial dealings", false, il) {}
};

class ElenaMarsh : public Suspect {
public:
    ElenaMarsh(bool il) : Suspect("Elena Marsh", "Was painting in her studio", "Her paintings predict the murders", false, il) {}
};

class DrSamuelLowe : public Suspect {
public:
    DrSamuelLowe(bool il) : Suspect("Dr. Samuel Lowe", "Was at his clinic", "Fascination with dark psychology", false, il) {}
};

class JackSparrow : public Suspect {
public:
    JackSparrow(bool il) : Suspect("Jack Sparrow", "Was at home", "Grudge against town's authorities", true, il) {}
};

// Class for rooms
class Room {
public:
    string name;
    Clue clues[MAX_CLUES];
    string visual;

    Room(string n = "", Clue c[] = nullptr, string v = "") : name(n), visual(v) {
        if (c != nullptr) {
            for (int i = 0; i < MAX_CLUES; ++i) {
                clues[i] = c[i];
            }
        }
    }

    // Function to display the visual representation of the room
    void displayRoomVisual() {
        cout << "Current Room: " << name << "\n";
        cout << visual << "\n";
    }
};

// Class for the detective game
class Game {
private:
    Suspect suspects[MAX_SUSPECTS];
    Room rooms[MAX_ROOMS];
    Clue inventory[MAX_ROOMS * MAX_CLUES];
    int inventorySize;
    int attemptsRemaining;
    int accusationAttempts;
    vector<string> history;  // Vector to store history of actions

    // Initialize suspects and rooms with predefined data
    void initializeSuspects() {
        bool isLying1 = rand() % 2 == 0;
        bool isLying2 = rand() % 2 == 0;
        bool isLying3 = rand() % 2 == 0;
        bool isLying4 = rand() % 2 == 0;

        suspects[0] = TomHargrove(isLying1);
        suspects[1] = ElenaMarsh(isLying2);
        suspects[2] = DrSamuelLowe(isLying3);
        suspects[3] = JackSparrow(isLying4);
    }

    void initializeRooms() {
        // Define clues for each room
        Clue tomClues[] = { BloodyRiddle(), TinyKey() };
        Clue robertClues[] = { PuzzlePiece(), BoxNote() };
        Clue townClues[] = { FinancialRecords(), MarkedMap() };
        Clue elenaClues[] = { EeriePainting(), BloodPaintbrush() };
		
		const string red = "\033[31m";
    	const string reset = "\033[0m";
    	
        // Define rooms with their name, clues, and visual representation
         rooms[0] = Room("Tom Hargrove House", tomClues,
        "           /\\               \n"
        "          /  \\              \n"
        "         /    \\             \n"
        "        /      \\            \n"
        "       /        \\           \n"
        "      /          \\          \n"
        "     /            \\         \n"
        "    /              \\        \n"
        "   /----------------\\       \n"
        "  /                  \\      \n"
        " /  []     []     []  \\     \n"
        "/______________________\\    \n"
        "|   ___           ___   |    \n"
        "|  |   |         |   |  |    \n"
        "|  |___|   " + red + "(O)" + reset + "   |___|  |    \n"
        "|         " + red + "--|--" + reset + "         |    \n"
        "|        " + red + "// | \\ " + reset + "        |    \n"
        "|       " + red + "//  |  \\ " + reset + "       |    \n"
        "|         " + red + "// \\  " + reset + "        |    \n"
        "|        " + red + "//   \\ " + reset + "        |    \n"
        "|_______________________|    \n");

    rooms[1] = Room("Robert's Study", robertClues,
        "    ________________        \n"
        "   /                \\       \n"
        "  /                  \\      \n"
        " /     STUDY          \\     \n"
        "/----------------------\\    \n"
        "|   []     []     []   |    \n"
        "|                      |    \n"
        "|   " + red + " (O)" + reset + "               |    \n"
        "|  " + red + " --|--" + reset + "              |    \n"
        "| " + red + " // | \\ " + reset + "             |    \n"
        "| " + red + "//  |  \\ " + reset + "            |    \n"
        "|  " + red + "// \\ " + reset + "               |    \n"
        "| " + red + "//   \\ " + reset + "              |    \n"
        "|                      |    \n"
        "|______________________|    \n");

    rooms[2] = Room("Town Hall", townClues,
        "       _______________     \n"
        "      /               \\    \n"
        "     /                 \\   \n"
        "    /    TOWN HALL      \\  \n"
        "   /---------------------\\ \n"
        "  /  []    []    []    [] \\ \n"
        " /                         \ \n"
        "|                          |\n"
        "|   " + red + " (O) " + reset + "                  |\n"
        "|  " + red + " --|--  " + reset + "                |\n"
        "| " + red + " // | \\   " + reset + "               |\n"
        "| " + red + "//  |  \\   " + reset + "              |\n"
        "|  " + red + " // \\    " + reset + "               |\n"
        "| " + red + " //   \\    " + reset + "              |\n"
        "|                          |\n"
        "___________________________|\n");

    rooms[3] = Room("Elena's Studio", elenaClues,
        " __________________________\n"
        "|                          |\n"
        "|                          |\n"
        "|          STUDIO          |\n"
        "|--------------------------|\n"
        "|      []         []       |\n"
        "|                          |\n"
        "|                          |\n"
        "|   " + red + "              (O) " + reset + "     |\n"
        "|   " + red + "             --|-- " + reset + "    |\n"
        "|   " + red + "            // | \\ " + reset + "    |\n"
        "|   " + red + "           //  |  \\ " + reset + "   |\n"
        "|   " + red + "             // \\ " + reset + "     |\n"
        "|   " + red + "            //   \\ " + reset + "    |\n"
        "|      |   |               |\n"
        "|      | 0 |               |\n"
        "|      |___|               |\n"
        "|__________________________|\n");
    }

    // Helper function to display centered text
    void displayCenteredText(const string& text) {
        int width = 80;  // assuming a width of 80 characters
        int padding = (width - text.length()) / 2;
        cout << setw(padding) << " " << text << "\n";
    }

    // Helper function to clear the console screen
    void clearScreen() {
        system("cls"); 
    }

    // Helper function to display text with a delay (in milliseconds)
    void displayTextWithDelay(const string& text, int delay = 50) {
        for (char c : text) {
            cout << c << flush;
            Sleep(delay);  // Sleep for specified milliseconds
        }
        cout << "\n";  // Add a new line at the end
    }

    // Function to display the introductory story
    void displayIntroductoryStory() {
    	
    	
        clearScreen();
        displayCenteredText("\t\t\t======================================");
        displayCenteredText("\t\t\tWELCOME TO THE RAVENSWOOD MYSTERY GAME");
        displayCenteredText("\t\t\t======================================");
        displayCenteredText("\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\tYOUR GAME STARTS IN ..... 3");
        Sleep(1000);  // Sleep for 1 second (1000 milliseconds)
        clearScreen();
        displayCenteredText("\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\tYOUR GAME STARTS IN ..... 2");
        Sleep(1000);  // Sleep for 1 second (1000 milliseconds)
        clearScreen();
        displayCenteredText("\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\tYOUR GAME STARTS IN ..... 1");
        Sleep(1000);  // Sleep for 1 second (1000 milliseconds)
        clearScreen();
        displayTextWithDelay("In the quiet town of Ravenswood, a series of mysterious murders has left the residents in fear and uncertainty.", 40);
        displayTextWithDelay("As the town's detective, it is your duty to uncover the truth and bring the killer to justice.", 40);
        displayTextWithDelay("The evidence is scattered, and the suspects are many.", 40);
        displayTextWithDelay("You must gather clues, solve riddles, and interrogate suspects to unravel the mystery.", 40);
        displayTextWithDelay("The killer might hide his actions by leaving clues that make others seem guilty.", 40);
        displayTextWithDelay("All the clues however, will still point to him.",40);
        displayTextWithDelay("But be careful, as the killer is cunning and will do anything to cover their tracks.", 40);
        displayTextWithDelay("The fate of Ravenswood rests in your hands...", 40);
    	displayTextWithDelay("All the witness could say is that they saw a SHADOW..", 40);
        displayTextWithDelay("Can you solve the mystery before it's too late?", 40);
        displayTextWithDelay("                    LET THE GAME BEGIN!! ",40);
        Sleep(2000);  // Sleep for 2 seconds (2000 milliseconds) to allow the player to read the story
        clearScreen();

        displaySuspects();
        Sleep(1000);
    }

    // Function to record an action in the history
    void recordAction(const string& action) {
        history.push_back(action);
    }

    // Function to investigate a room and gather clues
void investigateRoom(int roomIndex) {
    clearScreen();
    displayCenteredText("INVESTIGATING ROOM: " + rooms[roomIndex].name);
    rooms[roomIndex].displayRoomVisual();
    for (int i = 0; i < MAX_CLUES; ++i) {
        if (!rooms[roomIndex].clues[i].description.empty()) {
            displayTextWithDelay("Clue found: " + rooms[roomIndex].clues[i].description, 40);
            Sleep(1000);  // Wait for 1 second after displaying clue description
            displayTextWithDelay("Location: " + rooms[roomIndex].clues[i].location, 40);
            Sleep(1000);  // Wait for 1 second after displaying location
            displayTextWithDelay("Analysis: " + rooms[roomIndex].clues[i].analysis, 40);
            Sleep(1000);  // Wait for 1 second after displaying analysis
            if (!rooms[roomIndex].clues[i].riddle.empty()) {
                displayTextWithDelay("Riddle: " + rooms[roomIndex].clues[i].riddle, 40);
                Sleep(1000);  // Wait for 1 second after displaying riddle
                string answer;
                cout << "Answer: ";
                getline(cin, answer);
                if (answer == rooms[roomIndex].clues[i].answer) {
                    displayTextWithDelay("Correct! You solved the riddle.", 40);
                } else {
                    displayTextWithDelay("Incorrect. The answer was: " + rooms[roomIndex].clues[i].answer, 40);
                }
                Sleep(1000);  // Wait for 1 seconds after displaying answer
            }
            inventory[inventorySize++] = rooms[roomIndex].clues[i];
            recordAction("Investigated " + rooms[roomIndex].name);
        }
    }
}

    // Function to interrogate a suspect
    void interrogateSuspect(int suspectIndex) {
        clearScreen();
        displayCenteredText("INTERROGATING SUSPECT: " + suspects[suspectIndex].name);
        displayTextWithDelay("Name: " + suspects[suspectIndex].name, 40);
        displayTextWithDelay("Alibi: " + suspects[suspectIndex].alibi, 40);
        displayTextWithDelay("Motive: " + suspects[suspectIndex].motive, 40);
        displayTextWithDelay("Lying: " + string(suspects[suspectIndex].isLying ? "Yes" : "No"), 40);
        recordAction("Interrogated " + suspects[suspectIndex].name);
        Sleep(1000);
    }

    // Function to accuse a suspect
    void accuseSuspect() {
        clearScreen();
        displayCenteredText("ACCUSE A SUSPECT");
        for (int i = 0; i < MAX_SUSPECTS; ++i) {
            displayCenteredText(to_string(i + 1) + ". " + suspects[i].name);
        }
        int suspectChoice;
        cout << "Enter the number of the suspect you want to accuse: ";
        cout<<"1. Tom Hargrove"<<endl;
        cout<<"2. Elena Marsh"<<endl;
        cout<<"3. Dr.Samuel Lowe"<<endl;
        cout<<"4. Jack Sparrow"<<endl;
        cin >> suspectChoice;
        cin.ignore();  // Ignore the newline character after the integer input
        if (suspects[suspectChoice - 1].isMurderer) {
         displayTextWithDelay("Congratulations! You have correctly identified the murderer.", 40);
         displayTextWithDelay("Jack Sparrow, consumed by his grudge, is captured by the authorities.", 40);
         displayTextWithDelay("His actions have brought the town to the brink, leaving it in the cove of uncertainty.", 40);
         displayTextWithDelay("The town is now in the light, but for how long?", 40);

            recordAction("Accused and correctly identified " + suspects[suspectChoice - 1].name + " as the murderer.");
            exit(0);
        } else {
            displayTextWithDelay("Incorrect. The murderer is still at large.", 40);
            accusationAttempts--;
            if (accusationAttempts == 0) {
                displayTextWithDelay("You have used all your accusation attempts. The murderer has escaped.", 40);
                exit(0);
            }
        }
    }

    // Function to view inventory, suspects, and history
    void viewInventory() {
        clearScreen();
        displayCenteredText("INVENTORY:");
        for (int i = 0; i < inventorySize; ++i) {
            displayTextWithDelay(to_string(i + 1) + ". " + inventory[i].description, 40);
        }
        displayCenteredText("\n\nSUSPECTS:");
        displaySuspects();
        displayCenteredText("\n\nACTION HISTORY:");
        for (const auto& action : history) {
            displayTextWithDelay(action, 60);
        }
    }

    // Function to display details of all suspects
    void displaySuspects() {
        displayCenteredText("SUSPECTS:");
        for (int i = 0; i < MAX_SUSPECTS; ++i) {
            displayTextWithDelay("Name: " + suspects[i].name, 40);
            displayTextWithDelay("Alibi: " + suspects[i].alibi, 40);
            displayTextWithDelay("Motive: " + suspects[i].motive, 40);
            displayTextWithDelay("Lying: " + string(suspects[i].isLying ? "Yes" : "No"), 40);
            displayTextWithDelay("---------------------------------------", 40);
        }
    }

public:
    // Constructor to initialize the game
    Game() : inventorySize(0), attemptsRemaining(MAX_ATTEMPTS), accusationAttempts(2) {
    	   // PlaySound(TEXT("pin.wav"),NULL,SND_SYNC);
    	  //system(" pause ");
	
        srand(time(0));
        initializeSuspects();
        initializeRooms();
          
		PlaySound(TEXT("audio.wav"), NULL, SND_ASYNC | SND_LOOP);
        
    }
 
   
   // Function to start the game
    void start(const char* text) {
    		cout << redColor<<text<<resetColor<<endl; 
        Sleep(3000);
		
        displayIntroductoryStory();
        while (attemptsRemaining > 0) {
            clearScreen();
            displayCenteredText("ATTEMPTS REMAINING: " + to_string(attemptsRemaining));
            displayCenteredText("Choose an option:");
            displayCenteredText("1. Investigate a room");
            displayCenteredText("2. Interrogate a suspect");
            displayCenteredText("3. Accuse a suspect");
            displayCenteredText("4. View inventory");
            displayCenteredText("5. Exit");
            int choice;
            cout << "Enter your choice: ";
            cin >> choice;
            cin.ignore();  // Ignore the newline character after the integer input
            switch (choice) {
                case 1:
                    for (int i = 0; i < MAX_ROOMS; ++i) {
                        displayCenteredText(to_string(i + 1) + ". " + rooms[i].name);
                    }
                    int roomChoice;
                    cout << "Enter the number of the room to investigate: ";
                    cin >> roomChoice;
                    cin.ignore();  // Ignore the newline character after the integer input
                    investigateRoom(roomChoice - 1);
                    attemptsRemaining--;
                    break;
                case 2:
                    for (int i = 0; i < MAX_SUSPECTS; ++i) {
                        displayCenteredText(to_string(i + 1) + ". " + suspects[i].name);
                    }
                    int suspectChoice;
                    cout << "Enter the number of the suspect to interrogate: ";
                    cin >> suspectChoice;
                    cin.ignore();  // Ignore the newline character after the integer input
                    interrogateSuspect(suspectChoice - 1);
                    attemptsRemaining--;
                    break;
                case 3:
                    accuseSuspect();
                    attemptsRemaining--;
                    break;
                case 4:
                    viewInventory();
                    break;
                case 5:
                    exit(0);
                default:
                    displayTextWithDelay("Invalid choice. Please try again.", 40);
            }
           
        }
        displayTextWithDelay("You have used all your attempts. The murderer has escaped.", 40);
    }
};

// Main function to start the game
int main() {
    Game game;
    game.start(shadowText);
    
   // PlaySound(TEXT("pin.wav"),NULL,SND_SYNC);
    // system(" pause ");
	
	return 0;
}