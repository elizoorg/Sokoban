#include "EventHandler.h"
#include <iostream>
using namespace std;
EventHandler* EventHandler::sInstance = NULL;
EventHandler* EventHandler::Instance()
{
	if (!sInstance)
		sInstance = new EventHandler();
	return sInstance;
}

EventHandler::EventHandler()
{
	delete sInstance;
	sInstance = NULL;
}
void EventHandler::Handle(SDL_Event* Event) {
	switch (Event->type) {
	case SDL_KEYDOWN: {
		OnKeyDown(Event->key.keysym.sym, Event->key.keysym.mod);
		break;
	}
	case SDL_KEYUP: {
		OnKeyUp(Event->key.keysym.sym, Event->key.keysym.mod);
		break;
	}

	case SDL_MOUSEMOTION: {
		OnMouseMove(Event->motion.x, Event->motion.y,
			Event->motion.xrel, Event->motion.yrel,
			(Event->motion.state & SDL_BUTTON(SDL_BUTTON_LEFT)) != 0,
			(Event->motion.state & SDL_BUTTON(SDL_BUTTON_RIGHT)) != 0,
			(Event->motion.state & SDL_BUTTON(SDL_BUTTON_MIDDLE)) != 0);
		break;
	}

	case SDL_MOUSEBUTTONDOWN: {
		switch (Event->button.button) {
		case SDL_BUTTON_LEFT: {
			OnLButtonDown(Event->button.x, Event->button.y);
			break;
		}
		case SDL_BUTTON_RIGHT: {
			OnRButtonDown(Event->button.x, Event->button.y);
			break;
		}
		case SDL_BUTTON_MIDDLE: {
			OnMButtonDown(Event->button.x, Event->button.y);
			break;
		}
		}
		break;
	}

	case SDL_MOUSEBUTTONUP: {
		switch (Event->button.button) {
		case SDL_BUTTON_LEFT: {
			OnLButtonUp(Event->button.x, Event->button.y);
			break;
		}
		case SDL_BUTTON_RIGHT: {
			OnRButtonUp(Event->button.x, Event->button.y);
			break;
		}
		case SDL_BUTTON_MIDDLE: {
			OnMButtonUp(Event->button.x, Event->button.y);
			break;
		}
		}
		break;
	}
	case SDL_MOUSEWHEEL: {
		OnMouseWheel(Event->wheel.y);
		break;
	}
	case SDL_QUIT: {
		break;
	}
	}
}

void EventHandler::OnKeyDown(SDL_Keycode sym, Uint16 mod) { keys_down[sym] = true; }
void EventHandler::OnKeyUp(SDL_Keycode sym, Uint16 mod) { keys_down[sym] = false; }
void EventHandler::OnMouseMove(int mX, int mY, int relX, int relY, bool Left, bool Right, bool Middle) { MousePos.x = mX; MousePos.y = mY; }
void EventHandler::OnMouseWheel(int shift) { shift = shift; }
void EventHandler::OnLButtonDown(int mX, int mY) { mouse_down[SDL_BUTTON_LEFT] = true; setMousePos(mX, mY); }
void EventHandler::OnLButtonUp(int mX, int mY) { mouse_down[SDL_BUTTON_LEFT] = false; setMousePos(mX, mY); }
void EventHandler::OnRButtonDown(int mX, int mY) { mouse_down[SDL_BUTTON_RIGHT] = true; setMousePos(mX, mY); }
void EventHandler::OnRButtonUp(int mX, int mY) { mouse_down[SDL_BUTTON_RIGHT] = false; setMousePos(mX, mY); }
void EventHandler::OnMButtonDown(int mX, int mY) { mouse_down[SDL_BUTTON_MIDDLE] = true; setMousePos(mX, mY); }
void EventHandler::OnMButtonUp(int mX, int mY) { mouse_down[SDL_BUTTON_MIDDLE] = false; setMousePos(mX, mY); }

bool EventHandler::KeyDown(SDL_Keycode keycode) { return keys_down[keycode]; }
vec2i EventHandler::GetMousePos() { return MousePos; }
bool EventHandler::MouseDown(Uint8 mouse) { return mouse_down[mouse]; }
inline void EventHandler::setMousePos(Uint8 x, Uint8 y) { MousePos.x = x; MousePos.y = y; }
