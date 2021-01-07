/**
 * @file FunctionNodeTests.cpp
 *
 * @brief This class is used for unit testing the all FunctionNodes that inherit from IFunctionNode using GTest.
 *
 * @ingroup Testing
 *
 */

#include "gtest/gtest.h"

#include "OperationManagerTestingClass.h"
#include "Simulation/Core/FunctionNodes/GenericFunctionNode.h"

using namespace std;

/// Generic Function Node Tests
TEST(GenericFunctionNode, TemplateFunctionTest) {
    Foo foo;
    function<void()> func = std::bind(&Foo::loadParameters, foo);
    IFunctionNode *chainNode = new GenericFunctionNode(Operations::op::loadParameters, func);
    ASSERT_TRUE(chainNode->invokeFunction(Operations::op::loadParameters));
}