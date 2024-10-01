#include "controller.h"
#include <string.h>
#include <stdlib.h>

__weak void onLeftJoystickMove(int x, int y) {}
__weak void onRightJoystickMove(int x, int y) {}
__weak void onButtonCreateClick() {}
__weak void onButtonOptionsClick() {}
__weak void onButtonTriangleClick() {}
__weak void onButtonCircleClick() {}
__weak void onButtonCrossClick() {}
__weak void onButtonSquareClick() {}
__weak void onButtonL1Click() {}
__weak void onButtonR1Click() {}
__weak void onButtonL3Click() {}
__weak void onButtonR3Click() {}
__weak void onButtonUpClick() {}
__weak void onButtonDownClick() {}
__weak void onButtonLeftClick() {}
__weak void onButtonRightClick() {}
__weak void onL2Change(int l2Value) {}
__weak void onR2Change(int r2Value) {}

void processData(char *data) {
    char *ptr;

		if ((ptr = strstr(data, "L2:")) != NULL) {
        int l2Value = strtol(ptr + 3, NULL, 10);
        onL2Change(l2Value);  
    }


    if ((ptr = strstr(data, "R2:")) != NULL) {
        int r2Value = strtol(ptr + 3, NULL, 10);
        onR2Change(r2Value); 
    }
		
    if ((ptr = strstr(data, "LX:")) != NULL) {
        int leftHatX = strtol(ptr + 3, &ptr, 10);
        int leftHatY = strtol(ptr + 4, NULL, 10);  
        onLeftJoystickMove(leftHatX, leftHatY);
    }

    if ((ptr = strstr(data, "RX:")) != NULL) {
        int rightHatX = strtol(ptr + 3, &ptr, 10);
        int rightHatY = strtol(ptr + 4, NULL, 10);  
        onRightJoystickMove(rightHatX, rightHatY);
    }

    if (strstr(data, "CRT") != NULL) {
        onButtonCreateClick();
    }

    if (strstr(data, "OPT") != NULL) {
        onButtonOptionsClick();
    }

    if (strstr(data, "GT") != NULL) {
        onButtonTriangleClick();
    }

    if (strstr(data, "GC") != NULL) {
        onButtonCircleClick();
    }

    if (strstr(data, "GX") != NULL) {
        onButtonCrossClick();
    }

    if (strstr(data, "GS") != NULL) {
        onButtonSquareClick();
    }

    if (strstr(data, "L1") != NULL) {
        onButtonL1Click();
    }

    if (strstr(data, "R1") != NULL) {
        onButtonR1Click();
    }

    if (strstr(data, "L3") != NULL) {
        onButtonL3Click();
    }

    if (strstr(data, "R3") != NULL) {
        onButtonR3Click();
    }

    if (strstr(data, "DU") != NULL) {
        onButtonUpClick();
    }

    if (strstr(data, "DD") != NULL) {
        onButtonDownClick();
    }

    if (strstr(data, "DL") != NULL) {
        onButtonLeftClick();
    }

    if (strstr(data, "DR") != NULL) {
        onButtonRightClick();
    }
}