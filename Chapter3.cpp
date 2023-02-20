/**
 * @author ���п͡�������
 * @date 2022/12/28
 */
#include <iostream>

using namespace std;

short int f3_7(unsigned short a, unsigned short b);

double transferFtoC(double F);

bool isPrime(unsigned int n);

int GCD(int a, int b);

int LCM(int a, int b);

int sum(int n);

int Fibonacci(int n);

int Legendre(int x, int n);

int getPower(int x, int y);

double getPower(double x, int y);

int main() {
    /*3-1:
     * C++�еĺ����ǹ��ܳ���Ļ�����λ�����������ǵ������������ĺ��������������Ǳ������������õĺ���������֮��Ĺ�ϵ�ǵ����뱻���õĹ�ϵ��
     * ���ú����ķ�����������(ʵ���б�)
     */

    /*3-2:
     * rSomeRef�Ƕ�intOne������(����)������ͬ���仯�����ԣ���intOne = 5ʱ��rSomeRef = 5��
     * ��rSomeRef = intTwoʱ��intOne = intTwo
     */

    /*3-3:
     * ��ͬ��:������ʵ�γ�ʼ���β�
     * ��ͬ��:�������ô����У��βεĳ�ʼ��������ִ�����������ĵ��ñ��ʽʱ������ֵ�����У��βεĳ�ʼ��������˵��ʱ����
     *       �������ô����У��βκ�ʵ��ͬ���仯������ֵ�����У��βεı仯��������ʵ�εı仯
     * */

    //3-4: �����������ڱ���ʱ��������Ƕ�뵽ÿһ�����ô��ĺ��������ص��ǹ��ܼ򵥡���ģ��С��ʹ��Ƶ��

    //3-5: ����ԭ�͡���������ͺ��������еĲ������Ǿֲ�������������ֱ�Ϊ���Եĺ����壬�������ǵĲ���������һ��

    //3-6: ���ñ����صĺ���ʱ����������ͨ���βεĸ�����������ƥ�亯����

    //3-7:
    cout << f3_7(256, 2) << endl;

    //3-8:
    int F;
    cout << "Enter a Fahrenheit please:";
    cin >> F;
    cout << F << "�H" << " is equal to " << transferFtoC(F) << "��" << endl;

    //3-9:
    unsigned int n;
    cout << "Enter a number please:";
    cin >> n;
    if (isPrime(n))
        cout << n << " is a prime" << endl;
    else
        cout << n << " is not a prime" << endl;

    //3-10
    int a, b;
    cout << "Enter two integers please:";
    cin >> a >> b;
    cout << "The GCD of " << a << " and " << b << " is " << GCD(a, b) << ", and the LCM is " << LCM(a, b) << endl;

    //3-11:Ƕ�׵�����ָ����1�����˺���2������2�ֵ����˺���3��������������֮���γ���Ƕ�׵��á��ݹ���ָ����ֱ�ӻ��ӵ�������

    //3-12:
    int num;
    cout << "Enter a positive integers please:";
    cin >> num;
    cout << "1 + ... + " << num << " = " << sum(num) << endl;

    //3-13
    int fi;
    cout << "Enter a positive integers please:";
    cin >> fi;
    cout << "Fibonacci(" << fi << ") = " << Fibonacci(fi) << endl;

    //3-14:
    int x, order;
    cout << "Enter the arguments x and n for Legendre's polynomial in order:";
    cin >> x >> order;
    cout << "p(x" << x << ") of order " << order << " is " << Legendre(x, order) << endl;

    //3-15:
    int ai, m;
    double bi;
    cout << "Please enter an integer a and a real number b as the base, and an int m as the exponent:";
    cin >> ai >> bi >> m;
    cout << ai << "^" << m << " = " << getPower(ai, m) << "\t";
    cout << bi << "^" << m << " = " << getPower(bi, m) << endl;

    //3-16:���ú�������ջ������Ϣ
    return 0;
}

short int f3_7(unsigned short a, unsigned short b) {
    if (b == 0) return -1;
    else return a / b;
}

double transferFtoC(double F) {
    return 5.0 / 9 * (F - 32);
}

bool isPrime(unsigned int n) {
    //0��1�Ȳ�������Ҳ���Ǻ���
    if (n == 0 || n == 1) return false;

    for (int i = 2; i <= n / 2; i++) {
        if (n % i == 0) return false;
    }

    return true;
}

int GCD(int a, int b) {  //�����Լ���ķ����ܶ࣬��Ҫ���������ֽⷨ���̳�����շת������͸�����𷨵�
    //շת�����
    if (b % a == 0) return a;
    while (a % b) {
        int r = a % b;
        a = b;
        b = r;
    }
    return b;
}

int LCM(int a, int b) {  //����󹫱���
    //a��b���Լ������С������֮������a*b
    return a * b / GCD(a, b);
}

int sum(int n) { //д����Ψһ
    //����ٶ��û��ᰴ����ʾ�������������ʲ��ж�n��ȡֵ��Χ����Ҫ�жϣ������з����ԼӸ��켴��
    /*����һ:����������Ķ�·����
    int result = n;
    result && (result += sum(n - 1));
    return result;
    */

    //������:������Ŀ�����
    return n == 1 ? 1 : (n + sum(n - 1));

    /*������: ����˼·
    if(n == 1)
        return 1;
    else
        return n + sum(n - 1);
    */
}

int Fibonacci(int n) {
    if (n < 1) {
        cerr << "\nError: Non-positive integer" << endl;
        return -1;
    } else if (n == 1 || n == 2)
        return 1;
    else
        return Fibonacci(n - 1) + Fibonacci(n - 2);
}

int Legendre(int x, int n) {
    if (n == 0)
        return 1;
    else if (n == 1)
        return x;
    else
        return ((2 * n - 1) * x * Legendre(x, n - 1) - (n - 1) * Legendre(x, n - 2)) / n;
}

int getPower(int x, int y) {
    if (y < 0)
        return 0;
    else if (y == 0)
        return 1;
    else
        return x * getPower(x, y - 1);
}

double getPower(double x, int y) {
    double result = x;
    int t = abs(y);
    if (t == 0)
        return 1;
    else
        result *= getPower(x, t - 1);
    return y > 0 ? result : 1.0 / result;
}