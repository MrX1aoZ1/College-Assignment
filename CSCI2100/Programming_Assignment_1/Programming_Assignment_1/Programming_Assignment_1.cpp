#include "Singly_Linked_List.cpp"
#include "Doubly_Linked_List.cpp"
#include "Red_Black_Tree.cpp"
#include <iostream>
#include <vector>
#include <random>
#include <numeric>
#include <string>
#include <chrono>

int main()
{
    std::vector<int> testData1(10 + 1 + 1000);
    std::iota(testData1.begin(), testData1.end(), -10);

    std::vector<int> testData2(100 + 1 + 100000);
    std::iota(testData2.begin(), testData2.end(), -100);

    std::vector<int> testData3(500 + 1 + 500000);
    std::iota(testData3.begin(), testData3.end(), -500);

    std::vector<int> testData4(1000 + 1 + 1000000);
    std::iota(testData4.begin(), testData4.end(), -1000);
  
    std::random_device rd;
    std::mt19937 rng(rd());

    std::chrono::steady_clock::time_point begin;
    std::chrono::steady_clock::time_point end;

    
    std::cout << "Red Black tree:" << std::endl;
    for (int i = 1; i <= 4; i++)        // To loop 4 data set
    {
        std::vector<int> DS;            // DS refer to test data set
        int largestNumber;
        if (i == 1)                     
        {
            DS = testData1;             
            largestNumber = 1000;  
        }
        else if (i == 2)
        {
            DS = testData2;
            largestNumber = 100000;
        }
        else if (i == 3)
        {
            DS = testData3;
            largestNumber = 500000;
        }
        else if (i == 4)
        {
            DS = testData4;
            largestNumber = 1000000;
        }
        long long averageInsert = 0;
        long long averageDelete = 0; 
        long long averageSearch = 0;
        std::cout << "Data Set " << i << ":" << std::endl;
        for (int j = 1; j <= 5; j++)
        {
            RedBlackTree<int>* ADT = new RedBlackTree<int>();
            std::shuffle(DS.begin(), DS.end(), rng);

            // Insert Part
            begin = std::chrono::steady_clock::now();
            for (int i : DS)        // This kind of for loop ensures that all data of the data set are inserted into the data structure
            {
                ADT->insert(i);
            }
            end = std::chrono::steady_clock::now();
            averageInsert += std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count();
            // Delete Part
            begin = std::chrono::steady_clock::now();
            for (int i : DS)
            {
                if (i < 0)
                    ADT->remove(i);
            }
            end = std::chrono::steady_clock::now();
            averageDelete += std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count();
            // Search Part
            begin = std::chrono::steady_clock::now();
            ADT->searchTiming(largestNumber);
            end = std::chrono::steady_clock::now();
            averageSearch += std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count();
        }
        // It gives the average time of the operations in 5 shuffles
        std::cout << "Insert: " << averageInsert / 5 << "[ns]    Delete: " << averageDelete / 5 << "[ns]    Search: " << averageSearch / 5 << "[ns]" << std::endl;
    }
    std::cout << "\n" << std::endl;
    
    
    std::cout << "Doubly Linked list:" << std::endl;
    for (int i = 1; i <= 4; i++)
    {
        std::vector<int> DS;    // DS refer to test data set
        int largestNumber;
        if (i == 1)
        {
            DS = testData1;
            largestNumber = 1000;
        }
        else if (i == 2)
        {
            DS = testData2;
            largestNumber = 100000;
        }
        else if (i == 3)
        {
            DS = testData3;
            largestNumber = 500000;
        }
        else if (i == 4)
        {
            DS = testData4;
            largestNumber = 1000000;
        }
        long long averageInsert = 0;
        long long averageDelete = 0;
        long long averageSearch = 0;
        std::cout << "Data Set " << i << ":" << std::endl;
        for (int j = 1; j <= 5; j++)
        {
            DoublyLinkedList<int>* ADT = new DoublyLinkedList<int>();
            std::shuffle(DS.begin(), DS.end(), rng);

            // Insert Part
            begin = std::chrono::steady_clock::now();
            for (int i : DS)
            {
                ADT->insert(i);
            }
            end = std::chrono::steady_clock::now();
            averageInsert += std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count();
            // Delete Part
            begin = std::chrono::steady_clock::now();
            for (int i : DS)
            {
                if (i < 0)
                    ADT->remove(i);
            }
            end = std::chrono::steady_clock::now();
            averageDelete += std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count();
            // Search Part
            begin = std::chrono::steady_clock::now();
            ADT->searchTiming(largestNumber);
            end = std::chrono::steady_clock::now();
            averageSearch += std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count();
        }
        // It gives the average time of the operations in 5 shuffles
        std::cout << "Insert: " << averageInsert / 5 << "[ns]    Delete: " << averageDelete / 5 << "[ns]    Search: " << averageSearch / 5 << "[ns]" << std::endl;
    }
    std::cout << "\n" << std::endl;
    
    
    std::cout << "Singly Linked list:" << std::endl;
    for (int i = 1; i <= 4; i++)
    {
        std::vector<int> DS;    // DS refer to test data set
        int largestNumber;
        if (i == 1)
        {
            DS = testData1;
            largestNumber = 1000;
        }
        else if (i == 2)
        {
            DS = testData2;
            largestNumber = 100000;
        }
        else if (i == 3)
        {
            DS = testData3;
            largestNumber = 500000;
        }
        else if (i == 4)
        {
            DS = testData4;
            largestNumber = 1000000;
        }
        long long averageInsert = 0;
        long long averageDelete = 0;
        long long averageSearch = 0;
        std::cout << "Data Set " << i << ":" << std::endl;
        for (int j = 1; j <= 5; j++)
        {
            SinglyLinkedList<int>* ADT = new SinglyLinkedList<int>();
            std::shuffle(DS.begin(), DS.end(), rng);

            // Insert Part
            begin = std::chrono::steady_clock::now();
            for (int i : DS)
            {
                ADT->insert(i);
            }
            end = std::chrono::steady_clock::now();
            averageInsert += std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count();
            // Delete Part
            begin = std::chrono::steady_clock::now();
            for (int i : DS)
            {
                if (i < 0)
                    ADT->remove(i);
            }
            end = std::chrono::steady_clock::now();
            averageDelete += std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count();
            // Search Part
            begin = std::chrono::steady_clock::now();
            ADT->searchTiming(largestNumber);
            end = std::chrono::steady_clock::now();
            averageSearch += std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count();
        }
        // It gives the average time of the operations in 5 shuffles
        std::cout << "Insert: " << averageInsert  << "[ns]    Delete: " << averageDelete  << "[ns]    Search: " << averageSearch  << "[ns]" << std::endl;
    }
    
}