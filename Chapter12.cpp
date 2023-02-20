/**
 *@author ���п͡�������
 *@date 2023/2/17
 */
#include <iostream>
#include <utility>

using namespace std;

class Exception {
public:
    Exception() = default;

    virtual ~Exception() = default;

    virtual void ErrorInfo() = 0;
};

class OutOfMemory : public Exception {
public:
    OutOfMemory() = default;

    ~OutOfMemory() override = default;

    void ErrorInfo() override;
};

void OutOfMemory::ErrorInfo() {
    cerr << "Failed to allocate memory!" << endl;
}

class RangError : public Exception {
public:
    explicit RangError(size_t number) : invalidNum(number) {}

    ~RangError() override = default;

    void ErrorInfo() override;

    virtual size_t getNumber() { return invalidNum; }

    virtual void setNum(size_t number) { invalidNum = number; }

private:
    size_t invalidNum;
};

void RangError::ErrorInfo() {
    cerr << "The number " << invalidNum << " you used is out of range!" << endl;
}

class SomeClass {
public:
    explicit SomeClass(string name) : str(std::move(name)) {
        cout << str << ": in constructor" << endl;
    }

    SomeClass(const SomeClass &) {
        cout << str << ": in copy constructor" << endl;
    }

    ~SomeClass() {
        cout << str << ": in destructor" << endl;
    }

    SomeClass &operator=(const SomeClass &) {
        cout << str << ": in assignment function" << endl;
        return *this;
    }

private:
    string str;
};

void test1();

size_t *test2();

void test3(size_t *);

int main() {
    /*12-1:
     * 1.�쳣��ָ������ִ�й����г��ֵ�����״�������н���޷���������,��ᵼ�º���������쳣��ֹ
     * 2.�쳣������ָ��catch���鲶��throw�����׳�������˵���쳣����Ķ����,�Դ�������ǡ������
     */

    /*12-2
     * C++���쳣�������ʹ���쳣�������ʹ�������ͬһ��������,�����ײ�ĺ����������ؽ����������,�����ع��࿼���쳣�Ĵ���.
     * �ϲ�����߿�����Բ�ͬ���쳣������ͬ�Ĵ����ʩ.
     */

    /*12-3:
     * 1.throw�﷨Ϊ"throw ���ʽ;" ����throw runtime_error("Invalid arguments");
     * 2.catch�������ڲ��񲢴���try�����п����������쳣
     * try{
     *      ���;         //�������������쳣
     *  }
     *  catch(��������)
     *  {
     *      ���;         //���ڴ����쳣�ĳ���
     *  }
     */

    //12-4:
    try {
        test1();
    } catch (Exception &e) {
        e.ErrorInfo();
    }

    //12-5: �����Ͳ����ܴ����쳣,��Ϊ�ڴ�������ڱ�����ȷ����.����̫��,�������ᱨ��;���ֲ�����,�������ͻᾯ��"����ʼ��Ϊfalse".
    char *t;
    try {
        t = new char[999999999999999999];
        if (t == nullptr)
            throw "Failed to allocate!";
    } catch (char *address) {   //�޷����ʵĴ���
        cerr << "Exception: " << address << endl;
    }

    //12-6: ��Array.h

    //12-7: ��Ȼ���еĲ����ɾ�������漰��Դ�Ĳ����Ƿ��쳣��ȫ��,��Queue.h

    /*12-8:
     * 1.�������Ƽ�����C++14��׼,��auto_ptr����C++11�о��Ѿ�������,C++17ֱ�ӽ����Ƴ���,��֪�����ߵ��뷨��ʲô.
     * 2.ΪʲôҪ����auto_ptr? ������Ϊ��auto_ptr��Ȼ����copy������ת��ָ����Դ,��������ת��ָ������Ȩ��ͬʱȴ��
     *  ԭָ����Ϊ��nullptr,����������в�һ��,�ͺ�����const�����ڲ���const_cast�����������ȥ�����޸��˳������ֵ��
     *  �ڸ��ݡ�Effective STL����˵��,�����auto_ptrʹ��sort����,��ô�����Ľ������ִ���nullptr,��move����
     *  ��û���������,��Ҳ��unique_ptr�ܹ���STL�д���auto_ptr��ԭ�򣻢�auto_ptr����Ϊ��ֵ���岻���������´��뺯��
     *  �Ŀ�����Դ��ʧ��
     * 3.C++11��ʹ�õ�����ָ��������,�ֱ���unique_ptr��shared_ptr��weak_ptr
     *   unique_ptr"��ռ"��ָ��Ķ���,shared_ptr������ָ��ָ��ͬһ������,weak_ptrָ��shared_ptr������Ķ���
     */
    shared_ptr<SomeClass> p1(new SomeClass("p1"));      //auto_ptr��ͱ�������
    unique_ptr<SomeClass> p2(new SomeClass("p2"));

    *p2 = *p1;

    {
        shared_ptr<SomeClass> p3(new SomeClass("p3"));
        p1 = p3;
    }

    return 0;
}

size_t *test2() {
    auto *n = new size_t;
    if (n == nullptr)
        throw OutOfMemory();
    return n;
}

void test1() {
    auto p = test2();
    test3(p);
    cout << "The number is " << *p << endl;
    delete p;
}

void test3(size_t *p) {
    unsigned short age;
    cout << "Enter your age(0~150), please:";
    cin >> age;

    if (age > 150)
        throw RangError(age);
    *p = age;
}