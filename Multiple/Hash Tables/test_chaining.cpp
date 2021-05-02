#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>
#include <thread>
#include <chrono>
#include <future>
#include <memory>
#include "Chaining.h"
using namespace std;


bool timeOut;
promise<bool> done;

void timer(future<bool> done_future)
{
    std::chrono::seconds span (3);
    if(done_future.wait_for(span) == std::future_status::timeout)
    {
        timeOut = true;
    }
}

double test(vector<string> allWords, vector<string> queries, promise<bool> done_future)
{
    using namespace std::chrono;
    
    shared_ptr<HashC> myTable(new HashC(202001));
    double score = 0;
    high_resolution_clock::time_point timeStart = high_resolution_clock::now();

    cout << "Starting Tests" << endl;
    cout << "\nTesting Insert:    ";

    // Inserting entries into the hash table
    for(int i = 0; i < allWords.size(); i++)
    {
        myTable->insertWord(allWords[i]);
        if(timeOut)
        {
            cout << "Failed! The test timed out." << endl;
            return score;
        }
    }

    score += 1.5;
    cout << "Passed!" << endl;
    cout << "Testing Lookup:    ";

    // Searching entries from the hash table
    for(int i = 0; i < allWords.size(); i++)
    {
        if ( (myTable->lookupWord(allWords[i]) != NULL) &&  (myTable->lookupWord(allWords[i])->value != allWords[i]) )
        {
            cout << "Failed!" << endl;
            return score;
        }
        
        if(timeOut)
        {
            cout << "Failed! The test timed out." << endl;
            return score;
        }
    }

    score += 1.5;
    cout << "Passed!" << endl;
    cout << "Testing Delete:    ";

    // Deleting entries from the hash table
    for(int i = 0; i < queries.size(); i++)
    {
        myTable->deleteWord(queries[i]);
        if(timeOut)
        {
            cout << "Failed! The test timed out." << endl;
            return score;
        }
    }

    for(int i = 0; i < queries.size(); i++)
    {
        if (myTable->lookupWord(queries[i]) != NULL)
        {
            cout << "Failed!" << endl;
            return score;
        }

        if(timeOut)
        {
            cout << "Failed! The test timed out." << endl;
            return score;
        }
    }

    score += 2;
    cout << "Passed!" << endl;

    done_future.set_value(true);
    high_resolution_clock::time_point timeEnd = high_resolution_clock::now();
    duration<double> totalTime = duration_cast<duration<double>>(timeEnd - timeStart);

    cout << "\nTest Passed in: " << totalTime.count() << " seconds." << endl;
    return score;
}

int main(){

    vector<string> allWords;
    vector<string> queries;

    srand(time(NULL));
    ifstream file;
    file.open("words.txt");
    
    cout << "Loading the file: ";
    string temp;

    while(!file.eof())
    {
        file >> temp;
        allWords.push_back(temp);
        int x = rand() % 5;
        if (x < 2)
        {
            queries.push_back(temp);
        }
    }

    file.close();

    cout << allWords.size() << " words loaded." << endl;
    timeOut = false;
    
    future<bool> done_future = done.get_future();
    thread first (timer, move(done_future));
    double score = test(allWords, queries, move(done));
    first.join();

    cout << "Total Score: " << score << "/5" << endl;

    return 0;
}