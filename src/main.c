/* Work ON Intgration of Polecheck and development of it, as well as Drawnonmove clearing the screen between each transiotion*/
#include <sys/util.h>
#include <ti/real.h>
#include <sys/timers.h>

#include <string.h>
#include <math.h>

#include <graphx.h>
#include <keypadc.h>
#include <fileioc.h>
#include <compression.h>

/* Include the sprite data */
#include "gfx/gfx.h"

#define START_X ((GFX_LCD_WIDTH - cmcf_width) / 2)
#define START_Y ((GFX_LCD_HEIGHT - cmcf_height) / 2)

/* Create a buffer to store the background behind the sprite */

gfx_UninitedSprite(background, cmcf_width, cmcf_height);
char tempstring[10];
int i;
int collisionobj[6][30] = {{1,1,2,0,2,2,2,2,2,2,2,2,2,2,2,2,2,1,2,3,3}, {50,100,40,0,200,200,200,200,216,232,248,264,248,264,280,280,280,100,254,50,75},{190,200,200,0,107,91,75,75,75,75,75,75,119,119,75,91,107,30,91,200,200},{stump_width,berby_width,stump_width,ember_width,block_width-12,block_width-12,block_width-12,block_height,block_height,block_height,block_height,block_height,block_height,block_height,block_width-12,block_width-12,block_width-12,crash_width*2,barrel_width,berby_width,berby_width},{stump_height,berby_height,stump_height,ember_height,block_height,block_height,block_height,block_width-12,block_width-12,block_width-12,block_width-12,block_width-12,block_width-12,block_width-12,block_height,block_height,block_height,crash_height*2,barrel_height,berby_height,berby_height},{1,2,1,3,4,4,4,5,5,5,5,5,5,5,4,4,4,6,7,2,2}};
/* ***Define all of the functions before main*/
void PrestonMoves(int x, int y, int ori, int tool, int stat);
int poscheck(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2, int ca);
int GabeRead(int x, uint8_t z);
void Emote(int x, int y);
void Drawnonmove(int scr);
void peakcinema(int starty, char str[]);
int PoleCheck(int x, int y, int type, int scr);
void ScreenNamedVaugh();

int main(void)
{
    /* *** Intilize all Varibles(even if they get appvared)*/
    int ori = 1;
    int stat = 0;
    int tool = 0;
    int woods = 0;
    int berries = 0;
    int screen = 1;
    int day = 0;
    int boozlian = 0;
    int story = 0;
    /* Vaughn is the goat, he is health, hunger, and heat*/
    int vaughn[3] = {3000000, 1000000, 1000000};
    int inventory[5] = {1, 5, 3, 0, 0};
    int fireplace[2] = {0,0};
    int brew[2] = {0,0};
    /*int axedrop[3] = {0,0,0}; */


    background->width = cmcf_width;
    background->height = cmcf_height;

    /* All of the strings of diffrent saved varibles, will remove this latter on */
    char strx[5] = "";
    char stry[5] = "";

    char strscreen[2] = "";

    char strtool[5] = "";

    char strday[8] = "";
    char strstory[2] = "";

    char strberries[8] = "";

    char strbeer[8] = "";

    char firestat[1] = "";
    char firex[4] = "";
    char firey[4] = "";
    char firefuel[8] = "";

    char brewin[8] = "";
    char brewout[8] = "";

    char strvaughn[8] = "";
    char strhunger[8] = "";
    char strtemp[8] = "";
    char strwood[1] = "";
    uint8_t ryanvar;
    int x = START_X;
    int y = START_Y;
    /* Initialize the graphics */

    /* ryan was a teammate of mine and so I choose the varible to be nammed after him, he was really important and was like an older brother I never had*/
    if(ti_Open("COLDPI","r")==0){
        ryanvar = ti_Open("COLDPI","w+");
        }else{
        ryanvar = ti_Open("COLDPI","r+");
        x = GabeRead(5, ryanvar);
        y = GabeRead(5, ryanvar);
        screen = GabeRead(2, ryanvar);
        tool = GabeRead(5, ryanvar);
        day = GabeRead(8, ryanvar);
        story = GabeRead(2, ryanvar);
        berries = GabeRead(8, ryanvar);
        woods = GabeRead(1, ryanvar);
        boozlian = GabeRead(8, ryanvar);
        collisionobj[0][3] = GabeRead(1, ryanvar);
        collisionobj[1][3] = GabeRead(4, ryanvar);
        collisionobj[2][3] = GabeRead(4, ryanvar);
        fireplace[1] = GabeRead(8, ryanvar);
        brew[0] = GabeRead(8, ryanvar);
        brew[1] = GabeRead(8, ryanvar);
        vaughn[0] = GabeRead(8, ryanvar);
        vaughn[1] = GabeRead(8, ryanvar);
        vaughn[2] = GabeRead(8, ryanvar);


        if(berries>0){
            inventory[3] = 4;
        }
        if(woods>0){
            inventory[4] = 2;
        }
        if(collisionobj[0][3]!=0){
            inventory[2] = 0;
        }
    }
    gfx_Begin();
    

    /* Set the palette for the sprites */
    gfx_SetPalette(global_palette, sizeof_global_palette, 0);
    gfx_SetTransparentColor(0);
    gfx_FillScreen(2);
    peakcinema(20,"Preston");
    peakcinema(30,"Preston wake up");
    peakcinema(40,"You're the only survivor of the team");
    peakcinema(50,"You need to survive till extraction");
    peakcinema(60,"Protect the data at all costs");
    peakcinema(70,"Keep in contact with the radio");
    peakcinema(80,"Central Command Over and Out");
    delay(2000);
    gfx_FillScreen(2);
    peakcinema(40,"Day 0");
    peakcinema(50,"Objective:    Survive");
    delay(2000);

    ScreenNamedVaugh();
    
    if(screen ==1){
    /* ***Load all non moving entites, collision and noncollision*/
    Drawnonmove(1);


    }
    /* Get the original background behind the sprite */
    gfx_GetSprite(background, x, y);

    /* Draw the main sprite */
    PrestonMoves(x, y, ori, tool, stat);

    /* Copy the buffer to the screen */
    /* Same as gfx_Blit(gfx_buffer) */
    gfx_BlitBuffer();

    do
    {
        kb_key_t arrows;

        /* Scan the keypad to update kb_Data */
        kb_Scan();

        /* Get the arrow key statuses */
        arrows = kb_Data[7];
        if (vaughn[2]>0){
            if (fireplace[1]==0 || collisionobj[0][3]!=screen || (poscheck(x, y, cmcf_width, cmcf_height, collisionobj[1][3]-50, collisionobj[2][3]-50, ember_width+100, ember_height+100, 1) && poscheck(x, y, cmcf_width, cmcf_height, collisionobj[1][3]-50, collisionobj[2][3]-50, ember_width+100, ember_height+100, 3) && poscheck(x, y, cmcf_width, cmcf_height, collisionobj[1][3]-50, collisionobj[2][3]-50, ember_width+100, ember_height+100, 3) && poscheck(x, y, cmcf_width, cmcf_height, collisionobj[1][3]-50, collisionobj[2][3]-50, ember_width+100, ember_height+100, 4))){
            vaughn[2] -= 650;
            }
        }
        if (vaughn[1]>0){
            vaughn[1] -= 150;
        } else{
            vaughn[1] = 0;
        }
        if (vaughn[0]>1 && (vaughn[1]<100000 || vaughn[2] < 100000)){
            vaughn[0] -= 750;
        } else if (vaughn[0]<0){
            vaughn[0] = 0;
        }
        /* *** All of the diffrent inventory swaps*/
        if (kb_Data[1] & kb_Yequ){
            tool = inventory[0];
        }
        if (kb_Data[1] & kb_Zoom){
            tool = inventory[2];
        }
        if ((kb_Data[1] & kb_Window)){
            tool = inventory[1];
        }
        if ((kb_Data[1] & kb_Graph)){
            tool = inventory[4];
        }
        if ((kb_Data[6] & kb_Div)){
            Emote(x,y);
        }
        if ((kb_Data[1] & kb_Trace)){
            tool = inventory[3];
        } 
        if ((kb_Data[1] & kb_Mode) && (tool!=0)){
            if(tool==2){
                woods = 0;
                inventory[tool-1]=0;
            }
            if(tool==4){
                berries = 0;
                inventory[tool-1]=0;
            }
            /*if(tool==1){
                axedrop[0] = 1;
                axedrop[1] = x+2;
                axedrop[2] = y+30;
            } */
            tool = 0;
        }
        if(day/100000>0 && story==0){
             story=1;
        }
        if(brew[0]>0 && brew[1]<90000){
                brew[0] -= 100;
                brew[1] += 100;
                if(brew[0]>0){
                    gfx_TransparentSprite(berry, 257, 96);
                }
                if(brew[0]<=0 && brew[1]>0){
                    gfx_TransparentSprite(barrel, 254, 91);
                }
                if(brew[0]<=0 && brew[1]>0){
                    gfx_TransparentSprite(beer, 257, 96);
                }
            }
        /* *** 2nd is the action key */
        if (kb_Data[1] & kb_2nd){
            /* *** Collecting wood and berries respectively*/
            if(tool==1){
            if(woods<9  && (PoleCheck(x-2, y, 1, screen) || PoleCheck(x+2, y, 1, screen) || PoleCheck(x, y-2, 1, screen) || PoleCheck(x, y+2, 1, screen)) ){
                woods += 1;
                inventory[4] = 2;
            }
            if(berries<90000 && (PoleCheck(x-2, y, 2, screen) || PoleCheck(x+2, y, 2, screen) || PoleCheck(x, y-2, 2, screen) || PoleCheck(x, y+2, 2, screen))){
                berries += 500;
                inventory[3] = 4;
                stat = 1;
                
            } else stat = 1;
            if(boozlian+brew[1]<90000 && inventory[3]==0 && brew[0]<=0 && (PoleCheck(x-2, y, 7, screen) || PoleCheck(x+2, y, 7, screen) || PoleCheck(x, y-2, 7, screen) || PoleCheck(x, y+2, 7, screen))){
                inventory[3] = 6;
                boozlian += brew[1];
                brew[1] = 0;
                gfx_TransparentSprite(barrel, 254, 91);
                
            }
            } else stat = 1;
            if(tool==6){
            if(vaughn[1]<1000000 && boozlian>0){
                boozlian -= 100;
                vaughn[1] +=1000;
                if(vaughn[0]<3000000){
                    vaughn[0]-=100;
                }
                if(vaughn[2]<1000000){
                    vaughn[2]+=500;
                }
            }
            }
            if(tool==5){
            if(story>0){
                gfx_SetDrawScreen();
                gfx_FillScreen(2);
            if(story==1){
                peakcinema(20,"Preston, This is Central Command");
                peakcinema(30,"We have located a possible threat to your position");
                peakcinema(40,"There is a storm headed your way in a day");
                peakcinema(50,"Seek shelter in the nearby Cabin NW of the crash");
                peakcinema(60,"Repair it using nearby materials");
                peakcinema(70,"Remember, we're counting on you");
                peakcinema(80,"Central Command over and out");
                peakcinema(110,"Objective:      Seek Shelter and Repair Shelter");
            }
            if(story==2){
                peakcinema(20,"Preston, This is Central Command");
            }
            if(story==3){
                peakcinema(20,"Preston, This is Central Command");
            }
                story *= -1;
                ScreenNamedVaugh();
            }
            }
            if(tool==4){
            if(vaughn[1]<1000000 && berries>0 && (!PoleCheck(x-2, y, 7, screen) || !PoleCheck(x+2, y, 7, screen) || !PoleCheck(x, y-2, 7, screen) || !PoleCheck(x, y+2, 7, screen))){
                berries -= 100;
                vaughn[1] +=1000;
                if(vaughn[0]<3000000){
                    vaughn[0]+=750;
                }
            }
            if(berries>0 && (PoleCheck(x-2, y, 7, screen) || PoleCheck(x+2, y, 7, screen) || PoleCheck(x, y-2, 7, screen) || PoleCheck(x, y+2, 7, screen)) && (brew[0]+brew[1])<90000){
                berries -= 500;
                brew[0] += 500;
            }
            }
            
            if(tool==3){
                /* *** Placing down a fireplace*/
            if((woods!=0) && (inventory[2]==3) && poscheck(x+2, y-50, ember_width, ember_height, 50, 120, stump_width, stump_height, 1) && poscheck(x+2, y-50, ember_width, ember_height, 50, 120, stump_width, stump_height, 2) && poscheck(x+2, y-50, ember_width, ember_height, 50, 120, stump_width, stump_height, 3) && poscheck(x+2, y-50, ember_width, ember_height, 50, 120, stump_width, stump_height, 4)){
                tool = 0;
                inventory[4] = 0;
                collisionobj[0][3] = screen;
                collisionobj[1][3] = x+2;
                collisionobj[2][3] = y+50;
                fireplace[1] = 100000 * woods;
                woods = 0;
            }
            }
            /*If the player is inside of the fireplace, has extra wood, and is in an active state: decrease their wood and increase the fire's fuel */
            if(tool==2 && woods > 0 && fireplace[1]<900000 && (!poscheck(x, y, cmcf_width, cmcf_height, collisionobj[1][3]-20, collisionobj[2][3]-20, ember_width+40, ember_height+40, 1) || !poscheck(x, y, cmcf_width, cmcf_height, collisionobj[1][3]-20, collisionobj[2][3]-20, ember_width+40, ember_height+40, 3) || !poscheck(x, y, cmcf_width, cmcf_height, collisionobj[1][3]-20, collisionobj[2][3]-20, ember_width+40, ember_height+40, 3) || !poscheck(x, y, cmcf_width, cmcf_height, collisionobj[1][3]-20, collisionobj[2][3]-20, ember_width+40, ember_height+40, 4))){
                woods-=1;
                fireplace[1]+=100000;
            }
            if(woods==9 && tool==2 && (poscheck(x, y, cmcf_width, cmcf_height, collisionobj[1][3], collisionobj[2][3], ember_width, ember_height, 1) || poscheck(x, y, cmcf_width, cmcf_height, collisionobj[1][3], collisionobj[2][3], ember_width, ember_height, 3) || poscheck(x, y, cmcf_width, cmcf_height, collisionobj[1][3], collisionobj[2][3], ember_width, ember_height, 3) || poscheck(x, y, cmcf_width, cmcf_height, collisionobj[1][3], collisionobj[2][3], ember_width, ember_height, 4))){
                if (ori == 4){
                }
                
            }

            
        }
        if(woods == 0){
            inventory[4] = 0;
        }
        if (collisionobj[0][3]==screen){
            if(fireplace[1]>0 && vaughn[2]<1000000 && (!poscheck(x, y, cmcf_width, cmcf_height, collisionobj[1][3]-50, collisionobj[2][3]-50, ember_width+100, ember_height+100, 1) || !poscheck(x, y, cmcf_width, cmcf_height, collisionobj[1][3]-50, collisionobj[2][3]-50, ember_width+100, ember_height+100, 3) || !poscheck(x, y, cmcf_width, cmcf_height, collisionobj[1][3]-50, collisionobj[2][3]-50, ember_width+100, ember_height+100, 3) || !poscheck(x, y, cmcf_width, cmcf_height, collisionobj[1][3]-50, collisionobj[2][3]-50, ember_width+100, ember_height+100, 4))){
                vaughn[2]+=750;
            }
            if (fireplace[1]>0){
                fireplace[1]-=250;
            } else fireplace[1] = 0;
        }
        /* Check if any arrows are pressed */
        if (arrows)
        {
            /* Do different directions depending on the keypress */
            if (arrows & kb_Right && PoleCheck(x+2, y, -3, screen))
            {
                if(x<310){
                x += 2;
                }
                else{
                    x = 0;
                    if(screen == 1){
                    screen = 2;
                    }
                    if(screen == 3){
                    screen = 1;
                    }
                    Drawnonmove(screen);
                }
                ori = 3;
            }
            if (arrows & kb_Left && PoleCheck(x-2, y, -2, screen))
            {
                if(x>0){
                x -= 2;
                } else{
                    x = 305;
                    if(screen == 1){
                    screen = 3;
                    }
                    if(screen == 2){
                    screen = 1;
                    }
                    Drawnonmove(screen);
                }
                ori = 2;
            }
            if (arrows & kb_Down && PoleCheck(x, y+2, -1, screen))
            {
                if(y<211){
                y += 2;
                }
                ori = 1;
            }
            if ((arrows & kb_Up) && PoleCheck(x, y-2, -4, screen))
            {
                if(y>30){
                y -= 2;
                }
                ori = 4;
            }
           /* if(0==poscheck(x, y, cmcf_width, cmcf_height, axedrop[1], axedrop[2], axe_width, axe_height, 4)){
                axedrop[0] = 0;
                inventory[0] = 1;
            } */

        }
        /* ***Updates Position allong with all of the diffrent updates for diffrent items*/
        PrestonMoves(x, y, ori, tool, stat);
        gfx_SetColor(2);
        gfx_FillRectangle(277, 6, 22, 18);
        if(inventory[4]==2){
        gfx_TransparentSprite(wood, 277, 6);
        gfx_SetTextXY(292, 15);
        gfx_PrintInt(woods, 1);
        }
        gfx_SetColor(4);
        if(inventory[1]==5){
            
        gfx_TransparentSprite(radio, 208, 6);
        if(story>0){
            gfx_FillCircle_NoClip(222, 18, 3);
        }
        }
        gfx_SetColor(2);
        gfx_FillRectangle(253, 6, 22, 18);
        if(inventory[3]==4){
        gfx_TransparentSprite(berry, 253, 6);
        gfx_SetTextXY(267, 15);
        gfx_PrintInt(berries/10000, 1);
        }
        if(inventory[3]==6){
        gfx_TransparentSprite(beer, 253, 6);
        gfx_SetTextXY(267, 15);
        gfx_PrintInt(boozlian/10000, 1);
        }
        if(inventory[2]==3){
        gfx_TransparentSprite(ember, 231, 6);
        } else gfx_FillRectangle(231, 6, 21, 18);
        if(inventory[0]==1){
        gfx_TransparentSprite(axe, 183, 6);
        }/* else {
            gfx_FillRectangle(183, 6, 22, 18);
        }
        if (axedrop[0]==1){
            gfx_TransparentSprite(axe, axedrop[1], axedrop[2]);
        } */
        gfx_SetTextFGColor(2);
        if(collisionobj[0][3]==screen){
            gfx_TransparentSprite(ember, collisionobj[1][3], collisionobj[2][3]);
            gfx_SetTextXY(collisionobj[1][3]+2, collisionobj[2][3]+5);
            gfx_PrintInt((fireplace[1]/100000), 1);
        }
        gfx_SetTextFGColor(1);

        gfx_FillRectangle(50, 0, 25, 30);
        gfx_SetTextXY(60, 20);
        gfx_PrintInt((vaughn[2]/100000), 2);
        gfx_SetTextXY(60, 10);
        gfx_PrintInt((vaughn[1]/100000), 2);
        gfx_SetTextXY(60, 0);
        gfx_PrintInt((vaughn[0]/100000), 2);
        gfx_SetTextXY(150, 10);
        gfx_FillRectangle(150, 10, 25, 10);
        gfx_PrintInt((day/100000), 2);
        gfx_BlitBuffer();
        stat = 0;
        day+=40;
        if(day/100000>30){
            /* Victory*/
        }

    } while (kb_Data[6] != kb_Clear);

    /* End graphics drawing */
    gfx_End();

 /* *** Save everything to the appvar, might make another one later if new entities.*/
    ti_Rewind(ryanvar);
    real_t tmp_real = os_FloatToReal(x);
    os_RealToStr(strx, &tmp_real, 8, 1, 2);
    ti_Write(strx, sizeof(strx), 1, ryanvar);
    tmp_real = os_FloatToReal(y);
    os_RealToStr(stry, &tmp_real, 8, 1, 2);
    ti_Write(stry, sizeof(stry), 1, ryanvar);

    tmp_real = os_FloatToReal(screen);
    os_RealToStr(strscreen, &tmp_real, 8, 1, 2);
    ti_Write(strscreen, sizeof(strscreen), 1, ryanvar);

    tmp_real = os_FloatToReal(tool);
    os_RealToStr(strtool, &tmp_real, 8, 1, 2);
    ti_Write(strtool, sizeof(strtool), 1, ryanvar);

    tmp_real = os_FloatToReal(day);
    os_RealToStr(strday, &tmp_real, 8, 1, 2);
    ti_Write(strday, sizeof(strday), 1, ryanvar);

    tmp_real = os_FloatToReal(story);
    os_RealToStr(strstory, &tmp_real, 8, 1, 2);
    ti_Write(strstory, sizeof(strstory), 1, ryanvar);

    tmp_real = os_FloatToReal(berries);
    os_RealToStr(strberries, &tmp_real, 8, 1, 2);
    ti_Write(strberries, 8, 1, ryanvar);

    tmp_real = os_FloatToReal(boozlian);
    os_RealToStr(strbeer, &tmp_real, 8, 1, 2);
    ti_Write(strbeer, sizeof(strbeer), 1, ryanvar);

    tmp_real = os_FloatToReal(woods);
    os_RealToStr(strwood, &tmp_real, 8, 1, 2);
    ti_Write(strwood, 1, 1, ryanvar);

    tmp_real = os_FloatToReal(collisionobj[0][3]);
    os_RealToStr(firestat, &tmp_real, 8, 1, 2);
    ti_Write(firestat, 1, 1, ryanvar);

    tmp_real = os_FloatToReal(collisionobj[1][3]);
    os_RealToStr(firex, &tmp_real, 8, 1, 2);
    ti_Write(firex, 4, 1, ryanvar);

    tmp_real = os_FloatToReal(collisionobj[2][3]);
    os_RealToStr(firey, &tmp_real, 8, 1, 2);
    ti_Write(firey, 4, 1, ryanvar);

    tmp_real = os_FloatToReal(fireplace[1]);
    os_RealToStr(firefuel, &tmp_real, 8, 1, 2);
    ti_Write(firefuel, 8, 1, ryanvar);

    tmp_real = os_FloatToReal(brew[0]);
    os_RealToStr(brewin, &tmp_real, 8, 1, 2);
    ti_Write(brewin, sizeof(brewin), 1, ryanvar);

    tmp_real = os_FloatToReal(brew[1]);
    os_RealToStr(brewout, &tmp_real, 8, 1, 2);
    ti_Write(brewout, sizeof(brewout), 1, ryanvar);

    tmp_real = os_FloatToReal(vaughn[0]);
    os_RealToStr(strvaughn, &tmp_real, 8, 1, 2);
    ti_Write(strvaughn, sizeof(strvaughn), 1, ryanvar);
    tmp_real = os_FloatToReal(vaughn[1]);
    os_RealToStr(strhunger, &tmp_real, 8, 1, 2);
    ti_Write(strhunger, sizeof(strhunger), 1, ryanvar);
    tmp_real = os_FloatToReal(vaughn[2]);
    os_RealToStr(strtemp, &tmp_real, 8, 1, 2);
    ti_Write(strtemp, sizeof(strtemp), 1, ryanvar);

    ti_Close(ryanvar);

    return 0;
}
void peakcinema(int ystart, char str[]){
    gfx_SetTextFGColor(3);
    /* Was supposed to be mid, but thats basically mia sera, iykyk*/
    int mias = floor((GFX_LCD_WIDTH - (strlen(str)*7))/2);
    for (i = 0; i < strlen(str); i++){
        gfx_SetTextXY(mias,ystart);
        gfx_PrintChar(str[i]);
        mias+=7;
        delay(100);  
    }
    delay(1000);
}
/* *** Allows the character to rotate in a circle */
void Emote(int x, int y){
    for(i = 0; i<11; i++){
        gfx_Sprite(background, x, y);
        gfx_GetSprite(background, x, y);
        gfx_RotatedTransparentSprite_NoClip(cmcf, x, y, 36*i);
        delay(100);
        gfx_BlitBuffer();
    }
}
/* *** named after GC, takes an appvar and a lenght, and reads that to a varible */
int GabeRead(int longstuff, uint8_t davar){
    tempstring[longstuff] = "";
    ti_Read(tempstring, longstuff, 1, davar);
    char *endptr;
    return  strtol(tempstring, &endptr, 10);
}
/* Function for detecting two object collision */
int poscheck(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2, int ca){
    if(ca==3 || ca==5){
    if((x2 <= (x1+w1) & (x2+w2) >= (x1+w1) & y2 <= y1 & (y2+h2) >= y1) || (x2 <= (x1+w1) & (x2+w2) >= (x1+w1) & y2 <= (y1+h1) & (y2+h2) >= (y1+h1))){
        return 0;
    } else return 1;
    } else if(ca==1 || ca==5){
    if((x2 <= (x1) & (x2+w2) >= (x1) & y2 <= (y1+h1) & (y2+h2) >= (y1+h1)) || (x2 <= (x1+w1) & (x2+w2) >= (x1+w1) & y2 <= (y1+h1) & (y2+h2) >= (y1+h1))){
        return 0;
    } else return 1;
    } else if(ca==2 || ca==5){
    if((x2 <= (x1) & (x2+w2) >= (x1) & y2 <= y1 & (y2+h2) >= y1) || (x2 <= (x1) & (x2+w2) >= (x1) & y2 <= (y1+h1) & (y2+h2) >= (y1+h1))){
        return 0;
    } else return 1;
    } else if(ca==4 || ca==5){
    if((x2 <= (x1+w1) & (x2+w2) >= (x1+w1) & y2 <= y1 & (y2+h2) >= y1) || (x2 <= (x1) & (x2+w2) >= (x1) & y2 <= (y1) & (y2+h2) >= (y1))){
        return 0;
    } else return 1;
    } else return 0;
    }
/* *** Both draw all non-moving objects in a screen */
void ScreenNamedVaugh(){
    gfx_FillScreen(1);
    gfx_SetDrawBuffer();

    /* Draw to the offscreen buffer */
    
    gfx_SetColor(2);
    gfx_FillRectangle(0, 0, 320, 30);
    gfx_SetColor(1);
    gfx_Rectangle(180, 5, 120, 20);
    /* spilt by 24 into 5*/
    gfx_Line(204, 5, 204, 24);
    gfx_Line(228, 5, 228, 24);
    gfx_Line(252, 5, 252, 24);
    gfx_Line(276, 5, 276, 24);
    gfx_SetTextFGColor(1);
    gfx_PrintStringXY("Health:", 0, 0);
    gfx_PrintStringXY("/ 30", 90, 0);
    gfx_PrintStringXY("Hunger:", 0, 10);
    gfx_PrintStringXY("/ 10", 90, 10);
    gfx_PrintStringXY("Cold:", 0, 20);
    gfx_PrintStringXY("/ 10", 90, 20);
    gfx_PrintStringXY("Day", 120, 10);
}
void Drawnonmove(int scr){
    gfx_SetColor(1);
    gfx_FillRectangle(0, 30, 320, 210);
    for(int ph = 0; ph<sizeof(collisionobj[1]); ph++){
        if (collisionobj[0][ph] == scr){
            if(collisionobj[5][ph] == 1){
                gfx_TransparentSprite(stump, collisionobj[1][ph], collisionobj[2][ph]);
            }
            if(collisionobj[5][ph] == 7){
                gfx_TransparentSprite(barrel, collisionobj[1][ph], collisionobj[2][ph]);
            }
            if(collisionobj[5][ph] == 2){
                gfx_TransparentSprite(berby, collisionobj[1][ph], collisionobj[2][ph]);
            }
            if(collisionobj[5][ph] == 4){
                gfx_TransparentSprite(block, collisionobj[1][ph], collisionobj[2][ph]);
            }
            if(collisionobj[5][ph] == 5){
                gfx_RotatedTransparentSprite_NoClip(block, collisionobj[1][ph], collisionobj[2][ph], 64);
            }
            if(collisionobj[5][ph] == 6){
                gfx_ScaledTransparentSprite_NoClip(crash, collisionobj[1][ph], collisionobj[2][ph], 2, 2);
            }
        }
    }
}
/*Cause' RM hit a pole, Checks ALL Collision between the main character and any objects on screen*/
int PoleCheck(int x, int y, int type, int scr){
    for(int ph = 0; ph<sizeof(collisionobj[1]); ph++){
        if (collisionobj[0][ph] == scr){
            if(type==1){
            if(collisionobj[5][ph]==1 && 1== (!poscheck(x, y, cmcf_width, cmcf_height, collisionobj[1][ph], collisionobj[2][ph], collisionobj[3][ph], collisionobj[4][ph], 1) || !poscheck(x, y, cmcf_width, cmcf_height, collisionobj[1][ph], collisionobj[2][ph], collisionobj[3][ph], collisionobj[3][ph], 3) || !poscheck(x, y, cmcf_width, cmcf_height, collisionobj[1][ph], collisionobj[2][ph], collisionobj[3][ph], collisionobj[3][ph], 3) || !poscheck(x, y, cmcf_width, cmcf_height, collisionobj[1][ph], collisionobj[2][ph], collisionobj[3][ph], collisionobj[3][ph], 4))){
                return 1;
            }
            }
            if(type==2){
            if(collisionobj[5][ph]==2 && 1== (!poscheck(x, y, cmcf_width, cmcf_height, collisionobj[1][ph], collisionobj[2][ph], collisionobj[3][ph], collisionobj[4][ph], 1) || !poscheck(x, y, cmcf_width, cmcf_height, collisionobj[1][ph], collisionobj[2][ph], collisionobj[3][ph], collisionobj[3][ph], 3) || !poscheck(x, y, cmcf_width, cmcf_height, collisionobj[1][ph], collisionobj[2][ph], collisionobj[3][ph], collisionobj[3][ph], 3) || !poscheck(x, y, cmcf_width, cmcf_height, collisionobj[1][ph], collisionobj[2][ph], collisionobj[3][ph], collisionobj[3][ph], 4))){
                return 1;
            }
            }
            if(type==7){
            if(collisionobj[5][ph]==7 && 1== (!poscheck(x, y, cmcf_width, cmcf_height, collisionobj[1][ph], collisionobj[2][ph], collisionobj[3][ph], collisionobj[4][ph], 1) || !poscheck(x, y, cmcf_width, cmcf_height, collisionobj[1][ph], collisionobj[2][ph], collisionobj[3][ph], collisionobj[3][ph], 3) || !poscheck(x, y, cmcf_width, cmcf_height, collisionobj[1][ph], collisionobj[2][ph], collisionobj[3][ph], collisionobj[3][ph], 3) || !poscheck(x, y, cmcf_width, cmcf_height, collisionobj[1][ph], collisionobj[2][ph], collisionobj[3][ph], collisionobj[3][ph], 4))){
                return 1;
            }
            }
            if(type==-1){
                if(collisionobj[5][ph]==1 || collisionobj[5][ph]==4 || collisionobj[5][ph]==5 || collisionobj[5][ph]==6){
                    if (!poscheck(x, y, cmcf_width, cmcf_height, collisionobj[1][ph], collisionobj[2][ph], collisionobj[3][ph], collisionobj[4][ph], 1)){
                        return 0;
                    }
                }
            }
            if(type==-2){
                if(collisionobj[5][ph]==1 || collisionobj[5][ph]==4 || collisionobj[5][ph]==5 || collisionobj[5][ph]==6){
                    if (!poscheck(x, y, cmcl_width, cmcl_height, collisionobj[1][ph], collisionobj[2][ph], collisionobj[3][ph], collisionobj[4][ph], 2)){
                        return 0;
                    }
                }
            }
            if(type==-3){
                if(collisionobj[5][ph]==1 || collisionobj[5][ph]==4 || collisionobj[5][ph]==5 || collisionobj[5][ph]==6){
                    if (!poscheck(x, y, cmcf_width, cmcf_height, collisionobj[1][ph], collisionobj[2][ph], collisionobj[3][ph], collisionobj[4][ph], 3)){
                        return 0;
                    }
                }
            }
            if(type==-4){
                if(collisionobj[5][ph]==1 || collisionobj[5][ph]==4 || collisionobj[5][ph]==5 || collisionobj[5][ph]==6){
                    if (!poscheck(x, y, cmcf_width, cmcf_height, collisionobj[1][ph], collisionobj[2][ph], collisionobj[3][ph], collisionobj[4][ph], 4)){
                        return 0;
                    }
                }
            }
        }
    }
    if(0<type){
    return 0;
    } else{
        return 1;
    }
}
/* Draws the mc ie Preston, not relate in any way to PE ;) */
void PrestonMoves(int x, int y, int orient, int itemofintrest, int status)
{
    static int oldX = START_X;
    static int oldY = START_Y;

    /* Render the original background */
    gfx_Sprite(background, oldX, oldY);

    /* Get the background behind the sprite */
    gfx_GetSprite(background, x, y);

    /* Render the sprite */
    if (orient==1){
    gfx_TransparentSprite(cmcf, x, y);
    if (itemofintrest == 1){
        if (status == 1){
            gfx_RotatedTransparentSprite_NoClip(axe, x, y+4, -100);
        } else{
        gfx_RotatedTransparentSprite_NoClip(axe, x, y+4, 180);
        }
    }
    if (itemofintrest == 4){
        if (status == 1){
            gfx_RotatedTransparentSprite_NoClip(berry, x+1, y+2, 0);
        } else{
        gfx_RotatedTransparentSprite_NoClip(berry, x+1, y+9, 0);
        }
    }
    if (itemofintrest == 2){
        if (status == 1){
            gfx_RotatedTransparentSprite_NoClip(wood, x+2, y+7, 90);
        } else{
        gfx_RotatedTransparentSprite_NoClip(wood, x+2, y+7, 120);
        }
    }
    if (itemofintrest == 3){
        if (status == 1){
            gfx_RotatedTransparentSprite_NoClip(ember, x+2, y+8, -20);
        } else{
        gfx_RotatedTransparentSprite_NoClip(ember, x+2, y+7, 0);
        }
    }
    if (itemofintrest == 6){
        if (status == 1){
            gfx_RotatedTransparentSprite_NoClip(beer, x+2, y+8, -20);
        } else{
        gfx_RotatedTransparentSprite_NoClip(beer, x+2, y+7, 0);
        }
    }
    if (itemofintrest == 5){
        if (status == 1){
            gfx_TransparentSprite(radio, x, y+3);
        } else{
        gfx_TransparentSprite(radio, x+2, y+6);
        }
    }
    }
    if (orient==2){
    gfx_TransparentSprite(cmcl, x, y);
    }
    if (orient==3){
    gfx_TransparentSprite(cmcr, x, y);
    }
    if (orient==4){
    if (itemofintrest == 1){
        gfx_TransparentSprite(axe, x, y+4);
    }
    gfx_TransparentSprite(cmcb, x, y);
    }
        
    oldX = x;
    oldY = y;
}
