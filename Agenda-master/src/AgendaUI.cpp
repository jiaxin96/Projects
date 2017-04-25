#include"AgendaUI.hpp"
#include <iostream>

using namespace std;

AgendaUI::AgendaUI() {
  m_agendaService.startAgenda();
}

void AgendaUI::OperationLoop(void) {  startAgenda(); }
std::string AgendaUI::getOperation() {
  cout <<R"(
-------------------- Agenda --------------------
Action :
o   - log out Agenda
dc  - delete Agenda account
lu  - list all Agenda users
cm  - create meeting
la  - list all meetings
las - list all Sponsor meetings
lap - list all Participate meetings
qm  - query meeting by title
qt  - query meeting by timeInterval
dm  - delete meeting by title
da  - delete all meetings
------------------------------------------------

Agenda@)" << m_userName
          << " : # ";
  string action;
  cin >> action;
  return action;
}
void AgendaUI::startAgenda(void) {
  cout << R"(
-------------------- Agenda --------------------
Action :
l    - log in Agenda by user name and password
r    - register an Agenda account
q    - quit Agenda
------------------------------------------------
Agenda : ~$ )";
  string action = "q";
  cin >> action;
  if (action == "l") {
    userLogIn();
  } else if (action == "r") {
    userRegister();
  } else if (action == "q") {
    quitAgenda();
  } else {
    cout << "Error! Please input correctly!" << endl;
    startAgenda();
  }
}

bool AgendaUI::executeOperation(std::string op) {

  if (op == "cm") {
    createMeeting();
  } else if (op == "lu") {
    listAllUsers();
  } else if (op == "la") {
    listAllMeetings();
  } else if (op == "las") {
    listAllSponsorMeetings();
  } else if (op == "lap") {
    listAllParticipateMeetings();
  } else if (op == "qm") {
    queryMeetingByTitle();
  } else if (op == "qt") {
    queryMeetingByTimeInterval();
  } else if (op == "dc") {
    deleteUser();
  } else if (op == "da") {
    deleteAllMeetings();
  } else if (op == "dm") {
    deleteMeetingByTitle();
  } else if (op == "o") {
    userLogOut();
  } else {
    cout << "Error! Please input correctly!" << endl;
    executeOperation(getOperation());
    return false;
  }
  return true;
}
void AgendaUI::userLogIn(void) {


  cout <<R"(
[log in] [user name] [password]
[log in] )";
  cin >> m_userName >> m_userPassword;

  if (m_agendaService.userLogIn(m_userName, m_userPassword)) {
    cout << "[log in] succeed!" << endl;
    executeOperation(getOperation());
  } else {
    cout << "[error] log in fail!" << endl;
    startAgenda();
  }
}
void AgendaUI::userRegister(void) {
  string name, password, email, phone;
  cout << endl;
  cout << "[register] [user name] [password] [email] [phone]" << endl;
  cout << "[register] ";
  cin >> name;
  cin >> password;
  cin >> email;
  cin >> phone;
  if (m_agendaService.userRegister(name, password, email, phone)) {
    cout << "[register] succeed!" << endl;
  } else {
    cout << "[register] register fail!" << endl;
  }
  startAgenda();
}
void AgendaUI::quitAgenda(void) { m_agendaService.quitAgenda(); }
void AgendaUI::userLogOut(void) {
  cout << endl;
  // cout << "[Log Out] succeed!" << endl;
  startAgenda();
}
void AgendaUI::deleteUser(void) {
  cout << endl;
  if (m_agendaService.deleteUser(m_userName, m_userPassword)) {
    cout << "[delete agenda account] succeed!" << endl;
    startAgenda();
  } else {
    cout << "[delete agenda account] delete agenda account fail!\n";
    executeOperation(getOperation());
  }
}

void AgendaUI::listAllUsers(void) {
  cout << endl;
  cout << "[list all users]:\n\n";
  auto allUser = m_agendaService.listAllUsers();
  if (allUser.empty()) {
    cout << "[List all users]: No user!" << endl;
  } else {
    cout << "name      email                    phone\n";

    for (auto iter = allUser.begin(); iter != allUser.end(); ++iter) {
      string answer = "";
      answer += iter->getName();
      answer.resize(4 + 6, ' ');
      answer += iter->getEmail();
      answer.resize(10 + 5 + 20, ' ');
      answer += iter->getPhone();
      cout << answer << endl;
    }
  }
  executeOperation(getOperation());
}

void AgendaUI::createMeeting(void) {
  cout << endl;
  cout << "[create meeting] [the number of participators]" << endl;
  cout << "[create meeting] ";
  int number;
  cin >> number;
  vector<string> partcipator_list;
  for (int i = 0; i < number; ++i) {
    string participator;
    cout << "[create meeting] [please enter the participator " << i + 1 << " ]"
         << endl;
    cout << "[create meeting] ";
    cin >> participator;
    partcipator_list.push_back(participator);
  }
  cout << "[create meeting] [title] [start time(yyyy-mm-dd/hh:mm)] [end time(yyyy-mm-dd/hh:mm)]" << endl;
  cout << "[create meeting] ";
  std::string title, startDate, endDate;
  cin >> title;
  cin >> startDate;
  cin >> endDate;

  if (m_agendaService.createMeeting(m_userName, title, startDate, endDate,
                                    partcipator_list)) {
    cout << "[create meeting] succeed!" << endl;
  } else {
    cout << "[create meeting] error!" << endl;
  }
  executeOperation(getOperation());
}
void AgendaUI::listAllMeetings(void) {
  cout << endl;
  cout << "[list all meetings]:\n";
  auto meet_list = m_agendaService.listAllMeetings(m_userName);
  if (meet_list.empty()) {
    cout << "[list all meetings]:No meeting!\n";
  } else {
    printMeetings(meet_list);
  }
  executeOperation(getOperation());
}
void AgendaUI::listAllSponsorMeetings(void) {

  cout << endl;
  cout << "[list all sponsor meetings]:\n";
  auto meet_list = m_agendaService.listAllSponsorMeetings(m_userName);
  if (meet_list.empty()) {
    cout << "[list all sponsor meetings]:No meetings!" << endl;
  } else {
    printMeetings(meet_list);
  }
  executeOperation(getOperation());
}
void AgendaUI::listAllParticipateMeetings(void) {
  cout << endl;
  cout << "[list all participator meetings]:\n";
  auto meet_list = m_agendaService.listAllParticipateMeetings(m_userName);
  if (meet_list.empty()) {
    cout << "[list all participator meetings]:No meetings!\n";
  } else {
    printMeetings(meet_list);
  }
  executeOperation(getOperation());
}
void AgendaUI::queryMeetingByTitle(void) {
  cout << endl;
  cout << "[query meeting] [Title]:" << endl;
  std::string title;
  cout << "[query meeting] ";
  cin >> title;
  auto meet_list = m_agendaService.meetingQuery(m_userName, title);
  if (meet_list.empty()) {
    cout << "[query meeting]:No meeting!\n";
  } else {
    printMeetings(meet_list);
  }
  executeOperation(getOperation());
}
void AgendaUI::queryMeetingByTimeInterval(void) {
  cout << endl;
  cout << "[query meetings] [start time(yyyy-mm-dd/hh:mm)] [end "
          "time(yyyy-mm-dd/hh:mm)]"
       << endl;
  cout << "[query meetings] ";
  string startDate, endDate;
  cin >> startDate >> endDate;
  cout << endl;
  auto meet_list = m_agendaService.meetingQuery(m_userName, startDate, endDate);
  if (meet_list.empty()) {
    cout << "[query meeting]:No meeting!\n";
  } else {
    printMeetings(meet_list);
  }
  executeOperation(getOperation());
}

void AgendaUI::deleteMeetingByTitle(void) {
  cout << endl;
  cout << "[delete meeting] [title]" << endl;
  string title;
  cout << "[delete meeting] ";
  cin >> title;
  if (m_agendaService.deleteMeeting(m_userName, title)) {
    cout << "[delete meeting by title] succeed!\n";
  } else {
    cout << "[error] delete meeting fail!" << endl;
  }
  executeOperation(getOperation());
}
void AgendaUI::deleteAllMeetings(void) {
  cout << endl;
  if (m_agendaService.deleteAllMeetings(m_userName)) {
    cout << "[delete all meetings] succeed!" << endl;
  } else {
    cout << "[error]delete all meetings fail!" << endl;
  }
  executeOperation(getOperation());
}
void AgendaUI::printMeetings(std::list<Meeting> meetings) {
  cout << endl;
  if (meetings.empty()) {
    cout << "No meeting!\n";
  } else {
    string ansTitle = "title               sponsor             start time      "
                      "  end time          participators";
    cout << ansTitle << endl;
    string ansMeeting = "";
    for (auto iter = meetings.begin(); iter != meetings.end(); ++iter) {
      ansMeeting = "";
      ansMeeting += iter->getTitle();
      ansMeeting.resize(5 + 15, ' ');
      ansMeeting += iter->getSponsor();
      ansMeeting.resize(20 + 7 + 13, ' ');
      ansMeeting += Date::dateToString(iter->getStartDate());
      ansMeeting.resize(40 + 10 + 8, ' ');
      ansMeeting += Date::dateToString(iter->getEndDate());
      ansMeeting += ("  ");
      auto participator_ans = iter->getParticipator();
      for (size_t i = 0; i < participator_ans.size(); ++i) {
        ansMeeting += participator_ans[i];
        ansMeeting += ',';
      }
      int tempLength = ansMeeting.length();
      ansMeeting.resize(tempLength - 1);
      cout << ansMeeting << endl;
    }
  }
}
