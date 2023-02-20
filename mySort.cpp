#include <algorithm>
#include <iterator>
#include <vector>
#include <iostream>

using namespace std;

//ʵ����,�ú���ģ��ȷʵ�õ���,CLion��������������
template<class InputIterator, class OutputIterator>
void mySort_helper(InputIterator first, InputIterator last, OutputIterator result, output_iterator_tag) {
    vector<typename iterator_traits<InputIterator>::value_type> s(first, last);
    sort(s.begin(), s.end());
    copy(s.begin(), s.end(), result);
}

template<class InputIterator, class OutputIterator>
void mySort_helper(InputIterator first, InputIterator last, OutputIterator result, random_access_iterator_tag) {
    const auto &first2 = result;
    const auto &last2 = copy(first, last, result);
    sort(first2, last2);
    /*���������뵽����if����жϵ�����������������,�Ӷ���ɲ�ͬ��ʵ��,����ʵ�����������Ǵ����,�ȿ�����
     if (typeid(typename iterator_traits<OutputIterator>::iterator_category) == typeid(random_access_iterator_tag)){
        auto first2 = result;
        auto last2 = copy(first, last, result);
        sort(first2, last2);
     }else{
        vector<typename iterator_traits<InputIterator>::value_type> s(first, last);
        sort(s.begin(), s.end());
        copy(s.begin(), s.end(), result);
     }
     * 1.
     * ���ô�������Ϣ: In instantiation of function template specialization
     *              'mySort<double *, std::ostream_iterator<double>>'
     * sort(first2, last2)���Ĵ�����Ϣ: In template: invalid operands to binary expression
     *      ('const std::ostream_iterator<double>' and 'const std::ostream_iterator<double>')
     *      error occurred here in instantiation of function template specialization
     *      'std::sort<std::ostream_iterator<double>, std::less<>>' requested here in instantiation
     *      of function template specialization 'std::sort<std::ostream_iterator<double>>' requested
     *      here in instantiation of function template specialization 'mySort<double *,
     *      std::ostream_iterator<double>>' requested here candidate template ignored: could not match
     *      'reverse_iterator' against 'ostream_iterator' candidate template ignored: could not match
     *      'move_iterator' against 'ostream_iterator'
     * 2.ԭ�����: �����if-else�����е�sort��ȫ�����뻻Ϊ������,�ͻᷢ��mySort����������Ϊ��������ʵ�����ʱ,�����ȷ������
     *            else������,��˵����������ʵ����ģ��ʱ��ȫ���ӷ�֧�������п��ܱ��������õľ���"�߼���"�滻,��ŵ�����ֱ�ӽ�
     *            const std::ostream_iterator<double>��Ϊsort�Ĳ�������,�Ӷ������������Ͳ�ƥ�������
     */
}

//���������������p��n����ֵ���򣬽����ͨ�����������result���
template<class InputIterator, class OutputIterator>
inline void mySort(InputIterator first, InputIterator last, OutputIterator result) {
    mySort_helper(first, last, result, typename iterator_traits<OutputIterator>::iterator_category());
}

int main() {
    //��s�����������������
    double a[5] = {1.2, 2.4, 0.8, 3.3, 3.2};
    mySort(a, a + 5, ostream_iterator<double>(cout, " "));
    cout << endl;

    //�ӱ�׼����������ɸ��������������Ľ�����
    mySort(istream_iterator<int>(cin), istream_iterator<int>(), ostream_iterator<int>(cout, " "));
    cout << endl;

    vector<double> v(5, 0);         //�����ȶ�vector��ʼ��,�������޷�������Ч�ĵ�����,�Ӷ��ó����copy�������쳣��ֹ
    auto first = v.begin();
    mySort(a, a + 5, first);
    for (const auto i: v)
        cout << i << " ";

    return 0;
}
