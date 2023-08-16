#pragma once

#include "scene_object.hpp"
#include "camera.hpp"
#include <memory>
#include <vector>


class Scene {
public:
    Scene() {};

    void addLight(std::unique_ptr<Light> light) { _lights.push_back(std::move(light)); }
    const std::vector<std::unique_ptr<Light>>& lights() const { return _lights; }
    void addObject(std::unique_ptr<SceneObject> obj) { _objects.push_back(std::move(obj)); }
    const std::vector<std::unique_ptr<SceneObject>>& objects() const { return _objects; }
    void setCamera(std::unique_ptr<Camera> cam) { _cam = std::move(cam); }
    const std::unique_ptr<Camera>& cam() const { return _cam; }

private:
    std::vector<std::unique_ptr<Light>> _lights;
    std::vector<std::unique_ptr<SceneObject>> _objects;
    std::unique_ptr<Camera> _cam;
};
