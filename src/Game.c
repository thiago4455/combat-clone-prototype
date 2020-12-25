#include "Game.h"
#include "Manager.h"
#include "Utils.h"
#include <math.h>
#include <stdio.h>

struct Player Players[PLAYERS_NUMBER];
ALLEGRO_BITMAP *BITMAP_TANK[PLAYERS_NUMBER];
struct PLAYER_CONTROLS C_Player[PLAYERS_NUMBER];

struct Bullet bullets[MAX_BULLET_QUANTITY];


void G_Start(){
    CreatePlayer(90, WINDOW_HEIGHT/2, 0,
                (struct PLAYER_CONTROLS) {ALLEGRO_KEY_W, ALLEGRO_KEY_S, ALLEGRO_KEY_A, ALLEGRO_KEY_D, ALLEGRO_KEY_SPACE},
                "assets/tank.png", 0x0000ff);

    CreatePlayer(WINDOW_WIDTH - 90, WINDOW_HEIGHT/2, ALLEGRO_PI,
                (struct PLAYER_CONTROLS) {ALLEGRO_KEY_UP, ALLEGRO_KEY_DOWN, ALLEGRO_KEY_LEFT, ALLEGRO_KEY_RIGHT, ALLEGRO_KEY_ENTER},
                "assets/tank2.png", 0xff0000);
}

void G_ProcessInput(unsigned char key, char type){
    int i;
    for (i = 0; i < PLAYERS_NUMBER; i++)
    {
        if(!type)
            PlayerInputDown(&Players[i], C_Player[i], key);
        else
            PlayerInputUp(&Players[i], C_Player[i], key);
    }
}

void G_Update(){
    int i;
    for (i = 0; i < PLAYERS_NUMBER; i++)
    {
        PlayerUpdate(&Players[i]);
    }
    UpdateBullets();
}

void G_Render(){
    int i;
    for (i = 0; i < PLAYERS_NUMBER; i++){
        al_draw_scaled_rotated_bitmap(BITMAP_TANK[i], al_get_bitmap_width(BITMAP_TANK[i]) / 2, al_get_bitmap_height(BITMAP_TANK[i]) / 2, 
                           Players[i].PosX, Players[i].PosY, .5f, .5f, Players[i].Rotation, 0);
    }

    for (i = 0; i < MAX_BULLET_QUANTITY; i++)
    {
        float r = 3 + 30*bullets[i].Power/MAX_POWER;
        al_draw_filled_circle(bullets[i].PosX, bullets[i].PosY, r, al_map_hex(Players[bullets[i].Owner].BulletColor));
    }           
}

// 
// Initialize player
// 
int initializedPlayers = 0;
void CreatePlayer(float initialPosX, float initialPosY, float initialRot, struct PLAYER_CONTROLS controller, const char *playerImage, unsigned int bulletColor){
    Players[initializedPlayers] = (struct Player) { 0, 0, initialPosX, initialPosY, initialRot, 0, 0, 0, bulletColor };
    BITMAP_TANK[initializedPlayers] = al_load_bitmap(playerImage);
    C_Player[initializedPlayers] = controller;
    initializedPlayers++;
}


// 
// Manage inputs
// 

void PlayerInputDown(struct Player *player, struct PLAYER_CONTROLS controller, unsigned char key){
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

void PlayerInputUp(struct Player *player, struct PLAYER_CONTROLS controller, unsigned char key){
    if ((key == controller.up && player->TranslationV == 1) || (key == controller.down && player->TranslationV == -1))
        player->TranslationV = 0;
    else if((key == controller.left && player->RotationV == 1) || (key == controller.right && player->RotationV == -1))
        player->RotationV = 0;
    else if(key == controller.fire)
        player->WillFire = 0;
}


// 
// Calculations before rendering
// 

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
                int i;
                for (i = MAX_BULLET_QUANTITY - 1; i > 0; i--) {
                    bullets[i] = bullets[i-1];
                }
                bullets[0] = (struct Bullet) {player->Rotation, player->PosX, player->PosY, player->Power, player-Players};
                printf("O: %i", player-Players);
                player->Power = 0;
                player->Cooldown = COOLDOWN * FPS;

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