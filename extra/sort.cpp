#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <omp.h>
#include <memory>
#include <random>

void get_matrix_size_from_cin(int& number);
int parse_int_from_string(const std::string& input);
void init_matrix(std::vector<int>& v, const int& size);

// https://ru.wikipedia.org/Сортировка_слиянием

template <typename Iterator>
void merge_sort(Iterator from, Iterator to);

int main()
{
    int size;

    std::cout << "number of threads is in range [1, " << omp_get_max_threads() << "]" << std::endl << 
        "let\'s use max number of threads" << std::endl << std::endl;

    omp_set_num_threads(omp_get_max_threads());

    get_matrix_size_from_cin(size);

    std::vector<int> v;

    // v = {6, 4, 7, 6, 4, 4, 0, 1, 5};

    init_matrix(v, size);

    merge_sort(begin(v), end(v));

    for (int x : v)
    {
        std::cout << x << " ";
    }

    std::cout << std::endl;

    return 0;
}

void get_matrix_size_from_cin(int& number)
{
    bool done = false;
    std::string string_input;

    while (!done)
    {
        std::cout << "enter size of matrix" << std::endl;

        std::getline(std::cin, string_input);

        try
        {
            number = parse_int_from_string(string_input);

            if (1 <= number)
            {
                done = true;
            }
            else
            {
                std::cerr << "size of matrix should be natural number" << std::endl;
            }
            
        }
        catch(const std::exception& e)
        {
            std::cerr << "enter number in proper format" << std::endl << 
                e.what() << std::endl;
        }
    }
}

int parse_int_from_string(const std::string& string_input)
{
    std::istringstream string_stream(string_input);
    bool flag = true;

    int data(0);

    while (string_stream.peek() == ' ')
    {
        string_stream.ignore(1);
    }

    flag = flag && (string_stream >> data);

    while (string_stream.peek() == ' ')
    {
        string_stream.ignore(1);
    }

    flag = flag && (string_stream.eof());

    if (!flag)
    {
        throw std::runtime_error("wrong input format: \"" + string_input + "\"");
    }

    return data;
}

void init_matrix(std::vector<int>& v, const int& size)
{
    v.clear();

    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(-100, 100);

    for (int i = 0; i < size; i++)
    {
        v.emplace_back(distribution(generator));
    }    
}

template <typename Iterator>
void merge_sort(Iterator from, Iterator to)
{
#pragma omp parallel
    {
#pragma omp single nowait
        static_assert(!std::is_same<typename std::iterator_traits<Iterator>::value_type, void>::value);

        auto n = std::distance(from, to);

        if (1 < n)
        {
#pragma omp task firstprivate (from, to, n)
            {
                Iterator l_from = from;
                Iterator l_to = l_from;
                std::advance(l_to, n/2);
                merge_sort(l_from, l_to);
            }
#pragma omp task firstprivate (from, to, n)
            {
                Iterator r_from = from;
                std::advance(r_from, n/2);
                Iterator r_to = r_from;
                std::advance(r_to, n-(n/2));
                merge_sort(r_from, r_to);
            }
#pragma omp taskwait

            auto tmp_array = std::make_unique<typename Iterator::value_type[]>(n);
            Iterator l_iter = from;
            Iterator l_end = l_iter;
            std::advance(l_end, n/2);
            Iterator r_iter = l_end;
            Iterator& r_end = to;

            auto tmp_iter = tmp_array.get();

            while (l_iter != l_end || r_iter != r_end)
            {
                if (*l_iter < *r_iter)
                {
                    *tmp_iter = std::move(*l_iter);
                    ++l_iter;
                    ++tmp_iter;
                }
                else
                {
                    *tmp_iter = std::move(*r_iter);
                    ++r_iter;
                    ++tmp_iter;
                }

                if (l_iter == l_end)
                {
                    std::copy(
                                std::make_move_iterator(r_iter),
                                std::make_move_iterator(r_end),
                                tmp_iter
                    );

                    break;
                }

                if (r_iter == r_end)
                {
                    std::copy(
                                std::make_move_iterator(l_iter),
                                std::make_move_iterator(l_end),
                                tmp_iter
                    );

                    break;
                }
            }

            std::copy(
                        std::make_move_iterator(tmp_array.get()),
                        std::make_move_iterator(&tmp_array[n]),
                        from
            );
        }
    }
}
