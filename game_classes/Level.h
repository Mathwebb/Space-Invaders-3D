#ifndef LEVEL_H
#define LEVEL_H

struct borders{
    float xMin, xMax, yMin, yMax, zMin, zMax;
};

class Level{
    private:
        int levelNumber;
        int maxSpawnedEnemies, initialSpawnedEnemies, enemiesSpawned, enemiesLeft, enemiesKilled, enemiesEscaped;
        float enemySpawnRate;
        float ObjectiveHealthPoints;
        borders borders;
    public:
};

#endif
