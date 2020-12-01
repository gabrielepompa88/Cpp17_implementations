#ifndef TESTS_H
#define TESTS_H

#include "SharedPtr.h"
#include "WeakPtr.h"
#include "Resource.h"
#include "CircularDependencies.h"

void test_nested_blocks();
void test_resource_reassignment();
void test_weak_references();
void test_lock();
void test_circular_dependencies();

#endif
