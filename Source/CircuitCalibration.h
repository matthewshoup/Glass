#pragma once
struct CircuitCalibration {
    float bPlusVolts=400.0f, idlePlateCurrentmA=75.0f;
    float cathodeResistorOhms=1000.0f, cathodeCapuF=100.0f;
    float sourceResistanceOhms=1000.0f;
    float primaryLoadOhms=3500.0f, primaryInductanceH=18.0f;
    float leakageInductancemH=12.0f, windingResistanceOhms=180.0f;
    float saturationCurrentmA=120.0f;
    float supplyResistanceOhms=180.0f, supplyCapuF=220.0f;
    float nominalGridSwingVolts=80.0f, gridCurrentKneeVolts=-1.0f, gridCurrentScale=0.020f;
};