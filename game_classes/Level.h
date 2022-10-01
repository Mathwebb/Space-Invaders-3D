#ifndef LEVEL_H
#define LEVEL_H

#include <vector>

#include "Object.h"
#include "Projectile.h"
#include "Player.h"
#include "Enemy.h"
#include "../game_functions/check collisions.h"

using namespace std;

enum levelStatus{LEVEL_IN_PROGRESS, LEVEL_PAUSED, LEVEL_LOST, LEVEL_WON};

class Level{
    private:
        levelStatus status;
        int levelNumber;
        int maxEnemiesInLevel, maxSpawnedEnemies, initialSpawnedEnemies, enemiesAlreadySpawned;
        float enemiesSpawnRateMiliseconds;
        int enemiesLeft, enemiesKilled, enemiesEscaped;
        float ObjectiveHealthPoints;
        Player *player;
        vector<Enemy> enemies;
        vector<Projectile> projectiles;
        float borderXMin, borderXMax, borderYMin, borderYMax, borderZMin, borderZMax;
    public:
        // Constructors
        Level(){
            this->status = LEVEL_IN_PROGRESS;
            this->levelNumber = 1;
            this->maxEnemiesInLevel = 8;
            this->maxSpawnedEnemies = 20;
            this->initialSpawnedEnemies = 5;
            this->enemiesAlreadySpawned = 0;
            this->enemiesLeft = 0;
            this->enemiesKilled = 0;
            this->enemiesEscaped = 0;
            this->enemiesSpawnRateMiliseconds = 1000;
            this->ObjectiveHealthPoints = 100;
            this->player = new Player();
            this->borderXMin = -250;
            this->borderXMax = 250;
            this->borderYMin = -250;
            this->borderYMax = 250;
            this->borderZMin = -1000;
            this->borderZMax = 100;
        }

        //Getters
        levelStatus getStatus() {
            return this->status;
        }

        int getLevelNumber(){
            return this->levelNumber;
        }

        int getMaxEnemiesInLevel(){
            return this->maxEnemiesInLevel;
        }

        int getMaxSpawnedEnemies(){
            return this->maxSpawnedEnemies;
        }

        int getInitialSpawnedEnemies(){
            return this->initialSpawnedEnemies;
        }

        int getEnemiesAlreadySpawned(){
            return this->enemiesAlreadySpawned;
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

        float getEnemiesSpawnRateMiliseconds(){
            return this->enemiesSpawnRateMiliseconds;
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

        vector<Projectile> getProjectiles(){
            return this->projectiles;
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
        void setLevelStatus(levelStatus status) {
            this->status = status;
        }

        void setLevelNumber(int levelNumber){
            this->levelNumber = levelNumber;
        }

        void setMaxEnemiesInLevel(int maxEnemiesInLevel){
            this->maxEnemiesInLevel = maxEnemiesInLevel;
        }

        void setMaxSpawnedEnemies(int maxSpawnedEnemies){
            this->maxSpawnedEnemies = maxSpawnedEnemies;
        }

        void setInitialSpawnedEnemies(int initialSpawnedEnemies){
            this->initialSpawnedEnemies = initialSpawnedEnemies;
        }

        void setEnemiesAlreadySpawned(int enemiesAlreadySpawned){
            this->enemiesAlreadySpawned = enemiesAlreadySpawned;
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

        void setEnemiesSpawnRateMiliseconds(float enemiesSpawnRateMiliseconds){
            this->enemiesSpawnRateMiliseconds = enemiesSpawnRateMiliseconds;
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

            for (unsigned int i = 0; i < this->projectiles.size(); i++){
                this->projectiles[i].renderObject();
                for (unsigned int j = 0; j < enemies.size(); j++){
                    if (checkObjectsCollision(this->projectiles[i].getProjectileObject(), this->enemies[j].getEnemyObject())){
                        this->projectiles.erase(this->projectiles.begin() + i);
                        this->enemies[j].takeDamage(this->projectiles[i].getDamagePoints());
                        if (this->enemies[j].getIsAlive() == false){
                            this->enemies.erase(this->enemies.begin() + j);
                            this->enemiesLeft--;
                            this->enemiesKilled++;
                        }
                    }
                }
            }

            for (unsigned int i = 0; i < enemies.size(); i++){
                this->enemies[i].renderObject();
                if (checkObjectsCollision(this->player->getPlayerObject(), this->enemies[i].getEnemyObject())){
                    this->player->takeDamage(this->enemies[i].getDamagePoints());
                    this->enemies[i].takeDamage(this->player->getDamagePoints());
                }
            }

            if (this->ObjectiveHealthPoints <= 0 || this->player->getIsAlive() == false){
                this->status = LEVEL_LOST;
            }
            if (this->enemies.size() == 0){
                this->status = LEVEL_WON;
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
            bool allEnemiesDead = true;
            for (unsigned int i = 0; i < enemies.size(); i++){
                if (this->enemies[i].getIsAlive()){
                    allEnemiesDead = false;
                }
                if (this->enemies[i].getEnemyObject()->checkCollisionLeftBorder(this->borderXMin)){
                    this->enemies[i].setMovementDirectionX(1);
                }
                if (this->enemies[i].getEnemyObject()->checkCollisionRightBorder(this->borderXMax)){
                    this->enemies[i].setMovementDirectionX(-1);
                }
                if (this->enemies[i].getEnemyObject()->checkCollisionTopBorder(this->borderYMax)){
                    this->enemies[i].setMovementDirectionY(-1*enemies[i].getMovementDirectionY());
                }
                if (this->enemies[i].getEnemyObject()->checkCollisionBottomBorder(this->borderYMin)){
                    this->enemies[i].setMovementDirectionY(1*enemies[i].getMovementDirectionY());
                }
                if (this->enemies[i].getEnemyObject()->checkCollisionFrontBorder(this->borderZMax)){
                    this->enemies.erase(this->enemies.begin() + i);
                    this->enemiesEscaped++;
                    this->enemiesLeft--;
                    this->ObjectiveHealthPoints -= 50;
                }
                if (this->enemies[i].getEnemyObject()->checkCollisionBackBorder(this->borderZMin)){
                    this->enemies[i].setMovementDirectionZ(1);
                }
                enemies[i].moveEnemy();
            }
            if (allEnemiesDead){
                this->enemiesLeft = 0;
                enemies.clear();
            }
        }

        void moveProjectiles(){
            for (unsigned int i = 0; i < this->projectiles.size(); i++){
                if (this->projectiles[i].getProjectileObject()->checkCollision(this->borderXMin, this->borderXMax,
                                                                               this->borderYMin, this->borderYMax,
                                                                               this->borderZMin, this->borderZMax)){
                    this->projectiles.erase(this->projectiles.begin() + i);
                }
                else{
                    this->projectiles[i].moveProjectile();
                }
                projectiles[i].moveProjectile();
            }
        }

        void clearEnemies(){
            enemies.clear();
        }

        void resetLevel(){
            this->status = LEVEL_IN_PROGRESS;
            this->levelNumber = 1;
            this->maxEnemiesInLevel = 10;
            this->initialSpawnedEnemies = 5;
            this->enemiesAlreadySpawned = 0;
            this->enemiesLeft = 0;
            this->enemiesKilled = 0;
            this->enemiesEscaped = 0;
            this->enemiesSpawnRateMiliseconds = 1;
            this->ObjectiveHealthPoints = 100;
            this->player->resetPlayer();
            this->clearEnemies();
            this->spawnInitialEnemies();
        }

        void playerShoot(){
            if (this->player->getIsAlive() && !this->player->getIsShooting()){
                Projectile projectile(PLAYER_PROJECTILE, this->player->getPlayerObject()->getCoordinateX(), this->player->getPlayerObject()->getCoordinateY(), this->player->getPlayerObject()->getCoordinateZ());
                this->projectiles.push_back(projectile);
                player->setIsShooting(true);
            }
        }

        void spawnInitialEnemies(){
            if (this->enemiesAlreadySpawned < this->initialSpawnedEnemies){
                for (int i = 0; i < initialSpawnedEnemies; i++){
                    spawnEnemy();
                }
            }
        }

        void spawnEnemy(){
            if (enemiesLeft <= maxEnemiesInLevel && enemiesAlreadySpawned <= maxSpawnedEnemies){
                enemies.push_back(Enemy((rand()%(int)borderXMax*2) - borderXMax, (rand()%(int)borderYMax*2) - borderYMax, -900));
                this->enemiesLeft++;
                this->enemiesAlreadySpawned++;
            }
        }
};
#endif
