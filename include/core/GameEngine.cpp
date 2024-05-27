#include <imgui.h>

#include <imgui-SFML.h>

#include "GameEngine.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>
#include "../../include/core/GameEngine.hpp"

#include "../ECS/system/systems/MovementSystem.hpp"
#include "../ECS/system/systems/RenderSystem.hpp"
#include "../ECS/system/systems/CollisionSystem.hpp"
#include "../ECS/system/systems/InputSystem.hpp"
#include "../scene/scenes/Play.hpp"
#include "../scene/scenes/Title.hpp"


#include <iostream>
#include <typeinfo>
#include <fstream>
#include <type_traits>

#include "../ECS/Animation.hpp"

// ctor, no dtor neccessary... RAII be like that sometimes
GameEngine::GameEngine()
	: m_scenes{}, m_currentScene{}
	, wnd{ sf::VideoMode(::GameProperties::SCRW, ::GameProperties::SCRH), "ECS_Architecture", sf::Style::None }
	, paused{false}
	, animations{}
{
	

	m_scenes["title"] = std::make_shared<Title>(*this, Config::inputs);

	changeScene("title");
	

}

std::shared_ptr<Scene> GameEngine::currentScene()
{
	return m_scenes.at(m_currentScene);
}

void GameEngine::loadAnimations(std::string filename)
{
	std::ifstream iFile;
	iFile.open(filename);

	if (!iFile.is_open())
	{
		std::cout << "Animation File unable to be read in!" << std::endl;
	}
	else
	{
		int numTextures;
		iFile >> numTextures;

		for (int i = 0; i < numTextures; i++)
		{
			std::string texName;
			iFile >> texName;

			int numAnimsInTexture;
			iFile >> numAnimsInTexture;

			for (int j = 0; j < numAnimsInTexture; j++)
			{
				std::string animName;
				iFile >> animName;

				//file is open
				int sizex, sizey, numframes, cols, rows, startposx, startposy, framedelayMS;
				std::string looping, flippedH, flippedV;

				iFile >> sizex >> sizey >> numframes >> cols >> rows >> startposx >> startposy >> framedelayMS >> looping >> flippedH >> flippedV;
				const std::string str = animName;
				animations.insert(std::pair(Config::Textures::Player, std::map<std::string, std::shared_ptr<Animation>>{std::make_pair(str, std::make_shared<Animation>(sf::Vector2i(sizex, sizey), str, numframes, cols, rows, sf::Vector2i{ startposx,startposy }, (float)framedelayMS / 1000.f, (looping == "true") ? true : false, (flippedH == "true") ? true : false, (flippedV == "true") ? true : false))}));
			}
		}
		iFile.close();
	}
}

std::shared_ptr<Animation> GameEngine::getAnimation(Config::Textures texName, const std::string& animName)
{
	for (auto& outer : this->animations)
	{
		for (auto& inner : outer.second)
		{
			if (inner.second->name() == animName)
				return inner.second;
		}
	}

	return nullptr;

}


void GameEngine::changeScene(std::string l_scene)
{
	m_currentScene = l_scene;
	currentScene()->init();
}

// value passed to this function always simulates a normalization to 60 fps, no matter what
//  should be smooth physics calculations because of this
void GameEngine::update(sf::Time l_dt)
{
	currentScene()->update((double)l_dt.asSeconds());

	
}

// work your magic in here, blit a portion of a giant rendertexture sitting on the GPU the size of the window to the window for performance
void GameEngine::render(sf::RenderWindow& l_wnd)
{
	currentScene()->render(l_wnd);
}

bool GameEngine::gameRunning = true;


// to abstract implementation away from the main function, just to be clean and concise
void GameEngine::mainLoop()
{
	
	

	sf::Time deltaTime{ sf::Time::Zero };
	sf::Clock frameTimer{ };

	wnd.setVerticalSyncEnabled(true);

	wnd.setPosition(sf::Vector2i(450, 300));
	wnd.setSize({ (unsigned int)::GameProperties::SCRW, (unsigned int)::GameProperties::SCRH });
	ImGui::SFML::Init(wnd);
	frameTimer.restart();
	bool focus = false;
	bool hadFocus = false;
	bool waitingForARender = false;
	sf::Time fps60 = sf::seconds(1.f / 60.f);
	
	//
	
	while (gameRunning)
	{
		focus = wnd.hasFocus();

		if (focus && wnd.isOpen())
		{
			hadFocus = true;
			// process realtime input
			currentScene()->processInput();
			currentScene()->currentSystem->update((double)fps60.asSeconds());
			

			std::vector<sf::Event> evtsToProp;
			evtsToProp.clear();
			// process window events
			sf::Event event;
			while (wnd.pollEvent(event))
			{
				ImGui::SFML::ProcessEvent(wnd, event);
				if (event.type == sf::Event::KeyReleased)
				{
					if (event.key.code == sf::Keyboard::Escape)
					{
						gameRunning = false;
						goto afterLoop;
					}
					
				}
				else if (event.type == sf::Event::Closed)
				{
					gameRunning = false;
					goto afterLoop;
				}

				evtsToProp.emplace_back(std::move(event));
				if (!gameRunning) goto afterLoop;
			}
			currentScene()->processEvents(evtsToProp);

			deltaTime += frameTimer.restart();
			ImGui::SFML::Update(wnd, deltaTime);
			waitingForARender = true;
			// uncomment to learn ImGui
			//ImGui::ShowDemoWindow();
	
			while (deltaTime > fps60)
			{
				update(fps60);
				
				deltaTime -= fps60;
			}
			ImGui::Begin("Window");
			ImGui::SeparatorText("hello world");
			ImGui::End();

			wnd.clear(sf::Color::Blue);

			render(wnd);
			ImGui::SFML::Render(wnd);
			waitingForARender = false;
			wnd.display();
			
		}
		else
		{
			frameTimer.restart();
			if (hadFocus )
			{
				hadFocus = false;
				if (waitingForARender)
				{
					ImGui::SFML::Render(wnd);
					waitingForARender = false;
				}
			}
		}

	}
afterLoop:
	if (waitingForARender)
	{
		ImGui::SFML::Render(wnd);
		waitingForARender = false;
	}
	ImGui::SFML::Shutdown();
	wnd.close();
}




