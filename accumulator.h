/**��������ڸ�������,�ʶ����ñ���������
 *@author ���п͡�������
 *@date 2023/2/17
 */
#ifndef ACCUMULATOR_H
#define ACCUMULATOR_H

#include "date.h"

class Accumulator {    //��ĳ����ֵ�����ۼ�
private:
    Date lastDate;    //�ϴα����ֵ��ʱ��
    double value;    //��ֵ�ĵ�ǰֵ
    double sum;        //��ֵ�����ۼ�֮��
public:
    Accumulator() {
        Date date;
        lastDate = date;
        value = 0;
        sum = 0;
    }      //���Ĭ�Ϲ��캯��
    //���캯����dateΪ��ʼ�ۼӵ����ڣ�valueΪ��ʼֵ
    Accumulator(const Date &date, double value) : lastDate(date), value(value), sum(0) {}

    //��õ�����date���ۼӽ��
    double getSum(const Date &date) const {
        return sum + value * (date - lastDate);
    }

    //��date����ֵ���Ϊvalue
    void change(const Date &date, double d) {
        sum = getSum(date);
        lastDate = date;
        this->value = d;
    }

    //��ʼ���������ڱ�Ϊdate����ֵ��Ϊvalue���ۼ�������
    void reset(const Date &date, double d) {
        lastDate = date;
        this->value = d;
        sum = 0;
    }
};

#endif //ACCUMULATOR_H