#include "raylib.h"

int main(){

    //Window dimensions
    const int windowWidth{700};
    const int windowHeight{500};
    InitWindow(windowWidth, windowHeight, "Dapper Dasher");

    //acceleration due to gravity (pixels/second)/second
    const int gravity {1000};

    //nebula variables 
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    Rectangle nebRec{0.0, 0.0, nebula.width/8, nebula.height/8};
    Vector2 nebPos{windowWidth, windowHeight - nebRec.height};
    
    //nebula x velocity (pixels/s)
    int nebVel{-200};
    
    //nebula animation variables
    int nebFrame{};
    const float nebUpdateTime{1.0 / 12.0};
    float nebRunningTime{};

    //scarfy 
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    Rectangle scarfyRec;
    scarfyRec.width = scarfy.width/6;
    scarfyRec.height = scarfy.height; 
    scarfyRec.x = 0;
    scarfyRec.y = 0;
    Vector2 scarfyPos;
    scarfyPos.x = windowWidth/2 - scarfyRec.width/2;
    scarfyPos.y = windowHeight - scarfyRec.height;

    //animation frame
    int frame{};
    //amount of time before we update animation frame
    const float updateTime{1.0 / 12.0};
    float runningTime{};

    //is the rectangle in the air?
    bool isInAir{};

    //jump velocity (pixels/second)
    const int jumpVal{-600};

    int velocity{0};

    
    SetTargetFPS(60);

    while(!WindowShouldClose()){

        //delta time (time since last frame)
        const float dT{GetFrameTime()};

        //Start drawing
        BeginDrawing();
        ClearBackground(WHITE);

        //perform ground check
        if(scarfyPos.y >= windowHeight - scarfyRec.height){
            //rectangle is on the ground
            velocity = 0;
            isInAir = false;
        }else{
            //rectangle is in the air
            velocity += gravity * dT;
            isInAir = true;
        }

        //jump check
         if(IsKeyPressed(KEY_SPACE) && !isInAir){
            velocity += jumpVal;
        }
        
        //update nebula position
        nebPos.x += nebVel * dT;

        //update scarfy position
        scarfyPos.y += velocity * dT;

        //update scarfy animation frame
        if(!isInAir)
        {
            //update running time
            runningTime += dT;
            if(runningTime >= updateTime)
            {
                runningTime = 0.0;
                //update animation frame
                scarfyRec.x = frame * scarfyRec.width;
                frame++;
                if(frame > 5)
                {
                    frame = 0;
                }
            }
        }

        //update nebula running time
        nebRunningTime += dT;
        if(nebRunningTime >= nebUpdateTime)
        {
            nebRunningTime = 0.0;
            //update nebula animation frame
            nebRec.x = nebFrame * nebRec.width;
            nebFrame++;
            if(nebFrame > 7)
            {
                nebFrame = 0;
            }
        }

        //draw nebula
        DrawTextureRec(nebula, nebRec, nebPos, WHITE);

        //draw scarfy
        DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);


        //End drawing
        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
}