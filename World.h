#ifndef WORLD_H
#define WORLD_H

#include "emp/Evolve/World.hpp"
#include "emp/math/random_utils.hpp"
#include "emp/math/Random.hpp"

#include "Org.h"

class OrgWorld : public emp::World<Organism>
{

    emp::Random &random;
    emp::Ptr<emp::Random> random_ptr;

public:
    OrgWorld(emp::Random &_random) : emp::World<Organism>(_random), random(_random)
    {
        random_ptr.New(_random);
    }

    ~OrgWorld()
    {
    }

    void Update()
    {
        emp::World<Organism>::Update();
        std::cout << "Updating!" << std::endl; // feel free to get rid of this

        for (int i = 0; i < GetSize(); i++)
        {
            if (!IsOccupied(i))
                continue;           // skip if org is null
            Organism *org = pop[i]; // grabs the org from the vector pop

            // Get a permutation and loop it to give everyone 100 points
            emp::vector<size_t> schedule = emp::GetPermutation(random, GetSize());
            for (int i : schedule)
            {
                if (!IsOccupied(i))
                    continue; // skip if org is null
                pop[i]->Process(100);
            }
            // See if anyone can reproduce
            schedule = emp::GetPermutation(random, GetSize());
            for (int i : schedule)
            {
                if (!IsOccupied(i))
                    continue; // skip if org is null
                emp::Ptr<Organism> offspring = pop[i]->CheckReproduction();
                if (offspring)
                {
                    DoBirth(*offspring, i);
                }
            }
        }
    }
};
#endif