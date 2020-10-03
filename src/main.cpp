#include "config.h"
#include "udp_client.h"
#include "renderer.h"

using namespace Bono;

int main()
{
    // Shared inter-thread data container
    std::shared_ptr<RaceDataBuffer> raceDataBuffer = std::make_shared<RaceDataBuffer>(MAX_NUM_PACKETS);

    // Fire up the Async UDP Client on it's own thread
    UdpClient client("127.0.0.1", 20777, raceDataBuffer);
    std::thread udpReceiveThread([&] { client.Receive(); });

    // And start the renderer on Main
    Renderer renderer(raceDataBuffer);
    renderer.Render();

    // When the renderer closes, so too should the UDP client
    client.Shutdown();
    udpReceiveThread.join();

    return 0;
}