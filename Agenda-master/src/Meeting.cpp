#include"Meeting.hpp"
#include<sstream>
#include <string>
#include <vector>

using namespace std;

// Meeting::Meeting() :m_sponsor(), m_participators()
// m_startDate(),m_endDate(), m_title() {}

Meeting::Meeting(std::string sponsor, std::vector<string> participator,
                 Date startTime, Date endTime, std::string title)
    : m_sponsor(sponsor), m_participators(participator), m_startDate(startTime),
      m_endDate(endTime), m_title(title) {}

Meeting::Meeting(const Meeting &t_meeting) {
  m_sponsor = t_meeting.m_sponsor;
  m_participators = t_meeting.m_participators;
  m_startDate = t_meeting.m_startDate;
  m_endDate = t_meeting.m_endDate;
  m_title = t_meeting.m_title;
}

std::string Meeting::getSponsor(void) const { return m_sponsor; }
void Meeting::setSponsor(std::string sponsor) { m_sponsor = sponsor; }

std::vector<string> Meeting::getParticipator(void) const {
  return m_participators;
}
void Meeting::setParticipator(const vector<string> participator) {
  m_participators = participator;
}

Date Meeting::getStartDate(void) const { return m_startDate; }
void Meeting::setStartDate(Date startTime) { m_startDate = startTime; }
Date Meeting::getEndDate(void) const { return m_endDate; }
void Meeting::setEndDate(Date endTime) { m_endDate = endTime; }
std::string Meeting::getTitle(void) const { return m_title; }
void Meeting::setTitle(std::string title) { m_title = title; }

bool Meeting::isParticipator(const std::string t_username) const {
  for (size_t i = 0; i < m_participators.size(); ++i) {
    if (t_username == m_participators[i]) {
      return true;
    }
  }
  return false;
}

