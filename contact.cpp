#include "contact.h"

using namespace std;

string Contact::getName() const{
    return name;
}

string Contact::getPhone() const{
    return phone;
}

string Contact::getEmail() const{
    return email;
}

void Contact::setName(string name){
    this->name = name;
}

void Contact::setPhone(string phone){
    this->phone = phone;
}

void Contact::setEmail(string email){
    this->email = email;
}

void Contact::print(){
    printw("%s\n", name.c_str());
    printw("Phone: %s\n", phone.c_str());
    printw("Email: %s\n", email.c_str());
    printw("\n");
}

bool operator==(const Contact &a, const Contact &b){
    return (a.getName() == b.getName() && a.getPhone() == b.getPhone() && a.getEmail() == b.getEmail());
}

bool operator==(const Contact &a, const string &b){
    return (a.getName() == b);
}
