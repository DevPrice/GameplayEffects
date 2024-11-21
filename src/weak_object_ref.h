#ifndef WEAK_OBJECT_REF_H
#define WEAK_OBJECT_REF_H

#include <godot_cpp/core//object.hpp>

template <typename T>
class WeakObjectRef {

public:
    WeakObjectRef() = default;
    explicit WeakObjectRef(T* ref) : object_id(ref ? ref->get_instance_id() : ObjectID()) { }
    explicit WeakObjectRef(const ObjectID& id) : object_id(id) { }
    explicit WeakObjectRef(const uint64_t id) : object_id(id) { }

    T* ptr() const {
        return Object::cast_to<T>(ObjectDB::get_instance(object_id));
    }

    T& operator*() const {
        return *ptr();
    }

    T* operator->() const {
        return ptr();
    }

    operator bool() const {
        return object_id.is_valid() && ptr();
    }

private:
    ObjectID object_id;
};

#endif
