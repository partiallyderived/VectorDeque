#include <cppunit/extensions/HelperMacros.h>

#include "VectorDeque.hpp"
#include <iostream>
#include <vector>

class VectorDequeTest: public CppUnit::TestFixture {
    private:
        VectorDeque<int>* vectorDequePtr;
        VectorDeque<int>* vectorDeque2Ptr;
        VectorDeque<int>* vectorDequeOf0To99Ptr;
        VectorDeque<int>* vectorDequeOf99To0Ptr;
        std::vector<int>* emptyVectorPtr;
        std::vector<int>* vectorOf0To99Ptr;
        int* emptyArray;
        int* arrayOf0To99;
        int* destArray;

        CPPUNIT_TEST_SUITE(VectorDequeTest);
        CPPUNIT_TEST(testAccess);
        CPPUNIT_TEST(testAdd);
        CPPUNIT_TEST(testAddAll);
        CPPUNIT_TEST(testAddAllFirst);
        CPPUNIT_TEST(testAddFirst);
        CPPUNIT_TEST(testAssignment);
        CPPUNIT_TEST(testClear);
        CPPUNIT_TEST(testConstructors);
        CPPUNIT_TEST(testContains);
        CPPUNIT_TEST(testCopyToArray);
        CPPUNIT_TEST(testEquality);
        CPPUNIT_TEST(testFind);
        CPPUNIT_TEST(testFromBack);
        CPPUNIT_TEST(testInequality);
        CPPUNIT_TEST(testInsert);
        CPPUNIT_TEST(testInsertIterator);
        CPPUNIT_TEST(testIsEmpty);
        CPPUNIT_TEST(testIterators);
        CPPUNIT_TEST(testPeek);
        CPPUNIT_TEST(testPeekLast);
        CPPUNIT_TEST(testPop);
        CPPUNIT_TEST(testPopAll);
        CPPUNIT_TEST(testPopAllLast);
        CPPUNIT_TEST(testPopLast);
        CPPUNIT_TEST(testPopSome);
        CPPUNIT_TEST(testPopSomeLast);
        CPPUNIT_TEST(testRemoveAt);
        CPPUNIT_TEST(testRemoveAtIterator);
        CPPUNIT_TEST(testReverseCopyToArray);
        CPPUNIT_TEST(testReverseSliceToArray);
        CPPUNIT_TEST(testSize);
        CPPUNIT_TEST(testSliceToArray);
        CPPUNIT_TEST(testToString);
        CPPUNIT_TEST(testInternalInitialCapacity);
        CPPUNIT_TEST(testInternalPositionalInvariance);
        CPPUNIT_TEST(testInternalSpecialInsertion);
        CPPUNIT_TEST_SUITE_END();
    
    public:
        template<class IteratorType1, class IteratorType2>
        void helpTestOneOffIteratorCompare(const IteratorType1& lesserIterator, const IteratorType2& greaterIterator) {
            CPPUNIT_ASSERT(greaterIterator - lesserIterator == 1);

            // The following should be true.
            CPPUNIT_ASSERT(greaterIterator != lesserIterator);
            CPPUNIT_ASSERT(greaterIterator > lesserIterator);
            CPPUNIT_ASSERT(greaterIterator >= lesserIterator);
            CPPUNIT_ASSERT(lesserIterator < greaterIterator);
            CPPUNIT_ASSERT(lesserIterator <= greaterIterator);
            
            // The following should not be true (before negation).
            CPPUNIT_ASSERT(!(greaterIterator == lesserIterator));
            CPPUNIT_ASSERT(!(greaterIterator < lesserIterator));
            CPPUNIT_ASSERT(!(greaterIterator <= lesserIterator));
            CPPUNIT_ASSERT(!(lesserIterator > greaterIterator));
            CPPUNIT_ASSERT(!(lesserIterator >= greaterIterator));
        }
        
        template<class IteratorType1, class IteratorType2>
        void helpTestEqualIteratorCompare(const IteratorType1& iterator1, const IteratorType2& iterator2) {
            CPPUNIT_ASSERT(iterator1 - iterator2 == 0);
                
            // The following should be true.
            CPPUNIT_ASSERT(iterator1 == iterator2);
            CPPUNIT_ASSERT(iterator1 <= iterator2);
            CPPUNIT_ASSERT(iterator1 >= iterator2);
            CPPUNIT_ASSERT(iterator2 >= iterator1);
            CPPUNIT_ASSERT(iterator2 <= iterator1);
            
            // The following should not be true (before negation).
            CPPUNIT_ASSERT(!(iterator1 != iterator2));
            CPPUNIT_ASSERT(!(iterator1 < iterator2));
            CPPUNIT_ASSERT(!(iterator1 > iterator2));
            CPPUNIT_ASSERT(!(iterator2 > iterator1));
            CPPUNIT_ASSERT(!(iterator1 < iterator2));
        }
        
        template<class IteratorType>
        void helpTestIteratorArithmetic(IteratorType& iterator, int i) {
            CPPUNIT_ASSERT(*iterator == i);
            CPPUNIT_ASSERT(iterator[0] == i);
            CPPUNIT_ASSERT(iterator[2] == i + 2);
            CPPUNIT_ASSERT((*++iterator) == i + 1);
            CPPUNIT_ASSERT((*--iterator) == i);
            CPPUNIT_ASSERT(*(iterator++) == i);
            CPPUNIT_ASSERT(*(iterator--) == i + 1);
            CPPUNIT_ASSERT(*(iterator + 2) == i + 2);
            CPPUNIT_ASSERT(*(2 + iterator) == i + 2);
            CPPUNIT_ASSERT(*(iterator += 2) == i + 2);
            CPPUNIT_ASSERT(iterator[-2] == i);
            CPPUNIT_ASSERT(*(iterator - 2) == i);
            CPPUNIT_ASSERT(*(iterator -= 2) == i);
        }
    
        void setUp() {
            vectorDequePtr = new VectorDeque<int>();
            vectorDeque2Ptr = new VectorDeque<int>();
            vectorDequeOf0To99Ptr = new VectorDeque<int>();
            vectorDequeOf99To0Ptr = new VectorDeque<int>();
            vectorOf0To99Ptr = new std::vector<int>();
            emptyVectorPtr = new std::vector<int>();
            emptyArray = new int[0];
            arrayOf0To99 = new int[100];
            destArray = new int[100];
            for (int i = 0; i < 100; ++i) {
                arrayOf0To99[i] = i;
                vectorDequeOf0To99Ptr->add(i);
                vectorDequeOf99To0Ptr->addFirst(i);
                vectorOf0To99Ptr->push_back(i);
            }
        }

        void testAccess() {
            CPPUNIT_ASSERT_THROW((*vectorDequePtr)[0], std::length_error);
            vectorDequePtr->add(3);
            CPPUNIT_ASSERT((*vectorDequePtr)[0] == 3);
            CPPUNIT_ASSERT_THROW((*vectorDequePtr)[1], std::length_error);
            CPPUNIT_ASSERT_THROW((*vectorDequePtr)[10], std::length_error);
            vectorDequePtr->add(5);
            CPPUNIT_ASSERT((*vectorDequePtr)[1] == 5);
            CPPUNIT_ASSERT_THROW((*vectorDequePtr)[2], std::length_error);
            vectorDequePtr->clear();
            for (int i = 0; i < 100; ++i) {
                vectorDequePtr->add(i);
            }
            for (int i = 0; i < 100; ++i){
                CPPUNIT_ASSERT((*vectorDequePtr)[i] == i);
            }
            CPPUNIT_ASSERT_THROW((*vectorDequePtr)[100], std::length_error);
        }

        void testAdd() {
            vectorDequePtr->add(3);
            CPPUNIT_ASSERT((*vectorDequePtr)[0] == 3);
            CPPUNIT_ASSERT(vectorDequePtr->size() == 1);
            vectorDequePtr->add(5);
            CPPUNIT_ASSERT((*vectorDequePtr)[0] == 3);
            CPPUNIT_ASSERT((*vectorDequePtr)[1] == 5);
            CPPUNIT_ASSERT(vectorDequePtr->size() == 2);
            vectorDequePtr->clear();
            for (int i = 0; i < 100; ++i) {
                vectorDequePtr->add(i);
            }
            CPPUNIT_ASSERT(*vectorDequePtr == *vectorDequeOf0To99Ptr);
        }

        void testAddAll() {
            vectorDequePtr->addAll(emptyArray, 0);
            CPPUNIT_ASSERT(vectorDequePtr->isEmpty());
            vectorDequePtr->addAll(arrayOf0To99, 100);
            CPPUNIT_ASSERT(vectorDequePtr->size() == 100);
            
            CPPUNIT_ASSERT(*vectorDequePtr == *vectorDequeOf0To99Ptr);
            vectorDequePtr->clear();
            vectorDequePtr->addAll(emptyVectorPtr->begin(), emptyVectorPtr->end());
            
            CPPUNIT_ASSERT(vectorDequePtr->isEmpty());
            vectorDequePtr->addAll(vectorOf0To99Ptr->begin(), vectorOf0To99Ptr->end());
            
            CPPUNIT_ASSERT(*vectorDequePtr == *vectorDequeOf0To99Ptr);
            vectorDequePtr->clear();
            vectorDequePtr->addAll(vectorDequeOf0To99Ptr->begin(), vectorDequeOf0To99Ptr->end());

            CPPUNIT_ASSERT(*vectorDequePtr == *vectorDequeOf0To99Ptr);
        }

        void testAddAllFirst() {
            vectorDequePtr->addAllFirst(emptyArray, 0);
            CPPUNIT_ASSERT(vectorDequePtr->isEmpty());
            vectorDequePtr->addAllFirst(arrayOf0To99, 100);
            CPPUNIT_ASSERT(vectorDequePtr->size() == 100);
            CPPUNIT_ASSERT(*vectorDequePtr == *vectorDequeOf99To0Ptr);
            
            vectorDequePtr->clear();
            vectorDequePtr->addAllFirst(emptyVectorPtr->begin(), emptyVectorPtr->end());
            
            CPPUNIT_ASSERT(vectorDequePtr->isEmpty());
            vectorDequePtr->addAllFirst(vectorOf0To99Ptr->begin(), vectorOf0To99Ptr->end());
            
            CPPUNIT_ASSERT(*vectorDequePtr == *vectorDequeOf99To0Ptr);
            vectorDequePtr->clear();
            vectorDequePtr->addAllFirst(vectorDequeOf0To99Ptr->begin(), vectorDequeOf0To99Ptr->end());

            CPPUNIT_ASSERT(*vectorDequePtr == *vectorDequeOf99To0Ptr);
        }

        void testAddFirst() {
            vectorDequePtr->addFirst(3);
            CPPUNIT_ASSERT((*vectorDequePtr)[0] == 3);
            CPPUNIT_ASSERT(vectorDequePtr->size() == 1);
            vectorDequePtr->addFirst(5);
            CPPUNIT_ASSERT((*vectorDequePtr)[0] == 5);
            CPPUNIT_ASSERT((*vectorDequePtr)[1] == 3);
            CPPUNIT_ASSERT(vectorDequePtr->size() == 2);
            vectorDequePtr->clear();
            for (int i = 0; i < 100; ++i) {
                vectorDequePtr->addFirst(i);
            }
            CPPUNIT_ASSERT(*vectorDequePtr == *vectorDequeOf99To0Ptr);
        }

        void testAssignment() {
            *vectorDequePtr = *vectorDequePtr;
            CPPUNIT_ASSERT(vectorDequePtr->isEmpty());
            *vectorDequePtr = *vectorDequeOf0To99Ptr;
            CPPUNIT_ASSERT(*vectorDequePtr == *vectorDequeOf0To99Ptr);
            *vectorDequePtr = *vectorDequePtr;
            CPPUNIT_ASSERT(*vectorDequePtr == *vectorDequeOf0To99Ptr);
            *vectorDequePtr = VectorDeque<int>();
            CPPUNIT_ASSERT(vectorDequePtr->isEmpty());
        }

        void testClear() {
            vectorDequePtr->clear();
            CPPUNIT_ASSERT(vectorDequePtr->isEmpty());
            vectorDequePtr->add(5);
            vectorDequePtr->clear();
            CPPUNIT_ASSERT(vectorDequePtr->isEmpty());
            vectorDequePtr->addAll(arrayOf0To99, 100);
            vectorDequePtr->clear();
            vectorDequePtr->isEmpty();
        }

        void testConstructors() {
            *vectorDequePtr = VectorDeque<int>();
            CPPUNIT_ASSERT(vectorDequePtr->isEmpty());

            // Internal testing for actually initial capacity is in the test "testDefaultInitialCapacity".
            *vectorDequePtr = VectorDeque<int>(15);
            CPPUNIT_ASSERT(vectorDequePtr->isEmpty());

            *vectorDequePtr = VectorDeque<int>(*vectorDequeOf0To99Ptr);
            CPPUNIT_ASSERT(*vectorDequePtr == *vectorDequeOf0To99Ptr);

            *vectorDequePtr = VectorDeque<int>();
            CPPUNIT_ASSERT(vectorDequePtr->isEmpty());
        }

        void testContains() {
            CPPUNIT_ASSERT(!vectorDequePtr->contains(3));
            vectorDequePtr->add(3);
            CPPUNIT_ASSERT(vectorDequePtr->contains(3));
            CPPUNIT_ASSERT(!vectorDequePtr->contains(5));
            vectorDequePtr->add(5);
            CPPUNIT_ASSERT(vectorDequePtr->contains(3));
            CPPUNIT_ASSERT(vectorDequePtr->contains(5));
            vectorDequePtr->clear();
            vectorDequePtr->addAll(arrayOf0To99, 100);
            for (int i = 0; i < 100; ++i) {
                CPPUNIT_ASSERT(vectorDequePtr->contains(i));
            }
            CPPUNIT_ASSERT(!vectorDequePtr->contains(100));
        }

        void testCopyToArray() {
            vectorDequePtr->copyToArray(emptyArray);
            vectorDequePtr->add(5);
            vectorDequePtr->copyToArray(destArray);
            CPPUNIT_ASSERT(destArray[0] == 5);
            vectorDequePtr->add(4);
            vectorDequePtr->copyToArray(destArray);
            CPPUNIT_ASSERT(destArray[0] == 5);
            CPPUNIT_ASSERT(destArray[1] == 4);
            vectorDequeOf0To99Ptr->copyToArray(destArray);
            for (int i = 0; i < 100; ++i) {
                CPPUNIT_ASSERT(destArray[i] == i);
            }
        }

        void testEquality() {
            CPPUNIT_ASSERT(*vectorDequePtr == *vectorDequePtr);
            CPPUNIT_ASSERT(*vectorDequePtr == VectorDeque<int>());
            CPPUNIT_ASSERT(*vectorDequePtr == VectorDeque<int>(15));
            CPPUNIT_ASSERT(!(*vectorDequePtr == *vectorDequeOf0To99Ptr));
            vectorDequePtr->addAll(arrayOf0To99, 100);
            CPPUNIT_ASSERT(*vectorDequePtr == *vectorDequePtr);
            CPPUNIT_ASSERT(!(*vectorDequePtr == VectorDeque<int>()));
            CPPUNIT_ASSERT(*vectorDequePtr == *vectorDequeOf0To99Ptr);
        }

        void testFind() {
            CPPUNIT_ASSERT(vectorDequePtr->find(3) == -1);
            vectorDequePtr->add(3);
            CPPUNIT_ASSERT(vectorDequePtr->find(3) == 0);
            CPPUNIT_ASSERT(vectorDequePtr->find(5) == -1);
            vectorDequePtr->add(5);
            CPPUNIT_ASSERT(vectorDequePtr->find(3) == 0);
            CPPUNIT_ASSERT(vectorDequePtr->find(5) == 1);
            *vectorDequePtr = *vectorDequeOf0To99Ptr;
            for (int i = 0; i < 100; ++i) {
                CPPUNIT_ASSERT(vectorDequePtr->find(i) == i);
            }
            CPPUNIT_ASSERT(vectorDequePtr->find(100) == -1);
        }

        void testFromBack() {
            CPPUNIT_ASSERT_THROW(vectorDequePtr->fromBack(0), std::length_error);
            vectorDequePtr->add(3);
            CPPUNIT_ASSERT(vectorDequePtr->fromBack(0) == 3);
            CPPUNIT_ASSERT_THROW(vectorDequePtr->fromBack(1), std::length_error);
            vectorDequePtr->add(4);
            vectorDequePtr->add(5);
            CPPUNIT_ASSERT(vectorDequePtr->fromBack(0) == 5);
            CPPUNIT_ASSERT(vectorDequePtr->fromBack(1) == 4);
            CPPUNIT_ASSERT(vectorDequePtr->fromBack(2) == 3);

            for (int i = 0; i < 100; ++i) {
                CPPUNIT_ASSERT(vectorDequeOf99To0Ptr->fromBack(i) == i);
            }
        }

        void testInequality() {
            CPPUNIT_ASSERT(!(*vectorDequePtr != *vectorDequePtr));
            CPPUNIT_ASSERT(!(*vectorDequePtr != VectorDeque<int>()));
            CPPUNIT_ASSERT(!(*vectorDequePtr != VectorDeque<int>(15)));
            CPPUNIT_ASSERT(*vectorDequePtr != *vectorDequeOf0To99Ptr);
            vectorDequePtr->addAll(arrayOf0To99, 100);
            CPPUNIT_ASSERT(!(*vectorDequePtr != *vectorDequePtr));
            CPPUNIT_ASSERT(*vectorDequePtr != VectorDeque<int>());
            CPPUNIT_ASSERT(!(*vectorDequePtr != *vectorDequeOf0To99Ptr));
        }

        void testInsert() {
            CPPUNIT_ASSERT_THROW(vectorDequePtr->insert(3, 1), std::length_error);
            vectorDequePtr->insert(3, 0);
            CPPUNIT_ASSERT((*vectorDequePtr)[0] == 3);
            CPPUNIT_ASSERT_THROW(vectorDequePtr->insert(5, 2), std::length_error);
            vectorDequePtr->insert(7, 0);
            CPPUNIT_ASSERT((*vectorDequePtr)[0] == 7);
            CPPUNIT_ASSERT((*vectorDequePtr)[1] == 3);
            vectorDequePtr->insert(5, 1);
            CPPUNIT_ASSERT((*vectorDequePtr)[0] == 7);
            CPPUNIT_ASSERT((*vectorDequePtr)[1] == 5);
            CPPUNIT_ASSERT((*vectorDequePtr)[2] == 3);
            vectorDequePtr->insert(9, 2);
            CPPUNIT_ASSERT((*vectorDequePtr)[0] == 7);
            CPPUNIT_ASSERT((*vectorDequePtr)[1] == 5);
            CPPUNIT_ASSERT((*vectorDequePtr)[2] == 9);
            CPPUNIT_ASSERT((*vectorDequePtr)[3] == 3);
        }

        void testInsertIterator() {
            VectorDeque<int>::Iterator iterator = vectorDequePtr->begin();
            vectorDequePtr->insert(3, iterator);
            CPPUNIT_ASSERT((*vectorDequePtr)[0] == 3);
            
            vectorDequePtr->insert(2, iterator);
            CPPUNIT_ASSERT((*vectorDequePtr)[0] == 2);
            CPPUNIT_ASSERT((*vectorDequePtr)[1] == 3);
            
            ++iterator;
            vectorDequePtr->insert(5, iterator);
            CPPUNIT_ASSERT((*vectorDequePtr)[0] == 2);
            CPPUNIT_ASSERT((*vectorDequePtr)[1] == 5);
            CPPUNIT_ASSERT((*vectorDequePtr)[2] == 3);
            
            iterator += 2;
            CPPUNIT_ASSERT(iterator == vectorDequePtr->end());
            vectorDequePtr->insert(7, iterator);
            CPPUNIT_ASSERT((*vectorDequePtr)[0] == 2);
            CPPUNIT_ASSERT((*vectorDequePtr)[1] == 5);
            CPPUNIT_ASSERT((*vectorDequePtr)[2] == 3);
            CPPUNIT_ASSERT((*vectorDequePtr)[3] == 7);
        }

        void testIsEmpty() {
            CPPUNIT_ASSERT(vectorDequePtr->isEmpty());
            CPPUNIT_ASSERT(!vectorDequeOf0To99Ptr->isEmpty());
            
            vectorDequePtr->add(3);
            CPPUNIT_ASSERT(!vectorDequePtr->isEmpty());
        }

        void testIterators() {
            VectorDeque<int>::Iterator iterator = vectorDequeOf0To99Ptr->begin();
            VectorDeque<int>::ConstIterator constIterator = vectorDequeOf0To99Ptr->cbegin();
            VectorDeque<int>::ReverseIterator reverseIterator = vectorDequeOf99To0Ptr->rbegin();
            VectorDeque<int>::ConstReverseIterator constReverseIterator = vectorDequeOf99To0Ptr->crbegin();
            // For simplicity, omit the last two ints to avoid going OOB.
            for (int i = 0; i < 98; ++i) {
                helpTestIteratorArithmetic(iterator, i);
                helpTestIteratorArithmetic(constIterator, i);
                helpTestIteratorArithmetic(reverseIterator, i);
                helpTestIteratorArithmetic(constReverseIterator, i);
                
                ++iterator;
                helpTestOneOffIteratorCompare(constIterator, iterator);
                
                ++constIterator;
                helpTestEqualIteratorCompare(iterator, constIterator);
                
                ++reverseIterator;
                helpTestOneOffIteratorCompare(constReverseIterator, reverseIterator);
                
                ++constReverseIterator;
                helpTestEqualIteratorCompare(reverseIterator, constReverseIterator);
            }
            VectorDeque<int>::ConstIterator constFromNotConstIterator = VectorDeque<int>::ConstIterator(iterator);
            VectorDeque<std::string> vectorDequeOfStrings;
            vectorDequeOfStrings.add("hi");
            VectorDeque<std::string>::Iterator stringIterator = vectorDequeOfStrings.begin();
            CPPUNIT_ASSERT(stringIterator->length() == 2);
        }

        void testPeek() {
            CPPUNIT_ASSERT_THROW(vectorDequePtr->peek(), std::length_error);
            vectorDequePtr->add(3);
            CPPUNIT_ASSERT(vectorDequePtr->peek() == 3);
            vectorDequePtr->add(4);
            CPPUNIT_ASSERT(vectorDequePtr->peek() == 3);
            vectorDequePtr->addFirst(5);
            CPPUNIT_ASSERT(vectorDequePtr->peek() == 5);
        }

        void testPeekLast() {
            CPPUNIT_ASSERT_THROW(vectorDequePtr->peekLast(), std::length_error);
            vectorDequePtr->add(3);
            CPPUNIT_ASSERT(vectorDequePtr->peekLast() == 3);
            vectorDequePtr->add(4);
            CPPUNIT_ASSERT(vectorDequePtr->peekLast() == 4);
            vectorDequePtr->addFirst(5);
            CPPUNIT_ASSERT(vectorDequePtr->peekLast() == 4);
        }

        void testPop() {
            CPPUNIT_ASSERT_THROW(vectorDequePtr->pop(), std::length_error);
            vectorDequePtr->add(3);
            CPPUNIT_ASSERT(vectorDequePtr->pop() == 3);
            vectorDequePtr->add(5);
            vectorDequePtr->add(6);
            CPPUNIT_ASSERT(vectorDequePtr->pop() == 5);
            vectorDequePtr->addFirst(2);
            CPPUNIT_ASSERT(vectorDequePtr->pop() == 2);
            
            for (int i = 0; i < 100; ++i) {
                CPPUNIT_ASSERT(vectorDequeOf0To99Ptr->pop() == i);
            }
        }

        void testPopAll() {
            vectorDequePtr->popAll(destArray);
            vectorDequePtr->add(3);
            vectorDequePtr->popAll(destArray);
            CPPUNIT_ASSERT(vectorDequePtr->isEmpty());
            CPPUNIT_ASSERT(destArray[0] == 3);
            vectorDequePtr->add(4);
            vectorDequePtr->add(5);
            vectorDequePtr->popAll(destArray);
            CPPUNIT_ASSERT(destArray[0] == 4);
            CPPUNIT_ASSERT(destArray[1] == 5);
            vectorDequeOf0To99Ptr->popAll(destArray);
            
            for (int i = 0; i < 100; ++i) {
                CPPUNIT_ASSERT(destArray[i] == i);
            }
        }

        void testPopAllLast() {
            vectorDequePtr->popAllLast(destArray);
            vectorDequePtr->add(3);
            vectorDequePtr->popAllLast(destArray);
            CPPUNIT_ASSERT(vectorDequePtr->isEmpty());
            CPPUNIT_ASSERT(destArray[0] == 3);
            vectorDequePtr->add(4);
            vectorDequePtr->add(5);
            vectorDequePtr->popAllLast(destArray);
            CPPUNIT_ASSERT(destArray[0] == 5);
            CPPUNIT_ASSERT(destArray[1] == 4);
            vectorDequeOf99To0Ptr->popAllLast(destArray);
            
            for (int i = 0; i < 100; ++i) {
                CPPUNIT_ASSERT(destArray[i] == i);
            }
        }

        void testPopLast() {
            CPPUNIT_ASSERT_THROW(vectorDequePtr->popLast(), std::length_error);
            vectorDequePtr->add(3);
            CPPUNIT_ASSERT(vectorDequePtr->popLast() == 3);
            vectorDequePtr->add(5);
            vectorDequePtr->add(6);
            CPPUNIT_ASSERT(vectorDequePtr->popLast() == 6);
            vectorDequePtr->addFirst(2);
            CPPUNIT_ASSERT(vectorDequePtr->popLast() == 5);
            
            for (int i = 0; i < 100; ++i) {
                CPPUNIT_ASSERT(vectorDequeOf99To0Ptr->popLast() == i);
            }
        }

        void testPopSome() {
            vectorDequePtr->popSome(destArray, 0);
            CPPUNIT_ASSERT_THROW(vectorDequePtr->popSome(destArray, 1), std::length_error);
            vectorDequePtr->add(3);
            vectorDequePtr->popSome(destArray, 1);
            CPPUNIT_ASSERT(vectorDequePtr->isEmpty());
            CPPUNIT_ASSERT(destArray[0] == 3);
            vectorDequePtr->add(4);
            vectorDequePtr->add(5);
            vectorDequePtr->add(6);
            CPPUNIT_ASSERT_THROW(vectorDequePtr->popSome(destArray, 4), std::length_error);
            vectorDequePtr->popSome(destArray, 0);
            CPPUNIT_ASSERT(vectorDequePtr->size() == 3);
            vectorDequePtr->popSome(destArray, 3);
            CPPUNIT_ASSERT(destArray[0] == 4);
            CPPUNIT_ASSERT(destArray[1] == 5);
            CPPUNIT_ASSERT(destArray[2] == 6);
            
            vectorDequeOf0To99Ptr->popSome(destArray, 50);
            CPPUNIT_ASSERT(vectorDequeOf0To99Ptr->size() == 50);
            for (int i = 0; i < 50; ++i) {
                CPPUNIT_ASSERT(destArray[i] == i);
            }
        }

        void testPopSomeLast() {
            vectorDequePtr->popSomeLast(destArray, 0);
            CPPUNIT_ASSERT_THROW(vectorDequePtr->popSomeLast(destArray, 1), std::length_error);
            vectorDequePtr->add(3);
            vectorDequePtr->popSomeLast(destArray, 1);
            CPPUNIT_ASSERT(vectorDequePtr->isEmpty());
            CPPUNIT_ASSERT(destArray[0] == 3);
            vectorDequePtr->add(4);
            vectorDequePtr->add(5);
            vectorDequePtr->add(6);
            CPPUNIT_ASSERT_THROW(vectorDequePtr->popSomeLast(destArray, 4), std::length_error);
            vectorDequePtr->popSomeLast(destArray, 0);
            CPPUNIT_ASSERT(vectorDequePtr->size() == 3);
            vectorDequePtr->popSomeLast(destArray, 3);
            CPPUNIT_ASSERT(destArray[0] == 6);
            CPPUNIT_ASSERT(destArray[1] == 5);
            CPPUNIT_ASSERT(destArray[2] == 4);
            
            vectorDequeOf99To0Ptr->popSomeLast(destArray, 50);
            CPPUNIT_ASSERT(vectorDequeOf99To0Ptr->size() == 50);
            for (int i = 0; i < 50; ++i) {
                CPPUNIT_ASSERT(destArray[i] == i);
            }
        }

        void testRemoveAt() {
            CPPUNIT_ASSERT_THROW(vectorDequePtr->removeAt(0), std::length_error);
            vectorDequePtr->add(3);
            CPPUNIT_ASSERT(vectorDequePtr->removeAt(0) == 3);
            CPPUNIT_ASSERT(vectorDequePtr->isEmpty());
            vectorDequePtr->add(4);
            vectorDequePtr->add(5);
            CPPUNIT_ASSERT(vectorDequePtr->removeAt(1) == 5);
            CPPUNIT_ASSERT(vectorDequeOf0To99Ptr->removeAt(37) == 37);
            int result = vectorDequeOf0To99Ptr->removeAt(37);
            CPPUNIT_ASSERT(result == 38);
        }

        void testRemoveAtIterator() {
            vectorDequePtr->add(3);
            vectorDequePtr->add(4);
            vectorDequePtr->add(5);
            VectorDeque<int>::Iterator it = vectorDequePtr->begin();
            CPPUNIT_ASSERT(vectorDequePtr->removeAt(it) == 3);
            CPPUNIT_ASSERT(vectorDequePtr->removeAt(it) == 4);
            CPPUNIT_ASSERT(vectorDequePtr->removeAt(it) == 5);
        }

        void testReverseCopyToArray() {
            vectorDequePtr->reverseCopyToArray(emptyArray);
            vectorDequePtr->add(5);
            vectorDequePtr->reverseCopyToArray(destArray);
            CPPUNIT_ASSERT(destArray[0] == 5);
            vectorDequePtr->add(4);
            vectorDequePtr->reverseCopyToArray(destArray);
            CPPUNIT_ASSERT(destArray[0] == 4);
            CPPUNIT_ASSERT(destArray[1] == 5);
            vectorDequeOf99To0Ptr->reverseCopyToArray(destArray);
            for (int i = 0; i < 100; ++i) {
                CPPUNIT_ASSERT(destArray[i] == i);
            }
        }

        void testReverseSliceToArray() {
            vectorDequePtr->reverseSliceToArray(destArray, 0, 0);
            vectorDequePtr->add(3);
            vectorDequePtr->reverseSliceToArray(destArray, 0, 1);
            CPPUNIT_ASSERT(destArray[0] == 3);
            vectorDequePtr->add(4);
            vectorDequePtr->add(5);
            vectorDequePtr->add(6);
            vectorDequePtr->reverseSliceToArray(destArray, 1, 3);
            CPPUNIT_ASSERT(destArray[0] == 5);
            CPPUNIT_ASSERT(destArray[1] == 4);

            vectorDequeOf99To0Ptr->reverseSliceToArray(destArray, 25, 75);
            for (int i = 0; i < 50; ++i) {
                CPPUNIT_ASSERT(destArray[i] == i + 25);
            }
        }

        void testSize() {
            CPPUNIT_ASSERT(vectorDequePtr->size() == 0);
            vectorDequePtr->add(3);
            CPPUNIT_ASSERT(vectorDequePtr->size() == 1);
            vectorDequePtr->add(4);
            CPPUNIT_ASSERT(vectorDequePtr->size() == 2);

            CPPUNIT_ASSERT(vectorDequeOf0To99Ptr->size() == 100);
        }

        void testSkip() {
            vectorDequePtr->skip(0);
            CPPUNIT_ASSERT_THROW(vectorDequePtr->skip(1), std::length_error);
            vectorDequePtr->add(3);
            CPPUNIT_ASSERT_THROW(vectorDequePtr->skip(2), std::length_error);
            vectorDequePtr->skip(1);
            CPPUNIT_ASSERT(vectorDequePtr->isEmpty());
            vectorDequePtr->add(4);
            vectorDequePtr->add(5);
            vectorDequePtr->skip(1);
            CPPUNIT_ASSERT((*vectorDequePtr)[0] == 5);
            vectorDequePtr->add(6);
            vectorDequePtr->add(7);
            vectorDequePtr->skip(2);
            CPPUNIT_ASSERT((*vectorDequePtr)[0] == 7);
        }
        
        void testSkipLast() {
            vectorDequePtr->skipLast(0);
            CPPUNIT_ASSERT_THROW(vectorDequePtr->skipLast(1), std::length_error);
            vectorDequePtr->add(3);
            CPPUNIT_ASSERT_THROW(vectorDequePtr->skipLast(2), std::length_error);
            vectorDequePtr->skipLast(1);
            CPPUNIT_ASSERT(vectorDequePtr->isEmpty());
            vectorDequePtr->add(4);
            vectorDequePtr->add(5);
            vectorDequePtr->skipLast(1);
            CPPUNIT_ASSERT((*vectorDequePtr)[0] == 4);
            vectorDequePtr->add(6);
            vectorDequePtr->add(7);
            vectorDequePtr->skipLast(2);
            CPPUNIT_ASSERT((*vectorDequePtr)[0] == 4);
        }

        void testSliceToArray() {
            vectorDequePtr->sliceToArray(destArray, 0, 0);
            vectorDequePtr->add(3);
            vectorDequePtr->sliceToArray(destArray, 0, 1);
            CPPUNIT_ASSERT(destArray[0] == 3);
            vectorDequePtr->add(4);
            vectorDequePtr->add(5);
            vectorDequePtr->add(6);
            vectorDequePtr->sliceToArray(destArray, 1, 3);
            CPPUNIT_ASSERT(destArray[0] == 4);
            CPPUNIT_ASSERT(destArray[1] == 5);

            vectorDequeOf0To99Ptr->sliceToArray(destArray, 25, 75);
            for (int i = 0; i < 50; ++i) {
                CPPUNIT_ASSERT(destArray[i] == i + 25);
            }
        }

        void testToString() {
            CPPUNIT_ASSERT(((std::string) *vectorDequePtr) == "{}");
            vectorDequePtr->add(3);
            CPPUNIT_ASSERT(((std::string) *vectorDequePtr) == "{3}");
            vectorDequePtr->add(4);
            vectorDequePtr->add(5);
            CPPUNIT_ASSERT(((std::string) *vectorDequePtr) == "{3, 4, 5}");
        }

        void testInternalInitialCapacity() {
            VectorDeque<int> newVectorDeque1;
            CPPUNIT_ASSERT(newVectorDeque1._capacity == VectorDeque<int>::DEFAULT_INITIAL_CAPACITY);

            VectorDeque<int> newVectorDeque2(0);
            CPPUNIT_ASSERT(newVectorDeque2._capacity == 0);

            VectorDeque<int> newVectorDeque3(100);
            CPPUNIT_ASSERT(newVectorDeque3._capacity == 100);
        }

        // Test that the contents are consistent with the internal position.
        void testInternalPositionalInvariance() {
            // Add all first to ensure capacity is the same on each iteration.
            vectorDequePtr->addAll(arrayOf0To99, 100);
            for (int i = 0; i < vectorDequePtr->_capacity; ++i) {
                CPPUNIT_ASSERT(*vectorDequePtr == *vectorDequeOf0To99Ptr);
                CPPUNIT_ASSERT_THROW((*vectorDequePtr)[100], std::length_error);
                vectorDequePtr->clear();
                vectorDequePtr->_position = i + 1;
                vectorDequePtr->addAll(arrayOf0To99, 100);
            }
        }

        void testInternalSpecialInsertion() {
            // First, empty.
            vectorDequePtr->insert(3, 0);
            CPPUNIT_ASSERT(vectorDequePtr->peek() == 3);
            // First, nonempty.
            vectorDequePtr->insert(5, 0);
            CPPUNIT_ASSERT(vectorDequePtr->peek() == 5);
            CPPUNIT_ASSERT((*vectorDequePtr)[1] == 3);
            // Last
            vectorDequePtr->insert(7, 2);
            CPPUNIT_ASSERT(vectorDequePtr->peek() == 5);
            CPPUNIT_ASSERT((*vectorDequePtr)[1] == 3);
            CPPUNIT_ASSERT((*vectorDequePtr)[2] == 7);
            // Bottom half
            vectorDequePtr->insert(9, 1);
            CPPUNIT_ASSERT(vectorDequePtr->peek() == 5);
            CPPUNIT_ASSERT((*vectorDequePtr)[1] == 9);
            CPPUNIT_ASSERT((*vectorDequePtr)[2] == 3);
            CPPUNIT_ASSERT((*vectorDequePtr)[3] == 7);
            // Top half
            vectorDequePtr->insert(11, 3);
            CPPUNIT_ASSERT(vectorDequePtr->peek() == 5);
            CPPUNIT_ASSERT((*vectorDequePtr)[1] == 9);
            CPPUNIT_ASSERT((*vectorDequePtr)[2] == 3);
            CPPUNIT_ASSERT((*vectorDequePtr)[3] == 11);
            CPPUNIT_ASSERT((*vectorDequePtr)[4] == 7);
            // During resize
            vectorDequePtr->clear();
            const size_t previousCapacity = vectorDequePtr->_capacity;
            for (int i = 0; i < vectorDequePtr->_capacity; ++i) {
                vectorDequePtr->add(i);
            }
            vectorDequePtr->insert(20, 5);
            for (int i = 0; i < 5; ++i) {
                CPPUNIT_ASSERT((*vectorDequePtr)[i] == i);
            }
            CPPUNIT_ASSERT((*vectorDequePtr)[5] == 20);
            for (int i = 6; i <= previousCapacity; ++i) {
                CPPUNIT_ASSERT((*vectorDequePtr)[i] == i - 1);
            }
        }

        void tearDown() {
            delete vectorDequePtr;
            delete vectorDeque2Ptr;
            delete vectorDequeOf0To99Ptr;
            delete vectorDequeOf99To0Ptr;
            delete vectorOf0To99Ptr;
            delete emptyVectorPtr;
            delete[] emptyArray;
            delete[] arrayOf0To99;
            delete[] destArray;
        }
};
