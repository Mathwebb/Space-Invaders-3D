#ifndef LEVEL_H
#define LEVEL_H

#include <vector>

#include "Object.h"
#include "Projectile.h"
#include "Player.h"
#include "Enemy.h"
#include "../game_functions/check collisions.h"


using namespace std;

class Level{
    private:
        int levelNumber;
        int maxSpawnedEnemies, initialSpawnedEnemies, enemiesSpawned, enemiesLeft, enemiesKilled, enemiesEscaped;
        float enemySpawnRate;
        float ObjectiveHealthPoints;
        Player *player;
        vector<Enemy> enemies;
        vector<Projectile> projectiles;
        float borderXMin, borderXMax, borderYMin, borderYMax, borderZMin, borderZMax;
    public:
        // Constructors
        Level(){
            this->levelNumber = 1;
            this->maxSpawnedEnemies = 10;
            this->initialSpawnedEnemies = 5;
            this->enemiesSpawned = 0;
            this->enemiesLeft = 0;
            this->enemiesKilled = 0;
            this->enemiesEscaped = 0;
            this->enemySpawnRate = 1;
            this->ObjectiveHealthPoints = 100;
            this->player = new Player();
            this->borderXMin = 0;
            this->borderXMax = 500;
            this->borderYMin = 0;
            this->borderYMax = 500;
            this->borderZMin = -1000;
            this->borderZMax = 0;
            
            // Initialize 10 enemies on random positions
            for (int i = 0; i < 10; i++){
                enemies.push_back(Enemy(rand()%(int)borderXMax, rand()%(int)borderYMax, 0));
            }
        }

        //Getters
        int getLevelNumber(){
            return this->levelNumber;
        }

        int getMaxSpawnedEnemies(){
            return this->maxSpawnedEnemies;
        }

        int getInitialSpawnedEnemies(){
            return this->initialSpawnedEnemies;
        }

        int getEnemiesSpawned(){
            return this->enemiesSpawned;
        }

        int getEnemiesLeft(){
            return this->enemiesLeft;
        }

        int getEnemiesKilled(){
            return this->enemiesKilled;
        }

        int getEnemiesEscaped(){
            return this->enemiesEscaped;
        }

        float getEnemySpawnRate(){
            return this->enemySpawnRate;
        }

        float getObjectiveHealthPoints(){
            return this->ObjectiveHealthPoints;
        }

        Player *getPlayer(){
            return this->player;
        }

        vector<Enemy> getEnemies(){
            return this->enemies;
        }
        
        vector<float> getLevelBorders(){
            vector<float> borders;
            borders.push_back(this->borderXMin);
            borders.push_back(this->borderXMax);
            borders.push_back(this->borderYMin);
            borders.push_back(this->borderYMax);
            borders.push_back(this->borderZMin);
            borders.push_back(this->borderZMax);
            return borders;
        }

        // Setters
        void setLevelNumber(int levelNumber){
            this->levelNumber = levelNumber;
        }

        void setMaxSpawnedEnemies(int maxSpawnedEnemies){
            this->maxSpawnedEnemies = maxSpawnedEnemies;
        }

        void setInitialSpawnedEnemies(int initialSpawnedEnemies){
            this->initialSpawnedEnemies = initialSpawnedEnemies;
        }

        void setEnemiesSpawned(int enemiesSpawned){
            this->enemiesSpawned = enemiesSpawned;
        }

        void setEnemiesLeft(int enemiesLeft){
            this->enemiesLeft = enemiesLeft;
        }

        void setEnemiesKilled(int enemiesKilled){
            this->enemiesKilled = enemiesKilled;
        }

        void setEnemiesEscaped(int enemiesEscaped){
            this->enemiesEscaped = enemiesEscaped;
        }

        void setEnemySpawnRate(float enemySpawnRate){
            this->enemySpawnRate = enemySpawnRate;
        }

        void setObjectiveHealthPoints(float ObjectiveHealthPoints){
            this->ObjectiveHealthPoints = ObjectiveHealthPoints;
        }

        void setLevelBorders(float borderXMin, float borderXMax, float borderYMin, float borderYMax, float borderZMin, float borderZMax){
            this->borderXMin = borderXMin;
            this->borderXMax = borderXMax;
            this->borderYMin = borderYMin;
            this->borderYMax = borderYMax;
            this->borderZMin = borderZMin;
            this->borderZMax = borderZMax;
        }

        void setLevelBorders(vector<float> borders){
            this->borderXMin = borders[0];
            this->borderXMax = borders[1];
            this->borderYMin = borders[2];
            this->borderYMax = borders[3];
            this->borderZMin = borders[4];
            this->borderZMax = borders[5];
        }

        // Methods
        void renderLevel(){
            this->player->renderObject();

            for (unsigned int i = 0; i < enemies.size(); i++){
                this->enemies[i].renderObject();
                if (checkObjectsCollision(this->player->getPlayerObject(), this->enemies[i].getEnemyObject())){
                    this->player->takeDamage(this->enemies[i].getDamagePoints());
                    this->enemies[i].takeDamage(this->player->getDamagePoints());
                }
            }
        }

        void movePlayerUp(){
            if (!this->player->getPlayerObject()->checkCollisionTopBorder(this->borderYMax)){
                this->player->moveUp();
            }
        }

        void movePlayerDown(){
            if (!this->player->getPlayerObject()->checkCollisionBottomBorder(this->borderYMin)){
                this->player->moveDown();
            }
        }

        void movePlayerLeft(){
            if (!this->player->getPlayerObject()->checkCollisionLeftBorder(this->borderXMin)){
                this->player->moveLeft();
            }
        }

        void movePlayerRight(){
            if (!this->player->getPlayerObject()->checkCollisionRightBorder(this->borderXMax)){
                this->player->moveRight();
            }
        }

        void moveEnemies(){
            for (unsigned int i = 0; i < enemies.size(); i++){
                cout << "Enemy " << i << " is moving" << endl;
                enemies[i].moveEnemy();
            }
        }

        void clearEnemies(){
            enemies.clear();
        }

        void resetLevel(){
            this->levelNumber = 1;
            this->maxSpawnedEnemies = 10;
            this->initialSpawnedEnemies = 5;
            this->enemiesSpawned = 0;
            this->enemiesLeft = 0;
            this->enemiesKilled = 0;
            this->enemiesEscaped = 0;
            this->enemySpawnRate = 1;
            this->ObjectiveHealthPoints = 100;
            this->player->resetPlayer();
            this->clearEnemies();
            // Initialize 10 enemies on random positions
            for (int i = 0; i < 10; i++){
                enemies.push_back(Enemy(rand()%(int)borderXMax, rand()%(int)borderYMax, 0));
            }
        }
};

#endif
