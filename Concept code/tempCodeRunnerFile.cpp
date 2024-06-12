if (gameMap->checkoccupied(newX, newY) == true)
        {
            newX = oldX;
            newY = oldY;
            cout << "There seems to be something in the way...";
        }