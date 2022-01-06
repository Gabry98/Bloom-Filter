#include "BloomFilter_parallel.cpp"
#include <chrono>
#include <fstream>

template <typename T>
void print(bool* results, std::deque<T> q);

int main()
{
    std::deque<int> q;
    ifstream myfile("2701.txt");

    if(myfile.is_open()){

        while(myfile.peek() != EOF)
        {
           q.push_back(myfile.get());
        }
        myfile.close();
    }
    else cout << "Unable to open file" << endl;

    auto start_bw = std::chrono::steady_clock::now();

    BloomFilter_parallel<int> bf(q);
    bool* results = bf.probably_contains(q);

    auto end_bw = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds_bw = end_bw-start_bw;
    std::cout << "elapsed time: " << elapsed_seconds_bw.count() << "s\n\n";
    cout << "You're going to print all the results." << endl;
    system("pause");

    print(results,q);

    return 0;
}

template <typename T>
void print(bool* results, std::deque<T> q)
{
    for(size_t i=0; i<q.size(); i++)
    {
        cout << q[i] << "-->" << results[i] << endl;
    }
}

