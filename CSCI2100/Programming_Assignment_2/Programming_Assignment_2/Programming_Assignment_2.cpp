#include <iostream>
#include <vector>
#include <random>
#include <numeric>
#include <string>
#include <climits> 
#include <cmath>
#include <fstream>
#include <string>
#include <sstream> 
#include <chrono>
#include "MinHeap.cpp"

using namespace std;

int main()
{    
    cout << "Choose your operation:" << endl;
    cout << "Input 1 to use random generation (for doing heap sort)" << endl;
    cout << "Input 2 to use random generation (for finding K-th Minimum Difference" << endl;
    cout << "Input 3 to read file and do answer comparision:" << endl;

    int userInput;
    cout << "Users input: ";
    cin >> userInput; 

    cout << "=======================================================================================\n" << endl;

    chrono::steady_clock::time_point begin;
    chrono::steady_clock::time_point end;

    if (userInput == 1)
    {
        random_device rd;
        mt19937 gen(rd());


        bool isSorted = true;

        for (int i = 0; i < 10000; i++)
        {
            if (i == 0)                     // empty arrays
            {
                vector<int> empty(0);

                cout << "Test " << i + 1 << ":" << endl;
                cout << "*********" << endl;

                cout << "Length of the vector: " << empty.size() << endl;

                MinHeap* tempheap = new MinHeap(empty.size());

                begin = std::chrono::steady_clock::now();
                tempheap->heapSort(empty);
                end = std::chrono::steady_clock::now();

                cout << "Time used: " << chrono::duration_cast<chrono::nanoseconds> (end - begin).count() << "[ns]" << endl;
                cout << endl << "=======================================================================================\n" << endl;

                continue;
            }

            uniform_int_distribution<> v_size(0,100000); // v_size stands for the size of vector
            vector<int> testData(v_size(gen));          // Generate an array with size 

            cout << "Test " << i + 1 << ":" << endl;
            cout << "*********" << endl;

            cout << "Length of the vector: " << testData.size() << endl;
            
            if (i < 500)                        // arrays with all identical elements
            {
                uniform_int_distribution<> ranNumGen(INT32_MIN + 1, INT32_MAX);
                int ranNum = ranNumGen(gen);

                for (int j = 0; j < testData.size(); j++)
                {
                    testData[j] = ranNum;
                }
            }
            else if (i >= 500 && i <= 2000)           // arrays are sorted in reversed order
            {
                uniform_int_distribution<> ranNumGen(INT32_MIN + 1, INT32_MAX);
                int ranNum = ranNumGen(gen);
                iota(testData.begin(), testData.end(), ranNum);
                reverse(testData.begin(), testData.end());
            }
            else if (i > 2000)                       // array that can contain negative numbers, random arrays
            {
                uniform_int_distribution<> upperLimitGen(INT32_MIN + 1, INT32_MAX);         // Generating an upperlimit for the array
                int upperLimit = upperLimitGen(gen);
                uniform_int_distribution<> lowerLimitGen(INT32_MIN + 1, upperLimit);        // Generating an lowerlimit for the array
                int lowerLimit = lowerLimitGen(gen);
                //cout << "Range of the vector: [" << lowerLimit << ", " << upperLimit << "]" << endl;    // Value of each elements will be generated between this 
                uniform_int_distribution<> v_element(lowerLimit, upperLimit);           // Generating an random value base on the upperlimit and lowerlimit
                for (int j = 0; j < testData.size(); j++)
                {
                    testData[j] = v_element(gen);
                } 
            }

            MinHeap* tempheap = new MinHeap(testData.size());

            begin = std::chrono::steady_clock::now();
            tempheap->heapSort(testData);
            end = std::chrono::steady_clock::now();

            cout << "Time used: " << chrono::duration_cast<chrono::nanoseconds> (end - begin).count() << "[ns]" << endl;
            cout << endl << "=======================================================================================\n" << endl;

            for (int j = 0; j < testData.size(); j++)
            {
                //cout << testData[j] << " ";
                if (j != testData.size() - 1)
                {
                    if (testData[j] > testData[j + 1])
                    {
                        isSorted = false;
                        break;
                    }
                }
            }

            if (!isSorted)
                break;
        }

        if (isSorted)
            cout << "All random generated arrays are sorted" << endl;
        else
            cout << "Some random generated array is not sorted" << endl;


    }
    else if (userInput == 2)
    {
        random_device rd;                           
        mt19937 gen(rd());                          

        for (int i = 0; i < 100; i++)
        {
            uniform_int_distribution<> v_size(0, 1000); // v_size stands for the size of vector
            vector<int> testData(v_size(gen));          // Generate an array with size 

            cout << "Test " << i + 1 << ":" << endl;
            cout << "*********" << endl;

            cout << "Length of the vector: " << testData.size() << endl;

            uniform_int_distribution<> upperLimitGen(INT32_MIN + 1, INT32_MAX);         // May gives negative numbers
            int upperLimit = upperLimitGen(gen);
            uniform_int_distribution<> lowerLimitGen(INT32_MIN + 1, upperLimit);
            int lowerLimit = lowerLimitGen(gen);

            cout << "Range of the vector: [" << lowerLimit << ", " << upperLimit << "]" << endl;    // Value of each elements will be generated between this range

            uniform_int_distribution<> v_element(lowerLimit, upperLimit);

            if (i < 10)              
            {
                for (int j = 0; j < testData.size(); j++)
                {
                    testData[j] = v_element(gen) % 100;                  // After %100, duplicated numbers input can be generated
                }
            }
            else                                                         // For i >= 5 just do random insert
            {
                for (int j = 0; j < testData.size(); j++)               
                {
                    testData[j] = v_element(gen);
                }
            }

            unsigned long long KthHeapSize = 0;

            for (int i = 1; i < testData.size(); i++)
            {
                KthHeapSize += i;
            }

            cout << "Size of heap for finding K-th Minimum: " << KthHeapSize << endl;

            if (KthHeapSize == 0)
                cout << "Size of vector is "<< testData.size() << "! Kth Minimum value cannot be determined!" << endl;
            else
            {
                uniform_int_distribution<> KthMinGen(1, KthHeapSize);
                int K = KthMinGen(gen);

                cout << "Value of K: " << K << endl;

                MinHeap* tempheap = new MinHeap(KthHeapSize);
                int KthMin = tempheap->KthMinimum(testData, K);

                cout << "K-th Minimum Difference = " << KthMin << endl;
            }
            
            cout << endl << "=======================================================================================\n" << endl;
        }
    }
    else if (userInput == 3)
    {
        ifstream readInput;

        char separator = ' ';                   // sperator to separe a string into different elements
        string line;                            // lines being read in the text file
            
        vector<int> answer;                     // arrays that used to stored the answer of corresponding lines

        readInput.open("input.txt");

        while (readInput)
        {
            while (getline(readInput, line))
            {
                stringstream ss(line);
                string token;
                vector<int> readDataSet;
                
                int K;

                int i = 0;
                while (getline(ss, token, separator))
                {
                    if (i == 0)
                        K = stoi(token);                        // The first element is the value of K
                    else 
                        readDataSet.push_back(stoi(token));     // Others elements are the array
                    
                    i++;
                }

                unsigned long long KthHeapSize = 0;

                for (int i = 1; i < readDataSet.size(); i++)
                {
                    KthHeapSize += i;                                   // Calcuate the size of heap that need to store all differences
                }

                MinHeap* tempheap = new MinHeap(KthHeapSize);           // Create a binary heap with KthHeapSize
                int KthMin = tempheap->KthMinimum(readDataSet, K);      // Find the K-th Minimum Difference

                cout << KthMin << endl;                                 // Output the K-th Minimum Differnece (for testing)
                answer.push_back(KthMin);                               // Store the answer into an array
            }
        }

        readInput.close();              // Close the input file

        ifstream readOutput;
        int line_no = 0;
        int temp;
        bool isSame = true;                 

        readOutput.open("output.txt");  // Start reading the given "output.txt"

        while (!readOutput.eof())
        {
            readOutput >> temp;
            if (temp != answer[line_no++])  // Compare the "output.txt" line by line with the array
            {
                isSame = false;             // If one answer is detected as not the same as the "output.txt"
                break;                      // Exit the loop and change isSame to false
            }   
        }

        if (isSame)
            cout << "\nYour answers are correct!" << endl;
        else
            cout << "There are some bugs in your answers." << endl;

        readOutput.close();
    }

    return 0;
}