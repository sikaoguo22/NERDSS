#include <gtest/gtest.h>
#include "core/Membrane.hpp"

TEST(MembraneTest, WaterBoxSerialization) {
    Membrane::WaterBox box({10.0, 20.0, 30.0});
    unsigned char buffer[256]{};
    int offset = 0;

    box.serialize(buffer, offset);

    Membrane::WaterBox boxCopy;
    int offset2 = 0;
    boxCopy.deserialize(buffer, offset2);

    EXPECT_DOUBLE_EQ(box.x, boxCopy.x);
    EXPECT_DOUBLE_EQ(box.y, boxCopy.y);
    EXPECT_DOUBLE_EQ(box.z, boxCopy.z);
    EXPECT_DOUBLE_EQ(box.volume, boxCopy.volume);
    EXPECT_DOUBLE_EQ(box.xLeft, boxCopy.xLeft);
    EXPECT_DOUBLE_EQ(box.xRight, boxCopy.xRight);
}

TEST(MembraneTest, BoundaryAssignment) {
    Membrane m;
    m.setBoundaryValue("reflect", BoundaryKeyword::XBoundaryType);
    m.setBoundaryValue("periodic", BoundaryKeyword::ZBoundaryType);

    EXPECT_EQ(m.xBoundaryType, "reflect");
    EXPECT_EQ(m.zBoundaryType, "periodic");
}

TEST(MembraneTest, CreateWaterBoxSetsVolumeAndBounds) {
    Membrane m;
    m.waterBox = Membrane::WaterBox({10.0, 10.0, 10.0});
    m.createWaterBox();

    EXPECT_DOUBLE_EQ(m.waterBox.volume, 1000.0);
    EXPECT_DOUBLE_EQ(m.waterBox.xLeft, -5.0);
    EXPECT_DOUBLE_EQ(m.waterBox.xRight, 5.0);
}
