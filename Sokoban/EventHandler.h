#pragma once
#include <SDL.h>
#include <unordered_map>
#include "Vector.h"
class EventHandler
{
public:
	static EventHandler* Instance();
	EventHandler();
	void Handle(SDL_Event* Event);
	void OnKeyDown(SDL_Keycode sym, Uint16 mod);
	void OnKeyUp(SDL_Keycode sym, Uint16 mod);
	void OnMouseMove(int mX, int mY, int relX, int relY, bool Left, bool Right, bool Middle);
	void OnMouseWheel(int shift);
	void OnLButtonDown(int mX, int mY);
	void OnLButtonUp(int mX, int mY);
	void OnRButtonDown(int mX, int mY);
	void OnRButtonUp(int mX, int mY);
	void OnMButtonDown(int mX, int mY);
	void OnMButtonUp(int mX, int mY);
	bool KeyDown(SDL_Keycode keycode);
	vec2i GetMousePos();
	void setMousePos(Uint8 x, Uint8 y);
	bool MouseDown(Uint8 mouse);
	void Reset() {
		keys_down.clear();
		mouse_down.clear();
		shift = 0;
	};

private:
	static EventHandler* sInstance;
	std::unordered_map<uint16_t, bool> keys_down;
	short shift;
	vec2i MousePos;
	std::unordered_map<uint8_t, bool> mouse_down;
};