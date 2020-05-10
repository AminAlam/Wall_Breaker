//
//  Window.h
//  Project
//
//  Created by MohammadAmin Alamalhoda on 12/26/18.
//  Copyright © 2018 MohammadAmin Alamalhoda. All rights reserved.
//

#ifndef Header_h
#define Header_h

#define BOMB 1000000
int Bomb_explod(int count_collision,int *level,int N,int Score);
void print_result(int count,int level,int N,int *Score);
void drawcircle(int x0, int y0, int radius,SDL_Renderer *renderer,int E);
void draw_R_of_boxes(int X,int Y,int R,SDL_Renderer *renderer);
void print_one_digit(int X,int Y,int R,SDL_Renderer *renderer);
struct BOX {
    int R;
    int X;
    int Y;
    int Level;
}boxes[1000];


void Window_Circle(int N , int shooterX )
{
    int Score=1,level=0,row=0,colomn=0,count=0,count1=1,count2=1,count_collision,X=50,Y=50,collision=0,w=0,Score_Change=0,l=0,Y_2=0,X_2=0;
    double theta=0;
    char NAME[30];
    char File_Name[20];
    
    printf("if you want to load a game press 1 , for making a new game press 2: ");
    scanf("%d",&l);
    if (l==1) {
    Ask_Again:
        printf("please Enter File name to load The Game :");
        scanf("%s",File_Name);
        FILE *Load_File = fopen(File_Name, "rb");
        if (Load_File != NULL) {
            printf("File loaded successfully!\n");
        }
        else {
            printf("Failed to open the file.\n");
            goto Ask_Again;
        }
        fread(boxes, sizeof(struct BOX), 1000, Load_File);
        fscanf(Load_File, "%d %d %lf %s %d %d %d", &level , &Score , &theta , NAME , &count1,&N,&shooterX);
        fclose(Load_File);
        printf("\n Welcome back %s",NAME);
        level--;
    }
    else{
    printf("\nplease Enter Your Name:");
    scanf("%s",NAME);
    }
    Loaded_From_File:
    printf("");
    SDL_Window *window;
    SDL_Init(SDL_INIT_VIDEO);
    
    window = SDL_CreateWindow(
                              "Best Game Evere",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              3*(N),
                              2*(N),
                              SDL_WINDOW_OPENGL
                              );
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    bool is_running = true;
    SDL_Event event;
    if ( SDL_PollEvent( &event ))
    {
        if ( event.type == SDL_QUIT )
        {
            is_running = false;
        }
    }
    
    while(is_running){
        
        level++;
        const_level:
        
//initializing R of Boxes START
        if(Score_Change!=0||level==1){
            for(count=1;count<N/35 -2;(count++),(count1++)){
                boxes[count1].Level=level;
                if(Score>=5){boxes[count1].R=rand()%Score;
                    if(count==rand()%10||count==rand()%10)boxes[count1].R=0;
                    if(level==rand()%10||level-count==rand()%10)boxes[count1].R=0;
                    if(Score%10==rand()%10)boxes[count1].R=BOMB;
                }
                else{ boxes[count1].R=rand()%5;
                    if(count==rand()%10||level==rand()%10||level==rand()%5||count==rand()%10||level==rand()%10)boxes[count1].R=0;
                }
            }
        }
//initializing R of Boxes END
        
//drawing boxes START
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);
     //draw shooting place START
            drawcircle(shooterX+50, 2*(N), 70,renderer,2);
        SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
            draw_R_of_boxes(shooterX,2*(N)-50,Score,renderer);
     //draw shooting place END
        
            for (row=1,count2=1; row<=level; row++) {
                for(colomn=1;colomn<N/35 -2;colomn++){
                    Y=(level-row)*70+50;
                    SDL_Rect rect_box;
                    rect_box.x=X;
                    rect_box.y=Y;
                    rect_box.w=100;
                    rect_box.h=50;
                    
                        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0 );
                        SDL_RenderDrawRect(renderer, &rect_box);
                        drawcircle(X+50, Y+20, 30,renderer,1);
                        if(boxes[count2].R!=0){
                            if (boxes[count2].R==BOMB) {
                                drawcircle(X+50,Y+20,30,renderer,0);
                            }
                            else{
                                SDL_SetRenderDrawColor(renderer, rand()+1, rand()+1, rand()+1, SDL_ALPHA_OPAQUE );
                                SDL_RenderDrawRect(renderer, &rect_box);
                            }
                            boxes[count2].X=X;
                            boxes[count2].Y=Y;
                            
                            if(boxes[count2].Y>2*(N)-100)goto GAME_OVER;
                        }
                    draw_R_of_boxes(X,Y,boxes[count2].R,renderer);
                    X+=140;
                    count2++;
                }
                
                X=50;
            }
            SDL_RenderPresent(renderer);
        
//drawing boxes END
        
    Take_Theta_Again:
        print_result(count1,level,N,&Score);
        
     //cleaning shooting line START
        
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0 );
        SDL_RenderDrawLine(renderer, shooterX+45, 2*(N), -(2*(N))/tan((180-theta)*M_PI/180)+shooterX+50 , 0);
        SDL_RenderDrawLine(renderer, shooterX+55, 2*(N), -(2*(N))/tan((180-theta)*M_PI/180)+shooterX+50 , 0);
        if(theta<90){
        SDL_RenderDrawLine(renderer, 3*(N), tan((180-theta)*M_PI/180)*(3*(N)-shooterX-50)+2*(N),tan(theta*M_PI/180)*(3*(N)-shooterX-50)+tan((180-theta)*M_PI/180)*(3*(N)-shooterX-50)+2*(N) , 0);
        }
        if (theta>90) {
            SDL_RenderDrawLine(renderer, 0, tan((180-theta)*M_PI/180)*(0-shooterX-50)+2*(N),tan(theta*M_PI/180)*(0-shooterX-50)+tan((180-theta)*M_PI/180)*(0-shooterX-50)+2*(N) , 0);
        }
        
     //cleaning shooting line END
        
        printf("\nplease enter theta: ");
        scanf("%lf",&theta);
        if((double)theta!=theta)goto Take_Theta_Again;
        
//drawing shooting line START
        
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE );
        SDL_RenderDrawLine(renderer, shooterX+45, 2*(N), -(2*(N))/tan((180-theta)*M_PI/180)+shooterX+50  , 0);
        SDL_RenderDrawLine(renderer, shooterX+55, 2*(N), -(2*(N))/tan((180-theta)*M_PI/180)+shooterX+50  , 0);
        if(theta<90){
        SDL_RenderDrawLine(renderer, 3*(N), tan((180-theta)*M_PI/180)*(3*(N)-shooterX-50)+2*(N),tan(theta*M_PI/180)*(3*(N)-shooterX-50)+tan((180-theta)*M_PI/180)*(3*(N)-shooterX-50)+2*(N)   , 0);
            
               Y_2=tan((180-theta)*M_PI/180)*(3*(N)-shooterX-50)+2*(N);
               X_2=tan(theta*M_PI/180)*(3*(N)-shooterX-50)+tan((180-theta)*M_PI/180)*(3*(N)-shooterX-50)+2*(N);
            
        }
        if (theta>90) {
            SDL_RenderDrawLine(renderer, 0, tan((180-theta)*M_PI/180)*(0-shooterX-50)+2*(N),tan(theta*M_PI/180)*(0-shooterX-50)+tan((180-theta)*M_PI/180)*(0-shooterX-50)+2*(N)   , 0);
            Y_2=tan((180-theta)*M_PI/180)*(0-shooterX-50)+2*(N);
            X_2=tan(theta*M_PI/180)*(0-shooterX-50)+tan((180-theta)*M_PI/180)*(0-shooterX-50)+2*(N);
            
        }
        SDL_RenderPresent(renderer);
        
//drawing shooting line END
        
        printf("\nfor shoot Enter 1,for changing theta Enter 0,for save current game Enter 2,for load a Game Enter 3: ");
        scanf("%d",&l);
        if(l==0)goto Take_Theta_Again;
        if (l==2) {
            printf("please enter File name to make it :");
            scanf("%s",File_Name);
            FILE *Save_File = fopen(File_Name, "wb");
            fflush(Save_File);
            fwrite (boxes, sizeof(struct BOX), 1000, Save_File);
            fprintf(Save_File, "%d %d %lf %s %d %d %d", level , Score , theta , NAME ,count1+1,N,shooterX);
            fclose(Save_File);
            printf("\nGame Saved Successfully!");
            goto Take_Theta_Again;
        }
        if(l==3){
            printf("please Enter File name to load The Game :");
            scanf("%s",File_Name);
           FILE *Load_File = fopen(File_Name, "rb");
            if (Load_File != NULL) {
                printf("File loaded successfully!\n");
            }
            else {
                printf("Failed to open the file.\n");
                goto Take_Theta_Again;
            }
            fread(boxes, sizeof(struct BOX), 1000, Load_File);
            fscanf(Load_File, "%d %d %lf %s %d %d %d", &level , &Score , &theta , NAME , &count1,&N,&shooterX);
            fclose(Load_File);
            printf("\n Welcome back %s !!!\n",NAME);
            level--;
            SDL_DestroyWindow(window);
            SDL_DestroyRenderer(renderer);
            SDL_Quit();
            goto Loaded_From_File;
        }
        
// CHECKING COLLISION START
        
         collision=0;
        Score_Change=0;
        BARKHORD_KARD_RAD_SHOD :
        if(theta>=90){
            for(row=1;row<=level;row++){
        for(count_collision=0;count_collision<N/35-3;count_collision++){
            if(boxes[row*(N/35-3)-count_collision].R==0)continue;
            if(
               (
          (  boxes[row*(N/35-3)-count_collision].X<=  (boxes[row*(N/35-3)-count_collision].Y+50-2*(N))/tan((180-theta)*M_PI/180) + shooterX+50 )
                &&
          (  (boxes[row*(N/35-3)-count_collision].Y+50-2*(N))/tan((180-theta)*M_PI/180)+shooterX+50 <= boxes[row*(N/35-3)-count_collision].X+100   )
               )
              ||
               (
            boxes[row*(N/35-3)-count_collision].Y <= tan((180-theta)*M_PI/180)*(boxes[row*(N/35-3)-count_collision].X+100 - shooterX-50) +2*(N)
               &&
           ( tan((180-theta)*M_PI/180)*(boxes[row*(N/35-3)-count_collision].X+100-shooterX-50)+2*(N)<=boxes[row*(N/35-3)-count_collision].Y+50 )
                )
               ||
               (
               boxes[row*(N/35-3)-count_collision].Y <= tan((180-theta)*M_PI/180)*(boxes[row*(N/35-3)-count_collision].X - shooterX-50) +2*(N)
               &&
               ( tan((180-theta)*M_PI/180)*(boxes[row*(N/35-3)-count_collision].X - shooterX-50) +2*(N) <=  boxes[row*(N/35-3)-count_collision].Y+50 )
               )
               ||
               (
                (  boxes[row*(N/35-3)-count_collision].X<=  (boxes[row*(N/35-3)-count_collision].Y-2*(N))/tan((180-theta)*M_PI/180) + shooterX + 50 )
                &&
                (  (boxes[row*(N/35-3)-count_collision].Y-2*(N))/tan((180-theta)*M_PI/180)+shooterX +50 <= boxes[row*(N/35-3)-count_collision].X+100   )
                )
              )
            {
                if(boxes[row*(N/35-3)-count_collision].R!=BOMB&&boxes[row*(N/35-3)-count_collision].R!=0)printf("You Hit It!!!\n");
                //when bomb exploded start
                if(boxes[row*(N/35-3)-count_collision].R==BOMB){
                    Score_Change=1;
                    Score+=Bomb_explod(row*(N/35-3)-count_collision,&level,N,Score - collision);
                    goto PassIt;
                }
                //when bomb exploded end
                for (w=1; w<=Score - collision; w++) {
                    if(boxes[row*(N/35-3)-count_collision].R==0)break;
                    boxes[row*(N/35-3)-count_collision].R--;
                    collision++;
                    if(boxes[row*(N/35-3)-count_collision].R==0){
                        Score++;Score_Change=1;boxes[row*(N/35-3)-count_collision].X=0;boxes[row*(N/35-3)-count_collision].Y=0;break;}
                }
                if (collision<Score) {
                    goto BARKHORD_KARD_RAD_SHOD;
                }
            PassIt:
                break;
            }
        }
            }
        }
        if(theta<90){
            for(count_collision=1;count_collision<=count1;count_collision++){
                if(boxes[count_collision].R==0)continue;
                if(
                   (
                    (  boxes[count_collision].X<=  (boxes[count_collision].Y+50-2*(N))/tan((180-theta)*M_PI/180) + shooterX+50 )
                    &&
                    (  (boxes[count_collision].Y+50-2*(N))/tan((180-theta)*M_PI/180)+shooterX+50 <= boxes[count_collision].X+100   )
                    )
                   ||
                   (
                    boxes[count_collision].Y <= tan((180-theta)*M_PI/180)*(boxes[count_collision].X+100 - shooterX-50) +2*(N)
                    &&
                    ( tan((180-theta)*M_PI/180)*(boxes[count_collision].X+100-shooterX-50)+2*(N)<=boxes[count_collision].Y+50 )
                    )
                   ||
                   (
                    boxes[count_collision].Y <= tan((180-theta)*M_PI/180)*(boxes[count_collision].X - shooterX-50) +2*(N)
                    &&
                    ( tan((180-theta)*M_PI/180)*(boxes[count_collision].X - shooterX-50) +2*(N) <=  boxes[count_collision].Y+50 )
                    )
                   ||
                   (
                    (  boxes[count_collision].X<=  (boxes[count_collision].Y-2*(N))/tan((180-theta)*M_PI/180) + shooterX + 50 )
                    &&
                    (  (boxes[count_collision].Y-2*(N))/tan((180-theta)*M_PI/180)+shooterX +50 <= boxes[count_collision].X+100   )
                    )
                   )
                {
                    if(boxes[count_collision].R!=BOMB&&boxes[count_collision].R!=0)printf("You Hit It!!!\n");
                    //when bomb exploded start
                    if(boxes[count_collision].R==BOMB){
                        Score_Change=1;
                        Score+=Bomb_explod(count_collision,&level,N,Score - collision);
                        goto PassIt3;
                    }
                    //when bomb exploded end
                    for (w=1; w<=Score - collision; w++) {
                        if(boxes[count_collision].R==0)break;
                        boxes[count_collision].R--;
                        collision++;
                        if(boxes[count_collision].R==0){
                            Score++;Score_Change=1;boxes[count_collision].X=0;boxes[count_collision].Y=0;break;}
                    }
                    if (collision<Score) {
                        goto BARKHORD_KARD_RAD_SHOD;
                    }
                PassIt3:
                    break;
                }
            }
        }
        if (collision<Score)
        {
            if(theta<90){
            if(
            tan((180-theta)*M_PI/180)*(3*(N)-shooterX-50)+2*(N)>0
            &&
            tan((180-theta)*M_PI/180)*(3*(N)-shooterX-50)+2*(N)<2*(N)
               )
            {
            BARKHORD_KARD_RAD_SHOD2:
                 for(count_collision=1;count_collision<=count1;count_collision++){
                    if(boxes[count_collision].R==0)continue;
                    if(
                    (    -(boxes[count_collision].Y+50-Y_2)*(X_2-3*(N))/Y_2 +3*(N) >= boxes[count_collision].X
                       &&
                       -(boxes[count_collision].Y+50-Y_2)*(X_2-3*(N))/Y_2 +3*(N) <= boxes[count_collision].X+100
                     )
                       ||
                     (  -(Y_2)*(boxes[count_collision].X-3*(N))/(X_2-3*(N))+Y_2 >= boxes[count_collision].Y
                       &&
                       -(Y_2)*(boxes[count_collision].X-3*(N))/(X_2-3*(N))+Y_2 <= boxes[count_collision].Y+50 )
                       ||
                       ( -(Y_2)*(boxes[count_collision].X+100-3*(N))/(X_2-3*(N))+Y_2 >= boxes[count_collision].Y
                        &&
                    -(Y_2)*(boxes[count_collision].X+100-3*(N))/(X_2-3*(N))+Y_2 <= boxes[count_collision].Y+50 )
                       )
                    {
                        if(boxes[count_collision].R!=BOMB&&boxes[count_collision].R!=0)printf("You Hit It!!!\n");
                        //when bomb exploded start
                        if(boxes[count_collision].R==BOMB){
                            Score_Change=1;
                            Score+=Bomb_explod(count_collision,&level,N,Score - collision);
                            goto PassIt2;
                        }
                        //when bomb exploded end
                        for (w=1; w<=Score - collision; w++) {
                            if(boxes[count_collision].R==0)break;
                            boxes[count_collision].R--;
                            collision++;
                            if(boxes[count_collision].R==0){
                                Score++;Score_Change=1;boxes[count_collision].X=0;boxes[count_collision].Y=0;break;}
                        }
                        if (collision<Score) {
                            goto BARKHORD_KARD_RAD_SHOD2;
                        }
                    PassIt2:
                        break;
                    }
                }
            }
               }
            if(theta>90){
                if(
                   tan((180-theta)*M_PI/180)*(0-shooterX-50)+2*(N)>0
                   &&
                   tan((180-theta)*M_PI/180)*(0-shooterX-50)+2*(N)<2*(N)
                   )
                {
                BARKHORD_KARD_RAD_SHOD3:
                    for(row=1;row<=level;row++){
                        for(count_collision=0;count_collision<N/35-3;count_collision++){
                            if(boxes[row*(N/35-3)-count_collision].R==0)continue;
                            if(
                               (    -(boxes[row*(N/35-3)-count_collision].Y+50-Y_2)*(X_2-0)/Y_2 +0 >= boxes[row*(N/35-3)-count_collision].X
                                &&
                                -(boxes[row*(N/35-3)-count_collision].Y+50-Y_2)*(X_2-0)/Y_2 +0 <= boxes[count_collision].X+100
                                )
                               ||
                               (  -(Y_2)*(boxes[row*(N/35-3)-count_collision].X-0)/(X_2-0)+Y_2 >= boxes[count_collision].Y
                                &&
                                -(Y_2)*(boxes[row*(N/35-3)-count_collision].X-0)/(X_2-0)+Y_2 <= boxes[row*(N/35-3)-count_collision].Y+50 )
                               ||
                               ( -(Y_2)*(boxes[row*(N/35-3)-count_collision].X+100-0)/(X_2-0)+Y_2 >= boxes[row*(N/35-3)-count_collision].Y
                                &&
                                -(Y_2)*(boxes[row*(N/35-3)-count_collision].X+100-0)/(X_2-0)+Y_2 <= boxes[row*(N/35-3)-count_collision].Y+50 )
                               )
                            {
                                if(boxes[row*(N/35-3)-count_collision].R!=BOMB&&boxes[row*(N/35-3)-count_collision].R!=0)printf("You Hit It!!!\n");
                                //when bomb exploded start
                                if(boxes[row*(N/35-3)-count_collision].R==BOMB){
                                    Score_Change=1;
                                    Score+=Bomb_explod(row*(N/35-3)-count_collision,&level,N,Score - collision);
                                    goto PassIt5;
                                }
                                //when bomb exploded end
                                for (w=1; w<=Score - collision; w++) {
                                    if(boxes[row*(N/35-3)-count_collision].R==0)break;
                                    boxes[row*(N/35-3)-count_collision].R--;
                                    collision++;
                                    if(boxes[row*(N/35-3)-count_collision].R==0){
                                        Score++;Score_Change=1;boxes[row*(N/35-3)-count_collision].X=0;boxes[row*(N/35-3)-count_collision].Y=0;break;}
                                }
                                if (collision<Score) {
                                    goto BARKHORD_KARD_RAD_SHOD;
                                }
                            PassIt5:
                                break;
                            }
                        }
                    }
                }
            }
        }
        
// CHECKING COLLISION END
        
        if(Score_Change==0){
            goto const_level;
        }
    }
GAME_OVER:
    printf("\n...Game Over...\n");
    print_result(count1,level,N,&Score);
    SDL_Delay(20000);
}
int Bomb_explod(int count_collision,int *level,int N,int Score){
    int i=1;
    boxes[count_collision].R=0;
    printf("You Hit a BOMB!!!\n");
    //left--
    if (boxes[count_collision-1].R!=0&&(boxes[count_collision-1].Level==boxes[count_collision].Level)) {
        if(boxes[count_collision-1].R==BOMB){Bomb_explod(count_collision-1,level,N,Score);}
        else{
            if(boxes[count_collision-1].R!=0){
                boxes[count_collision-1].R-=Score;
                if(boxes[count_collision-1].R<0)boxes[count_collision-1].R=0;
                if(boxes[count_collision-1].R==0)i++;}
        }
    }
    //right--
    if (boxes[count_collision+1].R!=0&&(boxes[count_collision+1].Level==boxes[count_collision].Level)) {
        if(boxes[count_collision+1].R==BOMB){Bomb_explod(count_collision+1,level,N,Score);}
        else{
            if(boxes[count_collision+1].R!=0){
                boxes[count_collision+1].R-=Score;
                if(boxes[count_collision+1].R<0)boxes[count_collision+1].R=0;
                if(boxes[count_collision+1].R==0)i++;}
        }
    }
    //up--
    if(boxes[count_collision + N/35 -3].R!=0&&(boxes[count_collision].Level!=*level)){
        if(boxes[count_collision + N/35 -3].R==BOMB){Bomb_explod(count_collision + N/35 -3,level,N,Score);}
        else{
            if(boxes[count_collision + N/35 -3].R!=0){
                boxes[count_collision + N/35 -3].R-=Score;
                if(boxes[count_collision + N/35 -3].R<0)boxes[count_collision + N/35 -3].R=0;
                if(boxes[count_collision + N/35 -3].R==0)i++;}
        }
    }
    //down--
    if(boxes[count_collision].Level!=1){
        if(boxes[count_collision - (N/35 -3)].R==BOMB){Bomb_explod(count_collision - (N/35 -3),level,N,Score);}
        else{
            if(boxes[count_collision - (N/35 -3)].R!=0){
                boxes[count_collision - (N/35 -3)].R-=Score;
                if(boxes[count_collision - (N/35 -3)].R<0)boxes[count_collision - (N/35 -3)].R=0;
                if(boxes[count_collision - (N/35 -3)].R==0)i++;}
        }
    }
    //down_right--
    if(boxes[count_collision].Level!=1){
        if(boxes[count_collision - (N/35 -3)+1].R==BOMB){Bomb_explod(count_collision + (N/35 -3)+1,level,N,Score);}
        else{
            if(boxes[count_collision - (N/35 -3)+1].R!=0){
                boxes[count_collision - (N/35 -3)+1].R-=Score;
                if(boxes[count_collision - (N/35 -3)+1].R<0)boxes[count_collision - (N/35 -3)+1].R=0;
                if(boxes[count_collision - (N/35 -3)+1].R==0)i++;}
        }
    }
    //down_left--
    if(boxes[count_collision].Level!=1){
        if(boxes[count_collision - (N/35 -3)-1].R==BOMB){Bomb_explod(count_collision + (N/35 -3)-1,level,N,Score);}
        else{
            if(boxes[count_collision - (N/35 -3)-1].R!=0){
                boxes[count_collision - (N/35 -3)-1].R-=Score;
                if(boxes[count_collision - (N/35 -3)-1].R<0)boxes[count_collision - (N/35 -3)-1].R=0;
                if(boxes[count_collision - (N/35 -3)-1].R==0)i++;}
        }
    }
    //up_right--
    if(boxes[count_collision].Level!=*level){
        if(boxes[count_collision + N/35 -2].R==BOMB){Bomb_explod(count_collision + N/35 -2,level,N,Score);}
        else{
            if(boxes[count_collision + N/35 -2].R!=0){
                boxes[count_collision + N/35 -2].R-=Score;
                if(boxes[count_collision + N/35 -2].R<0)boxes[count_collision + N/35 -2].R=0;
                if(boxes[count_collision + N/35 -2].R!=0)i++;}
        }
    }
    //up_left
    if(boxes[count_collision].Level!=*level){
        if(boxes[count_collision + N/35 -4].R==BOMB){Bomb_explod(count_collision + N/35 -4,level,N,Score);}
        else{
            if(boxes[count_collision + N/35 -4].R!=0){
                boxes[count_collision + N/35 -3].R-=Score;
                if(boxes[count_collision + N/35 -3].R<0)boxes[count_collision + N/35 -3].R=0;
                if(boxes[count_collision + N/35 -4].R==0)i++;}
        }
    }return i;
}
void drawcircle(int x0, int y0, int radius, SDL_Renderer *renderer,int E){
    int x = radius-1;
    int y = 0;
    int dx = 1;
    int dy = 1;
    int err = dx - (radius << 1);
    if(E==1)SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    if(E==0)SDL_SetRenderDrawColor(renderer, rand()*10+1, rand()+1, rand()+1, SDL_ALPHA_OPAQUE );
    if(E==2)SDL_SetRenderDrawColor(renderer, 255, 255,255, 255);
    
    while (x >= y)
    {
        SDL_RenderDrawPoint(renderer, x0 + x, y0 + y);
        SDL_RenderDrawPoint(renderer, x0 + y, y0 + x);
        SDL_RenderDrawPoint(renderer, x0 - y, y0 + x);
        SDL_RenderDrawPoint(renderer, x0 - x, y0 + y);
        SDL_RenderDrawPoint(renderer, x0 - x, y0 - y);
        SDL_RenderDrawPoint(renderer, x0 - y, y0 - x);
        SDL_RenderDrawPoint(renderer, x0 + y, y0 - x);
        SDL_RenderDrawPoint(renderer, x0 + x, y0 - y);
        
        if (err <= 0)
        {
            y++;
            err += dy;
            dy += 2;
        }
        
        if (err > 0)
        {
            x--;
            dx += 2;
            err += dx - (radius << 1);
        }
    }
}
void print_result(int count,int level,int N,int *Score){
    int i=1,k=1;
    for(i=1;i<=level;i++){
        printf("\n               row %d :",i);
        for (k=1;k<N/35 -2; k++) {
            if(boxes[(level-i)*(N/35 -3)+k].R==BOMB){printf(" B ");}
            else{
                if(boxes[(level-i)*(N/35 -3)+k].R<0)boxes[(level-i)*(N/35 -3)+k].R=0;
                printf(" %d ",boxes[(level-i)*(N/35 -3)+k].R);}
        }
    }
    printf("\nScore : %d\n",*Score);
}
void draw_R_of_boxes(int X,int Y,int R,SDL_Renderer *renderer){
 
    if((int)(R/10)==0){
        print_one_digit(X+33, Y, R,renderer);
    }
    if((int)(R/100)==0&&(int)(R/10)!=0){
        print_one_digit(X+20, Y, (int)(R/10),renderer);
        print_one_digit(X+55, Y, R%10,renderer);
    }
    if((int)(R/1000)==0&&(int)(R/10)!=0&&(int)(R/100)!=0){
        print_one_digit(X, Y, (int)(R/100),renderer);
        print_one_digit(X+33, Y, (int)(R/10),renderer);
        print_one_digit(X+66, Y, R%10,renderer);
    }
}
void print_one_digit(int X,int Y,int R,SDL_Renderer *renderer){
    if (R==0) {
        SDL_RenderDrawLine(renderer, X+5, Y+10, X+30, Y+10);
        SDL_RenderDrawLine(renderer, X+5, Y+40, X+30, Y+40);
        SDL_RenderDrawLine(renderer, X+5, Y+10, X+5, Y+40);
        SDL_RenderDrawLine(renderer, X+30, Y+10, X+30, Y+40);
    }
    if (R==1) {
        SDL_RenderDrawLine(renderer, X+17, Y+40, X+17, Y+10);
    }
    if (R==2) {
        SDL_RenderDrawLine(renderer, X+5, Y+10, X+30, Y+10);
        SDL_RenderDrawLine(renderer, X+5, Y+40, X+30, Y+40);
        SDL_RenderDrawLine(renderer, X+5, Y+25, X+30, Y+25);
        SDL_RenderDrawLine(renderer, X+30, Y+10, X+30, Y+25);
        SDL_RenderDrawLine(renderer, X+5, Y+25, X+5, Y+40);
    }
    if (R==3) {
        SDL_RenderDrawLine(renderer, X+5, Y+10, X+30, Y+10);
        SDL_RenderDrawLine(renderer, X+5, Y+40, X+30, Y+40);
        SDL_RenderDrawLine(renderer, X+5, Y+25, X+30, Y+25);
        SDL_RenderDrawLine(renderer, X+30, Y+10, X+30, Y+40);
    }
    if (R==4) {
        SDL_RenderDrawLine(renderer, X+30, Y+10, X+30, Y+40);
        SDL_RenderDrawLine(renderer, X+5, Y+10, X+5, Y+20);
        SDL_RenderDrawLine(renderer, X+5, Y+20, X+30, Y+20);
    }
    if (R==5) {
        SDL_RenderDrawLine(renderer, X+5, Y+10, X+30, Y+10);
        SDL_RenderDrawLine(renderer, X+5, Y+25, X+30, Y+25);
        SDL_RenderDrawLine(renderer, X+5, Y+40, X+30, Y+40);
        SDL_RenderDrawLine(renderer, X+5, Y+10, X+5, Y+25);
        SDL_RenderDrawLine(renderer, X+30, Y+25, X+30, Y+40);
    }
    if (R==6) {
        SDL_RenderDrawLine(renderer, X+5, Y+10, X+30, Y+10);
        SDL_RenderDrawLine(renderer, X+5, Y+25, X+30, Y+25);
        SDL_RenderDrawLine(renderer, X+5, Y+40, X+30, Y+40);
        SDL_RenderDrawLine(renderer, X+30, Y+25, X+30, Y+40);
        SDL_RenderDrawLine(renderer, X+5, Y+10, X+5, Y+40);
    }
    if (R==7) {
        SDL_RenderDrawLine(renderer, X+5, Y+10, X+30, Y+10);
        SDL_RenderDrawLine(renderer, X+30, Y+10, X+5, Y+40);
    }
    if (R==8) {
        SDL_RenderDrawLine(renderer, X+5, Y+10, X+30, Y+10);
        SDL_RenderDrawLine(renderer, X+5, Y+25, X+30, Y+25);
        SDL_RenderDrawLine(renderer, X+5, Y+40, X+30, Y+40);
        SDL_RenderDrawLine(renderer, X+30, Y+10, X+30, Y+40);
        SDL_RenderDrawLine(renderer, X+5, Y+10, X+5, Y+40);
    }
    if (R==9) {
        SDL_RenderDrawLine(renderer, X+30, Y+10, X+30, Y+40);
        SDL_RenderDrawLine(renderer, X+5, Y+10, X+5, Y+20);
        SDL_RenderDrawLine(renderer, X+5, Y+20, X+30, Y+20);
        SDL_RenderDrawLine(renderer, X+5, Y+10, X+30, Y+10);
    }
    
}
#endif /* Header_h */
