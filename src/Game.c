#include "Game.h"
#include "Manager.h"
#include "Utils.h"
#include <math.h>
#include <stdio.h>

unsigned int MAX_COOLDOWN_FRAMES;

ALLEGRO_BITMAP *BITMAP_TANK_1;
ALLEGRO_BITMAP *BITMAP_TANK_2;

static const struct PLAYER_CONTROLLERS C_Player1 = {ALLEGRO_KEY_W, ALLEGRO_KEY_S, ALLEGRO_KEY_A, ALLEGRO_KEY_D, ALLEGRO_KEY_SPACE};
static const struct PLAYER_CONTROLLERS C_Player2 = {ALLEGRO_KEY_UP, ALLEGRO_KEY_DOWN, ALLEGRO_KEY_LEFT, ALLEGRO_KEY_RIGHT, ALLEGRO_KEY_ENTER};

struct Player Player1;
struct Player Player2;
struct Bullet bullets[5];

void PlayerInputDown(struct Player *player, struct PLAYER_CONTROLLERS controller, unsigned char key){
    if (key == controller.up)
        player->TranslationV = 1;
    else if(key == controller.down)
        player->TranslationV = -1;
    else if(key == controller.left)
        player->RotationV = 1;
    else if(key == controller.right)
        player->RotationV = -1;
    else if(key == controller.fire)
        player->WillFire = 1;
}

void PlayerInputUp(struct Player *player, struct PLAYER_CONTROLLERS controller, unsigned char key){
    if ((key == controller.up && player->TranslationV == 1) || (key == controller.down && player->TranslationV == -1))
        player->TranslationV = 0;
    else if((key == controller.left && player->RotationV == 1) || (key == controller.right && player->RotationV == -1))
        player->RotationV = 0;
    else if(key == controller.fire)
        player->WillFire = 0;
}

void G_Start(){
    MAX_COOLDOWN_FRAMES = COOLDOWN * FPS;
    Player1 = (struct Player) { 0, 0, 90, WINDOW_HEIGHT/2, 0, 0, 0, 0 };
    Player2 = (struct Player) { 0, 0, WINDOW_WIDTH - 90, WINDOW_HEIGHT/2, ALLEGRO_PI, 0, 0, 0 };

    BITMAP_TANK_1 = al_load_bitmap("assets/tank.png");
    BITMAP_TANK_2 = al_load_bitmap("assets/tank2.png");
}

void G_ProcessInput(unsigned char key, char type){
    if(!type){
        PlayerInputDown(&Player1, C_Player1, key);
        PlayerInputDown(&Player2, C_Player2, key);
    }
    else{
        PlayerInputUp(&Player1, C_Player1, key);
        PlayerInputUp(&Player2, C_Player2, key);
    }
}

void PlayerUpdate(struct Player *player){
    player->Rotation += -ALLEGRO_PI * 0.001 * player->RotationV * PLAYER_ROTATION_VELOCITY;
    player->PosX += player->TranslationV * PLAYER_VELOCITY * cos(player->Rotation);
    player->PosY += player->TranslationV * PLAYER_VELOCITY * sin(player->Rotation);

    if(player->Cooldown > 0)
        player->Cooldown--;
    else {
        if(player->WillFire)
            player->Power = player->Power < MAX_POWER? player->Power + 1 : player->Power;
        else
        {
            if(player->Power>0){
                bullets[0] = (struct Bullet) {player->Rotation, player->PosX, player->PosY, player->Power, 0};
                player->Power = 0;
                player->Cooldown = MAX_COOLDOWN_FRAMES;

            }
        }
        
    }
}

void UpdateBullets(){
    int i;
    for (i = 0; i < MAX_BULLET_QUANTITY; i++)
    {
        bullets[i].PosX += BULLET_VELOCITY * cos(bullets[i].Direction);
        bullets[i].PosY += BULLET_VELOCITY * sin(bullets[i].Direction);
    }
    
}

void G_Update(){
    PlayerUpdate(&Player1);
    PlayerUpdate(&Player2);
    UpdateBullets();
}

void G_Render(){
    al_draw_scaled_rotated_bitmap(BITMAP_TANK_1, al_get_bitmap_width(BITMAP_TANK_1) / 2, al_get_bitmap_height(BITMAP_TANK_1) / 2, 
                           Player1.PosX, Player1.PosY, .5f, .5f, Player1.Rotation, 0);
    al_draw_scaled_rotated_bitmap(BITMAP_TANK_2, al_get_bitmap_width(BITMAP_TANK_2) / 2, al_get_bitmap_height(BITMAP_TANK_2) / 2, 
                           Player2.PosX, Player2.PosY, .5f, .5f, Player2.Rotation, 0);

    int i;
    for (i = 0; i < MAX_BULLET_QUANTITY; i++)
    {
        al_draw_circle(bullets[i].PosX, bullets[i].PosY, 1, al_map_hex(0x0000ff), 10);
    }           
}