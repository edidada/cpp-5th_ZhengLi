/**
 *@author ���п͡�������
 *@date 2023/2/13
 */
#include <iostream>
#include <fstream>
#include <string>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <unordered_map>

using namespace std;

/**��boost::serialization�浵
 * ǰ�᣺ͨ�����л������ÿ���඼������һ���������Ա����ָ����״̬(�������Ի�ϣ���ָ�������)
 * һ������ģ�庯��serialize�ķ�ʽ
 * 1.��Ϊ��浵��ĳ�Աģ�庯�������ƻ���Ķ���
 * class Demo{
 *      friend class boost::serialization::access;
 *      template<class Archive>
 *      void serialize(Archive &ar, const unsigned int version}{
 *          ar & ���ݳ�Ա1;
 *          ....
 *      }
 * };
 * 2.��Ϊ��浵��ķǳ�Աģ�庯������������Ԫ����ģ�壻���ṩ�㹻��Ľӿڣ��۽����ݳ�Ա����Ϊpublic(�ƻ��˷�װ��)����������
 * namespace boost{
 *    namespace serialization{
 *       template<class Archive>
 *       void serialize(Archive &ar, youClass &instance, const unsigned int version}{
             ar & instance.���ݳ�Ա1;
             ....
         }
       }
     }
 * ���������л������ͣ����ࡢ�����ࡢָ�롢���顢STL����
 * �����������ԣ���汾���ơ������л����Ϊsave/load
 * ������ϸ��Ϣ���Ķ��ٷ��ĵ� https://www.boost.org/doc/libs/1_81_0/libs/serialization/doc/index.html
 */
class Dog {
    friend boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & _age;
        ar & _weight;
    }

public:
    Dog() = default;

    Dog(unsigned age, unsigned weight) : _age(age), _weight(weight) {}

    unsigned age() const { return _age; }

    unsigned weight() const { return _weight; }

private:
    unsigned _age;
    unsigned _weight;
};

int main() {
    /*11-1
     * 1.����һ�ֳ���,�����������ݵ������ߺ�������֮�佨����ϵ,���������ݵ�����
     * 2.������ȡ��ָ�����л�ȡ����,���Ĳ�����ָ������д������
     * 3.I/O����C++���������Ű������������������ݽ���������
     */

    /*11-2
     * cout�Ǳ�׼�����,����'>'��������ض���
     * cerr�Ǳ�׼���������,û�л���,���͸��������ݱ��������,����'2>'��������ض���
     * clog������cerr,�����л���,��������ʱ���
     */

    //11-3:
    /*locale GBK(".936");
    string filename = "../test1.txt";
    wofstream out;
    out.imbue(GBK);

    out.open(filename);
    out << L"�ѳɹ�д���ļ���";
    out.close();

    //11-4:
    wifstream in;
    in.imbue(GBK);

    in.open(filename);
    if (in){
        wcout.imbue(GBK);
        wstring test1;
        in >> test1;
        wcout << test1 << endl;
    }else
        cout << "Error: cannot open the file" << endl;
    in.close();

    //11-5
    out.open(filename, ios_base::out | ios_base::app);
    out.imbue(GBK);
    out << L"�ѳɹ�����ַ���";
    out.close();

    in.open(filename);
    if (in){
        wcout.imbue(GBK);
        wstring test1;
        in >> test1;
        wcout << test1 << endl;
    }else
        cout << "Error: cannot open the file" << endl;
    in.close();*/

    /*11-6:
     * 1.��������ȷ�鵵�ͻָ�,��16������ʽ�����ļ�,��ͻᷢ�ֽ��м��serialization::archive��ASC������ͬ,�������ͬ
     * ע��: serialization��ֻ�����Ӿ�̬��,�ı��鵵�Ͷ����ƹ鵵ʱ����ʹ��ͬһ��Dog����(������ע�͵��ı��鵵�����д���)
     */
    /*Dog dog1(10, 5), dog2{};
    ofstream ofs;
    ifstream ifs;
    ofs.open("../dogInfo.txt");
    boost::archive::text_oarchive oa(ofs);
    oa << dog1;
    ofs.close();

    ifs.open("../dogInfo.txt");
    boost::archive::text_iarchive ia(ifs);
    ia >> dog2;
    cout << "age: " << dog2.age() << "\nweight: " << dog2.weight() << endl;

    ofs.open("../dogInfo.dat", ios_base::binary);
    boost::archive::binary_oarchive boa(ofs);
    boa << dog1;
    ofs.close();

    ifs.open("../dogInfo.dat", ios_base::binary);
    boost::archive::binary_iarchive bia(ifs);
    bia >> dog2;
    cout << "age: " << dog2.age() << "\nweight: " << dog2.weight() << endl;*/

    //11-7:
    /*ios_base::fmtflags original_flags = cout.flags();     //����cout��Ĭ�������ʽ
    cout << 812 << '|';                                     //���"812|"
    cout.setf(ios_base::left, ios_base::adjustfield);       //�����ֵ,���ʵ�������ַ�����ұ�
    cout.width(10);                                         //�����ַ�������Ϊ10
    cout << 813 << 815 << '\n';
    cout.unsetf(ios_base::adjustfield);                     //�����ʽ
    cout.precision(2);                                      //�����������
    cout.setf(ios_base::uppercase | ios_base::scientific);  //���������ʽΪ��ѧ������,������ĸΪ��дE
    cout << 831.0;
    cout.flags(original_flags);                             //�ָ�����������ʽ*/

    //11-8:
    /*cout << "Enter a decimal integer please:";
    int dec;
    cin >> dec;

    ios_base::fmtflags origin= cout.flags();
    cout << "Decimal:     " << dec << endl;
    cout << "Octal:       " << oct << showbase << dec << endl;
    cout << "Hexadecimal: " << hex << showbase << dec << endl;
    cout.flags(origin);*/

    //11-9:
    /*cout << "Enter a name of txt file please:";
    string fileName, str;
    cin >> fileName;
    ifstream input(fileName);   //"../test2.txt"
    ofstream output("../result.txt");
    int lineNo = 0;
    if (input){
        while (!input.eof()){
            getline(input, str);
            output << ++lineNo << " " << str;
            //ֻ�����ļ�ĩβǰ�Ĳ�������з�,��Ȼ����򵥵ؽ����з�����str��,�����ļ���ĩβ�ͻ���һ������
            if (!input.eof())
                output << endl;
        }
    }else{
        cerr << "cannot open this file" << endl;
    }
    input.close();
    output.close();*/

    //11-10:
    locale GDB(".936");
    wifstream ToTheOak("../������.txt");
    wofstream ToTheOak_wordFrequency("../������_����Ƶ��.txt");
    ToTheOak.imbue(GDB);
    ToTheOak_wordFrequency.imbue(GDB);

    if (ToTheOak) {
        wchar_t word;
        int total = 0;
        unordered_map<wchar_t, int> word_map;
        while (ToTheOak >> word) {
            if (ispunct(word, GDB))     //�������ͳ�Ʊ����ŵ�Ƶ��,�Ǿ�ɾ�������
                continue;
            ++word_map[word];
            ++total;
        }
        ToTheOak_wordFrequency << L"����\tƵ��" << endl;
        for (const auto &pair: word_map)
            ToTheOak_wordFrequency << pair.first << "\t" << pair.second << endl;
        ToTheOak_wordFrequency << L"������(����������)��" << total;
    } else
        wcerr << L"�޷����ļ�\"������.txt\"" << endl;
    ToTheOak.close();
    ToTheOak_wordFrequency.close();

    //11-11: ��IBAM.cpp��account.h/.cpp��date.h/.cpp��accumulator.h

    return 0;
}