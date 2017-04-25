#include"Storage.hpp"
#include "Path.hpp"
#include <cctype>
#include <fstream>
#include <string>
#include <iostream>
using namespace std;

std::shared_ptr<Storage> Storage::m_instance = nullptr;
Storage::Storage() { 
  m_dirty = false;
  readFromFile();
}

bool Storage::readFromFile(void) {
  ifstream icin(Path::userPath);

  string tempLine;
  string userNam;
  string userPasswd;
  string userEmail;
  string userPhone;
  if (!icin.good()) {
    return false;
  }
  if (icin.fail()) {
    return false;
  }
  while (getline(icin, tempLine)) {

    userNam = "";
    userPasswd = "";
    userEmail = "";
    userPhone = "";

    int pos = 1;

    for (; tempLine[pos] != '\"'; ++pos) {
      userNam += tempLine[pos];
    }
    for (pos += 3; tempLine[pos] != '\"'; ++pos) {
      userPasswd += tempLine[pos];
    }
    for (pos += 3; tempLine[pos] != '\"'; ++pos) {
      userEmail += tempLine[pos];
    }
    for (pos += 3; tempLine[pos] != '\"'; ++pos) {
      userPhone += tempLine[pos];
    }

    User tempuser(userNam, userPasswd, userEmail, userPhone);

    m_userList.push_back(tempuser);
  }
  icin.clear();
  icin.close();

  ifstream icin2(Path::meetingPath);
  if (!icin2.good()) {
    return false;
  }
  if (icin2.fail()) {
    return false;
  }
  tempLine = "";
  while (getline(icin2, tempLine)) {
    string meetingSpos;
    string meetingPart;
    string meetingStartStr;
    string meetingEndStr;
    string meetingTitle;


    int pos = 1;
    for (; tempLine[pos] != '\"'; ++pos) {
      meetingSpos += tempLine[pos];
    }
    for (pos += 3; tempLine[pos] != '\"'; ++pos) {
      meetingPart += tempLine[pos];
    }
    for (pos += 3; tempLine[pos] != '\"'; ++pos) {
      meetingStartStr += tempLine[pos];
    }
    for (pos += 3; tempLine[pos] != '\"'; ++pos) {
      meetingEndStr += tempLine[pos];
    }
    for (pos += 3; tempLine[pos] != '\"'; ++pos) {
      meetingTitle += tempLine[pos];
    }

    std::vector<string> meetingPartNam;
    string tempPart = "";
    int partLength = meetingPart.length();
    for (int i = 0; i < partLength; ++i) {
      if (meetingPart[i] == '&') {

        meetingPartNam.push_back(tempPart);
        tempPart = "";
        continue;
      }
      tempPart += meetingPart[i];

      if (i == partLength - 1) {
        meetingPartNam.push_back(tempPart);
      }
    }

    Date meetingStartDate = Date::stringToDate(meetingStartStr);
    Date meetingEndDate = Date::stringToDate(meetingEndStr);

    Meeting temp(meetingSpos, meetingPartNam, meetingStartDate, meetingEndDate,
                 meetingTitle);

    m_meetingList.push_back(temp);
  }
  icin2.clear();
  icin2.close();
  return true;
}

bool Storage::writeToFile(void) {
  ofstream writeStream(Path::userPath);
  if (!m_dirty) return true;
  if (!writeStream.good()) {
    return false;
  }
  if (writeStream.fail()) {
    return false;
  }
  if (writeStream.is_open()) {
    for (std::list<User>::iterator iter = m_userList.begin();
         iter != m_userList.end(); ++iter) {
      User temp(*iter);
      writeStream << "\"" << temp.getName() << "\",\"" << temp.getPassword()
                  << "\",\"" << temp.getEmail() << "\",\"" << temp.getPhone()
                  << "\"\n";
    }
    writeStream.clear();
    writeStream.close();

    ofstream writeStream2(Path::meetingPath);
    if (!writeStream2.good()) {
      return false;
    }
    if (writeStream2.fail()) {
      return false;
    }
    if (writeStream2.is_open()) {

      for (std::list<Meeting>::iterator iter = m_meetingList.begin();
           iter != m_meetingList.end(); ++iter) {
        Meeting temp = *iter;
        string tempPart = "";
        auto participator_ans = temp.getParticipator();
        for (size_t i = 0; i < participator_ans.size(); ++i) {
          tempPart += (participator_ans[i] + '&');
        }

        int tempLength = tempPart.length();
        tempPart.resize(tempLength - 1);

        writeStream2 << "\"" << temp.getSponsor() << "\",\"" << tempPart
                     << "\",\"" << Date::dateToString(temp.getStartDate())
                     << "\",\"" << Date::dateToString(temp.getEndDate())
                     << "\",\"" << temp.getTitle() << "\"\n";
      }
      writeStream2.clear();
      writeStream2.close();
    }
    m_dirty = false;
    return true;
  }
  
  return false;
}

std::shared_ptr<Storage> Storage::getInstance(void) {
  if (!m_instance) {
    // m_dirty = false;
    m_instance.reset(new Storage());
  }
  return m_instance;
}

Storage::~Storage() { 
  sync();
  m_instance.reset();
}

void Storage::createUser(const User &t_user) {
  m_userList.push_back(t_user);
  m_dirty = true;
}

std::list<User>
Storage::queryUser(std::function<bool(const User &)> filter) const {
  std::list<User> temp;
  for (auto iter = m_userList.begin(); iter != m_userList.end(); ++iter) {
    if (filter(*iter)) {
      temp.push_back(*iter);
    }
  }
  return temp;
}

int Storage::updateUser(std::function<bool(const User &)> filter,
                        std::function<void(User &)> switcher) {
  int count = 0;
  for (auto iter = m_userList.begin(); iter != m_userList.end(); ++iter) {
    if (filter(*iter)) {
      switcher(*iter);
      ++count;
    }
  }
  return count;
}

int Storage::deleteUser(std::function<bool(const User &)> filter) {
  int count = 0;
  for (auto iter = m_userList.begin(); iter != m_userList.end();) {
    if (filter(*iter)) {
      count++;
      m_dirty = true;
      iter = m_userList.erase(iter);
    } else {
      ++iter;
    }
  }
  return count;
}

void Storage::createMeeting(const Meeting &t_meeting) {
  m_meetingList.push_back(t_meeting);
  m_dirty = true;
}

std::list<Meeting>
Storage::queryMeeting(std::function<bool(const Meeting &)> filter) const {
  std::list<Meeting> temp;
  for (auto iter = m_meetingList.begin(); iter != m_meetingList.end(); ++iter) {
    if (filter(*iter)) {
      temp.push_back(*iter);
    }
  }
  return temp;
}

int Storage::updateMeeting(std::function<bool(const Meeting &)> filter,
                           std::function<void(Meeting &)> switcher) {
  int count = 0;
  for (auto iter = m_meetingList.begin(); iter != m_meetingList.end(); ++iter) {
    if (filter(*iter)) {
      count++;
      switcher(*iter);
    }
  }
  return count;
}

int Storage::deleteMeeting(std::function<bool(const Meeting &)> filter) {
    int count = 0;
    for (auto iter = m_meetingList.begin(); iter != m_meetingList.end();) {
        if (filter(*iter)) {
            count++;
            m_dirty = true;
            iter = m_meetingList.erase(iter);
        } else {
          ++iter;
        }
    }
    return count;
}

bool Storage::sync(void) {
  if (m_dirty)
    return writeToFile();
  else
    return true;
}
