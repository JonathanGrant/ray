#pragma once

#include "vector.hpp"
#include <vector>
#include <optional>


struct HitInfo {
    std::unique_ptr<Vector3D> hitPoint;
    std::unique_ptr<Vector3D> bounceDir; 
};


class SceneObject {
public:
    SceneObject(float x, float y, float z, float r, float g, float b, float alpha):
        _position(Vector3D(x, y, z)), _color(std::move(std::make_unique<VectorData<float>>(std::vector<float>{r, g, b, alpha}))) {};
    
    const Vector3D& position() const { return _position; }
    const VectorND<float>& color() const { return _color; }
    void setPosition(float x, float y, float z) {
        _position.setX(x);
        _position.setY(y);
        _position.setZ(z);
    }
    void setColor(float r, float g, float b, float alpha) {
        _color.set(0, r);
        _color.set(1, g);
        _color.set(2, b);
        _color.set(3, alpha);
    }

    virtual float radius() const { return 0; }
    virtual void setRadius(float newR) {}

    virtual std::optional<HitInfo> intersect(const Vector3D& origin, const Vector3D& direction) const { return std::nullopt;; }

private:
    Vector3D _position;
    VectorND<float> _color;
};


class SphereSceneObject : public SceneObject {
public:

    SphereSceneObject(float x, float y, float z, float r, float g, float b, float alpha, float radius):
        SceneObject(x, y, z, r, g, b, alpha), _radius(radius) {};

    float radius() const { return _radius; }
    void setRadius(float newR) { _radius = newR; }

    std::optional<HitInfo> intersect(const Vector3D& origin, const Vector3D& direction) const {
        std::cout << "intersect1" << std::endl;
        // Vector from origin to sphere center
        Vector3D toCenter = position() - origin; 
        std::cout << "intersect2 " << position().toString() << " " << origin.toString() << " " << toCenter.toString() << std::endl;
        
        // Length squared of toCenter vector
        float distSq = toCenter.lengthSquared();
        std::cout << "intersect3" << std::endl;
        
        // Radius squared
        float radiusSq = radius() * radius();
        std::cout << "intersect4" << std::endl;
        
        // Projection of toCenter onto direction
        float proj = toCenter.dot(direction);
        std::cout << "intersect5" << std::endl;

        // Distance squared from projected point to sphere center
        float x = distSq - proj*proj;
        std::cout << "intersect6" << std::endl;

        // Check if projected point is outside sphere
        if (x > radiusSq) {
            return std::nullopt;; 
        }
        std::cout << "intersect7" << std::endl;

        // Distance squared from origin to projected point
        float y = std::sqrt(radiusSq - x);
        std::cout << "intersect8" << std::endl;

        // Check if origin is outside sphere
        if (distSq > y*y) {
            return std::nullopt;
        }
        std::cout << "intersect9" << std::endl;

        // Hit point is ray origin + ray direction * distance
        HitInfo hit;
        hit.hitPoint = std::make_unique<Vector3D>(std::move(origin + direction * (proj - y)));
        std::cout << "intersect10" << std::endl;

        // Normal at hit point
        Vector3D normal = (*hit.hitPoint - position()).normalize();
        std::cout << "intersect11 " << direction.toString() << normal.toString() << std::endl;

        // Bounce direction
        hit.bounceDir = std::make_unique<Vector3D>(std::move(direction.cross(normal).normalize()));
        std::cout << "intersect12" << std::endl;
        std::cout << "intersect post " << hit.hitPoint->toString() << std::endl;
        std::cout << "intersect post " << hit.bounceDir->toString() << std::endl;
        return std::make_optional(std::move(hit));
    }

private:
    float _radius;
};

class Light : public SphereSceneObject {
public:
    Light(float x, float y, float z, float r, float g, float b, float radius):
        SphereSceneObject(x, y, z, r, g, b, 1.0, radius) {};
private:
};

