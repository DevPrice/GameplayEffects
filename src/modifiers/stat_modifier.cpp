#include "modifiers/stat_modifier.h"
#include "godot_cpp/classes/global_constants.hpp"

#include <godot_cpp/core/class_db.hpp>

using namespace godot;

#define GET_SET_PROPERTY_IMPL(ClassName, Type, Name) \
Type ClassName::get_##Name() const { \
    return Name; \
} \
void ClassName::set_##Name(const Type p_##Name) { \
    ##Name = p_##Name; \
}

#define BIND_GET_SET_METHOD(ClassName, Name) \
    ClassDB::bind_method(D_METHOD("get_" #Name), &##ClassName::get_##Name); \
    ClassDB::bind_method(D_METHOD("set_" #Name, "p_" #Name), &##ClassName::set_##Name);

#define BIND_GET_SET(ClassName, Name, VariantType) \
    BIND_GET_SET_METHOD(ClassName, Name) \
    ClassDB::add_property(#ClassName, PropertyInfo(VariantType, #Name), "set_" #Name, "get_" #Name);

#define BIND_GET_SET_RESOURCE(ClassName, Name, Type) \
    BIND_GET_SET_METHOD(ClassName, Name) \
    ClassDB::add_property(#ClassName, PropertyInfo(Variant::OBJECT, #Name, PROPERTY_HINT_RESOURCE_TYPE, #Type), "set_" #Name, "get_" #Name);

#define BIND_GET_SET_ENUM(ClassName, Name, Values) \
    BIND_GET_SET_METHOD(ClassName, Name) \
    ClassDB::add_property(#ClassName, PropertyInfo(Variant::INT, #Name, PROPERTY_HINT_ENUM, Values), "set_" #Name, "get_" #Name);

void StatModifier::_bind_methods() {
    BIND_ENUM_CONSTANT(Offset)
    BIND_ENUM_CONSTANT(Multiply)
    BIND_ENUM_CONSTANT(Override)
    BIND_GET_SET_ENUM(StatModifier, operation, "Offset:0,Multiply:1,Override:2")
    BIND_GET_SET_RESOURCE(StatModifier, stat, GameplayStat)
}

GET_SET_PROPERTY_IMPL(StatModifier, Ref<GameplayStat>, stat)
GET_SET_PROPERTY_IMPL(StatModifier, StatModifier::Operation, operation)
