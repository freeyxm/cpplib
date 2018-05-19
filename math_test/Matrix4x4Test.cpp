#include "stdafx.h"
#include <gtest\gtest.h>
#include <Math\Vector3.h>
#include <Math\Quaternion.h>
#include <Math\Matrix4x4.h>
#include <Math\Math.h>
#include <iostream>

using namespace std;
using namespace cpplib::math;

extern void PrintMatrix(const char* name, const Matrix4x4& matrix)
{
    cout << name << ":" << endl;
    for (int i = 0; i < 16; ++i)
    {
        cout << matrix[i / 4][i % 4] << ",";
        if ((i + 1) % 4 == 0)
        {
            cout << endl;
        }
    }
}

TEST(Matrix4x4Test, Init)
{
    PrintMatrix("identity", Matrix4x4::identity);
}

TEST(Matrix4x4Test, Translate)
{
    Vector3 vec(1, 2, 3);
    {
        Matrix4x4 matrix = Matrix4x4::Translate(Vector3(2, 3, 4));
        Vector3 res = matrix.MultiplyPoint(vec);
        EXPECT_TRUE(res == Vector3(3, 5, 7));
    }
}

TEST(Matrix4x4Test, Scale)
{
    Vector3 vec(1, 2, 3);
    {
        Matrix4x4 matrix = Matrix4x4::Scale(Vector3(2, 3, 4));
        Vector3 res = matrix.MultiplyVector(vec);
        EXPECT_TRUE(res == Vector3(2, 6, 12));
    }
    {
        Matrix4x4 matrix2 = Matrix4x4::Scale(Vector3(1, 0, 0), 2);
        Vector3 res = matrix2.MultiplyVector(vec);
        EXPECT_TRUE(res == Vector3(2, 2, 3));
    }
    {
        Matrix4x4 matrix2 = Matrix4x4::Scale(Vector3(0, 1, 0), 2);
        Vector3 res = matrix2.MultiplyVector(vec);
        EXPECT_TRUE(res == Vector3(1, 4, 3));
    }
    {
        Matrix4x4 matrix2 = Matrix4x4::Scale(Vector3(0, 0, 1), 2);
        Vector3 res = matrix2.MultiplyVector(vec);
        EXPECT_TRUE(res == Vector3(1, 2, 6));
    }
    {
        Matrix4x4 matrix2 = Matrix4x4::Scale(Vector3(1, 1, 1), 2);
        Vector3 res = matrix2.MultiplyVector(vec);
        EXPECT_TRUE(res == Vector3(7, 8, 9));
    }
}

TEST(Matrix4x4Test, Rotate)
{
    Vector3 vec(1, 2, 3);
    {
        Matrix4x4 matrix = Matrix4x4::RotateX(45);
        Vector3 res = matrix.MultiplyVector(vec);
        EXPECT_TRUE(res == Vector3(1, -0.707107f, 3.535534f));
    }
    {
        Matrix4x4 matrix = Matrix4x4::RotateY(45);
        Vector3 res = matrix.MultiplyVector(vec);
        EXPECT_TRUE(res == Vector3(2.828427f, 2, 1.414213f));
    }
    {
        Matrix4x4 matrix = Matrix4x4::RotateZ(45);
        Vector3 res = matrix.MultiplyVector(vec);
        EXPECT_TRUE(res == Vector3(-0.7071069f, 2.12132f, 3));
    }
    {
        Matrix4x4 matrix = Matrix4x4::Rotate(Vector3(10, 20, 30));
        Vector3 res = matrix.MultiplyVector(vec);
        EXPECT_TRUE(res == Vector3(1.017141f, 1.677197f, 3.186289f));
    }
    {
        Matrix4x4 matrix = Matrix4x4::Rotate(Vector3(1, 0, 0), 45);
        Vector3 res = matrix.MultiplyVector(vec);
        EXPECT_TRUE(res == Vector3(1, -0.707107f, 3.535534f));
    }
    {
        Matrix4x4 matrix = Matrix4x4::Rotate(Vector3(0, 1, 0), 45);
        Vector3 res = matrix.MultiplyVector(vec);
        EXPECT_TRUE(res == Vector3(2.828427f, 2, 1.414213f));
    }
    {
        Matrix4x4 matrix = Matrix4x4::Rotate(Vector3(0, 0, 1), 45);
        Vector3 res = matrix.MultiplyVector(vec);
        EXPECT_TRUE(res == Vector3(-0.7071069f, 2.12132f, 3));
    }
    {
        Matrix4x4 matrix = Matrix4x4::Rotate(Vector3(1, 1, 1), 90);
        Vector3 res = matrix.MultiplyVector(Vector3(1, 0, 0));
        EXPECT_TRUE(res == Vector3(0.3333333f, 0.9106836f, -0.2440169f));
    }
}

TEST(Matrix4x4Test, Determinant)
{
    Matrix4x4 matrix = Matrix4x4::identity;
    float res = matrix.Determinant();
    EXPECT_FLOAT_EQ(res, 1);

    matrix = Matrix4x4::Scale(Vector3(2, 3, 4));
    res = matrix.Determinant();
    EXPECT_FLOAT_EQ(res, 24);

    matrix = Matrix4x4::Translate(Vector3(7, 8, 9)) * Matrix4x4::Scale(Vector3(2, 3, 4));
    res = matrix.Determinant();
    EXPECT_FLOAT_EQ(res, 24);
}

TEST(Matrix4x4Test, Transpose)
{
    Matrix4x4 matrix = Matrix4x4::Scale(Vector3(2, 3, 4));
    Matrix4x4 transpose = matrix.Transpose();
    Matrix4x4 matrix2 = transpose.Transpose();
    EXPECT_TRUE(matrix == matrix2);
}

TEST(Matrix4x4Test, Inverse)
{
    Matrix4x4 matrix = Matrix4x4::Translate(Vector3(7, 8, 9))
        * Matrix4x4::Scale(Vector3(2, 3, 4))
        * Matrix4x4::Rotate(Vector3(5, 6, 7), 45);
    Matrix4x4 inverse = matrix.Inverse();
    Matrix4x4 res = matrix * inverse;
    EXPECT_TRUE(res == Matrix4x4::identity);
}

TEST(Matrix4x4Test, TRS)
{
    Matrix4x4 matrix = Matrix4x4::TRS(Vector3(5, 6, 7), Vector3(20, 30, 40), Vector3(1, 2, 3));
    Vector3 vec(6, 7, 8);
    Vector3 res = matrix.MultiplyVector(vec);
    EXPECT_TRUE(res == Vector3(9.956966f, 5.493502f, 26.05149f));
}
