#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <boost/serialization/access.hpp>

namespace {    //namespaceʹ����Ķ���ֻ�ڵ�ǰ�ļ�����Ч
    //�洢ƽ����ĳ����1��֮ǰ�ж����죬Ϊ����getMaxDay������ʵ�֣���������һ��
    const int DAYS_BEFORE_MONTH[] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};
}

class Date {    //������
    friend boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & year;
        ar & month;
        ar & day;
    }

private:
    int year;        //��
    int month;        //��
    int day;        //��
    int totalDays;    //�������Ǵӹ�ԪԪ��1��1�տ�ʼ�ĵڼ���
public:
    Date() : Date(1, 1, 1) {}

    Date(int year, int month, int day);    //���ꡢ�¡��չ�������
    int getYear() const { return year; }

    int getMonth() const { return month; }

    int getDay() const { return day; }

    int getMaxDay() const;        //��õ����ж�����
    bool isLeapYear() const {    //�жϵ����Ƿ�Ϊ����
        return year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
    }

    //������������֮��������
    int operator-(const Date &date) const {
        return totalDays - date.totalDays;
    }

    //�ж��������ڵ�ǰ��˳��
    bool operator<(const Date &date) const { return totalDays < date.totalDays; }

    bool operator==(const Date &date) const { return totalDays == date.totalDays; }

    bool operator!=(const Date &date) const { return !(*this == date); }

    bool operator>(const Date &date) const { return date < *this; }

    bool operator<=(const Date &date) const { return !(*this > date); }

    bool operator>=(const Date &date) const { return !(*this < date); }
};

std::istream &operator>>(std::istream &in, Date &date);

std::ostream &operator<<(std::ostream &out, const Date &date);

#endif  //DATE_H