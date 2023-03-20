#include <vector>
#include <unordered_map>
#include <algorithm>
#include <fstream>
#include "contact.h"

using namespace std;

void printMenu(WINDOW *menuWin, int starty){
    int centerCol = menuWin->_maxx / 2;
    int halfWidth = 15;
    int startx = centerCol - halfWidth;

    string title = "Contact Manager";
    
    mvwprintw(menuWin, starty, centerCol - title.length() / 2, "Contact Manager");
    mvwprintw(menuWin, starty + 2, startx, "1. Add Contact");
    mvwprintw(menuWin, starty + 3, startx, "2. Delete Contact");
    mvwprintw(menuWin, starty + 4, startx, "3. Edit Contact");
    mvwprintw(menuWin, starty + 5, startx, "4. Print Contacts");
    mvwprintw(menuWin, starty + 6, startx, "5. Exit");

    wrefresh(menuWin);
}

void exitWindow(){
    curs_set(1);
    echo();
    endwin();
    exit(0);
}

void addContact(vector<Contact> &contactList){
    // bring back echo and cursor
    curs_set(1);
    echo();
    // take string input in ncurses
    char name[100];
    char phone[100];
    char email[100];

    // print in middle of screen
    int centerCol = stdscr->_maxx / 2;
    int halfWidth = 15;
    int startx = centerCol - halfWidth;
    
    mvprintw(10, startx, "Name: ");
    getstr(name);
    mvprintw(11, startx, "Phone: ");
    getstr(phone);
    mvprintw(12, startx, "Email: ");
    getstr(email);

    // create contact object
    Contact contact(name, phone, email);

    // add contact to vector if not already in vector
    if(find(contactList.begin(), contactList.end(), contact) == contactList.end()){
        contactList.push_back(contact);
        ofstream file("contactList.txt", ios::app);
        file << name << " " << phone << " " << email << endl;
    }
    else{
        clear();
        curs_set(0);
        mvprintw(13, startx, "Contact already exists...\n");
        getch();
    }
}

void printContacts(vector<Contact> &contactList){
    clear();
    refresh();

    sort(contactList.begin(), contactList.end(), [](Contact a, Contact b){
        return a.getName() < b.getName();
    });

    for(int i = 0; i < contactList.size(); i++){
        contactList[i].print();
    }
}

void deleteContact(vector<Contact> &contactList){
    curs_set(1);
    echo();

    while(true){
        clear();
        refresh();
        // print contacts to choose from
        printContacts(contactList);

        // choose contact to delete
        char name[100];
        printw("Enter name of contact to delete or nothing to exit: ");
        getstr(name);
    
        // exit if nothing entered
        if(name[0] == '\0'){
            break;
        }

        // find contact in vector
        Contact contact(name, "", "");
        auto it = find(contactList.begin(), contactList.end(), contact.getName());
        if(it != contactList.end()){
            contactList.erase(it);
            ofstream file("contactList.txt");
            for(int i = 0; i < contactList.size(); i++){
                file << contactList[i].getName() << " " << contactList[i].getPhone() << " " << contactList[i].getEmail() << endl;
            }
        }
        else{
            clear();
            curs_set(0);
            mvprintw(13, 0, "Contact does not exist...\n");
            getch();
        }
    }
}

void editContact(vector<Contact> &contactList){
    echo();
    while(true){
        curs_set(1);
        clear();
        refresh();

        int centerCol = stdscr->_maxx / 2;
        int halfWidth = 15;
        int startx = centerCol - halfWidth;
        // print contacts to choose from
        printContacts(contactList);

        // choose contact to edit
        char name[100];
        printw("Enter name of contact to edit or nothing to exit: ");
        getstr(name);
    
        // exit if nothing entered
        if(name[0] == '\0'){
            break;
        }

        // find contact with matching name but not other info
        Contact contact(name, "", "");
        auto it = find(contactList.begin(), contactList.end(), contact.getName());
        if(it != contactList.end()){
            // edit contact
            clear();
            refresh();
            char newName[100];
            char newPhone[100];
            char newEmail[100];
            
            mvprintw(10, startx, "Name: ");
            getstr(newName);
            mvprintw(11, startx, "Phone: ");
            getstr(newPhone);
            mvprintw(12, startx, "Email: ");
            getstr(newEmail);

            // create contact object
            Contact newContact(newName, newPhone, newEmail);

            // add contact to vector if not already in vector
            if(find(contactList.begin(), contactList.end(), newContact) == contactList.end()){
                contactList.erase(it);
                contactList.push_back(newContact);
                ofstream file("contactList.txt");
                for(int i = 0; i < contactList.size(); i++){
                    file << contactList[i].getName() << " " << contactList[i].getPhone() << " " << contactList[i].getEmail() << endl;
                }
            }
            else{
                clear();
                curs_set(0);
                mvprintw(13, startx, "Contact already exists...\n");
                getch();
            }
        }
        else{
            clear();
            curs_set(0);
            mvprintw(13, startx, "Contact does not exist...\n");
            getch();
        }
    }
}

int main(){
    initscr();
    refresh();

    vector<Contact> contactList;

    // read contacts from file
    ifstream file("contactList.txt");
    string first;
    string last;
    string phone;
    string email;
    // read file ensuring to get first and last name
    while(file >> first >> last >> phone >> email){
        string name = first + " " + last;
        Contact contact(name, phone, email);
        contactList.push_back(contact);
    }

    while(true){
        clear();
        noecho();
        curs_set(0);
        printMenu(stdscr, 10);
        int choice = getch();
        switch(choice){
            case '1':
                clear();
                addContact(contactList);
                break;
            case '2':
                deleteContact(contactList);
                break;
            case '3':
                editContact(contactList);
                break;
            case '4':
                printContacts(contactList);
                getch();
                break;
            case '5':
                exitWindow();
                break;
            default:
                break;
        }
    }

    curs_set(1);
    endwin();
    return 0;
}