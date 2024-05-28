template <typename T, typename FNC_PTR_T = bool(*)(typename T::value_type)>
inline bool array_all_of(const T &v1, const FNC_PTR_T ptr) {
    for (size_t i = 0; i < v1.size(); i++) {
        if (!ptr(v1[i])) {
            return false;
        }
    }
    return true;
}
