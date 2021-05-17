

#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <iterator>
#include <set>
#include <random>
#include <deque>
#include <numeric>

#define PI 3.14


// 1. Имеется отсортированный массив целых чисел. 
// Необходимо разработать функцию insert_sorted, которая принимает вектор и новое число и вставляет новое число в определенную позицию в векторе,
// чтобы упорядоченность контейнера сохранялась.
// Реализуйте шаблонную функцию insert_sorted, которая сможет аналогично работать с любым контейнером, содержащим любой тип значения.
//
// Вариант 1.
//void insert_sorted_Int(std::vector<int> &vec, int numberInsert)
//{
//    int size = vec.size();
//    for (int i = 1; i < size; ++i)
//    {
//        if (vec[i] > numberInsert) {
//            std::fill_n(std::inserter(vec, vec.begin()+i), 1, numberInsert);
//            break;
//        }
//    };
//}
//template <class T>
//T insert_sorted(std::vector<T> &a, T numberInsert)
//{
//    int size = a.size();
//    for (int i = 1; i < size; ++i)
//    {
//        if (a[i] > numberInsert) {
//            std::fill_n(std::inserter(a, a.begin() + i), 1, numberInsert);
//            break;
//        }
//    };
//    return 0;
//}

void insert_sortedInt(std::vector<int>& vec, const int& element)
{
    auto it = upper_bound(vec.begin(), vec.end(), element);
    vec.insert(it, element);
}
template <class T, class Box>
void insert_sorted(Box& box, const T& element)
{
    auto it = upper_bound(box.begin(), box.end(), element);
    box.insert(it, element);
}

int main()
{
    srand (time(NULL));
    std::cout << "Task 1." << '\n' << std::endl;
    // Вариант 1
    /*std::vector<int> task1_vector = { 1, 2, 4, 6, 9, 10 };
    std::cout << "Original vector:" << '\t' << '\t' << '\t' << '\t' << '\t';
    std::copy(task1_vector.begin(), task1_vector.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;  */

    std::vector<int32_t> original(10);
    generate(original.begin(), original.end(), []() {return rand() % 20; });
    sort(original.begin(), original.end());
    std::cout << "Vector original intager:" << '\t' << '\t' << '\t' << '\t';
    std::copy(original.begin(), original.end(), std::ostream_iterator<int32_t>(std::cout, " "));
    std::cout << std::endl;

    insert_sortedInt(original, 7);
    std::cout << "Vector with inserted 7 (insert_sorted_Int):" << '\t' << '\t';
    std::copy(original.begin(), original.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    insert_sorted(original, 5);
    std::cout << "Vector with inserted 5 (insert_sorted template):" << '\t';
    std::copy(original.begin(), original.end(), std::ostream_iterator<int32_t>(std::cout, " "));
    std::cout << std::endl;

    std::vector<char> words = { 'a', 'c', 'f', 'k', 'y'}; 
    std::cout << "Vector original chars:" << '\t' << '\t' << '\t' << '\t' << '\t';
    std::copy(words.begin(), words.end(), std::ostream_iterator<char>(std::cout, " "));
    std::cout << std::endl;

    insert_sorted(words, 'i');
    std::cout << "Vector with inserted 'i' (insert_sorted template):" << '\t';
    std::copy(words.begin(), words.end(), std::ostream_iterator<char>(std::cout, " "));
    std::cout << std::endl;

    std::deque<char> deq(10);
    generate(deq.begin(), deq.end(), []() {return rand() % 100; });
    sort(deq.begin(), deq.end());
    std::cout << "Deque original chars :" << '\t' << '\t' << '\t' << '\t' << '\t';
    std::copy(deq.begin(), deq.end(), std::ostream_iterator<char>(std::cout, " "));
    std::cout << std::endl;
    
    insert_sorted(deq, '=');
    std::cout << "Deque with inserted '=' (insert_sorted template):" <<'\t';
    std::copy(deq.begin(), deq.end(), std::ostream_iterator<char>(std::cout, " "));
    
    std::cout << '\n' << '\n' << std::endl;


    // Task 2.
    // Сгенерируйте вектор, состоящий из 100 вещественный чисел, представляющий собой значения аналогового сигнала, изменяющегося по синусоиде.
    // На основе этого массива чисел создайте другой вектор целых чисел, представляющий цифровой сигнал, в котором будут откинуты дробные части чисел.
    // Выведите получившиеся массивы чисел.Посчитайте ошибку, которой обладает цифровой сигнал по сравнению с аналоговым по формуле : .
    // Постарайтесь воспользоваться алгоритмическими функциями, не используя циклы.


    std::cout << "Task 2." << '\n' << std::endl;
  

    const size_t vectorSize = 100;
    std::vector<double> analog(vectorSize);
    std::vector<int> digital(vectorSize);
    auto sinusGenerate = [n = 0]() mutable{
        return 10.0 * sin (++n * 2.0 * PI / 180);
    };

    generate(begin(analog), end(analog), sinusGenerate);
    copy(begin(analog), end(analog), begin(digital));
    std::cout << "Analog signal " << std::endl;
    std::copy(begin(analog), end(analog), std::ostream_iterator<double>(std::cout, " "));
    std::cout << std::endl;
    std::cout << "Digital signal " << std::endl;
    std::copy(begin(digital), end(digital), std::ostream_iterator<double>(std::cout, " "));
    std::cout << std::endl;


    auto discrepancy = inner_product(begin(analog), end(analog), begin(digital),
        0.0, std::plus<double> {}, [](double x, double y) {
            return pow (x - y, 2);
        });
    std::cout << "Discrepancy of signals is " << discrepancy << std::endl;
}

