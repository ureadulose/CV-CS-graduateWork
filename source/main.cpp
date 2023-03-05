// standart hpps
#include <iostream>

// my hpps
#include "general/VideoHandler.h"

void main()
{
	VideoHandler VH("../resources/1.mp4", "myWindow");
	VH.Play();
}