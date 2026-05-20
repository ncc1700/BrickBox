#include <brickboxNet.h>

bool example = true;

void OnConnect(BrickBoxClient* client, void* connection, ConnectionResult result){
    if(result == CONNECTION_SUCCESS){
        DEBUG_INFO("SUCCESS!\n");

        ByteStream stream1;
        CreateByteStream(&stream1, 200);
        WriteVarInt(&stream1, 0x00);
        WriteVarInt(&stream1, 774);
        WriteCStr(&stream1, "127.0.0.1", 255);
        WriteU16(&stream1, 25565);
        WriteVarInt(&stream1, 2);
        WriteVarIntFront(&stream1, stream1.storage.used);
        WriteDataToServer(client, stream1.storage.buffer, stream1.storage.used);
        DestroyByteStream(&stream1);
        
        CreateByteStream(&stream1, 200);
        WriteVarInt(&stream1, 0x00);
        WriteCStr(&stream1, "BrickBox", 16);
        WriteU64(&stream1, 0);
        WriteU64(&stream1, 0);
        WriteVarIntFront(&stream1, stream1.storage.used);
        WriteDataToServer(client, stream1.storage.buffer, stream1.storage.used);
        DestroyByteStream(&stream1);
    } else DEBUG_INFO("FAIL\n");
}

int main(){
    BrickBoxClient client = {0};
    CreateBrickBoxClientResult result = CreateBrickBoxClient(&client, "127.0.0.1", 25565);
    if(result != CREATE_BB_CLIENT_SUCCESS){
        DEBUG_FAIL("failed with code of %d\n", result);
    }
    client.OnConnect = OnConnect;
    StartBrickBoxClient(&client);


    DestroyBrickBoxClient(&client);
    return 0;
}

