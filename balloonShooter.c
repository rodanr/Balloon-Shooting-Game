#include <raylib.h>
int main(void){
const int screenWidth = 1280;
const int screenHeight = 720;
int score = 0,colorChooser=1,missedBalloons=0,missedTimeCounter=0,recordedTimeBlast=0,resetTime=0,gameRunFlag = 1;
float ballSize = 50.0;
InitWindow(screenWidth,screenHeight,"Balloon Shooting Game By Rodan Ramdam");
InitAudioDevice();
Music music = LoadMusicStream("gameover.ogg");
Sound blastSound = LoadSound("blast.wav");//Loading Balloon Blast Sound
Image icon = LoadImage("icon.png");
SetWindowIcon(icon);
Vector2 ballPosition = { (float)screenWidth/2, (float)screenHeight/2 };
SetTargetFPS(30);
while(!WindowShouldClose()){
    Vector2 cursorPosition ={(float)GetMouseX(),(float)GetMouseY()};
      if(CheckCollisionCircles(cursorPosition,5.0,ballPosition,ballSize)&&IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            PlaySound(blastSound);
            score= score + 1;
            ballPosition.x = GetRandomValue(50,1230)%1200;
            ballPosition.y = GetRandomValue(50,1000)%680;
            colorChooser = GetRandomValue(1,7);
            missedTimeCounter=0;
            recordedTimeBlast = (int)GetTime();
         
      }
      missedTimeCounter = (int)GetTime() - recordedTimeBlast;
      if(missedTimeCounter>2){
          missedBalloons = missedBalloons + 1;
          missedTimeCounter = 0;
          ballPosition.x = GetRandomValue(100,1000)%1000;
          ballPosition.y = GetRandomValue(100,1000)%670;
          colorChooser = GetRandomValue(1,7);
          recordedTimeBlast = (int)GetTime();
      }
       if(IsKeyPressed(KEY_F)){
          ToggleFullscreen();
        }
    BeginDrawing();
    if (gameRunFlag ==  1){
     ClearBackground(RAYWHITE);
        DrawText("  Welcome to the Balloon Shooting Game ",(screenWidth/2)-200,10,20,RED);
        DrawLine((screenWidth/2)-200,30,(screenWidth/2)+240,30,RED);
        DrawText(FormatText("TIME :%d SECONDS",(int)GetTime()-resetTime),1000,10,20,BLACK); 
        DrawText(FormatText("SCORE :%d ",score),1000,30,20,BLACK);  
        DrawText(FormatText("MISSED :%d ",missedBalloons),1000,50,20,BLACK);  
        DrawLine(ballPosition.x,ballPosition.y+(ballSize/2),ballPosition.x,ballPosition.y+(ballSize/2)+80,BLACK);
switch(colorChooser){      
      case 1:
      DrawCircleV(ballPosition, ballSize, MAROON);
      break;
      case 2:
      DrawCircleV(ballPosition, ballSize, RED);
      break;
      case 3:
      DrawCircleV(ballPosition, ballSize, YELLOW);
      break;
      case 4:
      DrawCircleV(ballPosition, ballSize, GREEN);
      break;
      case 5:
      DrawCircleV(ballPosition, ballSize, BLUE);
      break;
      case 6:
      DrawCircleV(ballPosition, ballSize, PURPLE);
      break;
      case 7:
      DrawCircleV(ballPosition, ballSize, ORANGE);
      break;
      
    }}
if(missedBalloons>=5){
     ClearBackground(BLACK);
     DrawText("GAME OVER",(screenWidth/2)-300,100,100,RED);
     DrawText("Press 'R' TO RETRY",(screenWidth/2)-400,190,80,RED);
     UpdateMusicStream(music);
     PlayMusicStream(music);
     gameRunFlag = 0;
         if(IsKeyPressed(KEY_R)){
            StopMusicStream(music);
            missedBalloons = 0;
            missedTimeCounter =0;
            score =0;
            resetTime = (int)GetTime();
            gameRunFlag = 1;
         }
}
    EndDrawing();   
}
UnloadMusicStream(music);
UnloadSound(blastSound);
CloseAudioDevice();
CloseWindow();
return 0;
}