#ifndef GUIDE_UI_HPP
#define GUIDE_UI_HPP
#include "Guide_service.hpp"
#include <string>
#include <iostream>
#include <vector>
class Guide_UI {
private:
    Guide_service m_service;
public:
    Guide_UI();
    void startUI();
    void OperationLoop(void);
private:
    bool executeOperation(string t_operation);
    string getOperation();
    void QuitGUide();
    void Addspot();
    void Deletespot();
    void Refreshroad();
    void Logout();
    void displayspotname();
    void displayspotintroduction();
    void QueryPath();
};
#endif
