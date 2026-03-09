#pragma once
#include "cppflow/cppflow.h"
#include <JuceHeader.h>

class TriodeNN
{
public:
    TriodeNN();

    void prepare();
    float process(float vgk);

private:
    std::unique_ptr<cppflow::model> triodeModel;
    bool notLogged = true;
};
