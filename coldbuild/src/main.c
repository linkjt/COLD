#include <sys/util.h>
#include <ti/real.h>

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
char tempstring[];

void PrestonMoves(int x, int y, int ori, int tool, int stat);
int poscheck(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2, int ca);
int GabeRead(int x, uint8_t z);

int main(void)
{
    int ori = 1;
    int stat = 0;
    int tool = 0;
    int woods = 0;
    int berries = 0;
    /* Vaughn is the goat, he is health, hunger, and heat*/
    int vaughn[3] = {3000000, 1000000, 1000000};
    int inventory[4] = {1, 0, 3, 0};
    int fireplace[4] = {0,0,0,0};
    /*int axedrop[3] = {0,0,0}; */


    background->width = cmcf_width;
    background->height = cmcf_height;

    /* Loading the cordinates for the sprite */
    char strx[5] = "";
    char stry[5] = "";
    char strtool[5] = "";
    char strvaughn[8] = "";
    char strhunger[8] = "";
    char strtemp[8] = "";
    uint8_t ryanvar;
    int x = START_X;
    int y = START_Y;
    /* ryan was a teammate of mine and so I choose the varible to be nammed after him, he was really important and was like an older brother I never had*/
    if(ti_Open("COLDPI","r")==0){
        ryanvar = ti_Open("COLDPI","w+");
        }else{
        ryanvar = ti_Open("COLDPI","r+");
        x = GabeRead(5, ryanvar);
        y = GabeRead(5, ryanvar);
        tool = GabeRead(5, ryanvar);
        vaughn[0] = GabeRead(8, ryanvar);
        vaughn[1] = GabeRead(8, ryanvar);
        vaughn[2] = GabeRead(8, ryanvar);
    }

    /* Initialize the graphics */
    gfx_Begin();

    /* Set the palette for the sprites */
    gfx_SetPalette(global_palette, sizeof_global_palette, 0);
    gfx_SetTransparentColor(0);

    /* Draw to the offscreen buffer */
    gfx_SetDrawBuffer();
    gfx_FillScreen(1);
    
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
    gfx_TransparentSprite(stump, 50, 120);
    gfx_TransparentSprite(berby, 100, 200);

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
            if (fireplace[3]==0 || fireplace[0]!=1 || (poscheck(x, y, cmcf_width, cmcf_height, fireplace[1]-50, fireplace[2]-50, ember_width+100, ember_height+100, 1) && poscheck(x, y, cmcf_width, cmcf_height, fireplace[1]-50, fireplace[2]-50, ember_width+100, ember_height+100, 3) && poscheck(x, y, cmcf_width, cmcf_height, fireplace[1]-50, fireplace[2]-50, ember_width+100, ember_height+100, 3) && poscheck(x, y, cmcf_width, cmcf_height, fireplace[1]-50, fireplace[2]-50, ember_width+100, ember_height+100, 4))){
            vaughn[2] -= 750;
            }
        }
        if (vaughn[1]>0){
            vaughn[1] -= 1;
        } else{
            vaughn[1] = 0;
        }
        if (vaughn[0]>1 && (vaughn[1]==0 || vaughn[2] == 0)){
            vaughn[0] -= 750;
        } else if (vaughn[0]<0){
            vaughn[0] = 0;
        }
        if (kb_Data[1] & kb_Yequ){
            tool = inventory[0];
        }
        if (kb_Data[1] & kb_Zoom){
            tool = inventory[2];
        }
        if ((kb_Data[1] & kb_Window)){
            tool = inventory[1];
        }
        if ((kb_Data[1] & kb_Trace)){
            tool = inventory[3];
        } 
        if ((kb_Data[1] & kb_Mode) && (tool!=0)){
            if(tool==2){
                woods = 0;
                inventory[tool-1]=0;
            }
            /*if(tool==1){
                axedrop[0] = 1;
                axedrop[1] = x+2;
                axedrop[2] = y+30;
            } */
            tool = 0;
        }
        if (kb_Data[1] & kb_2nd){
            if(tool==1){
            if(woods<9  && (!poscheck(x, y-2, cmcf_width, cmcf_height, 50, 120, stump_width, stump_height, 4) || !poscheck(x+2, y, cmcf_width, cmcf_height, 50, 120, stump_width, stump_height, 3) || !poscheck(x, y+2, cmcf_width, cmcf_height, 50, 120, stump_width, stump_height, 1) || !poscheck(x-2, y, cmcl_width, cmcl_height, 50, 120, stump_width, stump_height, 2))){
                woods += 1;
                inventory[1] = 2;
            }
            if(berries<90000 && (!poscheck(x, y, cmcf_width, cmcf_height, 100, 200, berby_width, berby_height, 1) || !poscheck(x, y, cmcf_width, cmcf_height, 100, 200, berby_width, berby_height, 3) || !poscheck(x, y, cmcf_width, cmcf_height, 100, 200, berby_width, berby_height, 3) || !poscheck(x, y, cmcf_width, cmcf_height, 100, 200, berby_width, berby_height, 4))){
                berries += 500;
                inventory[3] = 4;
                stat = 1;
                
            } else stat = 1;
            } else stat = 1;
            if((tool==4) && vaughn[1]<1000000){
                berries -= 100;
                vaughn[1] +=1000;
                if(vaughn[0]<3000000){
                    vaughn[0]+=750;
                }
            }
            if(tool==3){
            if((woods!=0) && (inventory[2]==3) && poscheck(x+2, y-50, ember_width, ember_height, 50, 120, stump_width, stump_height, 1) && poscheck(x+2, y-50, ember_width, ember_height, 50, 120, stump_width, stump_height, 2) && poscheck(x+2, y-50, ember_width, ember_height, 50, 120, stump_width, stump_height, 3) && poscheck(x+2, y-50, ember_width, ember_height, 50, 120, stump_width, stump_height, 4)){
                tool = 0;
                inventory[2] = 0;
                fireplace[0] = 1;
                fireplace[1] = x+2;
                fireplace[2] = y+50;
                fireplace[3] = 100000 * woods;
                woods = 0;
            }
            }
            if(tool==2 && woods > 0 && (!poscheck(x, y, cmcf_width, cmcf_height, fireplace[1]-20, fireplace[2]-20, ember_width+40, ember_height+40, 1) || !poscheck(x, y, cmcf_width, cmcf_height, fireplace[1]-20, fireplace[2]-20, ember_width+40, ember_height+40, 3) || !poscheck(x, y, cmcf_width, cmcf_height, fireplace[1]-20, fireplace[2]-20, ember_width+40, ember_height+40, 3) || !poscheck(x, y, cmcf_width, cmcf_height, fireplace[1]-20, fireplace[2]-20, ember_width+40, ember_height+40, 4))){
                woods-=1;
                if (fireplace[3]<900000){
                fireplace[3]+=100000;
                } else fireplace[3] = 900000;
            }

            
        }
        if (fireplace[0]==1){
            if(fireplace[3]>0 && vaughn[2]<1000000 && (!poscheck(x, y, cmcf_width, cmcf_height, fireplace[1]-50, fireplace[2]-50, ember_width+100, ember_height+100, 1) || !poscheck(x, y, cmcf_width, cmcf_height, fireplace[1]-50, fireplace[2]-50, ember_width+100, ember_height+100, 3) || !poscheck(x, y, cmcf_width, cmcf_height, fireplace[1]-50, fireplace[2]-50, ember_width+100, ember_height+100, 3) || !poscheck(x, y, cmcf_width, cmcf_height, fireplace[1]-50, fireplace[2]-50, ember_width+100, ember_height+100, 4))){
                vaughn[2]+=750;
            }
            if (fireplace[3]>0){
                fireplace[3]-=250;
            } else fireplace[3] = 0;
        }
        /* Check if any arrows are pressed */
        if (arrows)
        {
            /* Do different directions depending on the keypress */
            if (arrows & kb_Right && poscheck(x+2, y, cmcf_width, cmcf_height, 50, 120, stump_width, stump_height, 3))
            {
                if(x<300){
                x += 2;
                }
                ori = 3;
            }
            if (arrows & kb_Left && poscheck(x-2, y, cmcl_width, cmcl_height, 50, 120, stump_width, stump_height, 2))
            {
                if(x>0){
                x -= 2;
                }
                ori = 2;
            }
            if (arrows & kb_Down && poscheck(x, y+2, cmcf_width, cmcf_height, 50, 120, stump_width, stump_height, 1))
            {
                if(y<211){
                y += 2;
                }
                ori = 1;
            }
            if ((arrows & kb_Up) && poscheck(x, y-2, cmcf_width, cmcf_height, 50, 120, stump_width, stump_height, 4))
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
        PrestonMoves(x, y, ori, tool, stat);
        gfx_SetColor(2);
        gfx_FillRectangle(205, 6, 22, 18);
        if(inventory[1]==2){
        gfx_TransparentSprite(wood, 205, 6);
        gfx_SetTextXY(220, 15);
        gfx_PrintInt(woods, 1);
        }
        gfx_FillRectangle(253, 6, 22, 18);
        if(inventory[3]==4){
        gfx_TransparentSprite(berry, 253, 6);
        gfx_SetTextXY(267, 15);
        gfx_PrintInt(berries/10000, 1);
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
        if(fireplace[0]==1){
            gfx_TransparentSprite(ember, fireplace[1], fireplace[2]);
            gfx_SetTextXY(fireplace[1]+2, fireplace[2]+5);
            gfx_PrintInt((fireplace[3]/100000), 1);
        }
        gfx_SetTextFGColor(1);

        gfx_FillRectangle(50, 0, 25, 30);
        gfx_SetTextXY(60, 20);
        gfx_PrintInt((vaughn[2]/100000), 2);
        gfx_SetTextXY(60, 10);
        gfx_PrintInt((vaughn[1]/100000), 2);
        gfx_SetTextXY(60, 0);
        gfx_PrintInt((vaughn[0]/100000), 2);
        gfx_BlitBuffer();
        stat = 0;

    } while (kb_Data[6] != kb_Clear);

    /* End graphics drawing */
    gfx_End();

    ti_Rewind(ryanvar);
    real_t tmp_real = os_FloatToReal(x);
    os_RealToStr(strx, &tmp_real, 8, 1, 2);
    ti_Write(strx, sizeof(strx), 1, ryanvar);
    tmp_real = os_FloatToReal(y);
    os_RealToStr(stry, &tmp_real, 8, 1, 2);
    ti_Write(stry, sizeof(stry), 1, ryanvar);
    tmp_real = os_FloatToReal(tool);
    os_RealToStr(strtool, &tmp_real, 8, 1, 2);
    ti_Write(strtool, sizeof(strtool), 1, ryanvar);
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
int GabeRead(int longstuff, uint8_t davar){
    tempstring[longstuff] = "";
    ti_Read(tempstring, longstuff, 1, davar);
    return atoi(tempstring);
}
/* Function for drawing the main sprite */
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
