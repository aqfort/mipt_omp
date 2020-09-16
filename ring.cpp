#include <iostream>
#include <sstream>
#include <string>
#include <omp.h>

using namespace std;

int parse_int_from_string(const string& input);

int main()
{
    int i;
    int my_id;
    int max_threads;
    int threads;
    string data = "data:";
    string string_input;
    bool done;

    max_threads = omp_get_max_threads();

    done = false;

    while (!done)
    {
        cout << "enter number of threads" << endl << 
            "it can be in range [1; " << max_threads << "]" << endl;

        getline(cin, string_input);

        try
        {
            threads = parse_int_from_string(string_input);

            if (1 <= threads && threads <= max_threads)
            {
                done = true;
            }
            else
            {
                cerr << "mind proper range" << endl;
            }
            
        }
        catch(const std::exception& e)
        {
            cerr << "enter number in proper format" << endl << 
                e.what() << endl;
        }
    }

    omp_set_num_threads(threads);

    #pragma omp parallel for    \
    shared(data)                \
    private(i, my_id)           \
    ordered
    for (i = 0; i < threads; i++)
    {
        my_id = omp_get_thread_num();
        #pragma omp ordered
        data += " " + to_string(my_id);
    }

    cout << data << endl;

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
