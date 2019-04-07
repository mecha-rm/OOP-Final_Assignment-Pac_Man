/*
Project: Mashadeau: Sorcerer's Quest (Game Development Workshop II (INFR 1396U) Video Game)
Team: Ampersand V (&V)
	- Caleb Birnie (100699828)
	- Carter Menary (100700587)
	- Devin Fitzpatrick (100709082)
	- Nathan Tuck (100708651)
	- Roderick “R.J.” Montague (100701758)
	- Jason Lee (100698121)
		*Jason Lee was only part of this group for the purposes of Digital Game Design.
		*Jason is not in Essential Mathematics for Games II, Object Oriented Programming, or Game Development Workshop II.
Date: 04/04/2019
*/

// an audio engine used for making game sound and music
#pragma once
#include "AudioEngine.h"

void profileSetup();

class Sound {
public: 
	Sound(std::string _effect, bool _loop);
	~Sound();

	void preload();
	void uncache();
	void play();
	void resume();
	void pause();
	void stop();
	void end();

private:
	std::string effect;
	int id;
	bool loop;
};

class Music {
public: 
	Music(std::string _AIN);
	~Music();
	
	void preload();
	void uncache();
	void play();
	void resume();
	void pause();
	void stop();
	void end();

private: 
	std::string AIN;
	int id;
};

void preload();