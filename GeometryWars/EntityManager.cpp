#include "EntityManager.h"

#include <algorithm>
#include <iterator>

EntityManager::EntityManager() : next_id_(0), entities_(), to_add_() {}

void EntityManager::update() {
  // Remove any pointers from the entity tag index
  size_t entities_by_tag_size = entities_by_tag_.size();
  for (size_t i = 0; i < entities_by_tag_size; i++) {
    std::vector<Entity*>& by_tag = entities_by_tag_[i];
    by_tag.erase(std::remove_if(by_tag.begin(), by_tag.end(),
                                [](const Entity* entity_pointer) -> bool {
                                  return !entity_pointer->isAlive();
                                }),
                 by_tag.end());
  }

  // Remove the entities
  entities_.erase(
      std::remove_if(entities_.begin(), entities_.end(),
                     [](const std::unique_ptr<Entity>& entity) -> bool {
                       return !entity->isAlive();
                     }),
      entities_.end());

  // Insert pending entities
  size_t size_before_insert = entities_.size();
  entities_.insert(entities_.end(), std::make_move_iterator(to_add_.begin()),
                   std::make_move_iterator(to_add_.end()));
  to_add_.clear();

  // Update entity tag index
  size_t size_after_insert = entities_.size();
  for (size_t i = size_before_insert; i < size_after_insert; i++) {
    std::unique_ptr<Entity>& new_entity = entities_[i];
    EntityTag tag = new_entity->getTag();
    if (tag + 1 > entities_by_tag_.size()) {
      entities_by_tag_.resize(tag + 1);
    }
    entities_by_tag_[tag].push_back(new_entity.get());
  }
}

Entity& EntityManager::addEntity(EntityTag tag) {
  to_add_.push_back(std::make_unique<Entity>(Entity(next_id_++, tag)));
  return *to_add_[to_add_.size() - 1].get();
}

std::vector<std::unique_ptr<Entity>>& EntityManager::getEntities() {
  return entities_;
}

std::vector<Entity*>& EntityManager::getEntitiesWithTag(EntityTag tag) {
  return entities_by_tag_[tag];
}

EntityTag EntityManager::getMaxTag() { return entities_by_tag_.size() - 1; }
