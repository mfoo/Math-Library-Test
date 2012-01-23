//#include <iostream>

#include <sys/time.h>

#include "Driver.h"
#include "mother.h"


const int NUM_TESTS = 1000000;
//const int NUM_TESTS = 10000000;

#include <android/log.h>
#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "native-activity", __VA_ARGS__))
void testLibraries(int count) {
    {

    std::cout << "Testing Eigen library Matrix4f class." << std::endl;

    LOGI("Testing Eigen library Matrix4f class.");

    Eigen::Matrix4f* inputA = generateEigenMat4s(count);
    Eigen::Matrix4f* inputB = generateEigenMat4s(count);
    Eigen::Matrix4f* output = generateEigenMat4s(count);

    std::cout << "Performing additions." << std::endl;
    LOGI("Performing additions.");
    // Time how long it takes to add [count] matrices NUM_TESTS times.
    struct timeval start, end;
    gettimeofday(&start, NULL);
    for(int i = 0; i < NUM_TESTS; i++) {
        test_eigen_mat4_addition(inputA, inputB, output, count);
    }
    gettimeofday(&end, NULL);
    difference(start, end);

    LOGI("Performing multiplications.");
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
#ifndef ANDROID
    {

    std::cout << "Testing GLM library Matrix4f class." << std::endl;
    LOGI("Testing GLM library Matrix4f class.");

    glm::mat4* inputA = generateGLMMat4s(count);
    glm::mat4* inputB = generateGLMMat4s(count);
    glm::mat4* output = generateGLMMat4s(count);

    std::cout << "Performing additions." << std::endl;
    LOGI("Performing additions.");

    // Time how long it takes to add [count] matrices NUM_TESTS times.
    struct timeval start, end;
    gettimeofday(&start, NULL);
    for(int i = 0; i < NUM_TESTS; i++) {
        test_glm_mat4_addition(inputA, inputB, output, count);
    }
    gettimeofday(&end, NULL);
    difference(start, end);

    std::cout << "Performing multiplications." << std::endl;
    LOGI("Performing multiplications.");

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
#endif
    {

    std::cout << "Testing CML library Matrix4f class." << std::endl;
    LOGI("Testing CML library Matrix4f class.");

    cml::matrix44f_c* inputA = generateCMLMat4s(count);
    cml::matrix44f_c* inputB = generateCMLMat4s(count);
    cml::matrix44f_c* output = generateCMLMat4s(count);

    std::cout << "Performing additions." << std::endl;
    LOGI("Performing additions.");

    // Time how long it takes to add [count] matrices NUM_TESTS times.
    struct timeval start, end;
    gettimeofday(&start, NULL);
    for(int i = 0; i < NUM_TESTS; i++) {
        test_cml_mat4_addition(inputA, inputB, output, count);
    }
    gettimeofday(&end, NULL);
    difference(start, end);

    std::cout << "Performing multiplications." << std::endl;
    LOGI("Performing multiplications.");

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
    std::stringstream ss;
    ss << "Took " << mtime << " milliseconds.";
    std::cout << ss.str() << std::endl;
    LOGI(ss.str().c_str());
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

#ifndef ANDROID
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
#endif
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

