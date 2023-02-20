/**
 *@author ���п͡�������
 *@date 2023/2/5
 */
#include <iostream>
#include <ctime>
#include <vector>
#include <deque>
#include <list>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <random>

using namespace std;

template<class Container>
int JosephProblem(int n, int m) {
    /*ֱ�Ӽ��㷨
     int survivor = 0;
     for (int i = 1; i <= n; i++)
         survivor = (survivor + m) % i;
     return survivor;
     */

    /*������ĿҪ��: �����������˳��
     * ����˫���������֧��ֱ���ƶ�nλ,����list������vector��deque����ֱ����seq.erase(seq.begin()+number),
     * �־���θ�Чʵ�ִ˺���ģ���������:
     * 1.�Զ���������ƶ�����:����typeid������ʱ��ȡ����������,���ݲ�ͬ���ͱ�д��������,���������ж�����������������
     * typeid(std::iterator_traits<Iterator>::iterator_category) == typeid(std::random_access_iterator_tag);
     * ��β�������������(����P471������),�Ǳ��������޷����õ�.
     * ԭ���������޷�ֱ�Ӵ����������,Container����ģ�����,���廯�� list<int>��list��,v�Ƕ���,v.begin()�ǵ�����,
     * auto�޷�����v.begin��ȡ�����������
     * 2.�Լ�ʵ��advance����: �����ģ��P471ҳ������,Ҳ����ģ��<iterator>�������,ģ�±��˶����һģһ��������û������
     * 3.����ģ���ػ�:
     * ���ػ�list: ��Ϊvector��deque�ĵ��������;�Ϊ������ʵ�����,��list����˫����ʵ�����
     * ���ػ�vector: ��vectorԤ��n�ݿռ�,��������ʱ���¶�̬����ռ䡾ע: �ٺ͢ڵ����ܱ��ּ���һ����
     * ��ȫ���ػ�: ��ģ�廹��ʲô���ڵı�Ҫ��?
     * 4.����3������������ģ��: �����һ������Ϊ����������,������ֻ����ø�������ģ�弴��,������������advance��ʵ��
     */
    Container v;

    for (int i = 1; i <= n; i++)
        v.push_back(i);

    ptrdiff_t number = 0;       //����:��ʼΪ0

    while (v.size() != 1) {
        number = (number + m - 1) % static_cast<ptrdiff_t>(v.size());    //��������ߵı��
        v.erase(v.begin() + number);
    }

    return v[0];
}

template<>
int JosephProblem<list<int>>(int n, int m) {
    list<int> v;

    for (int i = 1; i <= n; i++)
        v.push_back(i);

    ptrdiff_t number = 0;

    while (v.size() != 1) {
        number = (number + m - 1) % static_cast<ptrdiff_t>(v.size());
        auto iter = v.begin();      //iterΪ����������
        advance(iter, number);         //��iterָ�������
        v.erase(iter);                  //ɾ��Ԫ��
    }

    return v.front();
}

template<class T>
void exchange(list<T> &l1, typename list<T>::iterator p1, list<T> &l2, typename list<T>::iterator p2) {
    //��Ŀ�����ú���ԭ������,Ӧ����list<T>::iteratorǰ����typename: ��ģ�岻����Ϊ����,��ʵ���ſ���
    l1.splice(p1, l2, p2, l2.end());
    l2.splice(l2.end(), l1, p1, l1.end());
}

template<class Container>
void t10_7(Container c) {
    c.push(5);
    c.push(1);
    c.push(4);
    c.push(6);
    cout << c.top() << " ";
    c.pop();
    cout << c.top() << " ";
    c.pop();
    c.push(2);
    c.push(3);
    cout << c.top() << " ";
    c.pop();
    cout << c.top() << endl;
}

template<>
void t10_7(queue<int> c) {
    c.push(5);
    c.push(1);
    c.push(4);
    c.push(6);
    cout << c.front() << " ";
    c.pop();
    cout << c.front() << " ";
    c.pop();
    c.push(2);
    c.push(3);
    cout << c.front() << " ";
    c.pop();
    cout << c.front() << endl;
}

double pow_int(int base, int indices) {
    double result = 1.0;
    int cycles = abs(indices);
    if (indices == 0)           //x^0 = 1, 0^0 = 1
        return 1;
    else if (base == 0)         //0^x = 0 (x !=0)
        return 0;
    else {
        while (cycles--)
            result *= base;
    }
    return indices > 0 ? result : 1.0 / result;     //x^-a = 1 / x^a
}

int main() {
    /*10-1:
     * 1.�����Ӹ���
     *   ����: �ٻ���������Ԫ�ص���֯��ʽ: ˳����������������;�ڻ��������������ĵ���������: ��������-->�����������
     *   ������: ��������������������-->ǰ�������-->˫�������-->������ʵ�����
     *   �㷨: ���ɱ������㷨���ɱ������㷨�������㷨�������㷨����ֵ�㷨
     * 2.����
     * vector/deque --- ������ʵ�����
     * list/set/multiset/map/multimap  --- ˫�������
     */

    /*10-2:
     * 1.[s1+1, s+4)����s[1]��s[2]��s[3]
     * 2.��[s+4, s+4)���Ϊ�Ƿ�����
     */

    //10-3: ʵ�����н���.��������s����ӵ�Ԫ�ظ���С�ڵ���capacityʱ,s.capacity()����;֮��������·���ռ�����

    //10-4: vector  deque   list

    /*10-5:
     * 1.Լɪ������: �ֳƶ��־�����,����һ����ʽ��n����Χ��һȦ,��һ���˴�1��ʼ����,������mʱ,���˾ͻ���ɱ,���ʣһ���˴��.
     * ���統n = 4, m = 3ʱ, ��ɱ��˳����3,2,4,������������1
     * 2.�������:
     *   ��ֱ����forѭ��
     *   �ڰ�����ĿҪ�����˳������,��ֱ���һ��
     * 3.�����������ʱ��ķ���,�����getRunTime.cpp
     * ���л���˵��:
     * ������:     Intel(R) Core(TM) i5-7300HQ CPU @ 2.50GHz   2.50 GHz
     * ����RAM:    8.00 GB
     * ����ϵͳ�汾: Windows 10רҵ�� 22H2
     * GCC:        12.2.0
     * MinGW-w64:  10.0.0 (linked with ucrt)
     * IDE:        CLion 2022.3.2
     * ������:
     * vector: 1s����
     * deque:  6s����
     * list:   70s����
     */
    time_t start_time, end_time;

    start_time = clock();
    cout << JosephProblem<vector<int>>(100000, 5) << endl;
    end_time = clock();
    cout << "vector: " << (end_time - start_time) << "ms" << endl;

    start_time = clock();
    cout << JosephProblem<deque<int>>(100000, 5) << endl;
    end_time = clock();
    cout << "deque: " << (end_time - start_time) << "ms" << endl;

    start_time = clock();
    cout << JosephProblem<list<int>>(100000, 5) << endl;
    end_time = clock();
    cout << "list: " << (end_time - start_time) << "ms" << endl;

    //10-6: ����list��splice��Ա��������ʵ��
    list<int> list1, list2;
    for (int i = 0; i < 10; i++) {
        list1.push_back(i);
        list2.push_front(i);
    }
    auto iter1 = next(list1.begin(), 5);
    auto iter2 = next(list2.begin(), 7);
    exchange(list1, iter1, list2, iter2);

    cout << "list1: ";
    for (auto i: list1)
        cout << i << " ";
    cout << endl;

    cout << "list2: ";
    for (auto i: list2)
        cout << i << " ";
    cout << endl;

    /*10-7: ��ջ�����к����ȼ����еĲ����ص����ʶ
     * ջ:       ����ȳ�
     * ����:      �Ƚ��ȳ�
     * ���ȼ�����: ������������Ԫ��
     */
    stack<int> s;
    queue<int> q;
    priority_queue<int> pq;
    t10_7(s);   //��_��ͷ��ȫ�ֱ�����Ϊ�����ؼ���,�û�����ʹ��
    t10_7(q);
    t10_7(pq);

    /*10-8:I do not believe in taking the right decision . I take a decision and make it right .
     * �������EOF?
     * Linux/Unix/Mac:      ctrl + D
     * cmd/Visual Studio:   ctrl + Z
     * CLion + MinGW:       ctrl + C(û��Ӧ,Ӧ���Ǽ�λ��ͻ),��\CLion\bin�µ�idea.properties�ļ���,��
     * run.processes.with.pty=TRUE��TRUE��ΪFALSE,����CLion,Ȼ��Ϳ�����ctrl + D��
     * CLion + Cygwin:      ctrl + D
     */
    map<string, int> word_map;
    cout << "Enter several words please (end up with EOF):";
    string word;
    while (cin >> word)
        ++word_map[word];
    for (const auto &pair: word_map)   //C++17����pair�滻Ϊ[word, count]
        cout << "{" << pair.first << ", " << pair.second << "} ";
    cout << endl;

    /*10-9: ֱ�ӿ���׼ͷ�ļ��еĺ���������ģ��ʵ��(��MSVC�������ṩ�Ŀ�Ϊ��),�����б�д����Ա�
     * ΢��һ��ϲ����left��right����,���˸�Ϊ��a��b, T��_FwdIt1����ģ�����
     * void swap(T& a, T& b){       //�����ػ���������ڲ������Լ��ĳ�Ա����swap
     *     C++11ǰ��C++11��C++14��C++17���������׶�,�ú�������ͷ�ļ���һ��,����Ҳ���в�ͬ,������ʵ�ֻ���
     *     T temp = a;
     *     a = b;
     *     b = temp;
     *     ���https://zh.cppreference.com/w/cpp/algorithm/swap��ֱ�ӿ�ͷ�ļ��е�Դ����,������Ҳ�ܿ���������߱�����
     *     ��������Щ����
     * }
     * void iter_swap(_FwdIt1 _Left, _FwdIt2 _Right){
     *     swap(*_Left, *_Right);
     * }
     * _FwdIt2 swap_ranges(const _FwdIt1 _First1, const _FwdIt1 _Last1, _FwdIt2 _First2);
     * ����: swap���β�������,ʣ���������βζ���ָ��,swap_rangesʵ�������Ƚϸ���,��ԭ��ܼ�,��������֤�����ĺϷ���,Ȼ����
     *      ��Χ[first1, last1)��ʼ��first2����һ��Χ�佻��Ԫ��,��󷵻�ָ��ʼ�� first2 �ķ�Χ�б���������ĩԪ�غ�һԪ�ص�
     *      �������������ʵ���漰�ĺ���ģ��Ƚ϶�,����Ȥ�Ŀ������о�,΢���ڹؼ����봦д��ע��.
     * ˵��: ����Ҳ��֪����α�д����Ա������������������е�Ԫ��ִ�еĽ�������,��ӡ��ַ?����ֱ�ӿ�Դ�������ѡ��.
     */

    //10-10:������ȫû��Ҫ��sort����,��Ϊset�ڵ�Ԫ�ر�����������
    set<int> s1, s2;

    cout << "Enter a set of integers please (end up with 0):";    //49 36 59 50 49 65 52 78 67 96 0
    while (true) {
        int v;
        cin >> v;
        if (v == 0) break;
        auto r = s1.insert(v);
        if (!r.second)
            cout << v << " is duplicated." << endl;
    }
    cout << "Enter a set of integers again, please (end up with 0):"; //89 4 79 23 49 75 18 47 89 21 0
    while (true) {
        int v;
        cin >> v;
        if (v == 0) break;
        auto r = s2.insert(v);
        if (!r.second)
            cout << v << " is duplicated." << endl;
    }

    cout << "The intersection of s1 and s2 = {";
    set_intersection(s1.begin(), s1.end(), s2.begin(), s2.end(), ostream_iterator<int>(cout, ","));
    cout << "}" << endl;
    cout << "The union of s1 and s2 = {";
    set_union(s1.begin(), s1.end(), s2.begin(), s2.end(), ostream_iterator<int>(cout, ","));
    cout << "}" << endl;
    cout << "The difference of s1 and s2 = {";
    set_difference(s1.begin(), s1.end(), s2.begin(), s2.end(), ostream_iterator<int>(cout, ","));
    cout << "}" << endl;

    /*10-11:
     * (1).��������1 4 5 4 5,û�������ﵽȥ���ظ�Ԫ�ص�Ŀ��.�޸��������ʾ:
     * (2).list�Լ���unique��Ա�������Ǹ���Ч�ķ���
     * ���н������:
     * ��uniqueɾ������[first, last)�������ظ���Ԫ��(ֻ������һ��),�����ط�Χ�����߼���β��β�������(����,
     * ���ڱ������з��ص���ָ��s�ĵ�4��Ԫ�صĵ�����).����ʵ��ͨ���ø�д�ķ�ʽ���ظ�Ԫ�ؽ����߼��ϵ�ɾ����,�����ĵ�����������
     * ��ָ�붼û��ʧЧ,�������ǿ��Ե���erase������ɾ����Щ�ظ�Ԫ��.
     * ��list��ֱ��ɾ�����
     */
    int arr[] = {1, 1, 4, 4, 5};

    vector<int> v(arr, arr + 5);
    v.erase(unique(v.begin(), v.end()), v.end());
    copy(v.begin(), v.end(), ostream_iterator<int>(cout, "\n"));

    list<int> ls(arr, arr + 5);
    ls.unique();
    copy(ls.begin(), ls.end(), ostream_iterator<int>(cout, "\n"));

    //10-12:��srand()��rand()����ĺ�������ķ���ֵ����,����ֻ����C++��<random>����ʵ��
    vector<int> v1(5);

    generate(v1.begin(), v1.end(), [] {
        random_device seed;                         //�������������: Ӳ�����ɵ��������,�����ܴ�,���ʺ϶�ε������������������
        default_random_engine gen(seed());      //�����������: MSVC��Ĭ�������������÷ɭ��ת�㷨mersenne_twister
        uniform_int_distribution<int> dis(0, 9);    //������ֲ���:ֻ���þ��ȷֲ�,�����ֲ��޷�ָ����Χ
        return dis(gen);
    });
    for (const auto &i: v1)
        cout << i << " ";
    cout << endl;

    //10-13: ��ָ������,��ѭ������Ҫ��ϵͳ��pow����ִ��Ч�ʸ�
    cout << "5 to the of power of n:" << endl;
    transform(v1.begin(), v1.end(), ostream_iterator<int>(cout, " "),
              [](int n) { return pow_int(5, n); });
    cout << endl;

    cout << "n to the of power of 7:" << endl;
    transform(v1.begin(), v1.end(), ostream_iterator<int>(cout, " "),
              [](int n) { return pow_int(n, 7); });
    cout << endl;

    cout << "n to the of power of n:" << endl;
    transform(v1.begin(), v1.end(), ostream_iterator<int>(cout, " "),
              [](int n) { return pow_int(n, n); });
    cout << endl;

    //10-14: ��Array.h

    //10-15: ��IncrementIterator.h

    //10-16: ��ģ���ػ��ļ�Ӧ��,���mySort.cpp

    /*10-17:Boost����͵��뵽IDE���ǱȽ��ѵ�,���ṩCompile&Include_Boost.txt�Թ��ο�
     * 1.10_3.cpp�޸�ǰ��Աȣ��޸ĺ�����鿴��������STL����
     * 2.��10_18.cpp
     * 3.��10_18.cpp
     * 4.��10_10.cpp
     */

    return 0;
}