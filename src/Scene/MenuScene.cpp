#include "MenuScene.hpp"

#include <cstdio>
#include <SDL.h>
#include "Widget/Widget.hpp"
#include "../MainApp/MessageHandler.hpp"
#include "../Message/SceneTransitMessage.hpp"
#include "../MainUiManager/MainUiManager.hpp"
#include "GameScene.hpp"

MenuScene::MenuScene()
        : Scene() {

    loadWidgets();
}
MenuScene::~MenuScene() {}

void MenuScene::loadWidgets() {
	const static SDL_Color white = {255, 255, 255, 255};
	const static SDL_Color textColor = {255, 200, 200, 255};

	loadWidget( new Widget(
		{40, 20, 240, 20},
		Widget::HORZALIGN_LEFT,
		Widget::VERTALIGN_TOP,
		/*funcOnClick*/ []() {
			MessageHandler::postMessage( new SceneTransitMessage( new GameScene() ) );
		},
		/*drawFunc*/ [](const Widget* widget, MainUiManager* uiManager) {
			SDL_Color textColor;
			if (widget->getActive()) textColor = {255, 255, 200, 255};
			else                     textColor = {255, 200, 200, 255};
			widget->renderText(uiManager, "Click here to go to game", textColor);
		} ) );

    loadWidget( new Widget(
		{20, 20, 160, 20},
		Widget::HORZALIGN_CENTER,
		Widget::VERTALIGN_TOP,
		/*funcOnClick*/ nullptr,
		/*drawFunc*/ [&](const Widget* widget, MainUiManager* uiManager) {
			widget->renderText(uiManager, "MENU SCENE", textColor);
		} ) );

    loadWidget( new Widget(
		{20, 80, 160, 20},
		Widget::HORZALIGN_RIGHT,
		Widget::VERTALIGN_BOTTOM,
		/*funcOnClick*/ nullptr,
		/*drawFunc*/ [&](const Widget* widget, MainUiManager* uiManager) {
			if (!paused) return;
			widget->renderText(uiManager, "-- PAUSED --", white);
		} ) );

    loadWidget( new Widget(
		{20, 60, 160, 20},
		Widget::HORZALIGN_RIGHT,
		Widget::VERTALIGN_BOTTOM,
		/*funcOnClick*/ nullptr,
		/*drawFunc*/ [&](const Widget* widget, MainUiManager* uiManager) {
			char msg[256];
			sprintf(msg, "UiTick: %u", uiManager->getUiTick());
			widget->renderText(uiManager, msg, textColor);
		} ) );

    loadWidget( new Widget(
		{20, 40, 160, 20},
		Widget::HORZALIGN_RIGHT,
		Widget::VERTALIGN_BOTTOM,
		/*funcOnClick*/ nullptr,
		/*drawFunc*/ [&](const Widget* widget, MainUiManager* uiManager) {
			char msg[256];
			sprintf(msg, "ModelTick: %u", modelTick);
			widget->renderText(uiManager, msg, textColor);
		} ) );

    loadWidget( new Widget(
		{20, 20, 160, 20},
		Widget::HORZALIGN_RIGHT,
		Widget::VERTALIGN_BOTTOM,
		/*funcOnClick*/ nullptr,
		/*drawFunc*/ [&](const Widget* widget, MainUiManager* uiManager) {
			char msg[256];
			sprintf(msg, "FPS: %.2f", uiManager->fps);
			widget->renderText(uiManager, msg, textColor);
		} ) );
}