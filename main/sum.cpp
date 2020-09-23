#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <stdexcept>
#include <stdio.h>
#include <omp.h>

using namespace std;

int parse_int_from_string(const string& input);

int main()
{
    int i;
    int max_threads;
    int N;
    double sum;
    string string_input;
    bool done;

    max_threads = omp_get_max_threads();

    cout << "number of threads is in range [1, max]" << endl 
        << "let\'s use max number of threads -- " << max_threads << endl << endl;

    omp_set_num_threads(max_threads);

    // cin >> N;

    done = false;

    while (!done)
    {
        cout << "enter N -- number of elements in sequence" << endl << 
            "(harmonic series)" << endl;

        getline(cin, string_input);

        try
        {
            N = parse_int_from_string(string_input);

            done = true;
        }
        catch(const exception& e)
        {
            cerr << "enter number in proper format" << endl << 
                e.what() << endl;
        }
    }

    sum = 0;

    #pragma omp parallel for    \
    private(i)                  \
    schedule(guided)            \
    reduction(+:sum)
    for (i = 1; i <= N; i++)
    {
        sum += 1.0 / i;
    }

    cout << endl;
    
    cout << "sum of " << N << " elements of harmonic series" << endl << 
        "sum = " << fixed << setprecision(15) << sum << endl;

    cout.unsetf(ios::fixed | ios::scientific);

    return 0;
}

int parse_int_from_string(const string& string_input)
{
    istringstream string_stream(string_input);
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
        throw runtime_error("wrong input format: \"" + string_input + "\"");
    }

    return data;
}
