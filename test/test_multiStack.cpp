#include "MultiStack.h"
#include <gtest.h>

TEST(TMultiStack, can_create_MultiStack_with_positive_length)
{
	ASSERT_NO_THROW(TMultiStack<int> m(2, 1));
}

TEST(TMultiStack, cant_create_MultiStack_with_null)
{
	ASSERT_ANY_THROW(TMultiStack<int> m(0));
}

TEST(TMultiStack, check_empty_MultiStack)
{
	TMultiStack<int> m(2, 2);

	EXPECT_EQ(true, m.IsEmpty(1));
}

TEST(TMultiStack, check_for_non_existent_empty_MultiStack)
{
	TMultiStack<int> m(2, 1);

	ASSERT_ANY_THROW(m.IsEmpty(4));
}

TEST(TMultiStack, check_negative_empty_MultiStack)
{
	TMultiStack<int> m(2, 1);

	ASSERT_ANY_THROW(m.IsEmpty(-5));
}

TEST(TMultiStack, check_IsFull_MultiStack)
{
	TMultiStack<int> m(2, 2);

	EXPECT_EQ(false, m.IsFull(1));
}

TEST(TMultiStack, check_for_non_existent_IsFull_MultiStack)
{
	TMultiStack<int> m(2, 1);

	ASSERT_ANY_THROW(m.IsFull(4));
}

TEST(TMultiStack, check_negative_IsFull_MultiStack)
{
	TMultiStack<int> m(2, 1);

	ASSERT_ANY_THROW(m.IsFull(-5));
}

TEST(TMultiStack, can_push_with_mem)
{
	TMultiStack<int> m(2, 2);

	ASSERT_NO_THROW(m.Push(10, 1));
}

TEST(TMultiStack, cant_push_with_no_mem)
{
	TMultiStack<int> m(2, 1);

	ASSERT_ANY_THROW(m.Push(10, 4));
}

TEST(TMultiStack, can_copy_stack)
{
	TMultiStack<int> m1(2, 2);
	m1.Push(10, 1);

	ASSERT_NO_THROW(TMultiStack<int> m2(m1));
}


TEST(TMultiStack, can_assing_stack)
{
	TMultiStack<int> m1(2, 2);
	m1.Push(10, 1);
	TMultiStack<int> m2(2, 2);
	m2 = m1;

	EXPECT_EQ(10, m2.Pop(1));
}

TEST(TMultiStack, can_get)
{
	TMultiStack<int> m(2, 2);
	m.Push(10, 1);

	ASSERT_NO_THROW(m.Pop(1));
}

TEST(TMultiStack, cant_get_nonexistent)
{
	TMultiStack<int> m(2, 2);
	m.Push(10, 1);

	ASSERT_ANY_THROW(m.Pop(-4));
}

TEST(TMultiStack, cant_get_negative)
{
	TMultiStack<int> m1(2, 2);
	m1.Push(10, 1);

	ASSERT_ANY_THROW(m1.Pop(4));
}

TEST(TMultiStack, can_GetSize)
{
	TMultiStack<int> m1(2, 2);

	ASSERT_NO_THROW(m1.GetSize());
}

TEST(TMultiStack, can_Resize)
{
	TMultiStack<int> m1(1, 1);
	m1.Push(10, 0);

	ASSERT_NO_THROW(m1.Resize(5, 0));
}

TEST(TMultiStack, can_write_file)
{
	TMultiStack<int> m(15, 3);
	m.Push(11, 0);
	m.Push(12, 1);
	m.Push(12, 1);
	m.Push(12, 1);
	m.Push(12, 1);
	m.Push(12, 1);

	m.Push(15, 1);
	ASSERT_NO_THROW(m.WriteFile());
}

TEST(TMultiStack, can_read_file)
{
	TMultiStack<int> m;
	ASSERT_NO_THROW(m.ReadFile());
}

TEST(TMultiStack, cant_Resize_negative)
{
	TMultiStack<int> m1(1, 1);
	m1.Push(10, 0);

	ASSERT_ANY_THROW(m1.Resize(-5, 0));
}

TEST(TMultiStack, can_StackRelocation)
{
	TMultiStack<int> m(9, 3);
	m.Push(11, 0);
	m.Push(1, 1);
	m.Push(1, 1);
	m.Push(1, 1);

	ASSERT_NO_THROW(m.Push(15, 1));
}

