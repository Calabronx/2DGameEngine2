#include <iostream>

#include "core/application.h"
#include "app_layer.h"
#include "balls_app_layer.h"
#include "AudioVisualApp.h"
#include "TriangleShader.h"

int main(int argc,  char* argv[])
{
    Engine::ApplicationSpecification appSpec;
    appSpec.Name = "AppSpecification";
    appSpec.WindowSpec.Width = 800;
    appSpec.WindowSpec.Height = 600;

    Engine::Application application(appSpec);
    //application.PushLayer<BallsAppLayer>();
    application.PushLayer<TriangleShader>();
    // application.PushLayer<AudioVisualApp>();
    application.Run();


    return 0;
}