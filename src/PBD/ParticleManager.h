//
// Created by Dillon Yao on 4/26/17.
//

#ifndef FLOOID2_PARTICLEMANAGER_H
#define FLOOID2_PARTICLEMANAGER_H


#include <vector>
#include <glm/glm.hpp>
#include "Particle.h"
#include "../common.h"
#include "../model/Shader.h"
#include <map>
#include "PBDSolver.h"
#include "../scene/Plane.h"

using namespace glm;

class ParticleManager {
private:
    std::vector<Particle> particles;
    ivec3 bin(Particle &p);
    int hash_bin(glm::ivec3 pos);
    std::vector<Particle *> neighborhood(Particle& p);
    std::vector<glm::vec3> accels;

    std::map<int, std::vector<Particle *> *> spacial_map;

    int solver_iters;
    float particle_radius;
    float particle_mass;

    std::vector<Plane> planes;

public:
    ParticleManager();
    ~ParticleManager() { spacial_map.clear(); }
    void render() const;
    void step(float dt);
};


#endif //FLOOID2_PARTICLEMANAGER_H