//
// Created by Chris O'Keefe on 6/23/2020.
//

#include <iostream>
#include <Foo.h>
#include "GenericFunctionNode.h"
#include "gtest/gtest.h"

/**
 * This class is used for testing the GenericFunctionNode using GTest.
 *
 * Must test manually since the operations provide no return value.
 */


using namespace std;
using namespace std::placeholders;

TEST(ChainNode, TemplateFunctionTest) {
    Foo foo;
    function<void()> func = std::bind(&Foo::allocateMemory, foo);
    IFunctionNode *chainNode = new GenericFunctionNode(func);
    chainNode->invokeFunction();
}