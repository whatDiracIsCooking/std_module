/**
 * @file test_queue.cpp
 * @brief Comprehensive tests for std_module.queue
 */

import std_module.queue;

#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <deque>
#include <list>
#include <functional>

// Test basic queue operations
void test_queue_basic()
{
    std::cout << "Testing basic queue operations...\n";

    std::queue<int> q;

    // Test empty queue
    assert(q.empty());
    assert(q.size() == 0);
    std::cout << "  ✓ Empty queue creation\n";

    // Test push and size
    q.push(10);
    q.push(20);
    q.push(30);
    assert(q.size() == 3);
    assert(!q.empty());
    std::cout << "  ✓ Push and size: " << q.size() << " elements\n";

    // Test front and back
    assert(q.front() == 10);
    assert(q.back() == 30);
    std::cout << "  ✓ Front: " << q.front() << ", Back: " << q.back() << "\n";

    // Test pop
    q.pop();
    assert(q.size() == 2);
    assert(q.front() == 20);
    std::cout << "  ✓ Pop operation, new front: " << q.front() << "\n";

    // Pop remaining elements
    q.pop();
    q.pop();
    assert(q.empty());
    std::cout << "  ✓ All elements popped, queue is empty\n";
}

// Test queue with different types
void test_queue_types()
{
    std::cout << "\nTesting queue with different types...\n";

    // String queue
    std::queue<std::string> sq;
    sq.push("Hello");
    sq.push("World");
    assert(sq.front() == "Hello");
    assert(sq.back() == "World");
    std::cout << "  ✓ String queue: " << sq.front() << " " << sq.back() << "\n";

    // Double queue
    std::queue<double> dq;
    dq.push(3.14);
    dq.push(2.71);
    assert(dq.front() == 3.14);
    std::cout << "  ✓ Double queue: " << dq.front() << "\n";
}

// Test queue with different underlying containers
void test_queue_containers()
{
    std::cout << "\nTesting queue with different underlying containers...\n";

    // Queue with deque (default)
    std::queue<int, std::deque<int>> q_deque;
    q_deque.push(1);
    q_deque.push(2);
    assert(q_deque.front() == 1);
    std::cout << "  ✓ Queue with deque container\n";

    // Queue with list
    std::queue<int, std::list<int>> q_list;
    q_list.push(10);
    q_list.push(20);
    assert(q_list.front() == 10);
    std::cout << "  ✓ Queue with list container\n";
}

// Test queue swap
void test_queue_swap()
{
    std::cout << "\nTesting queue swap...\n";

    std::queue<int> q1, q2;
    q1.push(1);
    q1.push(2);
    q2.push(10);
    q2.push(20);
    q2.push(30);

    assert(q1.size() == 2);
    assert(q2.size() == 3);

    // Using std::swap
    std::swap(q1, q2);

    assert(q1.size() == 3);
    assert(q2.size() == 2);
    assert(q1.front() == 10);
    assert(q2.front() == 1);
    std::cout << "  ✓ Queue swap: q1.size()=" << q1.size() << ", q2.size()=" << q2.size() << "\n";

    // Using member swap
    q1.swap(q2);
    assert(q1.size() == 2);
    assert(q2.size() == 3);
    std::cout << "  ✓ Member swap: q1.size()=" << q1.size() << ", q2.size()=" << q2.size() << "\n";
}

// Test basic priority_queue operations
void test_priority_queue_basic()
{
    std::cout << "\nTesting basic priority_queue operations...\n";

    std::priority_queue<int> pq;

    // Test empty
    assert(pq.empty());
    assert(pq.size() == 0);
    std::cout << "  ✓ Empty priority_queue creation\n";

    // Test push (max heap by default)
    pq.push(30);
    pq.push(10);
    pq.push(50);
    pq.push(20);

    assert(pq.size() == 4);
    assert(!pq.empty());
    std::cout << "  ✓ Push operations, size: " << pq.size() << "\n";

    // Test top (should be max element: 50)
    assert(pq.top() == 50);
    std::cout << "  ✓ Top element (max): " << pq.top() << "\n";

    // Test pop (removes max element)
    pq.pop();
    assert(pq.size() == 3);
    assert(pq.top() == 30);
    std::cout << "  ✓ After pop, new top: " << pq.top() << "\n";

    // Pop all elements
    pq.pop();
    pq.pop();
    pq.pop();
    assert(pq.empty());
    std::cout << "  ✓ All elements popped, priority_queue is empty\n";
}

// Test priority_queue with custom comparator (min heap)
void test_priority_queue_min_heap()
{
    std::cout << "\nTesting priority_queue as min heap...\n";

    std::priority_queue<int, std::vector<int>, std::greater<int>> min_pq;

    min_pq.push(30);
    min_pq.push(10);
    min_pq.push(50);
    min_pq.push(20);

    // Top should be minimum element
    assert(min_pq.top() == 10);
    std::cout << "  ✓ Top element (min): " << min_pq.top() << "\n";

    min_pq.pop();
    assert(min_pq.top() == 20);
    std::cout << "  ✓ After pop, new top (min): " << min_pq.top() << "\n";
}

// Test priority_queue with different types
void test_priority_queue_types()
{
    std::cout << "\nTesting priority_queue with different types...\n";

    // String priority_queue
    std::priority_queue<std::string> pq_str;
    pq_str.push("apple");
    pq_str.push("zebra");
    pq_str.push("banana");

    // Top should be "zebra" (lexicographically largest)
    assert(pq_str.top() == "zebra");
    std::cout << "  ✓ String priority_queue, top: " << pq_str.top() << "\n";

    // Double priority_queue
    std::priority_queue<double> pq_dbl;
    pq_dbl.push(3.14);
    pq_dbl.push(2.71);
    pq_dbl.push(1.41);

    assert(pq_dbl.top() == 3.14);
    std::cout << "  ✓ Double priority_queue, top: " << pq_dbl.top() << "\n";
}

// Test priority_queue swap
void test_priority_queue_swap()
{
    std::cout << "\nTesting priority_queue swap...\n";

    std::priority_queue<int> pq1, pq2;
    pq1.push(1);
    pq1.push(2);
    pq2.push(10);
    pq2.push(20);
    pq2.push(30);

    assert(pq1.size() == 2);
    assert(pq2.size() == 3);

    // Using std::swap
    std::swap(pq1, pq2);

    assert(pq1.size() == 3);
    assert(pq2.size() == 2);
    std::cout << "  ✓ Priority_queue swap: pq1.size()=" << pq1.size() << ", pq2.size()=" << pq2.size() << "\n";
}

// Custom type for testing
struct Task
{
    int priority;
    std::string name;

    bool operator<(const Task& other) const
    {
        return priority < other.priority;  // Higher priority values come first
    }
};

// Test priority_queue with custom type
void test_priority_queue_custom_type()
{
    std::cout << "\nTesting priority_queue with custom type...\n";

    std::priority_queue<Task> task_queue;

    task_queue.push({1, "Low priority task"});
    task_queue.push({10, "High priority task"});
    task_queue.push({5, "Medium priority task"});

    assert(task_queue.top().priority == 10);
    assert(task_queue.top().name == "High priority task");
    std::cout << "  ✓ Top task: priority=" << task_queue.top().priority
              << ", name=\"" << task_queue.top().name << "\"\n";

    task_queue.pop();
    assert(task_queue.top().priority == 5);
    std::cout << "  ✓ After pop, next task: priority=" << task_queue.top().priority << "\n";
}

// Test queue comparison operators
void test_queue_comparison()
{
    std::cout << "\nTesting queue comparison operators...\n";

    std::queue<int> q1, q2, q3;

    q1.push(1);
    q1.push(2);
    q1.push(3);

    q2.push(1);
    q2.push(2);
    q2.push(3);

    q3.push(1);
    q3.push(2);
    q3.push(4);

    // Test equality
    assert(q1 == q2);
    assert(!(q1 == q3));
    std::cout << "  ✓ Equality operator\n";

    // Test inequality
    assert(!(q1 != q2));
    assert(q1 != q3);
    std::cout << "  ✓ Inequality operator\n";

    // Test less than
    assert(q1 < q3);
    assert(!(q3 < q1));
    std::cout << "  ✓ Less than operator\n";

    // Test less than or equal
    assert(q1 <= q2);
    assert(q1 <= q3);
    std::cout << "  ✓ Less than or equal operator\n";

    // Test greater than
    assert(q3 > q1);
    assert(!(q1 > q3));
    std::cout << "  ✓ Greater than operator\n";

    // Test greater than or equal
    assert(q1 >= q2);
    assert(q3 >= q1);
    std::cout << "  ✓ Greater than or equal operator\n";
}

// Test queue emplace (C++11)
void test_queue_emplace()
{
    std::cout << "\nTesting queue emplace...\n";

    std::queue<std::string> q;
    q.emplace("constructed");
    q.emplace("in");
    q.emplace("place");

    assert(q.front() == "constructed");
    assert(q.size() == 3);
    std::cout << "  ✓ Emplace operations, front: " << q.front() << "\n";
}

// Test priority_queue emplace
void test_priority_queue_emplace()
{
    std::cout << "\nTesting priority_queue emplace...\n";

    std::priority_queue<Task> pq;
    pq.emplace(5, "Task A");
    pq.emplace(10, "Task B");
    pq.emplace(3, "Task C");

    assert(pq.top().priority == 10);
    assert(pq.top().name == "Task B");
    std::cout << "  ✓ Emplace operations, top task: " << pq.top().name << "\n";
}

int main()
{
    std::cout << "=== Testing std_module.queue ===\n\n";

    try
    {
        // Queue tests
        test_queue_basic();
        test_queue_types();
        test_queue_containers();
        test_queue_swap();
        test_queue_comparison();
        test_queue_emplace();

        // Priority queue tests
        test_priority_queue_basic();
        test_priority_queue_min_heap();
        test_priority_queue_types();
        test_priority_queue_swap();
        test_priority_queue_custom_type();
        test_priority_queue_emplace();

        std::cout << "\n=== All tests passed! ===\n";
        return 0;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Test failed with exception: " << e.what() << "\n";
        return 1;
    }
}
