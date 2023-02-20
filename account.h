/**
 *@author ���п͡�������
 *@date 2023/2/17
 */
#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "accumulator.h"
#include "date.h"
#include <utility>
#include <cmath>
#include <boost/serialization/map.hpp>              //for std::multimap
#include <boost/serialization/string.hpp>           //for std::string
#include <boost/serialization/assume_abstract.hpp>  //for assuming class Account is a virtual base class
#include <boost/serialization/export.hpp>           //for polymorphic
#include <boost/serialization/base_object.hpp>      //for register derived class

class Account;      //ǰ������

class AccountRecord {    //��Ŀ��¼
    friend boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & date;
        ar & account;
        ar & amount;
        ar & balance;
        ar & desc;
    }

private:
    Date date;          //����
    const Account *account;   //�˻�
    double amount;            //���׶�
    double balance;           //���
    std::string desc;         //����
public:
    AccountRecord();    //���Ĭ�Ϲ��캯��
    AccountRecord(const Date &date, const Account *account, double amount, double balance, std::string desc);

    void show() const;    //�����ǰ��¼
};

using RecordMap = std::multimap<Date, AccountRecord>;

/**�й�Statements��Ŀ����ɻ�
 * 1.ΪʲôҪ��Account��ľ�̬���ݳ�Ա�����ó�����������?�ⲻ�Ƕ��һ����?
 *   ������Ƕ��һ��.������boost::serialization�н�Ϊ��̵���������֮ǰ�����,��ô��ͻᷢ��,��������
 *   �鵵�����ӵ����ݳ�Աʱ������û����serialize����,�����������ھ�̬���ݳ�Ա,��ôboost�ͻ�Ϊÿ������
 *   �洢һ�ݾ�̬���ݳ�Ա,�����������˷Ѵ洢�ռ�.�ڱ�����,������������ͻᵼ�¸��������˻���������ڻָ����ݺ�
 *   ������Ŀ�б��������������(���ķֲ���������ʵ�ֵ�save��load�����й�),�洢���ļ���СҲ��������ִ�д���
 *   ��ָ������.�������쳣��������ĸ�Դһ����ѱ����ַ���: �ⲻ�������ǵ�һ����ʶ,��ʹ���ڼ̳й�ϵ,��̬���ݳ�Ա
 *   Ҳֻ��һ��
 * 2.�������˻��������total����Statements�в�Υ����?
 *   ��ǰ����,��̬���ݳ�Ա�ᵼ�¹鵵�ļ���С��������,��Ȼdouble��ռ�ռ�ֻ��8�ֽ�,�������Ǳ���ÿ��ǳ����ڻ���
 *   ���е�����;����,���ַ���Ҳ�Ƿ���ʵ�������
 * 3.��Ȼ����,�Ǻβ���Account���record����ҲǨ�ƹ���?��Ҳ���˵��й�ѽ
 *   ��������,Account���ǳ�����,�����recordҲǨ�ƹ���,��ô��ʹAccount�Ľ�Statements������Ϊ�Լ�����Ԫ��,record
 *   Ҳ�޷�����Account��˽�����ݳ�Աid��balance,��Ϊ�������Ǿ�̬���ݳ�Ա,�޷�ͨ�������,Account�໹�ǳ�����,���ܱ�ʵ����,
 *   Ҳ���޷�ͨ���������,������Ҳ�ǲ�����.
 */
class Statements final {     //��ֹ�̳д���
    friend class Account;

    friend boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & recordMap;
        ar & total;
    }

public:
    //��ѯһ��ʱ���ڵ��˵�
    static void query(const Date &begin, const Date &end);

    static double getTotal() { return total; }

    //�����˵����һ�α����ʱ�䣺��Ҫ��Ϊ�˸������ϵ��������
    static Date lastDate();

    //�����˵���������ʱ��
    static Date startDate();

private:
    static RecordMap recordMap;     //���ɸ�Ϊ�Ǿ�̬��Ա
    static double total;
};

class Account { //�����˻���
    friend boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & id;
        ar & balance;
    }

private:
    std::string id;    //�ʻ�
    double balance;    //���
protected:
    //����������õĹ��캯����idΪ�˻�
    Account() : balance(0) {}   //���Ĭ�Ϲ��캯��
    Account(const Date &date, std::string id);

    //��¼һ���ʣ�dateΪ���ڣ�amountΪ��descΪ˵��
    void record(const Date &date, double amount, const std::string &desc);

    //���������Ϣ
    void error(const std::string &msg) const;

public:
    const std::string &getId() const { return id; }

    double getBalance() const { return balance; }

    //�����ֽ�dateΪ���ڣ�amountΪ��descΪ����˵��
    virtual void deposit(const Date &date, double amount, const std::string &desc) = 0;

    //ȡ���ֽ�dateΪ���ڣ�amountΪ��descΪ����˵��
    virtual void withdraw(const Date &date, double amount, const std::string &desc) = 0;

    //���㣨������Ϣ����ѵȣ���ÿ�½���һ�Σ�dateΪ��������
    virtual void settle(const Date &date) = 0;

    //��ʾ�˻���Ϣ
    virtual void show(std::ostream &out) const;

    //�����ඨ������������
    virtual ~Account() = default;
};

class SavingsAccount : public Account { //�����˻���
    friend boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & boost::serialization::base_object<Account>(*this); //���ø����serialize
        ar & rate;
    }

private:
    Accumulator acc;    //����������Ϣ���ۼ���: ���ù鵵,�Ժ�ͬ��
    double rate;        //����������
public:
    SavingsAccount();   //���Ĭ�Ϲ��캯��
    SavingsAccount(const Date &date, const std::string &id, double rate);

    double getRate() const { return rate; }

    void deposit(const Date &date, double amount, const std::string &desc) override;

    void withdraw(const Date &date, double amount, const std::string &desc) override;

    void settle(const Date &date) override;
};

class CreditAccount : public Account { //�����˻���
    friend boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & boost::serialization::base_object<Account>(*this); //���ø����serialize
        ar & credit;
        ar & rate;
        ar & fee;
    }

private:
    Accumulator acc;    //����������Ϣ���ۼ���
    double credit;        //���ö��
    double rate;        //Ƿ���������
    double fee;            //���ÿ����

    double getDebt() const {    //���Ƿ���
        double balance = getBalance();
        return (balance < 0 ? balance : 0);
    }

public:
    //���캯��
    CreditAccount();

    CreditAccount(const Date &date, const std::string &id, double credit, double rate, double fee);

    double getCredit() const { return credit; }

    double getRate() const { return rate; }

    double getFee() const { return fee; }

    double getAvailableCredit() const {    //��ÿ�������
        if (getBalance() < 0)
            return credit + getBalance();
        else
            return credit;
    }

    void deposit(const Date &date, double amount, const std::string &desc) override;

    void withdraw(const Date &date, double amount, const std::string &desc) override;

    void settle(const Date &date) override;

    void show(std::ostream &out) const override;
};

#endif //ACCOUNT_H