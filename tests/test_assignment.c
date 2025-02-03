// this file is where you can run tests

// 1. INCLUDE ANY DEPENDENCIES HERE
// ie. header files where your functions are protoytyped and math.h or string.h 
// or anything else your functions need
// NOTE the relative path of your files from here are "../private/"
// ================ DEPENDENCIES ================
#include "../private/givenA1.h"
// ============= END OF DEPENDENCIES ============

#include "unity.h"


// THIS IS CODE TO RUN THE TESTS - ADD YOUR FUNCTIONS HERE
// note when including or reading files, their path here will be "private/"

// 2. WRITE TESTS HERE following same format
// see right below tests for copy-paste test formats to test structures, arrays, strings, etc.
// ============== WRITE TESTS HERE ==============
void test_distances(void) {

    float expectedEuclidean = 4.795832;
    int expectedHamming = 8;
    float expectedJaccard = 0.384615;

    int vector1[NUM_FEATURES] = {1,1,1,0,1,0,1,1,1,0,0,0,0,1,1,1};
    int vector2[NUM_FEATURES] = {1,0,0,1,0,0,1,1,1,1,0,0,4,0,0,1};
    float euclideanDistance;
    int hammingDistance;
    float jaccardSimilarity;
    distanceFunctions(vector1, vector2, &euclideanDistance, &hammingDistance, &jaccardSimilarity);
    
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expectedEuclidean, euclideanDistance); // Allow a small margin for float comparison
    TEST_ASSERT_EQUAL(expectedHamming, hammingDistance);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expectedJaccard, jaccardSimilarity);
    
}

void test_predictions(void){

    struct Animal dataZoo[NUM_SAMPLES];
    readFromFile("private/a1Data.txt", dataZoo);
    
    int newSample [NUM_FEATURES] = {1,1,1,0,1,0,1,1,1,0,0,0,0,1,1,1};
    int predicted_class;

    predicted_class = predictClass(dataZoo, newSample, 1, 5);
    TEST_ASSERT_EQUAL(predicted_class, 4);

    predicted_class = predictClass(dataZoo, newSample, 2, 5);
    TEST_ASSERT_EQUAL(predicted_class, 2);

    predicted_class = predictClass(dataZoo, newSample, 3, 5);
    TEST_ASSERT_EQUAL(predicted_class, 4);

}

int compare(const void* a, const void* b) {
   return (*(int*)a - *(int*)b);
}

void test_neighbours(void){
    int k = 5;
    int expected_euclidean[] = {18, 59, 79, 91, 2};
    int expected_hamming[] = {94, 11, 16, 18, 20};
    int expected_jaccard[] = {94, 67, 91, 70, 59};

    struct Animal dataZoo[NUM_SAMPLES];
    readFromFile("private/a1Data.txt", dataZoo);
    
    int newSample [NUM_FEATURES] = {1,1,1,0,1,0,1,1,1,0,0,0,0,1,1,1};

    int kNeighbours[NUM_SAMPLES];

    qsort(expected_euclidean, k, sizeof(int), compare);
    qsort(expected_hamming, k, sizeof(int), compare);
    qsort(expected_jaccard, k, sizeof(int), compare);

    // setup
    findKNearestNeighbors(dataZoo, newSample, k, 1, kNeighbours);
    qsort(kNeighbours, k, sizeof(int), compare);
    TEST_ASSERT_EQUAL_INT_ARRAY(kNeighbours, expected_euclidean, k);

    findKNearestNeighbors(dataZoo, newSample, k, 2, kNeighbours);
    qsort(kNeighbours, k, sizeof(int), compare);
    TEST_ASSERT_EQUAL_INT_ARRAY(kNeighbours, expected_hamming, k);

    findKNearestNeighbors(dataZoo, newSample, k, 3, kNeighbours);
    qsort(kNeighbours, k, sizeof(int), compare);
    TEST_ASSERT_EQUAL_INT_ARRAY(kNeighbours, expected_jaccard, k);
    // sort before compare
}
// ================ END OF TESTS ================



// 3. GO TO MAIN AND ADD "RUN_TEST(your_function_name_here)"
void setUp(void){}
void tearDown(void){}

int main(void) {
    UNITY_BEGIN();
    // ========= ADD TO MAIN HERE ===================

    RUN_TEST(test_distances);
    RUN_TEST(test_predictions);
    RUN_TEST(test_neighbours);

    // ======= END OF RUN_TEST CALLS ================
    return UNITY_END();
}

// ======= EXAMPLES OF TESTING ARRAYS, STRUCTS, MORE BELOW ========

// void test_Subtraction(void) {
//     printf("\033[0;31m"); // Red color for test start
//     TEST_ASSERT_EQUAL(1, subtract(2, 2));
//     printf("\033[0m"); // Reset color
// }

/*
EXAMPLES OF TESTS:
the idea is that you are testing functions prototyped in an included header file
and are defined soemwhere else in your project

==========================================================
simple function: integers in, integers out:
*note : this assumes subtract() is prototyped in an included header file
and defined in the project somewhere

void test_Subtraction(void) {
    printf("\033[0;31m"); // Red color for test start
    TEST_ASSERT_EQUAL(1, subtract(2, 2));
    printf("\033[0m"); // Reset color
}

==========================================================
Test case for string equality:

void test_StringEquality(void) {
    TEST_ASSERT_EQUAL_STRING("Hello, World!", get_hello());
}

==========================================================
// Test case for integer array equality:

void test_ArrayEquality(void) {
    int expected[] = {1, 2, 3, 4, 5};
    int actual[5];
    get_numbers(actual, 5);
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, actual, 5);
}
==========================================================
// Helper function to compare structs

void assert_PersonEqual(Person expected, Person actual) {
    TEST_ASSERT_EQUAL_INT(expected.id, actual.id);
    TEST_ASSERT_EQUAL_STRING(expected.name, actual.name);
}

// Test case for struct equality

void test_StructEquality(void) {
    Person expected = {1, "Alice"};
    Person actual = create_person(1, "Alice");
    assert_PersonEqual(expected, actual);
}
*/
