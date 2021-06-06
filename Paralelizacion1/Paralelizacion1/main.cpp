#include <string>
#include <iostream>
#include <thread>
#include <chrono>
static double n=0.;
static double m=0.;
using namespace std;

// The function we want to execute on the new thread.
void task1()
{
    for(int i=0; i<1000000; i++)
        if(i%2==0)
            n+=1.0/(2*i+1);
    cout << "task1 says: " << "sumar pares";
}

void task2()
{
    for(int i=0; i<1000000; i++)
        if(i%2!=0)
            m+=1.0/(2*i+1);
    cout << "task2 says: " << "sumar impares";
    
}
int main()
{
    chrono::steady_clock sc;
    // Constructs the new thread and runs it. Does not block execution.
    auto start=sc.now();
    thread t1(task1);
    thread t2(task2);


    // Do other things...

    // Makes the main thread wait for the new thread to finish execution, therefore blocks its own execution.
    t1.join();
    t2.join();
    //task1();
    //task2();
    auto end=sc.now();
    auto time_span = static_cast<chrono::duration<double>>(end - start); // measure
    cout << "tiempo: " << time_span.count() <<endl;
    cout << "valor de n: " << n <<endl;
    cout << "valor de m: " << m <<endl;
    cout << "pi= : " << 4.*(n-m) <<endl;


}

