#include "core/Membrane.hpp"
#include "utils/serialization_utils.hpp"

#include <iostream>

void Membrane::WaterBox::serialize(unsigned char* buffer, int& offset) {
    PUSH(x);
    PUSH(y);
    PUSH(z);
    PUSH(xLeft);
    PUSH(xRight);
    PUSH(volume);
}

void Membrane::WaterBox::deserialize(unsigned char* buffer, int& offset) {
    POP(x);
    POP(y);
    POP(z);
    POP(xLeft);
    POP(xRight);
    POP(volume);
}

void Membrane::serialize(unsigned char* buffer, int& offset) {
    waterBox.serialize(buffer, offset);

    PUSH(sphereRadius);
    PUSH(sphereVolume);
    PUSH(siteCount);
    PUSH(lipidStateCount);
    PUSH(freeLipidCount);
    serialize_primitive_vector(freeLipidsPerState, buffer, offset);
    PUSH(proteinCount);
    serialize_primitive_vector(proteinsPerState, buffer, offset);
    PUSH(implicitLipidIndex);
    serialize_primitive_vector(rs3DTable, buffer, offset);

    PUSH(totalSurfaceArea);
    PUSH(dx); PUSH(dy); PUSH(dz);
    PUSH(drx); PUSH(dry); PUSH(drz);
    PUSH(offset);
    PUSH(lipidLength);

    PUSH(useImplicitLipid);
    PUSH(isTwoDimensional);
    PUSH(isBox);
    PUSH(isSphere);

    serialize_string(xBoundaryType, buffer, offset);
    serialize_string(yBoundaryType, buffer, offset);
    serialize_string(zBoundaryType, buffer, offset);
}

void Membrane::deserialize(unsigned char* buffer, int& offset) {
    waterBox.deserialize(buffer, offset);

    POP(sphereRadius);
    POP(sphereVolume);
    POP(siteCount);
    POP(lipidStateCount);
    POP(freeLipidCount);
    deserialize_primitive_vector(freeLipidsPerState, buffer, offset);
    POP(proteinCount);
    deserialize_primitive_vector(proteinsPerState, buffer, offset);
    POP(implicitLipidIndex);
    deserialize_primitive_vector(rs3DTable, buffer, offset);

    POP(totalSurfaceArea);
    POP(dx); POP(dy); POP(dz);
    POP(drx); POP(dry); POP(drz);
    POP(offset);
    POP(lipidLength);

    POP(useImplicitLipid);
    POP(isTwoDimensional);
    POP(isBox);
    POP(isSphere);

    deserialize_string(xBoundaryType, buffer, offset);
    deserialize_string(yBoundaryType, buffer, offset);
    deserialize_string(zBoundaryType, buffer, offset);
}

void Membrane::setBoundaryValue(const std::string& value, BoundaryKeyword keyword) {
    switch (keyword) {
        case BoundaryKeyword::XBoundaryType: xBoundaryType = value; break;
        case BoundaryKeyword::YBoundaryType: yBoundaryType = value; break;
        case BoundaryKeyword::ZBoundaryType: zBoundaryType = value; break;
        default: break;  // Extend as needed
    }
}

void Membrane::display() const {
    std::cout << "=== Membrane Configuration ===" << std::endl;
    std::cout << "Use Implicit Lipid: " << std::boolalpha << useImplicitLipid << std::endl;
    std::cout << "Geometry: " << (isBox ? "Box" : isSphere ? "Sphere" : "Unknown") << std::endl;
    std::cout << "xBC: " << xBoundaryType << ", yBC: " << yBoundaryType << ", zBC: " << zBoundaryType << std::endl;
    std::cout << "Sphere Radius: " << sphereRadius << " nm" << std::endl;
    std::cout << "Water Box: [" << waterBox.x << ", " << waterBox.y << ", " << waterBox.z << "]" << std::endl;
}

void Membrane::createWaterBox() {
    waterBox.volume = waterBox.x * waterBox.y * waterBox.z;
    waterBox.xLeft = -waterBox.x / 2.0;
    waterBox.xRight = waterBox.x / 2.0;
}