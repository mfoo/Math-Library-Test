#include <cml/cml.h>
#include <Eigen/Dense>
#include <glm/glm.hpp>

/**
 * Print the time difference between two timevals in milliseconds.
 */
void difference(timeval& start, timeval& end);

/**
 * Create a float array with a size specified by count. Each value is
 * initialised as a random number generated using George Masaliga's 'Mother
 * of All Random Number Generator'.
 */
float* generateRandomNumbers(int count);

///////////////////////////////////////////////////////////////////////////////
// Eigen Library
///////////////////////////////////////////////////////////////////////////////

Eigen::Matrix4f* generateEigenMat4s(int count);

/**
 * For each index, i, up to count, perform output[i] = inputA[i] + inputB[i].
 */
void test_eigen_mat4_addition(Eigen::Matrix4f* inputA,
                              Eigen::Matrix4f* inputB,
                              Eigen::Matrix4f* output,
                              int count);

/**
 * For each index, i, up to count, perform output[i] = inputA[i] * inputB[i].
 */
void test_eigen_mat4_multiplication(Eigen::Matrix4f* inputA,
                                    Eigen::Matrix4f* inputB,
                                    Eigen::Matrix4f* output,
                                    int count);

///////////////////////////////////////////////////////////////////////////////
// GLM library.
///////////////////////////////////////////////////////////////////////////////
glm::mat4* generateGLMMat4s(int count);

void test_glm_mat4_addition(glm::mat4* inputA, glm::mat4* inputB,
                            glm::mat4* output, int count);

void test_glm_mat4_multiplication(glm::mat4* inputA, glm::mat4* inputB,
                                  glm::mat4* output, int count);

///////////////////////////////////////////////////////////////////////////////
// CML library.
///////////////////////////////////////////////////////////////////////////////
cml::matrix44f_c* generateCMLMat4s(int count);

void test_cml_mat4_addition(cml::matrix44f_c* inputA, cml::matrix44f_c* inputB,
                            cml::matrix44f_c* output, int count);

void test_cml_mat4_multiplication(cml::matrix44f_c* inputA,
                                  cml::matrix44f_c* inputB,
                                  cml::matrix44f_c* output, int count);

