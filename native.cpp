#include <iostream>

#include "Org.h"
#include "emp/base/vector.hpp"
#include "emp/math/random_utils.hpp"
#include "emp/math/Random.hpp"

#include "World.h"

// This is the main function for the NATIVE version of this project.

int main(int argc, char *argv[])
{
  emp::Random random(2);
  OrgWorld world(random);

  Organism *new_org = new Organism(&random); // random is pointer
  world.Inject(*new_org);
  std::cout << world.size() << std::endl;
  world.Resize(10, 10);
  std::cout << "num orgs: " << world.GetNumOrgs() << std::endl;

  for (int i = 0; i < 10; i++)
  {
    world.Update();
  }
  std::cout << "num orgs: " << world.GetNumOrgs() << std::endl;
  // print points of orgs
}
