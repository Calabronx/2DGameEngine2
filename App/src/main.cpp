#include <iostream>

#include "core/application.h"
// #include "apps/TriangleShader.h"
#include "game/game.h"

int main(int argc,  char* argv[])
{
    Engine::ApplicationSpecification appSpec;
    // appSpec.Name = "TriangleRingApp";
    appSpec.Name = "Game";
    appSpec.WindowSpec.Width = 800;
    appSpec.WindowSpec.Height = 600;

    Engine::Application application(appSpec);
    application.PushLayer<Application::Game>();
    //application.PushLayer<BallsAppLayer>();
    // application.PushLayer<TriangleShader>();
    application.Run();


    return 0;
}