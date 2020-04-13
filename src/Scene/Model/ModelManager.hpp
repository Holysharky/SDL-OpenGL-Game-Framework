#ifndef MODEL_MANAGER_HPP
#define MODEL_MANAGER_HPP

#include <cstdint>
#include <functional>
#include <SDL.h>
class MainUiManager;

class ModelManager {
    protected:
        /**  Camera  **/
        float modelScale, initialModelScale; // pixels per game coord
        float cameraX, cameraY; // position of the center of the camera in game coords

        uint32_t modelTick;

        // Actual update function
        virtual void updateOneTick();

        std::function<void(int&, int&, float, float)> getGameToScreenCoordsFunc(MainUiManager *uiManager);
        std::function<float(float)> getGameToScreenLengthFunc();

    public:
        ModelManager(float initialModelScale);
        virtual ~ModelManager();

        uint32_t getModelTick();
        float getModelScale();
        float getCameraX();
        float getCameraY();

        // Wraps updateOneTick() in some admin
        void doTick();

        /**  UI  **/
        void screenToGameCoords(const SDL_Rect &screenRect, float& gameX, float& gameY, int screenX, int screenY) const;
        void gameToScreenCoords(const SDL_Rect &screenRect, int& screenX, int& screenY, float gameX, float gameY) const;
        float gameToScreenLength(float gameLength) const;

        void resetCamera();
        void moveCamera(float x, float y); // Move the camera by (x,y)
        void scaleCamera(float scale); // Scale the modelScale by a factor of scale

        // (x,y) in game coordinates
        virtual void pickActiveEntity(float x, float y);
        virtual void click();
        virtual void releaseMouse();

        virtual void draw(MainUiManager *uiManager);
};

#endif // MODEL_MANAGER_HPP