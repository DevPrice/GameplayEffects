#ifndef EVALUATED_MODIFIER_H
#define EVALUATED_MODIFIER_H

#include "modifiers/stat_modifier.h"

struct IEvaluatedModifier {
    virtual Ref<GameplayStat> get_stat() const = 0;
    virtual StatModifier::Operation get_operation() const = 0;
    virtual float get_magnitude() const = 0;
    virtual bool requirements_met() const = 0;
};

class EvaluatedModifier : public IEvaluatedModifier {

    Ref<GameplayStat> stat;
    StatModifier::Operation operation;
    float magnitude;

public:
    Ref<GameplayStat> get_stat() const override { return stat; }
    StatModifier::Operation get_operation() const override { return operation; }
    float get_magnitude() const override { return magnitude; }
    bool requirements_met() const override { return true; }
};

#endif