#include "pch.h"
#include "CppUnitTest.h"
#include "../SingleLinkedList/List.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ListTests
{
	TEST_CLASS(ListTests)
	{
	public:
		

		TEST_METHOD(ToString_ValidData_Success)
		{
			List list{1,2,3,4,5,6};
			Assert::IsTrue(list.to_string() == "[ 1 2 3 4 5 6 ]");
		}

		TEST_METHOD(EqualOperator_ValidData_Success)
		{
			List list_1{ 1,2,3,4,5,6 };
			List list_2{ 1,2,3,4,5,6 };
			List list_3{ 1,2,3,4 };
			Assert::IsTrue(list_1 == list_2 && list_1 != list_3);
		}

		TEST_METHOD(Push_ValidData_Success)
		{
			List list{1,2,3,4,5};
			list.push(6);
			List expected{ 6,1,2,3,4,5};
			Assert::IsTrue(list == expected);
		}

		TEST_METHOD(Pop_ValidData_Success)
		{
			List list{ 1,2,3,4,5 };
			list.pop();
			List expected{ 2,3,4,5};
			Assert::IsTrue(list == expected);
		}

		TEST_METHOD(HasElements_ValidData_Success)
		{
			List list{ 1,2,3,4,5 };
			Assert::IsTrue(list.has_elements());
		}

		TEST_METHOD(OutputOperator_ValidData_Success)
		{
			std::stringstream sstring;
			List list = List({ 1,2,3,4 });
			sstring << list;
			Assert::AreEqual(sstring.str(), list.to_string());
		}

		TEST_METHOD(CopyOperator_ValidData_Success)
		{
			List list_1{ 1,2,3,4,5 };
			List list_2{ 1,5,10,15 };
			list_1 = list_2;
			Assert::IsTrue(list_1 == list_2);
		}

		TEST_METHOD(MoveOperator_ValidData_Success)
		{
			List list_1{ 1,2,3,4,5 };
			List list_2{ 1,5,10,15 };
			list_1 = std::move(list_2);
			List expected{ 1,5,10,15 };
			Assert::IsTrue(list_1 == expected);
		}

		TEST_METHOD(Find_ValidData_Success)
		{
			List vector_1{ 1, 2,3,4,5 };
			Assert::IsTrue(vector_1.find(3) == true && vector_1.find(10) == false);
		}
	};
}
