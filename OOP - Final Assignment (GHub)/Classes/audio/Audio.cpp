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

#include "audio/Audio.h"

const cocos2d::experimental::AudioProfile * effectsProfile;
const cocos2d::experimental::AudioProfile * musicProfile;

void profileSetup() {
	//Audio Profiles (allows multiple audio tracks playing simultaneously)
	//effectsProfile.name = "Audio - Effects";
	//effectsProfile.maxInstances = 8;
	//effectsProfile.minDelay = 0.1f;
	//
	//musicProfile.name = "Audio - Music";
	//musicProfile.maxInstances = 1;
	//musicProfile.minDelay = 0.1f;
}

Sound::Sound(std::string _effect, bool _loop) {
	effect = "audio/fx/" + _effect + ".mp3";
	loop = _loop;
}

Sound::~Sound() {
}

void Sound::preload() {
	cocos2d::experimental::AudioEngine::preload(effect); //Preloads this track
}
void Sound::uncache() {
	cocos2d::experimental::AudioEngine::uncache(effect); //Removes from cache
}
void Sound::play() { //This thing plays the sound effect
	id = cocos2d::experimental::AudioEngine::play2d(effect, loop, 1.0f, effectsProfile);
}
void Sound::resume() {
	cocos2d::experimental::AudioEngine::resume(id);
}
void Sound::pause() {
	cocos2d::experimental::AudioEngine::pause(id);
}
void Sound::stop() {
	cocos2d::experimental::AudioEngine::stop(id);
}
void Sound::end() {
	cocos2d::experimental::AudioEngine::end();
}

Music::Music(std::string _AIN) {
	AIN = "audio/music/" + _AIN + ".mp3";
}

Music::~Music() {
}

void Music::preload() {
	cocos2d::experimental::AudioEngine::preload(AIN); //Preloads this track
}
void Music::uncache() {
	cocos2d::experimental::AudioEngine::uncache(AIN); //Removes from cache
}
void Music::play() { //This will play music
	id = cocos2d::experimental::AudioEngine::play2d(AIN, true, 0.1f, musicProfile);
}
void Music::resume() {
	cocos2d::experimental::AudioEngine::resume(id);
}
void Music::pause() {
	cocos2d::experimental::AudioEngine::pause(id);
}
void Music::stop() {
	cocos2d::experimental::AudioEngine::stop(id);
}
void Music::end() {
	cocos2d::experimental::AudioEngine::end();
}

void preload() { //Preloading things
	/*
	//General Sounds
	Sound ui_confirm("ui_confirm"); //Sound played when you confirm something on UI
	Sound ui_select("ui_select"); //Selecting different options on UI
	
	//Player Related Sounds
	Sound plr_move("plr_move"); //Moving
	Sound plr_land("plr_land"); //Lands after falling (MAYBE?)
	Sound plr_attack("plr_attack"); //Standard attack sound
	Sound plr_death("plr_death"); //When the player dies
	
	//Enemy Related Sounds
	Sound ene_move("ene_move"); //Moving
	Sound ene_land("ene_land"); //Lands after falling (MAYBE?)
	Sound ene_attack("ene_attack"); //Standard attack sound
	Sound ene_death("ene_death"); //When an enemy dies
	*/
	
	Music testTrack("Mashadeau_1");
}