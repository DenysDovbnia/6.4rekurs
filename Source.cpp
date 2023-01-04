#include <iostream>
#include <windows.h>
#include <iomanip>

using namespace std;

void create(double* a, int N, int i, double Low, double Max, double eps);
void print(double* a, int i, int N);
double find_max_fabs(double* a, int N, double max, int i, int l);
int get_positive_index(double* a, int N, int i);
void sum(double* a, int N);
void sum(double* a, int current, int last, double s);
void changeAll(double* a, int N);
void change(double* a, int current_index, int next_zero_place_index);


int main()
{
    cout << fixed << setprecision(2);
    int N;
    double Max, Low, eps;
    srand((unsigned)time(NULL));
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    cout << "Введіть кількість елементів масиву: "; cin >> N;
    cout << "Введіть мінімальне значення масиву: "; cin >> Low;
    cout << "Введіть максимальне значення масиву: "; cin >> Max;
    cout << "Введіть епселон: "; cin >> eps;
    double* a = new double[N];
    cout << endl;
    cout << "Рекурсивний" << endl;
    create(a, N, 0, Low, Max, eps);
    print(a, 0, N);
    cout << endl;
    cout << "Найбільший за модулем: " << find_max_fabs(a, N, a[0], 0, 0) << endl;
    sum(a, N);
    changeAll(a, N);
    print(a, 0, N);
    cout << endl;
    delete[] a;
}
void create(double* a, int N, int i, double Low, double Max, double eps)
{
    if (i < N)
    {
        double value = (Max - Low) * rand() / RAND_MAX + Low;
        // Якщо число за модулем менше епселон, прирівняти згенероване число
        // до нуля для перевірки умови 2 пункту лабораторної, в іншому випадку, 
        // заповнити масив згенерованим числом
        a[i] = eps > fabs(value) ? 0.0 : value;
        create(a, N, ++i, Low, Max, eps);
    }
}
void print(double* a, int i, int N)
{
    if (i < N)
    {
        cout << setw(5) << a[i] << " ";
        print(a, ++i, N);
    }
}

double find_max_fabs(double* a, int N, double max, int current, int last)
{
    if (current < N)
    {
        if (fabs(max) <= fabs(a[current]))
        {
            max = a[current];
            last = current;
        }
        find_max_fabs(a, N, max, ++current, last);
    }
    else
        return a[last];
}
int get_positive_index(double* a, int N, int current) {
    if (current < N)
    {
        if (a[current] > 0) {
            return current;
        }
        else {
            return get_positive_index(a, N, ++current);
        }
    }
    else
        return -1;
}
void sum(double* a, int N) {
    int current = get_positive_index(a, N, 0);
    int last = get_positive_index(a, N, current + 1);
    cout << "Current: " << current << endl;
    cout << "Last: " << last << endl;
    if (last - current > 1) {
        sum(a, current + 1, last, 0);
    }
    else {
        cout << "Немає додатніх елементів або між першим та другм додатніми елементами немає інших елементів" << endl;
    }
}
void sum(double* a, int current, int last, double s)
{
    if (current < last)
    {
        s += a[current];
        sum(a, ++current, last, s);
    }
    else
        cout << "Сума: " << s << endl;

}

void change(double* a, int N) {
    if (N > 1)
        change(a, N - 2, N - 1);
    else
        cout << "В масиві повинно бути більше 2 елементів для перестановки" << endl;
}

// На початку алгоритму next_zero_place_index дорівнює індексу останнього елементу,
// current_index дорівнює індексу передостаннього елементу
void change(double* a, int current, int next_zero_place)
{
    if (current >= 0)
    {
        if (a[current] == 0)
        {
            double tmp = a[next_zero_place];
            a[next_zero_place] = a[current];
            a[current] = tmp;
            --next_zero_place;
        }
        change(a, --current, next_zero_place);
    }
}
