#include "tensor.hxx"
#include <cassert>
#include <iostream>
#include <fstream>


typedef int TEST_TYPE;


int main(){
    loggingEnable();
    std::fstream file("../src/test_output.txt", std::ios::out);
    bool flag = true;
    if (!file.is_open()){
        std::cout << "Could not open the file";
        flag = false;
     }

    auto *shape = new ARRAY_SIZE[3];
    ARRAY_SIZE N = 3;
    ARRAY_SIZE M = 10;
    ARRAY_SIZE K = 10;
    shape[0] = N;
    shape[1] = M;
    shape[2] = K;

    Tensor<TEST_TYPE > test1(3, shape);

    assert(test1[0][0][0] == Tensor<TEST_TYPE >(0));

    int x = 0;
    for (ARRAY_SIZE i = 0; i < N; ++i){
        for (ARRAY_SIZE j = 0; j < M; ++j){
            for (ARRAY_SIZE k = 0; k < K; ++k){
                test1[i][j][k] = Tensor<TEST_TYPE>(x);
                x++;
            }
        }
    }
    assert(test1[0][0][0] == Tensor<TEST_TYPE>(0));

    std::cout << "test1:" << std::endl;
    test1.print();
    if (flag){
        file << "test1:" << std::endl;
        test1.write(file);
    }

    auto *new_shape = new ARRAY_SIZE[2];
    new_shape[0] = K;
    new_shape[1] = N*M;

    auto test2 = test1.copy();

    assert(test1 == test2);

    test2.reshape(2, new_shape);
    assert(test2[0][0] == Tensor<TEST_TYPE >(0));

    std::cout << "test1 after reshape:" << std::endl;
    test2.print();
    if (flag){
        file << "test1 after reshape:" << std::endl;
        test2.write(file);
    }

    auto test3 = (((test1.copy() + 3) - 1) * 2) / 4 + 1;

    std::cout << "test3 = (test1 + 3 - 1) * 2 / 4  + 1" << std::endl;
    test3.print();
    if (flag){
        file << "test3 = (test1 + 3 - 1) * 2 / 4  + 1" << std::endl;
        test3.write(file);
    }

    std::cout << "(test1 + test3 - test1 * test3) / test3" << std::endl;
    ((test1 + test3 - test1*test3)/test3).print();
    if (flag){
        file << "(test1 + test3 - test1 * test3) / test3" << std::endl;
        ((test1 + test3 - test1*test3)/test3).write(file);
    }

    std::cout << "chain for test1" << std::endl;
    if (flag) file << "chain for test1" << std::endl;
    auto test_chain = test1.chain();
    for (ARRAY_SIZE itr = 0; itr < N * M * K; ++itr){
        std::cout << test_chain[itr] << ' ';
        if (flag) file << test_chain[itr] << ' ';
    }
}

