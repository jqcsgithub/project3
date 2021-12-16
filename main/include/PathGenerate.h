#ifndef PATHGENERATE_H
#define PATHGENERATE_H

#include <QVector>
#include "Coordinate.h"

class PathGenerate{
private:
    QVector<QVector<coor>> Path;
    QVector<coor> TempPath;
    int dirc[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    int mapLength;
    int mapWidth;
    int **mp;
    void DFS(coor c) // here require that the map must be a tree
    {
        TempPath.push_back({c.x * blockLen, c.y * blockLen});
        for (int i = 0; i < 4; ++i)
        {
            int x = c.x + dirc[i][0];
            int y = c.y + dirc[i][1];
            if (x < 0 || y < 0 || x >= mapLength || y >= mapWidth) continue;
            if (mp[x][y] == castle)
            {
                TempPath.push_back({x * blockLen, y * blockLen});
                Path.push_back(TempPath);
                TempPath.pop_back();
                TempPath.pop_back();
                return;
            }
            else if (mp[x][y] == road)
            {
                mp[x][y] = 0;
                DFS({x, y});
                mp[x][y] = road;
            }
            else continue;
        }
        TempPath.pop_back();

        return;
    }
    void findPath()
    {
        Path.clear();
        TempPath.clear();
        for (int i = 0; i < mapLength; ++i){
            for (int j = 0; j < mapWidth; ++j){
                if (mp[i][j] == enemyCamp)
                {
                    TempPath.clear();
                    DFS({i, j});
                }
            }
        }
    }

public:
    QVector<QVector<coor>> GetPath(int *map, int length, int width){
        mapLength = length;
        mapWidth = width;
        for (int i = 0; i < mapLength; ++i){
            for (int j = 0; j < mapWidth; ++j){
                this->mp[i][j] = map[i * mapWidth + j];
            }
        }
        findPath();
        return Path;
    }
};

#endif // PATHGENERATE_H
