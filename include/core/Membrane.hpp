#pragma once

#include <string>
#include <vector>

#include "mpi/MpiContext.hpp"

/**
 * @brief Enum for membrane and boundary condition keywords parsed from input.
 */
enum class BoundaryKeyword : int {
    ImplicitLipid = 0,  ///< Use implicit lipid model
    WaterBox = 1,       ///< Use rectangular box; specify x, y, and z dimensions
    XBoundaryType = 2,  ///< Reflecting or periodic x-boundary
    YBoundaryType = 3,  ///< Reflecting or periodic y-boundary
    ZBoundaryType = 4,  ///< Reflecting or periodic z-boundary
    IsSphere = 5,       ///< Use spherical boundary
    SphereRadius = 6    ///< Radius of spherical boundary
};

/**
 * @brief Represents the simulation boundary conditions and membrane model.
 */
class Membrane {
public:
    /**
     * @brief Represents a rectangular water box boundary volume.
     */
    struct WaterBox {
        double x{0}, y{0}, z{0};         ///< Box dimensions
        double xLeft{0.0}, xRight{0.0};  ///< Local boundaries per rank
        double volume{0.0};              ///< Total volume

        WaterBox() = default;

        explicit WaterBox(const std::vector<double>& dims)
            : x(dims[0]), y(dims[1]), z(dims[2]) {
            volume = x * y * z;
            xLeft = -x / 2.0;
            xRight = x / 2.0;
        }

        void serialize(unsigned char* buffer, int& offset);
        void deserialize(unsigned char* buffer, int& offset);
    };

    // Main physical boundary config
    WaterBox waterBox;      ///< 3D box dimensions
    double sphereRadius{0}; ///< Radius if spherical boundary
    double sphereVolume{0};

    // Implicit lipid model
    int siteCount{0};
    int lipidStateCount{0};
    int freeLipidCount{0};
    std::vector<int> freeLipidsPerState;
    int proteinCount{0};
    std::vector<int> proteinsPerState;
    int implicitLipidIndex{-1};
    std::vector<double> rs3DTable;  ///< Reflecting surface table for 3D->2D

    // Geometry and spatial offsets
    double totalSurfaceArea{0};
    double dx{0}, dy{0}, dz{0};
    double drx{0}, dry{0}, drz{0};
    double offset{0};
    double lipidLength{0.0};

    // Boundary flags and types
    bool useImplicitLipid{false};
    bool isTwoDimensional{false};
    bool isBox{false};
    bool isSphere{false};
    std::string xBoundaryType;
    std::string yBoundaryType;
    std::string zBoundaryType;

    // Functional interface
    void setBoundaryValue(const std::string& value, BoundaryKeyword key);
    void display() const;
    void createWaterBox();

    void serialize(unsigned char* buffer, int& offset);
    void deserialize(unsigned char* buffer, int& offset);
};