// Copyright 2021 Gushchin Artem

#include <gtest/gtest.h>

#include <tuple>

#include "include/bit_array.h"

TEST(Bit_Array_Test, Can_Create_Bitfield_With_Positive_Length) {
    ASSERT_NO_THROW(BitArray bf(3));
}

TEST(Bit_Array_Test, can_get_length) {
    BitArray bf(3);

    EXPECT_EQ(3, bf.GetLength());
}

TEST(Bit_Array_Test, New_Bitfield_Is_Set_To_Zero) {
    BitArray bf(100);

    int sum = 0;
    for (int i = 0; i < bf.GetLength(); i++) {
        sum += bf.GetBit(i);
    }

    EXPECT_EQ(0, sum);
}

TEST(Bit_Array_Test, Can_Set_Bit) {
    BitArray bf(10);

    EXPECT_EQ(0, bf.GetBit(3));

    bf.SetBit(3);
    EXPECT_NE(0, bf.GetBit(3));
}

TEST(Bit_Array_Test, Can_Clear_Bit) {
    BitArray bf(10);

    int bitIdx = 3;

    bf.SetBit(bitIdx);
    EXPECT_NE(0, bf.GetBit(bitIdx));

    bf.ClrBit(bitIdx);
    EXPECT_EQ(0, bf.GetBit(bitIdx));
}

TEST(Bit_Array_Test, Throws_When_Create_Bitfield_With_Negative_Length) {
    ASSERT_ANY_THROW(BitArray bf(-3));
}

TEST(Bit_Array_Test, Throws_When_Set_Bit_With_Negative_Index) {
    BitArray bf(10);

    ASSERT_ANY_THROW(bf.SetBit(-3));
}

TEST(Bit_Array_Test, Throws_When_Set_Bit_With_Too_Large_Index) {
    BitArray bf(10);

    ASSERT_ANY_THROW(bf.SetBit(11));
}

TEST(Bit_Array_Test, Throws_When_Get_Bit_With_Negative_Index) {
    BitArray bf(10);

    ASSERT_ANY_THROW(bf.GetBit(-3));
}

TEST(Bit_Array_Test, Throws_When_Get_Bit_With_Too_Large_Index) {
    BitArray bf(10);

    ASSERT_ANY_THROW(bf.GetBit(11));
}

TEST(Bit_Array_Test, Throws_When_Clear_Bit_With_Negative_Index) {
    BitArray bf(10);

    ASSERT_ANY_THROW(bf.ClrBit(-3));
}

TEST(Bit_Array_Test, Throws_When_Clear_Bit_With_Too_Large_Index) {
    BitArray bf(10);

    ASSERT_ANY_THROW(bf.ClrBit(11));
}

TEST(Bit_Array_Test, Can_Assign_Bitfields_Of_Equal_Size) {
    const int size = 2;
    BitArray bf1(size), bf2(size);
    for (int i = 0; i < size; i++) {
        bf1.SetBit(i);
    }
    bf2 = bf1;

    EXPECT_NE(0, bf2.GetBit(0));
    EXPECT_NE(0, bf2.GetBit(1));
}

TEST(Bit_Array_Test, Assign_Operator_Changes_Bitfield_Size) {
    const int size1 = 2, size2 = 5;
    BitArray bf1(size1), bf2(size2);
    for (int i = 0; i < size1; i++) {
        bf1.SetBit(i);
    }
    bf2 = bf1;

    EXPECT_EQ(2, bf2.GetLength());
}

TEST(Bit_Array_Test, Can_Assign_Bitfields_Of_Non_Equal_Size) {
    const int size1 = 2, size2 = 5;
    BitArray bf1(size1), bf2(size2);
    for (int i = 0; i < size1; i++) {
        bf1.SetBit(i);
    }
    bf2 = bf1;

    EXPECT_NE(0, bf2.GetBit(0));
    EXPECT_NE(0, bf2.GetBit(1));
}

TEST(Bit_Array_Test, Compare_Equal_Bitfields_Of_Equal_Size) {
    const int size = 2;
    BitArray bf1(size), bf2(size);
    for (int i = 0; i < size; i++) {
        bf1.SetBit(i);
    }
    bf2 = bf1;

    EXPECT_EQ(bf1, bf2);
}

TEST(Bit_Array_Test, Or_Operator_Applied_To_Bitfields_Of_Equal_Size) {
    const int size = 4;
    BitArray bf1(size), bf2(size), expBf(size);
    // bf1 = 0011
    bf1.SetBit(2);
    bf1.SetBit(3);
    // bf2 = 0101
    bf2.SetBit(1);
    bf2.SetBit(3);

    // expBf = 0111
    expBf.SetBit(1);
    expBf.SetBit(2);
    expBf.SetBit(3);

    EXPECT_EQ(expBf, bf1 | bf2);
}

TEST(Bit_Array_Test, Or_Operator_Applied_To_Bitfields_Of_Non_Equal_Size) {
    const int size1 = 4, size2 = 5;
    BitArray bf1(size1), bf2(size2), expBf(size2);
    // bf1 = 0011
    bf1.SetBit(2);
    bf1.SetBit(3);
    // bf2 = 01010
    bf2.SetBit(1);
    bf2.SetBit(3);

    // expBf = 01110
    expBf.SetBit(1);
    expBf.SetBit(2);
    expBf.SetBit(3);

    EXPECT_EQ(expBf, bf1 | bf2);
}

TEST(Bit_Array_Test, And_Operator_Applied_To_Bitfields_Of_Equal_Size) {
    const int size = 4;
    BitArray bf1(size), bf2(size), expBf(size);
    // bf1 = 0011
    bf1.SetBit(2);
    bf1.SetBit(3);
    // bf2 = 0101
    bf2.SetBit(1);
    bf2.SetBit(3);

    // expBf = 0001
    expBf.SetBit(3);

    EXPECT_EQ(expBf, bf1 & bf2);
}

TEST(Bit_Array_Test, And_Operator_Applied_To_Bitfields_Of_Non_Equal_Size) {
    const int size1 = 4, size2 = 5;
    BitArray bf1(size1), bf2(size2), expBf(size2);
    // bf1 = 0011
    bf1.SetBit(2);
    bf1.SetBit(3);
    // bf2 = 01010
    bf2.SetBit(1);
    bf2.SetBit(3);

    // expBf = 00010
    expBf.SetBit(3);

    EXPECT_EQ(expBf, bf1 & bf2);
}

TEST(Bit_Array_Test, Can_Invert_Bitfield) {
    const int size = 2;
    BitArray bf(size), negBf(size), expNegBf(size);
    // bf = 01
    bf.SetBit(1);
    negBf = ~bf;

    // expNegBf = 10
    expNegBf.SetBit(0);

    EXPECT_EQ(expNegBf, negBf);
}

TEST(Bit_Array_Test, Can_Invert_Large_Bitfield) {
    const int size = 38;
    BitArray bf(size), negBf(size), expNegBf(size);
    bf.SetBit(35);
    negBf = ~bf;

    for (int i = 0; i < size; i++)
        expNegBf.SetBit(i);
    expNegBf.ClrBit(35);

    EXPECT_EQ(expNegBf, negBf);
}

TEST(Bit_Array_Test, Invert_Plus_And_Operator_On_Different_Size_Bitfield) {
    const int firstSze = 4, secondSize = 8;
    BitArray firstBf(firstSze), negFirstBf(firstSze),
             secondBf(secondSize), testBf(secondSize);
    // firstBf = 0001
    firstBf.SetBit(0);
    negFirstBf = ~firstBf;
    // negFirstBf = 1110

    // secondBf = 00011000
    secondBf.SetBit(3);
    secondBf.SetBit(4);

    // testBf = 00001000
    testBf.SetBit(3);

    EXPECT_EQ(secondBf & negFirstBf, testBf);
}

TEST(Bit_Array_Test, Can_Invert_Many_Random_Bits_Bitfield) {
    const int size = 38;
    BitArray bf(size), negBf(size), expNegBf(size);

    std::vector<int> bits;
    bits.push_back(0);
    bits.push_back(1);
    bits.push_back(14);
    bits.push_back(16);
    bits.push_back(33);
    bits.push_back(37);

    for (unsigned int i = 0; i < bits.size(); i++)
        bf.SetBit(bits[i]);

    negBf = ~bf;

    for (int i = 0; i < size; i++)
        expNegBf.SetBit(i);
    for (unsigned int i = 0; i < bits.size(); i++)
        expNegBf.ClrBit(bits[i]);

    EXPECT_EQ(expNegBf, negBf);
}

TEST(Bit_Array_Test, Bitfields_With_Different_Bits_Are_Not_Equal) {
    const int size = 4;
    BitArray bf1(size), bf2(size);

    bf1.SetBit(1);
    bf1.SetBit(3);

    bf2.SetBit(1);
    bf2.SetBit(2);

    EXPECT_NE(bf1, bf2);
}
