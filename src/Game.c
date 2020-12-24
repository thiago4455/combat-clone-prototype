#include "Game.h"
#include "Manager.h"
#include <stdio.h>

unsigned int MAX_COOLDOWN_FRAMES;

ALLEGRO_BITMAP *BITMAP_TANK;

static const struct PLAYER_CONTROLLERS C_Player1 = {ALLEGRO_KEY_W, ALLEGRO_KEY_S, ALLEGRO_KEY_A, ALLEGRO_KEY_D, ALLEGRO_KEY_SPACE};
static const struct PLAYER_CONTROLLERS C_Player2 = {ALLEGRO_KEY_UP, ALLEGRO_KEY_DOWN, ALLEGRO_KEY_LEFT, ALLEGRO_KEY_RIGHT, ALLEGRO_KEY_ENTER};

struct Player Player1;
struct Player Player2;

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
    Player1 = (struct Player) { 0, 0, 90, WINDOW_HEIGHT/2, 0, 0, 0, MAX_COOLDOWN_FRAMES };

    BITMAP_TANK = al_load_bitmap("assets/tank.png");
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

void G_Update(){
    Player1.PosX += Player1.TranslationV * PLAYER_VELOCITY;
    Player1.Rotation += Player1.RotationV * PLAYER_ROTATION_VELOCITY;
}

void G_Render(){
    al_draw_scaled_rotated_bitmap(BITMAP_TANK, al_get_bitmap_width(BITMAP_TANK) / 2, al_get_bitmap_height(BITMAP_TANK) / 2, 
                           Player1.PosX, Player1.PosY, .5f, .5f, -ALLEGRO_PI * 0.001 * Player1.Rotation, 0);
}