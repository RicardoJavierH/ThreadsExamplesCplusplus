//https://stackoverflow.com/questions/44755512/how-to-do-a-matrix-multiplication-using-threads-and-a-1-d-array-in-c
#include <iostream>
#include <memory>
#include <vector>
#include <thread>
#include <chrono>
using namespace std;
// multiplies the specified row and column from specified matrices
void multiply(const int* m_1, const int* m_2,
        std::size_t size, std::size_t row, std::size_t col, int* m_res) {
    for(std::size_t i = 0; i < size; ++i)
        m_res[row * size + col] += m_1[row * size + i] * m_2[i * size + col];
}

int main() {
    chrono::steady_clock sc;
    auto start=sc.now();

    constexpr int N = 3, THREAD_NUM = 2;
    /*int** pointer;
    pointer=new int*[N];
    for(int i=0;i<N;i++)
    pointer[i]=new int[N];*/
    // matrices to multiply and a matrix for result
    std::unique_ptr<int[]> A(new int[N * N] {
        11, 12, 13, 21, 22, 23, 31, 32, 33
    });
    std::unique_ptr<int[]> B(new int[N * N] {
        1, 0, 0, 0, 1, 0, 0, 0, 1
    });
    std::unique_ptr<int[]> C(new int[N * N] {});

    // create vector for running threads then assign threads to its elements
    std::vector<std::thread> thread_group(THREAD_NUM);

    for(int thread_i = 0; thread_i < THREAD_NUM; ++thread_i)
        thread_group[thread_i] = std::thread([&, thread_i]() {
            // each thread stars from consecutive rows then steps by
            // the number of threads
            for(int row = thread_i; row < N; row += THREAD_NUM) {
                for(int col = 0; col < N; ++col)
                    multiply(A.get(), B.get(), N, row, col, C.get());
            }
        });

    for(auto& t : thread_group)
        t.join();

    // show the result
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j)
            std::cout << (j ? "\t" : "") << C[i * N + j];
        std::cout << std::endl;
    }
    auto end=sc.now();
    auto time_span = static_cast<chrono::duration<double>>(end - start); // measure
    cout << "tiempo: " << time_span.count() <<endl;
}

