//
//  main.c
//  Project
//
//  Created by MohammadAmin Alamalhoda on 12/26/18.
//  Copyright © 2018 MohammadAmin Alamalhoda. All rights reserved.
//
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2_image/SDL_image.h>
#include "Window.h"
int main(){
    int N=0,Shooter;;
    printf("please Enter N (for best experience 300< N < 400):");
    scanf("%d",&N);
    printf("please Enter X coordinate of Shooter(80 < Shooter place < %d ):",3*N-80);
    scanf("%d",&Shooter);
    
    

    Window_Circle(N,Shooter);  
}

