#include "udp_client.h"
#include "renderer.h"

using namespace Bono;

int main()
{
    // Fire up the Async UDP Client on it's own thread
    UdpClient client("127.0.0.1", 20777);
    std::thread udpReceiveThread([&] { client.Receive(); });

    // And start the renderer on Main
    Renderer renderer;
    renderer.Render(&client);

    // When the renderer closes, so too should the UDP client
    udpReceiveThread.join();

    return 0;
}