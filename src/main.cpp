#include "config.h"
#include "udp_client.h"
#include "renderer.h"

using namespace Bono;

int main()
{
    // Shared inter-thread data container
    std::shared_ptr<GameData> gameData = std::make_shared<GameData>(MAX_NUM_PACKETS);

    // Fire up the Async UDP Client on it's own thread
    UdpClient client("127.0.0.1", 20777, gameData);
    std::thread udpReceiveThread([&] { client.Receive(); });

    // And start the renderer on Main
    Renderer renderer(gameData);
    renderer.Render();

    // When the renderer closes, so too should the UDP client
    udpReceiveThread.join();

    return 0;
}