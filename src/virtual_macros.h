#ifndef VIRTUAL_MACROS_H
#define VIRTUAL_MACROS_H

#define GDVIRTUAL1_NO_IMPL(m_name, m_type1)\
	::godot::StringName _gdvirtual_##m_name##_sn = #m_name;\
	template <bool required>\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call(m_type1 arg1) {\
		if (::godot::internal::gdextension_interface_object_has_script_method(_owner, &_gdvirtual_##m_name##_sn)) { \
			GDExtensionCallError ce;\
			::godot::Variant vargs[1] = { ::godot::Variant(arg1) };\
			const ::godot::Variant *vargptrs[1] = { &vargs[0] };\
			::godot::Variant ret;\
			::godot::internal::gdextension_interface_object_call_script_method(_owner, &_gdvirtual_##m_name##_sn, (const GDExtensionConstVariantPtr *)vargptrs, 1, &ret, &ce);\
			if (ce.error == GDEXTENSION_CALL_OK) {\
				return true;\
			}\
		}\
		if (required) {\
			ERR_PRINT_ONCE("Required virtual method " + get_class() + "::" + #m_name + " must be overridden before calling.");\
		}\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		return ::godot::internal::gdextension_interface_object_has_script_method(_owner, &_gdvirtual_##m_name##_sn); \
	}\
	static ::godot::MethodInfo _gdvirtual_##m_name##_get_method_info();

#define GDVIRTUAL1_IMPL(m_class, m_name, m_type1)\
    ::godot::MethodInfo m_class::_gdvirtual_##m_name##_get_method_info() {\
		::godot::MethodInfo method_info;\
		method_info.name = #m_name;\
		method_info.flags = ::godot::METHOD_FLAG_VIRTUAL;\
		method_info.arguments.push_back(::godot::GetTypeInfo<m_type1>::get_class_info());\
		method_info.arguments_metadata.push_back(::godot::GetTypeInfo<m_type1>::METADATA);\
		return method_info;\
	}

#define GDVIRTUAL1R_NO_IMPL(m_ret, m_name, m_type1)\
	::godot::StringName _gdvirtual_##m_name##_sn = #m_name;\
	template <bool required>\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call(m_type1 arg1, m_ret &r_ret) {\
		if (::godot::internal::gdextension_interface_object_has_script_method(_owner, &_gdvirtual_##m_name##_sn)) { \
			GDExtensionCallError ce;\
			::godot::Variant vargs[1] = { ::godot::Variant(arg1) };\
			const ::godot::Variant *vargptrs[1] = { &vargs[0] };\
			::godot::Variant ret;\
			::godot::internal::gdextension_interface_object_call_script_method(_owner, &_gdvirtual_##m_name##_sn, (const GDExtensionConstVariantPtr *)vargptrs, 1, &ret, &ce);\
			if (ce.error == GDEXTENSION_CALL_OK) {\
				r_ret = ::godot::VariantCaster<m_ret>::cast(ret);\
				return true;\
			}\
		}\
		if (required) {\
			ERR_PRINT_ONCE("Required virtual method " + get_class() + "::" + #m_name + " must be overridden before calling.");\
			(void)r_ret;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		return ::godot::internal::gdextension_interface_object_has_script_method(_owner, &_gdvirtual_##m_name##_sn); \
	}\
	static ::godot::MethodInfo _gdvirtual_##m_name##_get_method_info();

#define GDVIRTUAL1R_IMPL(m_class, m_ret, m_name, m_type1)\
	::godot::MethodInfo m_class::_gdvirtual_##m_name##_get_method_info() {\
		::godot::MethodInfo method_info;\
		method_info.name = #m_name;\
		method_info.flags = ::godot::METHOD_FLAG_VIRTUAL;\
		method_info.return_val = ::godot::GetTypeInfo<m_ret>::get_class_info();\
		method_info.return_val_metadata = ::godot::GetTypeInfo<m_ret>::METADATA;\
		method_info.arguments.push_back(::godot::GetTypeInfo<m_type1>::get_class_info());\
		method_info.arguments_metadata.push_back(::godot::GetTypeInfo<m_type1>::METADATA);\
		return method_info;\
	}

#define GDVIRTUAL3_NO_IMPL(m_name, m_type1, m_type2, m_type3) \
	::godot::StringName _gdvirtual_##m_name##_sn = #m_name;\
	template <bool required>\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call(m_type1 arg1, m_type2 arg2, m_type3 arg3) {\
		if (::godot::internal::gdextension_interface_object_has_script_method(_owner, &_gdvirtual_##m_name##_sn)) { \
			GDExtensionCallError ce;\
			::godot::Variant vargs[3] = { ::godot::Variant(arg1), ::godot::Variant(arg2), ::godot::Variant(arg3) };\
			const ::godot::Variant *vargptrs[3] = { &vargs[0], &vargs[1], &vargs[2] };\
			::godot::Variant ret;\
			::godot::internal::gdextension_interface_object_call_script_method(_owner, &_gdvirtual_##m_name##_sn, (const GDExtensionConstVariantPtr *)vargptrs, 3, &ret, &ce);\
			if (ce.error == GDEXTENSION_CALL_OK) {\
				return true;\
			}\
		}\
		if (required) {\
			ERR_PRINT_ONCE("Required virtual method " + get_class() + "::" + #m_name + " must be overridden before calling.");\
		}\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		return ::godot::internal::gdextension_interface_object_has_script_method(_owner, &_gdvirtual_##m_name##_sn); \
	}\
	static ::godot::MethodInfo _gdvirtual_##m_name##_get_method_info();

#define GDVIRTUAL3_IMPL(m_class, m_name, m_type1, m_type2, m_type3) \
    ::godot::MethodInfo m_class::_gdvirtual_##m_name##_get_method_info() {\
        ::godot::MethodInfo method_info;\
        method_info.name = #m_name;\
        method_info.flags = ::godot::METHOD_FLAG_VIRTUAL;\
        method_info.arguments.push_back(::godot::GetTypeInfo<m_type1>::get_class_info());\
        method_info.arguments_metadata.push_back(::godot::GetTypeInfo<m_type1>::METADATA);\
        method_info.arguments.push_back(::godot::GetTypeInfo<m_type2>::get_class_info());\
        method_info.arguments_metadata.push_back(::godot::GetTypeInfo<m_type2>::METADATA);\
        method_info.arguments.push_back(::godot::GetTypeInfo<m_type3>::get_class_info());\
        method_info.arguments_metadata.push_back(::godot::GetTypeInfo<m_type3>::METADATA);\
        return method_info;\
    }

#define GDVIRTUAL3R_NO_IMPL(m_ret, m_name, m_type1, m_type2, m_type3)\
	::godot::StringName _gdvirtual_##m_name##_sn = #m_name;\
	template <bool required>\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_ret &r_ret) {\
		if (::godot::internal::gdextension_interface_object_has_script_method(_owner, &_gdvirtual_##m_name##_sn)) { \
			GDExtensionCallError ce;\
			::godot::Variant vargs[3] = { ::godot::Variant(arg1), ::godot::Variant(arg2), ::godot::Variant(arg3) };\
			const ::godot::Variant *vargptrs[3] = { &vargs[0], &vargs[1], &vargs[2] };\
			::godot::Variant ret;\
			::godot::internal::gdextension_interface_object_call_script_method(_owner, &_gdvirtual_##m_name##_sn, (const GDExtensionConstVariantPtr *)vargptrs, 3, &ret, &ce);\
			if (ce.error == GDEXTENSION_CALL_OK) {\
				r_ret = ::godot::VariantCaster<m_ret>::cast(ret);\
				return true;\
			}\
		}\
		if (required) {\
			ERR_PRINT_ONCE("Required virtual method " + get_class() + "::" + #m_name + " must be overridden before calling.");\
			(void)r_ret;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		return ::godot::internal::gdextension_interface_object_has_script_method(_owner, &_gdvirtual_##m_name##_sn); \
	}\
	static ::godot::MethodInfo _gdvirtual_##m_name##_get_method_info();

#define GDVIRTUAL3R_IMPL(m_class, m_ret, m_name, m_type1, m_type2, m_type3)\
    ::godot::MethodInfo m_class::_gdvirtual_##m_name##_get_method_info() {\
		::godot::MethodInfo method_info;\
		method_info.name = #m_name;\
		method_info.flags = ::godot::METHOD_FLAG_VIRTUAL;\
		method_info.return_val = ::godot::GetTypeInfo<m_ret>::get_class_info();\
		method_info.return_val_metadata = ::godot::GetTypeInfo<m_ret>::METADATA;\
		method_info.arguments.push_back(::godot::GetTypeInfo<m_type1>::get_class_info());\
		method_info.arguments_metadata.push_back(::godot::GetTypeInfo<m_type1>::METADATA);\
		method_info.arguments.push_back(::godot::GetTypeInfo<m_type2>::get_class_info());\
		method_info.arguments_metadata.push_back(::godot::GetTypeInfo<m_type2>::METADATA);\
		method_info.arguments.push_back(::godot::GetTypeInfo<m_type3>::get_class_info());\
		method_info.arguments_metadata.push_back(::godot::GetTypeInfo<m_type3>::METADATA);\
		return method_info;\
	}

#endif
