#include "../include/Guide_UI.hpp"
#include <stdexcept>
using namespace std;
static auto interface = 0;
Guide_UI::Guide_UI() {
  startUI();
  m_service.StartService();
}
void Guide_UI::startUI() {
    if (interface == 0) {
      cout << "-------------- guidance system for sysu --------------" << endl;
  		cout << "Action :" << endl;
  		cout << "U    - user" << endl;
  		cout << "AD   - administrator" << endl;
  		cout << "Q    - quit guidance system" << endl;
  		cout << "------------------------------------------------------" << endl << endl;
  		cout << "guidance system: ~#";
    } else if (interface == 1) {
      cout << "-------------- guidance system for sysu --------------" << endl;
      cout << "Action :" << endl;
      cout << "A    - add spot into guidance system" << endl;
      cout << "D    - delete spot in guidance system" << endl;
      cout << "R    - refresh the road in guidance system" << endl;
      cout << "O    - log out the guidance system" << endl;
      cout << "guidance system: ~#administrator:";
    } else {
      cout << "-------------- guidance system for sysu --------------" << endl;
      cout << "S    - display all the spot name" << endl;
      cout << "D    - display the spot introduction" << endl;
      cout << "Q    - query the shortest path between the two spot" << endl;
      cout << "O    - log out the guidance system" << endl;
      cout << "guidance system: ~#user:";
    }
}
string Guide_UI::getOperation() {
    string selection;
    cin >> selection;
    return selection;
}
void Guide_UI::OperationLoop(void) {
    executeOperation(getOperation());
}
bool Guide_UI::executeOperation(string op) {
  try {
        if (interface == 0) {
      if (op == "U" || op == "u") {
        interface = 2;
        startUI();
        OperationLoop();
      } else if (op == "AD" || op == "ad") {
        interface = 1;
        startUI();
        OperationLoop();
      } else if (op == "Q" || op == "q") {
        QuitGUide();
      } else {
        cout << "Wrong Selection!\n";
        startUI();
        OperationLoop();
      }
    } else if (interface == 1) {
        if (op == "A" || op == "a") {
          Addspot();
        } else if (op == "D" || op == "d") {
          Deletespot();
        } else if (op == "R" || op == "r") {
          Refreshroad();
        } else if (op == "O" || op == "o"){
          Logout();
        } else {
          cout << "Wrong Selection!\n";
          startUI();
          OperationLoop();
        }
    } else if (interface == 2) {
        if (op == "S" || op == "s") {
          displayspotname();
        } else if (op == "D" || op == "d") {
          displayspotintroduction();
        } else if (op == "Q" || op == "q") {
          QueryPath();
        } else if (op == "O" || op == "o") {
          Logout();
        } else {
          cout << "Wrong Selection!\n";
          startUI();
          OperationLoop();
        }
    }
  }
  catch (overflow_error e) {
    cout << "Kidding !!! Wrong Selection!\n";
    startUI();
    OperationLoop();
  }
}
void Guide_UI::QuitGUide() {
    m_service.QuitService();
    cout << "[Quit]: succeed!" << endl;
}
void Guide_UI::Addspot() {
  vector<string> result = m_service.Spotname();
  if (!result.empty()) {
    cout << "[List Spot name]: Succeed!" << endl;
    int len = result.size();
    for (int i = 0; i < len; ++i) {
      cout << result[i];
      if (i != 0 && i % 3 == 0) {
        cout << endl;
      } else {
        cout << "  ";
      }
    }
    cout << endl;
  } else {
    cout << "[Spot name]: Failed!" << endl;
  }
    cout << "[Add Spot]: [Spot name] [Spot mark]" << endl;
    cout << "[Add Spot]: ";
    string name;
    cin >> name;
    int mark;
    cin >> mark;
    cout << "[Add Spot]: [Spot introduction]" << endl;
    string introduction;
    cin >> introduction;
    Spot temp(name, mark, introduction);
    if (m_service.Addspot(temp)) {
        cout << "[Add Spot]: Succeed!" << endl;
    } else {
        cout << "[Add Spot]: Failed!" << endl;
    }
    interface = 1;
    startUI();
    OperationLoop();
}
void Guide_UI::Deletespot() {
  vector<string> result = m_service.Spotname();
  if (!result.empty()) {
    cout << "[Spot name]: Succeed!" << endl;
    int len = result.size();
    for (int i = 0; i < len; ++i) {
      cout << result[i];
      if (i != 0 && i % 3 == 0) {
        cout << endl;
      } else {
        cout << "  ";
      }
    }
    cout << endl;
  } else {
    cout << "[Spot name]: Failed!" << endl;
  }
    cout << "[Delete Spot]: [Spot mark]" << endl;
    cout << "[Delete Spot]: " << endl;
    int mark;
    cin >> mark;
    if (m_service.Deletespot(mark)) {
      cout << "[Delete Spot]: Succeed!" << endl;
    } else {
      cout << "[Delete Spot]: Failed!" << endl;
    }
    interface = 1;
    startUI();
    OperationLoop();
}
void Guide_UI::Refreshroad() {
  try {
        vector<Edge> refresh;
    int s_pos = 0, e_pos = 0, weight, type;
    cout << "End with start mark is equal to -1 or end mark is number -1\n";
    while(s_pos != -1 && e_pos != -1) {
      cout << "[Refresh Road]: [start mark] [end mark] [weight] [type]" << endl;
      cout << "[Refresh Road]: ";
      cin >> s_pos >> e_pos >> weight >> type;
      if (s_pos == -1 || e_pos == -1) break;
      Edge edge(s_pos, e_pos, weight, type);
      refresh.push_back(edge);
      cout << "[Refresh Road]: Succeed!" << endl;
    }
    m_service.SetGraph(refresh);
    interface = 1;
    startUI();
    OperationLoop();
  }
  catch (overflow_error) {
    cout << "Kidding !!! Wrong Selection!\n";
    startUI();
    OperationLoop();
  }
}
void Guide_UI::Logout() {
    cout << "[Log Out]: Succeed!" << endl;
    interface = 0;
    startUI();
    OperationLoop();
}
void Guide_UI::displayspotname() {
    vector<string> result = m_service.Spotname();
    if (!result.empty()) {
      cout << "[Spot name]: Succeed!" << endl;
      int len = result.size();
      for (int i = 0; i < len; ++i) {
        cout << result[i];
        if (i != 0 && i % 3 == 0) {
          cout << endl;
        } else {
          cout << "  ";
        }
      }
      cout << endl;
    } else {
      cout << "[Spot name]: Failed!" << endl;
    }
    interface = 2;
    startUI();
    OperationLoop();
}
void Guide_UI::displayspotintroduction() {
  try {
        cout << "[Spot introduction]: [Spot mark]" << endl;
    cout << "[Spot introduction]: ";
    int mark;
    cin >> mark;
    string result = m_service.Spotintroduction(mark);
    if (result != "Unknown") {
      cout << "[Spot introduction]: Succeed!"<< endl;
      cout << result << endl;
    } else {
      cout << "[Spot introduction]: Failed!"<< endl;
    }
    interface = 2;
    startUI();
    OperationLoop();
  }
  catch (overflow_error) {
    cout << "Kidding !!! Wrong Selection!\n";
    startUI();
    OperationLoop();
  }
}
void Guide_UI::QueryPath() {
  try {
    cout << "[Query Path]: [Car(1)] or [Foot(0)]" << endl;
    cout << "[Query Path]: ";
    int selection;
    cin >> selection;
    cout << "[Query Path]: [Start position] [End position]" << endl;
    cout << "[Query Path]: ";
    int start, end;
    cin >> start >> end;
    if (selection == 1) {
        int dis = m_service.QueryCardis(start, end);
        string path = m_service.QueryCarpath(start, end);
        cout << "最短距离: " << dis << endl;
        cout << path << endl;
    } else {
      int dis = m_service.QueryFootdis(start, end);
      string path = m_service.QueryFootpath(start, end);
      cout << "最短距离: " << dis << endl;
      cout << path << endl;
    }
    interface = 2;
    startUI();
    OperationLoop();
  }
  catch (overflow_error) {
   cout << "Kidding!!";
    startUI();
    OperationLoop();
  }
}
