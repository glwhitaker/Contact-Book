#pragma once

#include <iostream>
#include <string>
#include <ncurses.h>

class Contact{
    private:
        std::string name;
        std::string phone;
        std::string email;
    public:
        Contact() : name(""), phone(""), email("") {}
        Contact(std::string name, std::string phone, std::string email) : name(name), phone(phone), email(email) {}
        std::string getName() const;
        std::string getPhone() const;
        std::string getEmail() const;
        void setName(std::string name);
        void setPhone(std::string phone);
        void setEmail(std::string email);
        void print();
        friend bool operator==(const Contact &a, const Contact &b);
        friend bool operator==(const Contact &a, const std::string &b);
};