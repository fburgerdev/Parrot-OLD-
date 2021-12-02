#pragma once
#include "ParrotScript.hpp"
using namespace Parrot;

static const char* lindnerZitate[] =
{
	"Jugendliche muessen erfahren, dass sie etwas koennen und gebraucht werden.Sie muessen gefordert und gefoerdert werden.",
	"Wir brauchen auch in der Zukunft eine gesteuerte Zuwanderung, aber eben in unsere Wirtschaft, in produktive Jobs und nicht in unser Sozialsystem.",
	"Die Terroristen gewinnen, wenn wir selbst unsere Freiheit aus Angst preisgeben und andauernd neue praeventive Eingriffe in die Privatsphaere hinnehmen.",
	"Ich empfinde Hochachtung vor dem libyschen Volk, das sich aus den Ketten Gaddafis befreit hat.Und ich empfinde auch Respekt vor unseren Verbuendeten, die Gaddafis Kriegsmaschinerie zerschlagen haben.",
	"Wir wollen eine Stabilitaetsunion in Europa und keine Transferunion.",
	"Der Abbau der Neuverschuldung des Staates und die Entlastung der Mittelschicht sind kein Widerspruch.",
	"Wir duerfen einen zweiten Fall Lehman Brothers nicht zulassen.",
	"Der Finanzmarkt wird gezaehmt, nicht in Ketten gelegt.",
	"Entlastung der unteren und mittleren Einkommen, das ist ein wesentliches Ziel.Wann denn, wenn nicht jetzt ?",
	"Was hilft uns denn die Vorratsdatenspeicherung, wenn bekannte Informationen nicht umgesetzt werden ?",
	"Die Gewinne der Stromunternehmen haben SPD und Gruene unangetastet gelassen.Dieser Klientelpolitik setzen wir endlich ein Ende.",
	"Eine offene Gesellschaft kann nicht die Sicherheit wichtiger nehmen als die Freiheit.",
};

class Prank : public Component::Script
{
public:
	Window* wndw;
	//Math::Vec2f v;
	//float g = 0.3f;
	//int wallsHit = 0;
public:
	using Script::Script;

	virtual void OnCreate() override
	{
		//v = { (float)rand() / RAND_MAX, (float)rand() / RAND_MAX };
		//v -= Math::Vec2f(0.5f);
		//v *= 20.0f;
		wndw = &sceneObj.GetScene().GetWindow();
		wndw->SetTitle(std::string(lindnerZitate[(int)(12.0f * (float)rand() / RAND_MAX)]));
	}
	virtual void OnEvent(Event e) override
	{
		if (e.type == EventType::CloseRequest)
			OpenWindow(AssetManager::GetWindowAsset("Lindner"));
	}

	virtual void OnUpdate() override
	{
		//wndw->SetWindowPos(wndw->GetWindowPos() + (Math::Vec2i)v);
		/*for (Window* other : prankWindows)
		{
			if (other = wndw)
				continue;
			if (wndw->GetWindowPos().x + wndw->GetSize().x >= other->GetWindowPos().x)
			{
				if (wndw.)
			}
		}*/
		//if (wndw->GetWindowPos().y + wndw->GetSize().y >= 1080)
		//	v.y *= -1;
		//else
		//	v.y += g;
		//if (wndw->GetWindowPos().x <= 0 || wndw->GetWindowPos().x + wndw->GetSize().x >= 1920)
		//{
		//	v.x *= -1;
		//	wallsHit++;
		//	if (wallsHit == 3)
		//	{
		//		OpenWindow(AssetManager::GetWindowAsset("Lindner"));
		//		wallsHit = 0;
		//	}
		//}

		//Math::Vec2i pos = wndw->GetCursorPos() + Math::Vec2i(32 - wndw->GetSize().x, 16);
		//if (pos < Math::Vec2i(40, 20) && pos > -Math::Vec2i(40, 20))
		//{
		//	Math::Vec2i newPos = wndw->GetWindowPos() - pos;
		//	wndw->SetWindowPos(newPos);
		//}
	}
};