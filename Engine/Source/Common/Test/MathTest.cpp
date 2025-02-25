//
// Created by Zach Lee on 2022/9/12.
//

#include <gtest/gtest.h>
#include <Common/Math/Vector2.h>
#include <Common/Math/Vector3.h>
#include <Common/Math/Vector4.h>

#include <Common/Math/Matrix3.h>
#include <Common/Math/Matrix4.h>

#include <Common/Math/Color.h>
#include <Common/Math/Box.h>
#include <Common/Math/Rect.h>
#include <Common/Math/Transform.h>

using namespace Common;

TEST(MathTest, VectorTest)
{
    Vector3 v0;
    Vector3 v1(1, 2, 3);
    Vector3 v2 = v0 + v1;
    ASSERT_FLOAT_EQ(v2.x, 1.f);
    ASSERT_FLOAT_EQ(v2.y, 2.f);
    ASSERT_FLOAT_EQ(v2.z, 3.f);
}
