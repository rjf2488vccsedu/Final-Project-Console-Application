/******************************************************************************
05/06/21
*******************************************************************************/
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// Struct declaration
struct Person{  
    
    string personName,
           personDOB;
           
    long personSSN,
         fatherSSN,
         motherSSN;
    
    char personGender;
    
    float personHeight,
          personWeight;
    
    Person* next;                                         
};
// End struct declaration

// Function prototypes
void show_welcomeMsg();

void show_goodbyeMsg();

int user_input();                                   // Utility -- user input

bool menu_loop(bool, Person*);                      // Main menu

Person* populate_Person(string);                    // Initial dataset

struct Person* swap_Person(struct Person*,          // Utility -- swap nodes
                           struct Person*);

int get_nodeCount(Person*);                         // Utility

void print_PersonNodes(Person*);                    // Utility

Person* sort_bySSN(struct Person**);                // Option 1

Person* delete_Person(Person**);                    // Option 2

Person* input_newPerson(Person**);                  // Option 3

Person* add_bulkPerson(Person**);                   // Option 4

void edit_PersonData(Person*);                      // Option 5

void display_Eligibility(Person*);                  // Option 6

void display_Cardiovascular_Risk (Person *);	    // Option 7

float get_BMI (Person *);                   	    // Gets BMI

void PersonPosition_swap(Person*, Person*);         // Positions person

void femaleMaleRatio(Person* head);                 // Option 8

void display_Parents(Person*);                      // Option 9

void display_Children(Person*);                     //Option 10

Person* option_ten(Person*);

void display_Siblings(Person*);

Person* option_twelve(Person*);

// File generation
void gen_file();                                    // create persondata.txt
void gen_suppFile();                                // create supplement.txt
// End function prototypes

// Driver
int main() {
     // ------------// [ IMPORTANT INFORMATION Please Read all of this ] \\------------ \\
    
    //          [ persondata.txt generation ]
    //       [ [Run this function at least once] ]
    //gen_file(); return 0; // Comment this out after running once to make the file
   
    //            [ supplement.txt generation ]
    //gen_suppFile();  return 0; // Comment this out after running once to make the file
    
    // P.S make sure you remove the extra line generated (last line) in each file. If you don't you will get an error.
    
        
    // Hello
    show_welcomeMsg();
    
    // Var declarations
    bool quit = false;                  // Control flow
    
    string fileName = "persondata.txt"; // Modularize filename for both file 
                                        // function calls; initialize to file 1
                                        // Change to "supplement.txt" in #4 call
    // End var declarations
    
    // Initialize Struct 
    Person* head = new Person;  // Independent person
    head -> next = NULL;
    // End Struct initialization
    
    // Populate Struct w/ start file -- first "module" before calling menu
    head = populate_Person(fileName);

    // Initial list sort
    sort_bySSN(&head);
    
    // Initial List Print            
    print_PersonNodes(head);
    
    
    
    // Main menu loop
    while (quit == false && cin) {
        
        quit = menu_loop(quit, head);  //  Exit on flag
    }
    
    // Goodbye
    show_goodbyeMsg();
    
    return 0;
}    

// Function definitions





// Utility function to get person count
// Parameters: Person* (head)
// Returns: Int (# of nodes)
int get_nodeCount(Person* head) {
    
    Person* temp = head;
    
    int nodeCount = 0;
    
    while(temp != NULL) {
        
        nodeCount++;
        temp = temp -> next;
    }
    
    return nodeCount;
}

// Utility function to swap for sorting
// Parameters: Person* node
// Returns: Second Person* node as defined when called
struct Person* swap_Person(struct Person* nodeOne, struct Person* nodeTwo) {
    
    struct Person* temp = nodeTwo -> next;
    
    nodeTwo -> next = nodeOne;
    
    nodeOne -> next = temp;

    return nodeTwo;
}


// Find and print Parents of a person
// Parameters: Pointer to head of person struct
// Returns: Void
void display_Parents(Person* head)
{
    Person* targetPerson{head};
    Person* current{head};
    
    string currentLine{0};
    long searchSSN{0};
    
    cin.ignore();
    
    cout << "\nEnter the SSN of a person to find their Mother and Father " << endl;
    getline(cin,currentLine);
    
    searchSSN = stol(currentLine);
    
    
    while(current->next != NULL) // Associate entered SSN with actual person Node
    {
        if(searchSSN == current->personSSN)
        {
            std::cout<< "\nSSN entered matches " << current->personName << "\n\n";
            break;
        }
             
        
        current = current->next;
    }
    
    targetPerson = current;
    
    current = head; // Reset to the begining of the person list
    
    std::cout<< targetPerson->personName << " Parents: \n";
    
    while(current->next != NULL) // Compare target person's Mother SSN to the SSN of everyone else
    {
        if(targetPerson->motherSSN == current->personSSN)
        {
            std::cout<< "Mother: " << current->personName << '\n';
            break;
        }
        
        current = current->next;
    }
    
    if(current->next == NULL)
        std::cout<< " Mother is not on the list\n\n";
    
    current = head; // Reset to the begining of the person list
    
    while(current->next != NULL) // Compare target person's father SSN to the SSN of everyone else
    {
        if(targetPerson->fatherSSN == current->personSSN)
        {
            std::cout<< "Father: " << current->personName << "\n\n";
            break;
        }
    
        current = current->next;
    }
    
    if(current->next == NULL)
        std::cout<< "Father is not on the list\n\n";
    
}

// Find the children of a given SSN
// Parameters: Pointer to head of person struct
// Returns: Void
void display_Children(Person* head) //Option 10
{
    Person* targetPerson{head};
    Person* current{head};
    
    string currentLine{0};
    long searchSSN{0};
    
    cin.ignore();
    
    cout << "\nEnter the SSN of a person to find children. " << endl;
    getline(cin,currentLine);
    
    searchSSN = stol(currentLine);
    
    
    while(current->next != NULL) // Associate entered SSN with actual person Node
    {
        if(searchSSN == current->personSSN)
        {
            std::cout<< "\nSSN entered matches " << current->personName << "\n\n";
            break;
        }
             
        current = current->next;
        
    }
    targetPerson = current;
    
    current = head; // Reset to the begining of the person list
    
    cout<<"The children are: \n";
    
    while(current->next != NULL) //Checks if the SSN the user input matches with the SSN of the mothers.
    {
        if(targetPerson->personSSN == current->motherSSN)
        {
            cout<< current->personName << '\n'; //If true, will print the name of the child(current).
            
        }
        
        current = current->next;
    }
    
  
    
    current = head; // Reset to the begining of the person list
    
    while(current->next != NULL) //Checks if the SSN the user input matches with the SSN of the fathers.
    {
        if(targetPerson->personSSN == current->fatherSSN)
        {
            cout<< current->personName << '\n'; //If true, will print the name of the child(current).
            
        }
        
        current = current->next;
    }
    

}


// Instantiate new person from user input and insert into sorted list
// Parameters: Person** (reference pointer to head)
// Returns: Person* (head)
Person* input_newPerson(Person** head) {
    
    string currentLine;
        
    cin.ignore();
        
    int count = 0;
        
    Person* userPerson = new Person;

    cout << "Please enter the new person's name: " << endl;
        
    getline(cin, currentLine);
    userPerson -> personName = currentLine;
        
    cout << "Please enter the new person's SSN: " << endl;
        
    getline(cin, currentLine);
    userPerson -> personSSN = stol(currentLine); 
        
    cout << "Please enter the new person's gender: " << endl;
        
    getline(cin, currentLine);
    userPerson -> personGender = currentLine[0]; 
        
    cout << "Please enter the new person's DOB: " << endl;
        
    getline(cin, currentLine);
    userPerson -> personDOB = currentLine; 
    
    cout << "Please enter the new person's height: " << endl;

    getline(cin, currentLine);
    userPerson -> personHeight = stof(currentLine);
    
    cout << "Please enter the new person's weight: " << endl;
    
    getline(cin, currentLine);
    userPerson -> personWeight = stof(currentLine);
    
    cout << "Please enter the new person's father's SSN: " << endl;
    
    getline(cin, currentLine);
    userPerson -> fatherSSN = stol(currentLine);
    
    cout << "Please enter the new person's mother's SSN: " << endl;
    
    getline(cin, currentLine);
    userPerson -> motherSSN = stol(currentLine);
    
    Person* current = *head;
        
    struct Person** headPointer;
                
    headPointer = head;
    
    while (current -> next != NULL) {
        
        if (current -> personSSN < userPerson -> personSSN) {

            if (current -> next -> personSSN > userPerson -> personSSN) {
                
                Person* prev = current;
            
                userPerson -> next = prev -> next;
            
                prev -> next = userPerson;
                
                break;
            }    
   
        } else {
            
            userPerson -> next = (*headPointer);
            
            (*headPointer) = userPerson;
            
            break;
        }
            
        current = current -> next;
    }
        
    if (current -> next == NULL) {
                
        userPerson -> next = NULL;
                    
        current -> next = userPerson;
    }
    
    cout << "Addition operation successful!" << endl;
    
    cout << "Person " << userPerson -> personSSN << " added." << endl;
    
    cout << "Updating database..." << endl;
            
    return *head;
}

// Sort ascending by SSN w/ bubblesort -- recursive call to swap_Person
// Parameters: Reference pointer to head of person struct
// Returns: Person*
Person* sort_bySSN(struct Person** head) {
    
    struct Person** headPointer;
    
    int PersonCount = get_nodeCount(*head);
    
    bool sorted = false,
         done = false;
    
    for (int i = 0; i <= PersonCount; i++) {
        
        headPointer = head;
        
        for (int j = 0; j < (PersonCount - i - 1); j++) {
            
            struct Person* nodeOne = *headPointer;
            
            struct Person* nodeTwo = nodeOne -> next;
            
            if (nodeOne -> personSSN > nodeTwo -> personSSN) {
                
                *headPointer = swap_Person(nodeOne, nodeTwo);
                
                sorted = true;
                done = true;
            }
            
            headPointer = &(*headPointer) -> next;
        }
        
        if (done == false) {
            
            sorted = true;
        }
    }
      
    return *head;
}

// Display all persons eligible for social security
// Parameters: Pointer to head of person struct
// Returns: Void
void display_Eligibility(Person* head)
{
    Person* current{head};

    std::cout<< "\nEligible for social security: \n";

    while(current->next != NULL)
    {
        if( 2021 - stoi(current->personDOB.substr(0,4)) >= 65 )
        {
            std::cout<< current->personName << ": Age: " << 2021 - stoi(current->personDOB.substr(0,4)) << '\n';
        }
        
        current = current->next;
    }
}

void display_Siblings(Person* head)
{
    Person* targetPerson{head};
    Person* current{head};
    Person* targetDOB{head};
    
    string currentLine{0};
    long searchSSN{0};
    
    cin.ignore();
    
    cout << "\nEnter the SSN of a person to find their sibling " << endl;
    getline(cin,currentLine);
    
    searchSSN = stol(currentLine);
    
    
    while(current->next != NULL) // Associate entered SSN with actual person Node
    {
        if(searchSSN == current->personSSN)
        {
            std::cout<< "\nSSN entered matches " << current->personName << "\n\n";
            break;
        }
             
        
        current = current->next;
    }
    
    targetPerson = current;
    
    current = head; // Reset to the begining of the person list
    
    int tempDOB;
    
    while(current->next != NULL) // Compare target person's SSN to the SSN of everyone else
    {
       
        if( (targetPerson->motherSSN == current->motherSSN) && (current->personSSN != targetPerson->personSSN) || (targetPerson->fatherSSN == current->fatherSSN) && (current->personSSN != targetPerson->personSSN))
        {
           targetDOB=current;
           
           if( 2021 - stoi(targetDOB->personDOB.substr(0,4)) > (2021 - stoi(targetDOB->next->personDOB.substr(0,4))))// compare the data of the nodes 
           {
            
              
              targetDOB->personDOB = targetDOB->next->personDOB;// swap the data
              
            
            }
              std::cout<< "Sibling: " << current->personName << " | " << targetDOB->personDOB << "\n\n";
              targetDOB = targetDOB -> next;
           }
          current = current->next;
        }
    }
        
   

// Edit Person  Name, Height and Weight for that SSN
// Parameters: Pointer to head of person struct
// Returns: Void
void edit_PersonData(Person* head)
{
    Person* current{head};
    
    long targetSSN{0};
    
    string currentLine;
    string newdata{""};
    
    cin.ignore();
    
    std::cout<< "Enter the SSN of the person to be edited: ";
    getline(cin,currentLine);
    
    targetSSN = stol(currentLine);
    
    
    while(current->next != NULL)
    {
        if(current->personSSN == targetSSN)
        {
            std::cout<< "SSN entered matches " << current->personName << '\n';
            std::cout<< "Editing commenced. Press 0 to keep original data\n";
            
            std::cout<< "Enter new Name: ";    
            getline(cin,newdata);
            if(newdata[0] != '0')
                current->personName = newdata;
            else
                std::cout<< "Retaining original data.\n";
            
            std::cout<< "Enter new Height: "; 
            getline(cin,newdata);
             if(newdata[0] != '0')
                current->personHeight = stof(newdata);
            else
                std::cout<< "Retaining original data.\n";
           
            
            std::cout<< "Enter new Weight: "; 
            getline(cin,newdata);
             if(newdata[0] != '0')
                current->personWeight= stof(newdata);
            else
                std::cout<< "Retaining original data.\n";
           
        }
        
        current = current->next;
    }
    
    std::cout<< "Editing Completed.\n";
    
}

// Print person Nodes
// Parameters: Pointer to head of person struct
// Returns: Void
void print_PersonNodes(Person* head) {

    Person* current = head;
    
    cout << endl;

    cout << "Here is the linked list of persons: " << endl << endl;

    while (current != NULL) {
        
        cout << current -> personName << " | "
             << current -> personSSN << " | "
             << current -> personGender << " | "
             << current -> personDOB << " | "
             << current -> personHeight << " | "
             << current -> personWeight << " | "
             << current -> fatherSSN << " | "
             << current -> motherSSN << " | "
             << endl;
        
        current = current -> next;
    }
    
    cout << endl; 
} 

// Welcome
// Parameters: None
// Returns: Void
void show_welcomeMsg() {                                                                
    cout << "Welcome to the Person Struct Linked List Manager!" 
         << endl << endl;
}

// Get user input
// Parameters: none
// Returns: Int
int user_input() {
    
    int inp = 0;
    
    while (cin >> inp) {
        
        return inp;
    } 
}

// Delete person from list, with user input SSN as key
// Parameters: Person** (Reference Person* -- call w/ &Person)
// Returns: Person*
Person* delete_Person(Person** head) {
    
    bool keyFound = false;
    
    string currentLine;
    
    cin.ignore();

    cout << "Enter the SSN of the person to be deleted: " << endl;
    
    getline(cin, currentLine);
    
    long key = stol(currentLine);
    
    Person* temp = *head;
    
    Person* prev = NULL;
    
    if (temp != NULL && temp -> personSSN == key) {

        *head = temp -> next;
        
        delete temp;
        
    } else {
        
        while (temp != NULL && temp -> personSSN != key) {
            
            prev = temp;
            
            temp = temp -> next;
            
            keyFound = true;
        }
    }
    
    if (temp == NULL) {
        
        cout << "Indicated SSN not found!" << endl;
        
        keyFound = false;
        
        cin.ignore();
        
        return *head;
    }    
    
    prev -> next = temp -> next;
        
    delete temp;
    
    cout << "Deletion operation successful!" << endl;
    
    cout << "Person " << temp -> personSSN << " deleted." << endl;
    
    cout << "Updating database..." << endl;
    
    return *head;
}

// Switchboard for menu options 
// Parameters: Bool, pointer to head of person struct
// Returns: Bool
bool menu_loop(bool quit, Person* head) {
    
    int choice = 0;
    
    bool dontQuitMenu = true;
    
    cout << "Menu Options: " << endl; 
    cout << "1: Display List By Ascending SSN" << endl;
    cout << "2: Delete Existing Person" << endl;
    cout << "3: Add New Person" << endl;
    cout << "4: Add New Persons From Supplemental File" << endl;
    cout << "5: Edit Person Data" << endl;
    cout << "6: Display all persons eligible for social security" << endl;
    cout << "7: Display all people at high risk for cardiovascular disease." << endl;
    cout << "8: Display the ratio of females to males." << endl;
    cout << "9: Display the parents of a person" << endl;
    cout << "10: Finds the children of a person " << endl;
    cout << "11: Display the siblings of a person " << endl;
    cout << "12: Display all uncles, aunts, cousins, nephews and nieces of a person" << endl;
         
    while (cin && dontQuitMenu == true) {
        
        cout << "Enter option 1-12, or enter -1 to show menu again. "
            << "Enter anything else to exit." << endl;    
        
        choice = user_input(); 
    
        switch (choice) {
        
            case -1:

                cout << "Menu options: " << endl;
                cout << "1: Display List By Ascending SSN" << endl;
                cout << "2: Delete Existing Person" << endl;
                cout << "3: Add New Person" << endl;
                cout << "4: Add New Persons From Supplemental File" << endl;
                cout << "5: Edit Person data" << endl;
                cout << "6: Display all persons eligible for social security" << endl;
                cout << "7: Display all people at high risk for cardiovascular disease." << endl;
                cout << "8: Display the ratio of females to males." << endl;
                cout << "9: Display the parents of a person" << endl;
                cout << "10: Finds the children of a person " << endl;
                cout << "11: Display the siblings of a person " << endl;
                cout << "12: Display all uncles, aunts, cousins, nephews and nieces of a person" << endl;
            
                break;
            
            case 1:
            
                cout << "Option 1: Display List By Ascending SSN" << endl;
                
                sort_bySSN(&head);
                
                print_PersonNodes(head);
            
                break;
        
            case 2:
            
                cout << "Option 2: Delete Existing Person" << endl;
                
                cin.clear();
                
                print_PersonNodes(head);
                
                head = delete_Person(&head);
                
                print_PersonNodes(head);
                
                break;
        
            case 3:
            
                cout << "Option 3: Add New Person" << endl;
            
                input_newPerson(&head);
                
                print_PersonNodes(head);

                break;
        
            case 4:
            
                cout << "Option 4: Add New Persons From Supplemental File" << endl;

                head = add_bulkPerson(&head);
    
                sort_bySSN(&head);
                
                print_PersonNodes(head);
            
                break;
        
            case 5:
            
                cout << "Option 5" << endl;
            
                print_PersonNodes(head);
                
                edit_PersonData(head); 
                
                print_PersonNodes(head);
            
                break;
        
            case 6:
            
                cout << " Option 6: Display all persons eligible for social security" << endl;
            
                display_Eligibility(head);
            
                break;
        
            case 7:
            
                cout << "7: Display all people at high risk for cardiovascular disease." << endl;
            
                 //get_BMI(head);
      
	  	        display_Cardiovascular_Risk(head);
            
                break;
            
            case 8:
            
                cout << "Option 8: Display ratio of females to males." << endl;
            
                femaleMaleRatio(head);
            
                break;
            
            case 9:
            
                cout << "Option 9: Display the parents of a person" << endl;
            
                display_Parents(head);
            
                break;
            
            case 10:
            
                 cout << "Option 10: Display the children of a person" << endl;
            
                display_Children(head);
            
                break;
            
            case 11:
            
                cout << "Option 11: Display the siblings of a person" << endl;
            
                display_Siblings(head);
            
                break;
            
            case 12:
            
                cout << "Display all uncles, aunts, cousins, nephews and nieces of a person" << endl;
            
                head = option_twelve(head);
            
                break;

            default:
            
                cout << "Terminating." << endl;
            
                return dontQuitMenu;
        }
    
    }
    return dontQuitMenu;
}    

// Populate persons from file and return person count
// Parameters: String -- initial file of 20 people (persondata.txt)
// Returns: Person*
Person* populate_Person(string fileName) {
    
    Person* head = new Person;
    head -> next = NULL;
    
    Person* current = head;
    Person* newPerson;
    
    ifstream dataFile;
    dataFile.open(fileName);
    
    string currentLine;
    
    while (!dataFile.eof()) {  
        
        getline(dataFile, currentLine);
        current -> personName = currentLine;
        
        getline(dataFile, currentLine);
        current -> personSSN = stol(currentLine); 
        
        getline(dataFile, currentLine);
        current -> personGender = currentLine[0]; 
        
        getline(dataFile, currentLine);
        current -> personDOB = currentLine; 

        getline(dataFile, currentLine);
        current -> personHeight = stof(currentLine);
        
        getline(dataFile, currentLine);
        current -> personWeight = stof(currentLine);
        
        getline(dataFile, currentLine);
        current -> fatherSSN = stol(currentLine);
        
        getline(dataFile, currentLine);
        current -> motherSSN = stol(currentLine);            
        
        newPerson = new Person;         
        current -> next = newPerson;    
        current = newPerson;
    }
    
    dataFile.close();
    
    current = head;
    
    Person* prevPerson;
    
    while (current -> next != NULL) {    
        
        prevPerson = current;
        
        current = current -> next;
    }
    
    prevPerson -> next = NULL;
    
    delete newPerson;
    
    newPerson -> next = NULL;
    
    current = head;
    
    return head;
}

// Populate persons from file and return person count
// Parameters: Person** (reference pointer to head)
// Returns: Person*
Person* add_bulkPerson(Person** head) {
    
    string suppLine;
          string fileName = "supplement.txt";
    
    Person* current = *head; 

    while (current -> next != NULL) {
        current = current -> next;
    } 
    
    ifstream dataFile;
    dataFile.open(fileName);

    while (!dataFile.eof()) { 
        
        Person* newPerson = new Person;
        current -> next = newPerson;    
        current = newPerson;
        
        getline(dataFile, suppLine);
        current -> personName = suppLine;
        
        getline(dataFile, suppLine);
        current -> personSSN = stol(suppLine);
                
        getline(dataFile, suppLine);
        current -> personGender = suppLine[0]; 
        
        getline(dataFile, suppLine);
        current -> personDOB = suppLine; 
    
        getline(dataFile, suppLine);
        current -> personHeight = stof(suppLine);

        getline(dataFile, suppLine);
        current -> personWeight = stof(suppLine);
    
        getline(dataFile, suppLine);
        current -> fatherSSN = stol(suppLine);

        getline(dataFile, suppLine);
        current -> motherSSN = stol(suppLine);
    }
    
    dataFile.close();
    
    current = *head;
  
    cout << "Bulk addition operation successful!" << endl;
    
    cout << "Updating database..." << endl;
    
    return *head;
}


void display_Cardiovascular_Risk(Person* head)
{
    Person* current{head};
    Person* temp{NULL};
    float bmi{0};
    float maxBMI{0};

    std::cout<< "\nPeople at risk of cardiovascular disease if any: \n";
    
     for(int count{0}; count < get_nodeCount(head); ++count)
    {
        bmi = (((current->personWeight / current->personHeight) / current->personHeight) * 703);

        if(bmi > 27.0)
        {
             PersonPosition_swap(current, current->next);
            break;
        }
        
       
        
        current = current->next;
    }
    


    current = head;

    while(current->next != NULL)
    {
        bmi = (((current->personWeight / current->personHeight) / current->personHeight) * 703);

        if( bmi > 27.001 )
        {
            std::cout<< current->personName << ": BMI: " << bmi << '\n';
        }

        current = current->next;
    }
    
    
    cout<< endl;
}

void PersonPosition_swap(Person* person1, Person* person2)
{
    Person* temp = person2->next;
    person2->next = person1;
    person1->next = temp;
}

float get_BMI (Person * head)
{
  Person* person1;
  Person* person2;
  float bmi;
  Person* current = head;
}

// Calculate and display f:m/1k ratio
// Parameters: Pointer to head of person struct
// Returns: Void
void femaleMaleRatio(Person* head) {
    
    Person* current = head;
    
    int maleCount = 0,
         femaleCount = 0;
    
    while (current != NULL) {
    
       if (current -> personGender == 'M') {
            
            maleCount++;
            
        } else {
       
            femaleCount++;
        }
      
        current = current -> next; 
    }

    float genRatio = ((static_cast<float>(femaleCount)/static_cast<float>(maleCount)) * 1000);
    
    cout << "The ratio of females to male per thousand is: " << genRatio << endl << endl;
}


// Option 12
// Parameters: Pointer to head of person struct
// Returns: Pointer to head of person struct
Person* option_twelve(Person* head) {
    
    cout << "Fnct 12" << endl;
    
    return head;
}

// Goodbye
// Parameters: None
// Returns: Void
void show_goodbyeMsg() {                                                              
	cout << endl << "Thank you for using the Person Struct Linked List " 
	     << "Manager!" << endl;
}

// persondata.txt generator
void gen_file() {
    
    ofstream outFile("persondata.txt");
        
    outFile << "Gregory Lennon" << endl;
    outFile << "4008140130" << endl;
    outFile << "M" << endl;
    outFile << "1930/06/11" << endl;
    outFile << "58.43" << endl;
    outFile << "148.02" << endl;
    outFile << "1212288810" << endl;
    outFile << "8486152371" << endl;
    outFile << "Lucian Schroeder" << endl;
    outFile << "9472071038" << endl;
    outFile << "M" << endl;
    outFile << "1950/07/14" << endl;
    outFile << "71.11" << endl;
    outFile << "186.33" << endl;
    outFile << "1834506014" << endl;
    outFile << "8311020265" << endl;
    outFile << "Charis Wong" << endl;
    outFile << "8130876020" << endl;
    outFile << "F" << endl;
    outFile << "1950/05/27" << endl;
    outFile << "53.09" << endl;
    outFile << "126.77" << endl;
    outFile << "7183804452" << endl;
    outFile << "6573650338" << endl;
    outFile << "Marwan Livingston" << endl;
    outFile << "7032751630" << endl;
    outFile << "M" << endl;
    outFile << "1980/08/01" << endl;
    outFile << "69.05" << endl;
    outFile << "171.22" << endl;
    outFile << "1834506014" << endl;
    outFile << "8311020265" << endl;
    outFile << "Manraj Perez" << endl;
    outFile << "8058302380" << endl;
    outFile << "M" << endl;
    outFile << "1958/03/17" << endl;
    outFile << "67.12" << endl;
    outFile << "144.81" << endl;
    outFile << "3761880562" << endl;
    outFile << "5466880215" << endl;
    outFile << "Eamonn Stanton" << endl;
    outFile << "8736458682" << endl;
    outFile << "M" << endl;
    outFile << "1940/06/08" << endl;
    outFile << "69.99" << endl;
    outFile << "150.47" << endl;
    outFile << "7655288240" << endl;
    outFile << "2878202873" << endl;
    outFile << "Ananya Reese" << endl;
    outFile << "1878446120" << endl;
    outFile << "F" << endl;
    outFile << "1968/12/25" << endl;
    outFile << "57.19" << endl;
    outFile << "123.45" << endl;
    outFile << "1212288810" << endl;
    outFile << "8486152371" << endl;
    outFile << "Adina Morgan" << endl;
    outFile << "6435484662" << endl;
    outFile << "F" << endl;
    outFile << "1987/03/03" << endl;
    outFile << "66.66" << endl;
    outFile << "138.42" << endl;
    outFile << "3350074578" << endl;
    outFile << "8702271843" << endl;
    outFile << "Madeleine Squires" << endl;
    outFile << "4415121732" << endl;
    outFile << "F" << endl;
    outFile << "1960/02/19" << endl;
    outFile << "60.32" << endl;
    outFile << "127.05" << endl;
    outFile << "2371870841" << endl;
    outFile << "5386088001" << endl;
    outFile << "Malia Bauer" << endl;
    outFile << "7810715561" << endl;
    outFile << "F" << endl;
    outFile << "1990/07/24" << endl;
    outFile << "62.76" << endl;
    outFile << "131.44" << endl;
    outFile << "7664121403" << endl;
    outFile << "4065560288" << endl;
    outFile << "Dwayne McDaniel" << endl;
    outFile << "2534617327" << endl;
    outFile << "M" << endl;
    outFile << "1950/05/10" << endl;
    outFile << "64.87" << endl;
    outFile << "159.99" << endl;
    outFile << "7664121403" << endl;
    outFile << "4065560288" << endl;
    outFile << "Cosmo Arnold" << endl;
    outFile << "7024715632" << endl;
    outFile << "M" << endl;
    outFile << "197/10/12" << endl;
    outFile << "68.53" << endl;
    outFile << "190.55" << endl;
    outFile << "5657545551" << endl;
    outFile << "8824238846" << endl;
    outFile << "Addison McMahon" << endl;
    outFile << "3054408150" << endl;
    outFile << "M" << endl;
    outFile << "1930/06/11" << endl;
    outFile << "58.43" << endl;
    outFile << "148.02" << endl;
    outFile << "1177562016" << endl;
    outFile << "1134541068" << endl;
    outFile << "Albert Key" << endl;
    outFile << "4737134755" << endl;
    outFile << "M" << endl;
    outFile << "1950/07/14" << endl;
    outFile << "71.11" << endl;
    outFile << "186.33" << endl;
    outFile << "4351238762" << endl;
    outFile << "4453754678" << endl;
    outFile << "Rosalie Austin" << endl;
    outFile << "9810808201" << endl;
    outFile << "F" << endl;
    outFile << "1950/05/27" << endl;
    outFile << "53.09" << endl;
    outFile << "126.77" << endl;
    outFile << "3567833621" << endl;
    outFile << "7185667065" << endl;
    outFile << "Mica Gonzalez" << endl;
    outFile << "6354421724" << endl;
    outFile << "M" << endl;
    outFile << "1980/08/01" << endl;
    outFile << "69.05" << endl;
    outFile << "171.22" << endl;
    outFile << "1861271104" << endl;
    outFile << "1404582053" << endl;
    outFile << "Dominic Hayes" << endl;
    outFile << "1264661044" << endl;
    outFile << "M" << endl;
    outFile << "1958/03/17" << endl;
    outFile << "67.12" << endl;
    outFile << "144.81" << endl;
    outFile << "3838401686" << endl;
    outFile << "2606722830" << endl;
    outFile << "Xander Iles" << endl;
    outFile << "5144368560" << endl;
    outFile << "M" << endl;
    outFile << "1940/06/08" << endl;
    outFile << "69.99" << endl;
    outFile << "150.47" << endl;
    outFile << "4351238762" << endl;
    outFile << "6573650338" << endl;
    outFile << "Priyanka Aguirre" << endl;
    outFile << "4453754678" << endl;
    outFile << "F" << endl;
    outFile << "1968/12/25" << endl;
    outFile << "57.19" << endl;
    outFile << "123.45" << endl;
    outFile << "4351238762" << endl;
    outFile << "6356177020" << endl;
    outFile << "Al Pacino" << endl;
    outFile << "4351238762" << endl;
    outFile << "M" << endl;
    outFile << "1940/04/25" << endl;
    outFile << "63.25" << endl;
    outFile << "174.35" << endl;
    outFile << "5884327028" << endl;
    outFile << "4453754678" << endl;
    outFile << "Maritza Barker" << endl;
    outFile << "8486152371" << endl;
    outFile << "F" << endl;
    outFile << "1999/01/20" << endl;
    outFile << "55.44" << endl;
    outFile << "100.23" << endl;
    outFile << "5884327028" << endl;
    outFile << "6685841680" << endl;
    outFile << "Ivan Good" << endl;
    outFile << "1212288810" << endl;
    outFile << "M" << endl;
    outFile << "1958/10/03" << endl;
    outFile << "66.11" << endl;
    outFile << "172.22" << endl;
    outFile << "5884327028" << endl;
    outFile << "6685841680" << endl;
    outFile << "Summer Gordon" << endl;
    outFile << "8311020265" << endl;
    outFile << "F" << endl;
    outFile << "1988/03/19" << endl;
    outFile << "54.01" << endl;
    outFile << "160.66" << endl;
    outFile << "3838401686" << endl;
    outFile << "2606722830" << endl;
    outFile << "Lincoln Patterson" << endl;
    outFile << "1834506014" << endl;
    outFile << "M" << endl;
    outFile << "1990/12/12" << endl;
    outFile << "60.88" << endl;
    outFile << "123.45" << endl;
    outFile << "3838401686" << endl;
    outFile << "2606722830" << endl;
    outFile << "Jakayla Potter" << endl;
    outFile << "4065560288" << endl;
    outFile << "F" << endl;
    outFile << "1974/10/10" << endl;
    outFile << "49.99" << endl;
    outFile << "150.22" << endl;
    outFile << "3567833621" << endl;
    outFile << "7185667065" << endl;
    outFile << "Maverick Roth" << endl;
    outFile << "7664121403" << endl;
    outFile << "M" << endl;
    outFile << "1977/12/13" << endl;
    outFile << "69.96" << endl;
    outFile << "169.96" << endl;
    outFile << "1177562016" << endl;
    outFile << "1134541068" << endl;
    outFile << "Lydia Liu" << endl;
    outFile << "6573650338" << endl;
    outFile << "F" << endl;
    outFile << "2001/01/01" << endl;
    outFile << "60.29" << endl;
    outFile << "144.44" << endl;
    outFile << "2371870841" << endl;
    outFile << "5386088001" << endl;
    outFile << "Zavier Gillespie" << endl;
    outFile << "7183804452" << endl;
    outFile << "M" << endl;
    outFile << "1995/11/11" << endl;
    outFile << "55.59" << endl;
    outFile << "145.67" << endl;
    outFile << "3761880562" << endl;
    outFile << "5466880215" << endl;
}

// supplement.txt generator
void gen_suppFile() {
    
    ofstream outFile("supplement.txt");
        
    outFile << "Andy Hunter" << endl;
    outFile << "5702526454" << endl;
    outFile << "M" << endl;
    outFile << "1970/10/12" << endl;
    outFile << "68.53" << endl;
    outFile << "190.55" << endl;
    outFile << "5657545551" << endl;
    outFile << "8824238846" << endl;
    outFile << "Meg Salinas" << endl;
    outFile << "2005418530" << endl;
    outFile << "F" << endl;
    outFile << "1987/03/03" << endl;
    outFile << "66.66" << endl;
    outFile << "138.42" << endl;
    outFile << "1861271104" << endl;
    outFile << "1404582053" << endl;
    outFile << "Trixie Pace" << endl;
    outFile << "3860575134" << endl;
    outFile << "F" << endl;
    outFile << "1960/02/19" << endl;
    outFile << "60.32" << endl;
    outFile << "127.05" << endl;
    outFile << "1861271104" << endl;
    outFile << "1404582053" << endl;
    outFile << "Lacie-Mae Forster" << endl;
    outFile << "8508104888" << endl;
    outFile << "F" << endl;
    outFile << "1990/07/24" << endl;
    outFile << "62.76" << endl;
    outFile << "131.44" << endl;
    outFile << "1834506014" << endl;
    outFile << "8311020265" << endl;
    outFile << "Jamaal Saunders" << endl;
    outFile << "6643503821" << endl;
    outFile << "M" << endl;
    outFile << "1950/05/10" << endl;
    outFile << "64.87" << endl;
    outFile << "159.99" << endl;
    outFile << "1861271104" << endl;
    outFile << "1404582053" << endl;
}
