#pragma once

#include "vector.hpp"

class Camera {
public:
    Camera(float x, float y, float z, float angleX, float angleY, float angleZ, float sizeOfLens) :
        _position(x, y, z), _orientation(angleX, angleY, angleZ), _sizeOfLens(sizeOfLens) {};

    const Vector3D& position() const { return _position; }
    const Vector3D& orientation() const { return _orientation; }
    void setPosition(float x, float y, float z) {
        _position.setX(x);
        _position.setY(y);
        _position.setZ(z);
    }
    void setOrientation(float x, float y, float z) {
        _orientation.setX(x);
        _orientation.setY(y);
        _orientation.setZ(z);
    }
    float sizeOfLens() const { return _sizeOfLens; }
    void setSizeOfLens(float s) { _sizeOfLens = s; }

    Vector3D getRayOrigin(int height, int width, int i, int j) const {
        std::cout << "getRayOrigin0 " << position().toString() << orientation().toString() << std::endl;
        // Get a vector perpendicular to the orientation
        Vector3D planeNormal = orientation().cross(Vector3D{1, 0, 0}).normalize();
        std::cout << "getRayOrigin1 " << planeNormal.toString() << std::endl;
        // Get the plane equation
        float d = -planeNormal.dot(position());

        // Get viewport coordinate
        float x = ((float)i / width) - 0.5;
        float y = ((float)j / height) - 0.5;
        Vector3D v{x, y, 0};

        float t = (d - planeNormal.dot(v)) / (planeNormal.dot(planeNormal));
        Vector3D proj = v*_sizeOfLens + planeNormal * t;
        return proj;
    }

private:
    Vector3D _position;
    Vector3D _orientation;
    float _sizeOfLens;
};
