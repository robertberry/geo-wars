#pragma once

#include <vector>

#include "Entity.h"

class EntityManager final {
 public:
  EntityManager();

  void update();

  Entity& addEntity(EntityTag tag);

  std::vector<std::unique_ptr<Entity>>& getEntities();
  std::vector<Entity*>& getEntitiesWithTag(EntityTag tag);
  EntityTag getMaxTag();

 private:
  int next_id_;
  std::vector<std::unique_ptr<Entity>> entities_;
  std::vector<std::unique_ptr<Entity>> to_add_;
  std::vector<std::vector<Entity*>> entities_by_tag_;
};
