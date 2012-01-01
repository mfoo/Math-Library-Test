#include <iostream>

#include <sys/time.h>

#include "Main.h"
#include "mother.h"

const int NUM_TESTS = 10000000;

int main(int argc, char** argv) {
    int count = 10;

    if(argc > 1) {
        count = atoi(argv[1]);
    }

    {

    std::cout << "Testing Eigen library Matrix4f class." << std::endl;

    Eigen::Matrix4f* inputA = generateEigenMat4s(count);
    Eigen::Matrix4f* inputB = generateEigenMat4s(count);
    Eigen::Matrix4f* output = generateEigenMat4s(count);

    std::cout << "Performing additions." << std::endl;

    // Time how long it takes to add [count] matrices NUM_TESTS times.
    struct timeval start, end;
    gettimeofday(&start, NULL);
    for(int i = 0; i < NUM_TESTS; i++) {
        test_eigen_mat4_addition(inputA, inputB, output, count);
    }
    gettimeofday(&end, NULL);
    difference(start, end);

    std::cout << "Performing multiplications." << std::endl;

    // Time how long it takes to multiply [count] matrices NUM_TESTS times.
    gettimeofday(&start, NULL);
    for(int i = 0; i < NUM_TESTS; i++) {
        test_eigen_mat4_multiplication(inputA, inputB, output, count);
    }
    gettimeofday(&end, NULL);
    difference(start, end);

    delete[] inputA;
    delete[] inputB;
    delete[] output;

    }

    {

    std::cout << "Testing GLM library Matrix4f class." << std::endl;

    glm::mat4* inputA = generateGLMMat4s(count);
    glm::mat4* inputB = generateGLMMat4s(count);
    glm::mat4* output = generateGLMMat4s(count);

    std::cout << "Performing additions." << std::endl;

    // Time how long it takes to add [count] matrices NUM_TESTS times.
    struct timeval start, end;
    gettimeofday(&start, NULL);
    for(int i = 0; i < NUM_TESTS; i++) {
        test_glm_mat4_addition(inputA, inputB, output, count);
    }
    gettimeofday(&end, NULL);
    difference(start, end);

    std::cout << "Performing multiplications." << std::endl;

    // Time how long it takes to multiply [count] matrices NUM_TESTS times.
    gettimeofday(&start, NULL);
    for(int i = 0; i < NUM_TESTS; i++) {
        test_glm_mat4_multiplication(inputA, inputB, output, count);
    }
    gettimeofday(&end, NULL);
    difference(start, end);

    delete[] inputA;
    delete[] inputB;
    delete[] output;

    }

    {

    std::cout << "Testing CML library Matrix4f class." << std::endl;

    cml::matrix44f_c* inputA = generateCMLMat4s(count);
    cml::matrix44f_c* inputB = generateCMLMat4s(count);
    cml::matrix44f_c* output = generateCMLMat4s(count);

    std::cout << "Performing additions." << std::endl;

    // Time how long it takes to add [count] matrices NUM_TESTS times.
    struct timeval start, end;
    gettimeofday(&start, NULL);
    for(int i = 0; i < NUM_TESTS; i++) {
        test_cml_mat4_addition(inputA, inputB, output, count);
    }
    gettimeofday(&end, NULL);
    difference(start, end);

    std::cout << "Performing multiplications." << std::endl;

    // Time how long it takes to multiply [count] matrices NUM_TESTS times.
    gettimeofday(&start, NULL);
    for(int i = 0; i < NUM_TESTS; i++) {
        test_cml_mat4_multiplication(inputA, inputB, output, count);
    }
    gettimeofday(&end, NULL);
    difference(start, end);

    delete[] inputA;
    delete[] inputB;
    delete[] output;

    }

    return 0;
}

float* generateRandomNumbers(int count) {
    unsigned long seed = time(NULL);
    float* numbers = new float[count];
    for(int i = 0; i < count; i++) {
        numbers[i] = static_cast<float>(Mother(&seed));
    }

    return numbers;
}

void difference(timeval& start, timeval& end) {
    long mtime, seconds, useconds;
    seconds = end.tv_sec - start.tv_sec;
    useconds = end.tv_usec - start.tv_usec;
    mtime = ((seconds) * 1000 + useconds / 1000.0) + 0.5;
    std::cout << "Took " << mtime << " milliseconds." << std::endl;
}

Eigen::Matrix4f* generateEigenMat4s(int count) {
    float* randomNumbers = generateRandomNumbers(count);

    Eigen::Matrix4f* eigenmats = new Eigen::Matrix4f[count];
    for(int i = 0; i < count; i++) {
        eigenmats[i](0,0) = randomNumbers[i];
        eigenmats[i](1,1) = randomNumbers[i];
        eigenmats[i](2,2) = randomNumbers[i];
        eigenmats[i](3,3) = 1.0f;
    }

    delete[] randomNumbers;

    return eigenmats;
}

void test_eigen_mat4_addition(Eigen::Matrix4f* inputA,
                              Eigen::Matrix4f* inputB,
                              Eigen::Matrix4f* output,
                              int count) {
    for(int i = 0; i < count; i++) {
        output[i] = inputA[i] + inputB[i];
    }
}

void test_eigen_mat4_multiplication(Eigen::Matrix4f* inputA,
                                    Eigen::Matrix4f* inputB,
                                    Eigen::Matrix4f* output,
                                    int count) {
    for(int i = 0; i < count; i++) {
        output[i] = inputA[i] * inputB[i];
    }
}

glm::mat4* generateGLMMat4s(int count) {
    float* randomNumbers = generateRandomNumbers(count);

    glm::mat4* mats = new glm::mat4[count];
    for(int i = 0; i < count; i++) {
        mats[i][0][0] = randomNumbers[i];
        mats[i][1][1] = randomNumbers[i];
        mats[i][2][2] = randomNumbers[i];
        mats[i][3][3] = 1.0f;
    }

    delete[] randomNumbers;

    return mats;
}

void test_glm_mat4_addition(glm::mat4* inputA, glm::mat4* inputB,
                            glm::mat4* output, int count) {
    for(int i = 0; i < count; i++) {
        output[i] = inputA[i] + inputB[i];
    }
}

void test_glm_mat4_multiplication(glm::mat4* inputA, glm::mat4* inputB,
                                  glm::mat4* output, int count){ 
    for(int i = 0; i < count; i++) {
        output[i] = inputA[i] * inputB[i];
    }
}

cml::matrix44f_c* generateCMLMat4s(int count) {
    float* randomNumbers = generateRandomNumbers(count);

    cml::matrix44f_c* mats = new cml::matrix44f_c[count];
    for(int i = 0; i < count; i++) {
        mats[i].set_basis_element(0, 0, randomNumbers[i]);
        mats[i].set_basis_element(1, 1, randomNumbers[i]);
        mats[i].set_basis_element(2, 2, randomNumbers[i]);
        mats[i].set_basis_element(3, 3, 1.0f);
    }

    delete[] randomNumbers;

    return mats;
}

void test_cml_mat4_addition(cml::matrix44f_c* inputA, cml::matrix44f_c* inputB,
                            cml::matrix44f_c* output, int count) {
    for(int i = 0; i < count; i++) {
        output[i] = inputA[i] + inputB[i];
    }
}

void test_cml_mat4_multiplication(cml::matrix44f_c* inputA,
                                  cml::matrix44f_c* inputB,
                                  cml::matrix44f_c* output, int count) {
    for(int i = 0; i < count; i++) {
        output[i] = inputA[i] * inputB[i];
    }
}

