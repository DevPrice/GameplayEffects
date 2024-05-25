#ifndef BINDING_MACROS_H
#define BINDING_MACROS_H

#define GET_SET_PROPERTY(Type, Name) \
private: \
    Type Name; \
public: \
    Type get_##Name() const; \
    void set_##Name(const Type p_##Name); \
private:

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

#define BIND_GET_SET_RESOURCE_ARRAY(ClassName, Name, Type) \
    BIND_GET_SET_METHOD(ClassName, Name) \
    ClassDB::add_property(#ClassName, PropertyInfo(Variant::ARRAY, #Name, PROPERTY_HINT_TYPE_STRING, String::num(Variant::OBJECT) + "/" + String::num(PROPERTY_HINT_RESOURCE_TYPE) + ":" #Type), "set_" #Name, "get_" #Name);

#endif
