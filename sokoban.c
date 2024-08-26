#define  USE_V200 

#include <tigcclib.h>
#include <math.h>
#include "sprites.h"
#include "maps.h"

#define block_in_spot 4
#define block 2
#define spot 3
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))
#define font_width 8

int x = 0, y = 0, spx = 0, spy = 0, key = 0, moves = 0, max_moves = 0, total_spots = 0, spots = 0, current_level = 0;
char buff[48];
void copy_map(char map1[8][15], char map2[map_count][8][15], int lvl) {
    for (int i = 0; i < map_height; i++)
        for (int j = 0; j < map_width; j++)
            map1[i][j] = map2[lvl][i][j];
}



unsigned short* wall_pick(char m[8][15], int x, int y){
    unsigned short *spr;

        spr = spr_player;


    if (m[y][MIN(x+1,map_width-1)]==1 && m[y][MAX(x-1,0)]==1
        && m[MAX(y-1,0)][x]==1 && m[MIN(y+1,map_height-1)][x]==1)
        spr = spr_clear;

    if ((m[y][MIN(x+1,map_width-1)]!=1 || x+1>map_width-1) && (m[y][MAX(x-1,0)]!=1 || x-1<0)
        && (m[MAX(y-1,0)][x]!=1 || y-1<0) && m[MIN(y+1,map_height-1)][x]!=1)
        spr = spr_wall;

    if (m[y][MIN(x+1,map_width-1)]==1 && (m[y][MAX(x-1,0)]!=1 || x-1<0)
        && m[MAX(y-1,0)][x]==1 && (m[MIN(y+1,map_height-1)][x]==1))
        spr = spr_wall_thin_right;


    if ((m[y][MIN(x+1,map_width-1)]!=1 || x+1>map_width-1) && m[y][MAX(x-1,0)]==1
        && m[MAX(y-1,0)][x]==1 && (m[MIN(y+1,map_height-1)][x]==1))
        spr = spr_wall_thin_left;


        if (m[y][MIN(x+1,map_width-1)]==1 && (m[y][MAX(x-1,0)]==1 || x-1<0)
        && (m[MAX(y-1,0)][x]!=1 || y-1<0) && m[MIN(y+1,map_height-1)][x]==1)
        spr = spr_wall_thin_up;

        if (m[y][MIN(x+1,map_width-1)]==1 && m[y][MAX(x-1,0)]==1
        && m[MAX(y-1,0)][x]==1 && (m[MIN(y+1,map_height-1)][x]!=1 || y+1>map_height-1))
        spr = spr_wall_thin_down;
        
    if ((m[y][MIN(x+1,map_width-1)]!=1 || x+1>map_width-1) && m[y][MAX(x-1,0)]==1
        && (m[MAX(y-1,0)][x]!=1 || y-1<0) && (m[MIN(y+1,map_height-1)][x]!=1 || y+1>map_height-1))
        spr = spr_wall_left;

    if (m[y][MIN(x+1,map_width-1)]==1 && (m[y][MAX(x-1,0)]!=1 || x-1<0)
        && (m[MAX(y-1,0)][x]!=1 || y-1<0) && (m[MIN(y+1,map_height-1)][x]!=1 || y+1>map_height-1))
        spr = spr_wall_right;



    if ((m[y][MIN(x+1,map_width-1)]!=1 || x+1>map_width-1) && (m[y][MAX(x-1,0)]!=1 || x-1<0)
    && m[MAX(y-1,0)][x]==1 && (m[MIN(y+1,map_height-1)][x]!=1 || y+1>map_height-1))
    spr = spr_wall_down;


    if ((m[y][MIN(x+1,map_width-1)]!=1 || x+1>map_width-1) && (m[y][MAX(x-1,0)]!=1 || x-1<0)
    && m[MAX(y-1,0)][x]!=1 && m[MIN(y+1,map_height-1)][x]==1)
    spr = spr_wall_up;

    if (m[y][MIN(x+1,map_width-1)]==1 && (m[y][MAX(x-1,0)]!=1 || x-1<0)
        && m[MAX(y-1,0)][x]==1 && (m[MIN(y+1,map_height-1)][x]!=1 || y+1>map_height-1))
        spr = spr_wall_down_right;

    if ((m[y][MIN(x+1,map_width-1)]!=1 || x+1>map_width-1) && m[y][MAX(x-1,0)]==1
        && m[MAX(y-1,0)][x]==1 && (m[MIN(y+1,map_height-1)][x]!=1 || y+1>map_height-1))
        spr = spr_wall_down_left;

   if (m[y][MIN(x+1,map_width-1)]==1 && (m[y][MAX(x-1,0)]!=1 || x-1<0)
        && (m[MAX(y-1,0)][x]!=1 || y-1<0) && m[MIN(y+1,map_height-1)][x]==1)
        spr = spr_wall_top_right;

    if ((m[y][MIN(x+1,map_width-1)]!=1 || x+1>map_width-1) && m[y][MAX(x-1,0)]==1
        && (m[MAX(y-1,0)][x]!=1 || y-1<0) && m[MIN(y+1,map_height-1)][x]==1)
        spr = spr_wall_top_left;

    if ((m[y][MIN(x+1,map_width-1)]!=1 || x+1>map_width-1) && (m[y][MAX(x-1,0)]!=1 || x-1<0)
        && m[MAX(y-1,0)][x]==1 && m[MIN(y+1,map_height-1)][x]==1)
        spr = spr_wall_middle_up;
    
    if (m[y][MIN(x+1,map_width-1)]==1 && m[y][MAX(x-1,0)]==1
        && (m[MAX(y-1,0)][x]!=1 || y-1<0) && (m[MIN(y+1,map_height-1)][x]!=1 || y+1>map_height-1))
        spr = spr_wall_middle_right;

    return spr;
}

void load_map(char map1[8][15]) {
    ClrScr();
    spots = 0;
    moves = 0;
    total_spots = 0;
    max_moves = map1[map_height - 1][map_width - 1];

    for (int j = 0; j < map_height; j++) {
        for (int i = 0; i < map_width; i++) {
            if (i!=map_width-1 || j!=map_height-1)
            switch (map1[j][i]) {
                case 0: break;
                case 1: Sprite16(i * 16, j * 16, SPRITE_HEIGHT, wall_pick(map1,i,j), LCD_MEM, SPRT_XOR); break;
                case 2: Sprite16(i * 16, j * 16, SPRITE_HEIGHT, spr_box, LCD_MEM, SPRT_XOR); break;
                case 3: Sprite16(i * 16, j * 16, SPRITE_HEIGHT, spr_spot, LCD_MEM, SPRT_XOR); total_spots++; break;
                case 4: Sprite16(i * 16, j * 16, SPRITE_HEIGHT, spr_box_in, LCD_MEM, SPRT_XOR);
                        spots++;
                        total_spots++;
                        break;
                case 5: x = i * 16; y = j * 16; map1[j][i] = 0; Sprite16(x, y, SPRITE_HEIGHT, spr_player, LCD_MEM, SPRT_XOR); break;
                default: map1[j][i] = 0; break;
            }
        }
    }
}


void next_level_screen(){
    ClrScr();
    sprintf(buff, "Level %d Completed!",current_level);
    DrawStr(LCD_WIDTH / 2 -strlen(buff)*font_width/2, LCD_HEIGHT/2, buff, A_REVERSE);
    sprintf(buff, "All %d spots filled!",total_spots);
    DrawStr(LCD_WIDTH / 2 -strlen(buff)*font_width/2, LCD_HEIGHT/2+12, buff, A_REVERSE);
    sprintf(buff, "Total moves %d/%d",moves,max_moves);
    DrawStr(LCD_WIDTH / 2 -strlen(buff)*font_width/2, LCD_HEIGHT/2+24, buff, A_REVERSE);
    ngetchx(); // wait for keypress
    current_level++;
    if (current_level>=map_count){
        current_level = 0;
    }
    copy_map(level, map,current_level);
    load_map(level);
}

void _main(void) {
    ClrScr();
    copy_map(level, map,current_level);
    load_map(level);
    sprintf(buff, "Level %d Spots %d/%d Moves %d/%d",current_level, spots,total_spots, moves, max_moves);
    DrawStr(LCD_WIDTH / 2 -strlen(buff)*font_width/2, 0, buff, A_REVERSE);
    while ((key = ngetchx()) != KEY_ESC) {
        if (key == KEY_F1) {
            copy_map(level, map,current_level);
            load_map(level);
        }else if (key == KEY_F2) {
            copy_map(level, map,++current_level % map_count);
            load_map(level);
        }

        spx = 0;
        spy = 0;
        Sprite16(x, y, SPRITE_HEIGHT, spr_clear, LCD_MEM, SPRT_AND);

        if (level[y / 16][x / 16] == 3 || level[y / 16][x / 16] == 4)
            Sprite16(x, y, SPRITE_HEIGHT, spr_spot, LCD_MEM, SPRT_XOR);

        spx = (key == KEY_RIGHT)-(key == KEY_LEFT);
        spy = (key == KEY_DOWN)-(key == KEY_UP);
        if ((spx != 0 || spy != 0) && moves < max_moves)
            if (level[y / 16 + spy][x / 16 + spx] != 1) {
                if (level[y / 16 + spy][x / 16 + spx] == 2 || level[y / 16 + spy][x / 16 + spx] == 4) {
                    if (level[y / 16 + spy * 2][x / 16 + spx * 2] == 0 || level[y / 16 + spy * 2][x / 16 + spx * 2] == 3) {
                        if (level[y / 16 + spy][x / 16 + spx] == block_in_spot) {
                            level[y / 16 + spy][x / 16 + spx] = spot;
                            Sprite16(x + spx * 16, y + spy * 16, SPRITE_HEIGHT, spr_clear, LCD_MEM, SPRT_AND);
                            Sprite16(x + spx * 16, y + spy * 16, SPRITE_HEIGHT, spr_spot, LCD_MEM, SPRT_XOR);
                            spots--;
                        } else {
                            level[y / 16 + spy][x / 16 + spx] = 0;
                            Sprite16(x + spx * 16, y + spy * 16, SPRITE_HEIGHT, spr_clear, LCD_MEM, SPRT_AND);
                        }
                        if (level[y / 16 + spy * 2][x / 16 + spx * 2] == spot) {
                            level[y / 16 + spy * 2][x / 16 + spx * 2] = 4;
                            Sprite16(x + spx * 32, y + spy * 32, SPRITE_HEIGHT, spr_clear, LCD_MEM, SPRT_AND);
                            Sprite16(x + spx * 32, y + spy * 32, SPRITE_HEIGHT, spr_box_in, LCD_MEM, SPRT_XOR);
                            spots++;
                        } else {
                            level[y / 16 + spy * 2][x / 16 + spx * 2] = 2;
                            Sprite16(x + spx * 32, y + spy * 32, SPRITE_HEIGHT, spr_box, LCD_MEM, SPRT_XOR);
                        }
                        x += spx * 16;
                        y += spy * 16;
                        moves++;
                    }
                } else {
                    x += spx * 16;
                    y += spy * 16;
                    moves++;
                }
            }
        x = x % LCD_WIDTH;
        y = y % LCD_HEIGHT;
        sprintf(buff, "Level %d Spots %d/%d Moves %d/%d",current_level, spots,total_spots, moves, max_moves);
        DrawStr(LCD_WIDTH / 2-strlen(buff)*font_width/2, 0, buff, A_REVERSE);
        Sprite16(x, y, SPRITE_HEIGHT, spr_player, LCD_MEM, SPRT_OR);


        if (spots==total_spots){
            sprintf(buff, "Nice!!",current_level,total_spots);
            DrawStr(LCD_WIDTH / 2 -strlen(buff)*font_width/2, LCD_HEIGHT/2, buff, A_REVERSE);
            ngetchx();
            next_level_screen();
        }
        if (moves >= max_moves){
                sprintf(buff, "All moves used %d/%d",moves,max_moves);
                DrawStr(LCD_WIDTH / 2 -strlen(buff)*font_width/2, LCD_HEIGHT/2, buff, A_REVERSE);
                sprintf(buff, "press F1 to restart level");
                DrawStr(LCD_WIDTH / 2 -strlen(buff)*font_width/2, LCD_HEIGHT/2+12, buff, A_REVERSE);
        }

        idle();
    }
    ClrScr();
}
