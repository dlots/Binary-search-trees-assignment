#include "Graphs.h"

#include "../src/trees/AVLTree.h"
#include "../src/trees/Treap.h"
#include "../src/trees/SplayTree.h"
#include <set>

#include "Timer.h"
#include "../src/util/RandomGenerator.h"
#include <fstream>
#include <iostream>

void measureSearch()
{
    ofstream searchFile("search.csv");
    if (!searchFile)
    {
        return;
    }

    searchFile << "n,avl,splay,treap,rb" << endl;

    AVLTree avl;
    SplayTree splay;
    Treap treap;
    std::set<uint64_t> rb;

    vector<uint64_t> numbers;
    RandomNumberGenerator::getUniqueRandomNumbers(N_end, numbers);

    Timer t;
    for (size_t n = 0; n < N_end; ++n)
    {
        bool write = (n % step == 0);
        vector<uint64_t> search_numbers;
        if (write) {
            RandomNumberGenerator::getUniqueRandomNumbers(N_end, search_numbers);
            cout << n << endl;
            if (write) searchFile << n << ",";
        }

        avl.insert(numbers[n]);
        if (write) {
            t.reset();
            for (size_t i = 0; i < simultaneous; ++i) {
                avl.search(search_numbers[i]);
            }
            if (write) searchFile << t.elapsed() << ",";
        }

        splay.insert(numbers[n]);
        if (write) {
            t.reset();

            for (size_t i = 0; i < simultaneous; ++i) {
                splay.search(search_numbers[i]);
            }
            if (write) searchFile << t.elapsed() << ",";
        }

        treap.insert(numbers[n]);
        if (write) {
            t.reset();
            for (size_t i = 0; i < simultaneous; ++i) {
                treap.search(search_numbers[i]);
            }
            if (write) searchFile << t.elapsed() << ",";
        }

        rb.insert(numbers[n]);
        if (write)
        {
            t.reset();
            for (size_t i = 0; i < simultaneous; ++i) {
                rb.find(search_numbers[i]);
            }
            if (write) searchFile << t.elapsed() << endl;
        }
    }

    searchFile.close();
}

void measureInsert()
{
    ofstream insertFile("insert.csv");
    if (!insertFile)
    {
        return;
    }

    insertFile << "n,avl,splay,treap,rb" << endl;

    AVLTree avl;
    SplayTree splay;
    Treap treap;
    std::set<uint64_t> rb;

    vector<uint64_t> numbers;
    RandomNumberGenerator::getUniqueRandomNumbers(N_end, numbers);

    Timer t;
    for (size_t n = 0; n < N_end; ++n)
    {
        size_t n_saved = n;

        bool write = (n % step == 0);
        if (write) cout << n << endl;
        if (write) insertFile << n << ",";

        if (write) t.reset();
        for (size_t i = 0; i < simultaneous; ++i, ++n)
        {
            avl.insert(numbers[n]);
        }
        if (write) insertFile << t.elapsed() << ",";
        n = n_saved;

        if (write) t.reset();
        for (size_t i = 0; i < simultaneous; ++i, ++n)
        {
            splay.insert(numbers[n]);
        }
        if (write) insertFile << t.elapsed() << ",";
        n = n_saved;

        if (write) t.reset();
        for (size_t i = 0; i < simultaneous; ++i, ++n)
        {
            treap.insert(numbers[n]);
        }
        if (write) insertFile << t.elapsed() << ",";
        n = n_saved;

        if (write) t.reset();
        for (size_t i = 0; i < simultaneous; ++i, ++n)
        {
            rb.insert(numbers[n]);
        }
        if (write) insertFile << t.elapsed() << endl;
        --n;
    }

    insertFile.close();
}

void measureRemove()
{
    ofstream removeFile("remove.csv");
    if (!removeFile)
    {
        return;
    }

    removeFile << "n,avl,splay,treap,rb" << endl;

    AVLTree avl;
    SplayTree splay;
    Treap treap;
    std::set<uint64_t> rb;

    vector<uint64_t> numbers;
    RandomNumberGenerator::getUniqueRandomNumbers(N_end, numbers);

    Timer t;
    for (size_t n = 0; n < N_end; ++n)
    {
        bool write = (n % step == 0) && (n > 0);
        vector<uint64_t> search_numbers;
        if (write) {
            RandomNumberGenerator::getUniqueRandomNumbers(n, search_numbers);
            cout << n << endl;
            if (write) removeFile << n << ",";
        }

        /*avl.insert(numbers[n]);
        if (write) {
            t.reset();
            for (size_t i = 0; i < simultaneous; ++i) {
                avl.remove(search_numbers[i]);
            }
            if (write) removeFile << t.elapsed() << ",";
            for (size_t i = 0; i < simultaneous; ++i) {
                avl.insert(search_numbers[i]);
            }
        }*/

        splay.insert(numbers[n]);
        if (write) {
            t.reset();

            for (size_t i = 0; i < simultaneous; ++i) {
                splay.remove(search_numbers[i]);
            }
            if (write) removeFile << t.elapsed() << ",";
            for (size_t i = 0; i < simultaneous; ++i) {
                splay.insert(search_numbers[i]);
            }
        }

        treap.insert(numbers[n]);
        if (write) {
            t.reset();
            for (size_t i = 0; i < simultaneous; ++i) {
                treap.remove(search_numbers[i]);
            }
            if (write) removeFile << t.elapsed() << ",";
            for (size_t i = 0; i < simultaneous; ++i) {
                treap.insert(search_numbers[i]);
            }
        }

        rb.insert(numbers[n]);
        if (write)
        {
            t.reset();
            for (size_t i = 0; i < simultaneous; ++i) {
                rb.erase(search_numbers[i]);
            }
            if (write) removeFile << t.elapsed() << endl;
            for (size_t i = 0; i < simultaneous; ++i) {
                rb.insert(search_numbers[i]);
            }
        }
    }

    removeFile.close();
}

void launchMeasure()
{
    //measureSearch();
    //measureInsert();
    //measureRemove();
}