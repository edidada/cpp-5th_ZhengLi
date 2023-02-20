/**
 *@author ���п͡�������
 *@date 2023/1/13
 */
#include <iostream>
#include <cstring>
#include <cassert>
#include <string>

using namespace std;

const double PI = 3.1415926;

class SimpleCircle {     //CLion:���ļ����ڸ���,�޷���������������
private:
    int *itsRadius;
public:
    SimpleCircle() { itsRadius = new int(0); }

    explicit SimpleCircle(int radius) { itsRadius = new int(radius); }

    SimpleCircle(const SimpleCircle &sc) {
        itsRadius = new int(*(sc.itsRadius));
    }

    ~SimpleCircle() { delete itsRadius; }

    int getRadius() { return *itsRadius; }

    double getArea() { return PI * (*itsRadius) * (*itsRadius); }

    double getCircumference() { return 2 * PI * (*itsRadius); }
};

void reverse(string &s) {
    if (s.length() < 2)
        return;
    else {
        /*s.substr(1, s.length() - 2)���ص���һ��basic_string<char>���͵���ʱ����,�����䲻�ܱ����û�
         * ��ָ��ָ��,�Ӷ�Ҳ���޷����䴫������reverse�Ա�ֱ�Ӳٿ�s���м��ַ���
         */
        string in = s.substr(1, s.length() - 2);    //�ݴ��ȡ���м��ַ���
        reverse(in);    //����in
        s = s[s.length() - 1] + in + s[0];   //�����ú��in��ԭ�ַ�������β�ַ�ƴ�ӳ����ս��
    }
}

class MyString {
private:
    char *str;      //�ַ������׵�ַ
    unsigned int size;
public:
    friend ostream &operator<<(ostream &os, const MyString &s);

    friend istream &operator>>(istream &is, MyString &s);

    MyString();

    MyString(const char *s);        //���������ַ����顢�ַ���������(������string)��char*��ʽת��,���Բ���explicit
    MyString(const MyString &rhs);

    ~MyString() {
        delete[] str;
        size = 0;
    }

    unsigned int length() const { return size; }

    MyString &operator=(const MyString &s);

    MyString operator+(const MyString &s) const;      //�����س���������ɼ�������ʵ�ֲ���
    MyString &operator+=(const MyString &s);

    const char &operator[](unsigned int index) const {      //"[]"�������const�汾,���㳣���������
        assert(index >= 0 && index <= size);        //����±��Ƿ�Խ��,�����õ�12�µ��쳣����
        return str[index];
    }

    char &operator[](unsigned int index) {           //����������Ϊ��֧�ָ�ֵ����,����s[1] = 'a';
        assert(index >= 0 && index <= size);        //����±��Ƿ�Խ��,�����õ�12�µ��쳣����
        return str[index];
    }
};

MyString::MyString() {
    str = new char[1];
    str[0] = '\0';
    size = 0;
}

MyString::MyString(const char *s) {
    size = strlen(s);
    str = new char[size + 1];
    strcpy(str, s);
}

MyString::MyString(const MyString &rhs) {
    size = rhs.size;
    str = new char[size + 1];
    strcpy(str, rhs.str);
}

MyString &MyString::operator=(const MyString &s) {
    if (&s != this) {             //����������Ҹ�ֵ
        if (size != s.size) {     //����������������С��s��ͬ,��ô�ͷ�ԭ������ڴ�,Ȼ��Ϊ�����·����ڴ�
            delete[] str;       //ɾ��ԭ���ڴ�
            size = s.size;      //���ñ�����������С
            str = new char[size + 1];   //���·����ڴ�
        }
        strcpy(str, s.str);
    }
    return *this;               //���ص�ǰ���������
}

MyString MyString::operator+(const MyString &s) const {
    /*Ϊʲô�����س�����
     * ������֪,��C++��,������������ı��ʽֻ��������ֵ,��������c = a + b,��������a + b = c,Ȼ�����Գ���(a + b) = c,����ʵ��
     * ��c��ֵ��һ����ʱ��������,��û���κ�����.Ϊ�˱����������������ĸ�ֵ���,����������+��-��*��/�����������ʱѡ�񷵻س�����,
     * ��������Ϊ��ή�ʹ���Ŀɶ���,����,��ȻC++��ע�����������������ĸ�ֵ�������,�������ֺαؽ�ֹ��?
     */
    MyString temp;
    temp.size = size + s.size;
    temp.str = new char[temp.size + 1];

    //�����������ķ���ֵ����Dest,�����Ϊ��ƴ�Ӻ���,��ôstr�ͱ��ı���
    strcat(strcpy(temp.str, str), s.str);

    return temp;    //������ʱ����
}

MyString &MyString::operator+=(const MyString &s) {
    /* 1.��Ҳ������ѭ���������ַ����ĸ���,�������ɻ����Ӵ�����
     * 2.һ�ֱȽϱ��İ취:������ʱ����temp,��str��s.str�е��ַ���ƴ�Ӻ��Ƶ�temp.str��,Ȼ��temp��ֵ��*this,��󷵻�*this.
     * ��Ȼ,���ֶ��һ�ٵ���������������ʱ�տ���,���Ҵ���Ҳ�������
     */
    char *temp = str;               //�ݴ汾�����ַ�������׵�ַ
    size += s.size;
    str = new char[size + 1];       //���·���ռ�
    strcat(strcpy(str, temp), s.str);
    delete[] temp;                  //ɾ��ԭ�пռ�
    return *this;
}

ostream &operator<<(ostream &os, const MyString &s) {
    for (int i = 0; i < s.size; i++)
        os << (s.str)[i];               //��Ҫ��os�滻Ϊcout,�������Ͳ���֧�������������
    return os;
}

istream &operator>>(istream &is, MyString &s) {
    is >> s.str;
    s.size = strlen(s.str);
    return is;
}

void T_Matrix(double a[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < i; j++) {       //����Ϊj < 3,�������ָ�ԭ��
            swap(a[i][j], a[j][i]);
        }
    }
}

void T_Matrix(double **a, double **at, unsigned rowSize, unsigned columnSize) {
    for (int i = 0; i < rowSize; i++)
        for (int j = 0; j < columnSize; j++)
            at[j][i] = a[i][j];
}

void printMatrix(double **matrix, unsigned rowSize, unsigned columnSize) {
    for (int i = 0; i < rowSize; i++) {
        for (int j = 0; j < columnSize; j++) {
            cout << matrix[i][j] << "  ";
        }
        cout << endl;
    }
}

class Employee {
public:
    Employee();

    Employee(const char *name, const char *city, const char *street, const char *postalCode);

    Employee(const Employee &employee);

    ~Employee();

    void setName(const char *newName);

    void display();

private:
    char *name;
    char *city;
    char *street;
    char *postalCode;
};

Employee::Employee() {
    name = new char[1];
    city = new char[1];
    street = new char[1];
    postalCode = new char[1];
    name[0] = '\0';
    city[0] = '\0';
    street[0] = '\0';
    postalCode[0] = '\0';
}

Employee::Employee(const char *name, const char *city, const char *street, const char *postalCode) {
    this->name = new char[strlen(name)];
    this->city = new char[strlen(city)];
    this->street = new char[strlen(street)];
    this->postalCode = new char[strlen(postalCode)];
    strcpy(this->name, name);
    strcpy(this->city, city);
    strcpy(this->street, street);
    strcpy(this->postalCode, postalCode);
}

Employee::Employee(const Employee &employee) {
    name = new char[strlen(employee.name)];
    city = new char[strlen(employee.city)];
    street = new char[strlen(employee.street)];
    postalCode = new char[strlen(employee.postalCode)];
    strcpy(name, employee.name);
    strcpy(city, employee.city);
    strcpy(street, employee.street);
    strcpy(postalCode, employee.postalCode);
}

Employee::~Employee() {
    delete[] name;
    delete[] city;
    delete[] street;
    delete[] postalCode;
}

void Employee::setName(const char *newName) {
    char *temp = name;
    name = new char[strlen(newName)];
    strcpy(name, newName);
    delete[] temp;
}

void Employee::display() {
    char *n = name, *c = city, *s = street, *p = postalCode;
    while (*n != '\0') {
        cout << *n;
        n++;
    }
    cout << "  ";
    while (*c != '\0') {
        cout << *c;
        c++;
    }
    cout << "  ";
    while (*s != '\0') {
        cout << *s;
        s++;
    }
    cout << "  ";
    while (*p != '\0') {
        cout << *p;
        p++;
    }
    cout << endl;
}

int main() {
    //6-1:һ����10 * 5 * 15 = 750

    //6-2:��һ��Ԫ����a[0],���һ��Ԫ����a[19]

    //6-3:
    int a1[] = {1, 2, 3, 4, 5};

    //6-4: sizeof(oneArray) / sizeof(oneArray[0])

    /*6-5:�ڱ�����,����forѭ�����ص�����
     * �ٻ��ڷ�Χ��forѭ��:�ʺϱ���,�������Ƚ���д��ɶ�д�ϲ�,��Ҫ��ʼ��,�����������
     * ����ͨforѭ��:��Ҫ�ҵ�һ����ϵʽ����ʼ��
     */
    int b[5][3];
    /*
    int init = 1;
    for (auto & i : b)
        for (int & j : i)
            j = init++;
    */
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 3; j++) {
            b[i][j] = 3 * i + j + 1;
        }
    }

    //6-6:*��ΪһԪ�����ʱ���ڽ���������ַ,&��ΪһԪ�����ʱ����ȡ������ַ

    /*6-7:ָ����C/C++�о��ǵ�ַ;ָ���д洢�ĵ�ַ�Ǽ�ӵ�ַ,�����ַ�е�ֵ������,����int���͵���ֵ10
     * �洢�ڵ�ַΪ1000�Ĵ洢��Ԫ��,��ָ��洢�ĵ�ַ����1000,�����ַ(1000)�洢�ľ���10
     */

    //6-8:���봴���������͵Ķ����Ϊ����int *p = new int[10];

    //6-9: '\0'

    //6-10:
    cout << "Enter 5 integers please:";
    int arr[5];
    for (int &i: arr)
        cin >> i;
    for (int &i: arr)
        cout << i << " ";
    cout << endl;

    /*6-11:
     * 1.����:�������൱���˸���ָ�볣��,�����ñ�ָ�볣�����Ӹ߲�,�����ڷ�װ��������,������ַ����������;�ڿ��Զ�ָ�볣��ȡ��ַ,
     * ���޷�������ȡ��ַ;����ָͨ����Զ�θ�ֵ,������ֻ���ڳ�ʼ��ʱָ�������õĶ���,֮��Ͳ��ܸ���;����Ҫʵ�����ݵ�˫�����
     * ��С���ݿ���,��ʹ����������������Ҫ����ָ��������㡢��ȫ,�ɶ���Ҳ����
     * 2.ֻ��ʹ��ָ��,������ʹ�����õ����;
     *   ����Ҫͨ����֧���ȷ����ָ����ָ����,����Ҫ����;�ı�����ָ�Ķ���
     *   ��ָ���ֵ����Ϊ��ָ��
     *   ����Ҫʹ�ú���ָ��
     *   ����Ҫ�洢��new��̬�����ĵĶ��������
     *   �ݺ��������򷵻�����Ϊ����
     */

    /*6-12:
     * float *pfloat;
     * char *pstr;
     * struct Customer *pcus;
     */

    //6-13: cout << *fp << endl;

    //6-14:��ռ8�ֽ�
    double d = 1.2, *fd = &d;
    cout << "fd: " << sizeof(fd) << "B\n" << "*fd: " << sizeof(*fd) << "B" << endl;

    /*6-15:
     * const int* p1��ָ�����ͳ�����ָ��,ͨ��p1�޷��޸�����ָ������ֵ;int * const p2��ָ�����͵�ָ�볣��,һ����ʼ��,
     * �Ͳ�����ָ����������
     */

    //6-16:
    int a, *p = &a, &r = a;
    *p = 10;
    r = 5;

    //6-17:ָ�����pδ����ʼ����ʹ��,������ڰ�ȫ����

    /*6-18:
     * 1.���ڵ�����:����fn1�ж�̬�������ڴ�,����ʹ�ú�û�н��й黹���ͷ�,�������ڴ�й©.
     * 2.�޸ķ���:�ٷ���p,����̬������ڴ���׵�ַ,�õ�����������ͷ��ڴ�;�ڸ�����fn1�������ò���,���䴫��p;
     *  ����д�˺���,�������ڴ�
     * ����:��Ȼ,�����ٸ�������Ŀ�Ŀ�����ͼ,���������취һһ��Ӧ,����ʵ������һ������Ҫ�ɳ���Ա����ʵʩ,���սϴ�,
     * ����,������Ҫд���ຯ��
     */

    /*6-19:
     * long (*f1)(int);            //ֱ����������ָ��
     * typedef long (*f2)(int);    //ʹ��typedef
     * long (A::*f1)(int);
     */

    //6-20:
    SimpleCircle s1, s2(5), s3(s2);
    cout << "Circle\t" << "Radius\t" << "Area\t" << " Circumference" << endl;
    cout << "s1    \t" << s1.getRadius() << "\t" << s1.getArea() << "\t " << s1.getCircumference() << endl;
    cout << "s2    \t" << s2.getRadius() << "\t" << s2.getArea() << "\t " << s2.getCircumference() << endl;
    cout << "s3    \t" << s3.getRadius() << "\t" << s3.getArea() << "\t " << s3.getCircumference() << endl;

    /*6-21:To handle yourself, use your head; to handle others, use your heart.
     * ע��:��ʹ��>>��ȡ����,���������м�Ŀո�;��ʹ��getline��ȡ����,����������в����Ŀհ��ַ�(����ǰ��û��������)
     */
    //��ջ�����
    cin.clear();
    cin.sync();

    cout << "Enter an English sentence please:";
    string str;
    int cnt = 0;
    getline(cin, str);
    for (char i: str)
        if (isalpha(i))
            cnt++;
    cout << "The total of letters in the sentence: " << cnt << endl;

    /*6-22:
     * ��������:�޸���Ŀ,���罫�����ķ��������޸�Ϊstring,�Ӷ������Ѷ�
     * ����:�ݹ��㷨�ĺ������ڷֽ�����
     * �����ַ���sΪ�ջ���ֻ��һ���ַ�,���㷨����;
     * �ڷ���,�Ƚ���s[0]��s[s.length() - 1]),Ȼ���ȡ�����ַ���������Ϊ�µ�s,�ص������;
     * ˵��:����string��substr�����ķ���ֵ����Ϊbasic_string,���Ծ����㷨˼�벻��,������ʵ�ֵĴ���ȴ�޷���֮һһ��Ӧ;
     * ���뽫�㷨˼��ֱ�ӷ���Ϊ�������,��������ʵ�ַ���ֵ����Ϊstring���ַ�����ȡ�������跨��string���substr������
     * ����ֵ�����޸�Ϊstring(��ʱ������ܷ�ͨ���̳к���д�ķ���)
     */
    string ts;
    cout << "Enter a string please:";
    getline(cin, ts);
    reverse(ts);
    cout << "Reverse:" << ts << endl;

    //6-23:��Ҳ���Խ���8���ɼ���д������,Ȼ���ȡ�����еĳɼ�,�������ƽ���ɼ�.���ⲻ����Щ���һ����
    double total = 0.0, score;
    cout << "Enter the scores of 8 students:";
    for (int i = 0; i < 8; i++) {
        cin >> score;
        total += score;
    }
    cout << "The average score is " << total / 8 << endl;

    /*6-24:
     * 1.˵��:��MyString��ʵ������Ŀ����ȷҪ��Ĺ���,δ���и�������
     * 2.����˼·:����ʵ��string������й����ӿ�,δ�򻯴���,���Ե���<cstring>�е�strcat/strncat/strcpy/strncpy/
     * strlen/strcmp/strchr(�����ַ��״γ��ֵ�λ��)/strrchr/strstr/...����˵����Ϣ��ο�
     * https://zh.cppreference.com/w/cpp/header/cstring
     * �ɴ˿ɼ�.<cstring>�еĺ����Ѿ�ʵ����string�Ĵ󲿷ֹ���,ʣ�๦���������ʵ��,��Ȼ��Ҳ����ѡ�񲻵��ÿ⺯��,ֻ��
     * �������Զ�,���ܿ��ܽϲ�.֮������Ը����Լ����뷨�������������,�������û�����ʵ�����ѡ������ʺϵ��ַ���ƥ���㷨
     * (��ƥ���㷨��KMP�㷨)
     */
    char str1[] = "world";
    MyString s10 = "hello ", s20 = str1, s30, s40("jack"), s50(str1), s60 = s10;
    cout << "s1: " << s10 << "\t" << s10.length() << endl;
    cout << "s2: " << s20 << "\t" << s20.length() << endl;
    cout << "s3: " << s30 << "\t" << s30.length() << endl;
    cout << "s4: " << s40 << "\t" << s40.length() << endl;
    cout << "s5: " << s50 << "\t" << s50.length() << endl;
    cout << "s6: " << s60 << "\t" << s60.length() << endl;
    cout << "Enter a string please:";
    cin >> s30;
    cout << "s6: " << s30 << "\t" << s30.length() << endl;
    cout << s10 + s20 << endl;
    s10 += s20;
    cout << "s1: " << s10 << "\t" << s10.length() << endl;
    cout << s10[10] << endl;
    s10[10] = 'x';
    cout << s10 << endl;

    //6-25:����ת�ü����л���,��Ŀ��δ��ȷָ�������ķ�������,�ʶ�����ѡ��ֱ���޸�����򷵻�����
    cout << "Enter a matrix of 3*3:";
    double matrix[3][3];
    for (auto &i: matrix) {
        for (double &j: i) {
            cin >> j;
        }
    }
    for (auto &i: matrix) {
        for (double j: i) {
            cout << j << "  ";
        }
        cout << endl;
    }

    T_Matrix(matrix);

    cout << endl;
    for (auto &i: matrix) {
        for (double j: i) {
            cout << j << "  ";
        }
        cout << endl;
    }

    /*6-26:
     * 1.����:����ĿҪ�����û�������������������,����ά������к��ж��Ǳ���,�����ڶ����ά����ʱ,�ǵ�һά���붼�ǳ������ʽ,
     * ����ֻ��ʹ�ö�̬�����ڴ�ķ�ʽ������;���ϸ���˵,C++��û�ж�ά����,nά�������Ԫ��Ϊn-1ά�����һά����,���ڴ�,����ֻ
     * ��Ҫһάһά���������鼴��,���ڶ�ά����,������������ָ��(����row��),Ȼ��Ϊÿһ������ռ�(�����СΪcol,ѭ��row��),
     * ���ͷ��ڴ�ʱ��ѭ���ͷ��пռ�(һά����),���ͷ���ָ��(Ҳ��һά����);�������Ͼ���ת�ú������������ַ�ʽ---����һ����ά����
     * �ʹ���������ά����,����ǰ�ߵĺ���ԭ�͸��ӡ�����Ҫ���������ͷ��ڴ�(�ͷ����ɶ��Խϲ�,Ҫ��"�����ͷ�"�������ڴ�й©),
     * ���֮�º��ߵĺ���ԭ�ͼ�,�ҷ���"�������ͷ��ڴ�"���������;�ܶ�̬����Ķ�ά����ʵ������ָ������(��ṹ��P209ͼ6-9(a)),
     * �����󲢲����Ƿ���,���Բ�����ԭ����Ŀռ�洢ת�ú�ľ���(ͨ���޸���������ǿ�н�ʡ�ռ䲻�Ǹ�������)
     * 2.��������:��ȻC++�еĶ�ά����Ĵ洢�ṹ��һά�������ͬ,ֻ�ǽ��ͺͷ��ʷ�ʽ��ͬ,��ô����Ҳ���Լ�����һά����洢,Ȼ������
     * ������ȫ�����ں�����,��������ֻ�贫��һά����(���鳤��Ϊ��*��)�������к��м��ɡ������ַ�����ȱ��Ҳ�ܶ�:�پ����Ƕ�ά,����
     * ȴ��һά����,������ֱ�۸���;�ھ���Ԫ���±���ʽ��ת�ñ��ʽ��������ʽ������;�۱����������Խ���������������Ϳ����"ת��";
     * �����������������һ����ά������ܽ����������ı�ԭ�����ֵ,�˺����ͻ�ֱ������;��Ҫ��������������һά�������ת�þ���,��ô
     * ����������û�д��ڵı�Ҫ,��Ϊ��������������������˱��������ķ��ؽ���Ƿ�
     */
    cout << "Enter the size of row and column of the matrix respectively:";
    unsigned row, col;
    cin >> row >> col;

    cout << "Enter the matrix orderly:";
    auto **m = new double *[row];       //����ԭ������ָ��
    auto **mt = new double *[col];      //����ת�þ������ָ��
    for (int i = 0; i < row; i++)
        m[i] = new double[col];         //Ϊÿһ�з���ռ�
    for (int i = 0; i < col; i++)
        mt[i] = new double[row];        //Ϊת�þ����ÿһ�з���ռ�

    //�����Դ����о���Ԫ�ص��±�˳���ȡ
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            cin >> m[i][j];

    cout << "Origin:" << endl;
    printMatrix(m, row, col);

    T_Matrix(m, mt, row, col);
    cout << "Transpose:" << endl;
    printMatrix(mt, col, row);      //ע��ת�þ���洢�ռ����������ʹ�ӡ����

    //�ͷſռ�
    for (int i = 0; i < row; i++)
        delete[] m[i];
    delete[] m;

    for (int i = 0; i < col; i++)
        delete[] mt[i];
    delete[] mt;

    /*6-27:
     * 1.����˽����������:����ֱ��ʹ��string�洢��4�����Ժܷ���,��������һ����Employee�������͵�ռ��128�ֽڿռ�,���������
     * �ַ�ָ��(����)��̬������ͷ��ڴ�,��ô��ֻ��ռ��32�ֽڿռ�,����,��Ҳ���ǶԶ�̬�ڴ����֪ʶ��Ĺ���.��Ȼ,����ú��������
     * ��ø������,��ֻ������һ�ֽ���˼·.
     * 2.����������Ч���ж�:�Ⲣ���Ǳ���Ӧ�ÿ��ǵ�����,Ҫ�жϳ��������ֵ������ʱ��Ƿ�Ϊ��׫�Լ�����֮���Ƿ�ƥ��,����ʹ��GUI���
     * �����Ϊѡ��,Ҳ�ɽ������ݿ���ļ������жϵ�
     */
    Employee e1, e2("����", "������", "����������·�ֵ�", "100017");
    e1.display();
    e2.display();
    e1.setName("����");
    e1.display();

    /*6-28:
     * 1.��6_10.cpp���޸Ľ����6_10r.cpp,��6_16.cpp���޸Ľ����6_16r.cpp
     * 2.�ɴ˿ɼ�,�ڽ������ݵ�˫����ʱ,���ʺϴ����ò���;�ڱ��涯̬��������ʱ������׵�ַʱ,ʹ��ָ�����
     */

    /*6-29:
     * 1.���û���:������reinterpret_cast��int��һά������׵�ַ(int*)ǿ��ת������double*,ǰ��ռ4�ֽ�,����ռ8�ֽ�,
     * ��ִ����*p = 5֮��,˫���ȸ�����5�ͻḲ�ǵ�int�͵�arr[0]��arr[1]
     * 2.����������(���Ͳ���ȫ)�ķ���:�����зǳ�����ĵײ���;,����Ҫ��reinterpret_cast
     */

    /*6-30:
     * 1.reinterpret_castһ�����ڷǳ�����ĵײ�
     * 2.const_staticֻ���ڽ���ָ��ת��Ϊ��ָͨ�롢��������ת��Ϊ��ͨ���ú�ĳЩ���ⳡ��(����P248~P249������)
     * 3.static_cast�����������,��ͨ��
     */

    return 0;
}