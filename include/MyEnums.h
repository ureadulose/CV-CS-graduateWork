#ifndef MY_ENUMS_H
#define MY_ENUMS_H

enum class EventType
{
    MouseLeftPressed,
    MouseRightPressed,
    MouseMove
};

enum class OptflowType
{
    DenseFarneback,
    SparceToDense,
    SparseLucasKanade,
    DeepFlow,
    SimpleFlow,
    Calculated
};

#endif
