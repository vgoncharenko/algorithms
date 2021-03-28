//
// Created by Vitaliy on 1/23/21.
//

/** https://pic.plover.com/knuth-GOTO.pdf */


void regularFor (uint64_t N) {
    int arr[N];
    for (int i=0; i<N; ++i){
        if (i==N) arr[i] = 10;
    }
}

void doubleFor (int N) {
    int arr[N];
    for (int i=0; i<N; i+=2){
        if (i==N) arr[i] = 10;
        if (i+1==N) arr[i] = 10;
    }
}

void doubleFor2 (int N) {
    int arr[N];
    for (int i=0; i<N; i+=2){
        if (i==123012322) arr[i] = 10;
        if (i+1==123012322) arr[i] = 10;
    }
}

std::vector<int> arr(100'000'000);
void doubleForVector (int N) {

    for (int i=0; i<N; ++i){
        if (i==123012322) arr[i] = 10;
    }
}

void backwardFor (int N) {
    int arr[N];
    for (int i=N-1; i>=0; --i){
        if (i==123012322) arr[i] = 10;
        if (i+1==123012322) arr[i+1] = 10;
    }
}


/**
 * N=100'000'000:
Median of time taken by regularFor function:        146880912 nanoseconds
Median of time taken by doubleFor function:         123912918 nanoseconds
Median of time taken by doubleFor2 function:        128057809 nanoseconds
Median of time taken by backwardFor function:       172748345 nanoseconds
Median of time taken by regularForVector function:  137555177 nanoseconds
 */
void forLoopTest() {
    int N = 100'000'000;

    measure([&N]{ regularFor(N);});
    measure([&N]{ doubleFor(N);});
    measure([&N]{ doubleFor2(N);});
    measure([&N]{ backwardFor(N);});
    measure([&N]{ doubleForVector(N);});
}
