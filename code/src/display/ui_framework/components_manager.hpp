
#pragma once

#ifndef CODE_COMPONENTS_MANAGER_HPP
#define CODE_COMPONENTS_MANAGER_HPP

#include "components.hpp"
#include <vector>


template <typename T>
class ComponentsManager {
public:
    void register_component(Component<T>* component);
    void updateFrame();
private:
    std::vector<Component<T>*> components;
};



/***************************
 *     implementations     *
 ***************************/

template <typename T>
void ComponentsManager<T>::register_component(Component<T> *component) {
    this->components.push_back(component);
}

template <typename T>
void ComponentsManager<T>::updateFrame() {
    for (auto *component : this->components) {
        if (component->isVisible()){
            component->draw();
        }
    }
}
#endif
