﻿#include <ctime>
#define EXCLUDE_WINDOWS_TIME_H
#include <sys/stat.h>
#define EXCLUDE_WINDOWS_STAT_H
#include "StopWatch.h"
import user;
import game;
import<iostream>;
import<vector>;
#include<deque>
#include<filesystem>
#include<memory>
#include <crow.h>
#include "usersDB.h"

int main()
{
	using namespace gartic;
	//std::cout << "Introduceti Username-ul:";
	//std::string name;
	//std::cin >> name;
	//User a = User(1, name);
	//Game b = Game();
	//b.FileRead();
	//b.verifyGuessed();
	//std::string word = b.GetGuessedWord();


	const std::string db_file = "products.sqlite";
	Storage db = createStorage(db_file);
	db.sync_schema();

	auto initUsersCount = db.count<User>();
	if (initUsersCount == 0)
		populateStorage(db);

	auto usersCount = db.count<User>();
	std::cout << "\nusersCount = " << usersCount << '\n';

	std::deque<std::string> chatMessages;

	crow::SimpleApp app;


	CROW_ROUTE(app, "/")([]() {
		return "<html>"
			"<body>"
			"<p>This is the main lobby</p>"
			"<p>Go to the Game section: <a href=\"/game\">Game</a></p>"
			"<p>Go to the Users section: <a href=\"/users\">users</a></p>"
			"<p>Go to the chat section: <a href=\"/chat\">chat</a></p>"
			"<p>Go to the Guesser's section: <a href=\"/guesser\">WordToGuess</a></p>"
			"</body>"
			"</html>";
		});

	CROW_ROUTE(app, "/game")([]() {
		return "This is the Game section";
		});


	CROW_ROUTE(app, "/users")([&db]()
		{
			std::vector<crow::json::wvalue> users_json;

			for (const auto& user : db.iterate<User>())
			{
				users_json.push_back(crow::json::wvalue{
					{"id", user.GetId()},
					{"name", user.GetName()},
					});
			}
			return crow::json::wvalue{ users_json };
		});

	CROW_ROUTE(app, "/adduser").methods(crow::HTTPMethod::Put)([&db](const crow::request& req)
		{
			std::string name{ req.url_params.get("name") };

			gartic::User newUser;
			newUser.SetName(name);
			db.insert(newUser);

			return crow::response(200);
		});

	CROW_ROUTE(app, "/chat").methods(crow::HTTPMethod::Put)([&chatMessages](const crow::request& req) {
		

		// Extract the message from the request body
		std::string message{ req.url_params.get("You") };

		// Store the message in the chatMessages deque
		chatMessages.push_back(message);

		return crow::response(200);
		});

	CROW_ROUTE(app, "/get_chat").methods("GET"_method)([&chatMessages]() {
		std::vector<crow::json::wvalue> jsonMessages;
		std::string a;
		for (auto x : chatMessages)
		{
			jsonMessages.push_back(crow::json::wvalue{
					{"message", x},
				
				});
		}
		return crow::json::wvalue{ jsonMessages };
		});

	app.port(18080).multithreaded().run();
	return 0;
}


	//Incercare addUser V1


	//// Construiește JSON-ul
	//std::string json_data = R"({"name": ")" + name + R"(", "average": )" + std::to_string(average) + "}";

	//// Trimite cererea POST către server
	//cpr::Response r = cpr::Post(cpr::Url{ "http://localhost:18080/addUser" },
	//	cpr::Header{ {"Content-Type", "application/json"} },
	//	cpr::Body{ json_data });

	//// Verifică dacă cererea a fost realizată cu succes
	//if (r.status_code == 201) {
	//	std::cout << "User adăugat cu succes!\n";
	//}
	//else {
	//	std::cerr << "Eroare la adăugarea utilizatorului. Cod de stare: " << r.status_code << "\n";
	//}

	//CROW_ROUTE(app, "/addUser").methods("POST"_method)([&db](const crow::request& req) 
	//{
	//	// Parsare și procesare cerere POST



	//CROW_ROUTE(app, "/adduser").methods("POST"_method)([&db](const crow::request& req, crow::response& res)
	//	{

	//		if (req.body == "")
	//		{
	//			res.code = 400;
	//			res.write("Body empty");
	//			return;
	//		}

	//		auto name = req.body;

	//		gartic::User newUser;
	//		newUser.SetName(name);
	//		db.insert(newUser);

	//		res.code = 200; // OK
	//		res.write("User added successfully");
	//	});




	//CROW_ROUTE(app, "/guesser")([word, a]() {
	//	std::vector<crow::json::wvalue> word_json;
	//	word_json.push_back(crow::json::wvalue{
	//		{"Name",a.GetName()},
	//		{"Guess:", word}
	//		});
	//	return crow::json::wvalue{ word_json };
	//	});








	//	auto json = crow::json::load(req.body);
	//	if (!json)
	//	{
	//		return crow::response(400, "Invalid JSON");
	//	}

	//	// Extrage informațiile despre utilizator din JSON
	//	//int id= json["id"].s();
	//	std::string name = json["name"].s();
	//	float average = json["average"].d();

	//	// Creează un obiect User și adaugă-l în baza de date
	//	gartic::User newUser(0, name, average); // Id-ul va fi setat automat de baza de date
	//	db.insert(newUser);

	//	return crow::response(201); // Răspuns pentru succes
	//	});

	


	//Incercare addUser V2
	//CROW_ROUTE(app, "/adduser/<int>")([&db](const crow::request& req, int userId) { 
	//gartic::User newUser; 
	//std::string name_chr=req.url_params.get("name");   
	//
	//newUser.SetId(userId); 
	//newUser.SetName(name_chr); 
	//db.insert(newUser); 
	//return crow::response(200); 
	//	});
	//
	//auto& addToUserPut = CROW_ROUTE(app, "/adduser").methods(crow::HTTPMethod::PUT); // https://stackoverflow.com/a/630475/12388382 
	//addToUserPut(AddToUser(db));